//////////////////////////////////////////////////////////////////////
//
//    CodeGenVisitor - Walk the parser tree to do
//                     the generation of code
//
//    Copyright (C) 2019  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#include "CodeGenVisitor.h"

#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/code.h"

#include <string>
#include <cstddef>    // std::size_t

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;


// Constructor
CodeGenVisitor::CodeGenVisitor(TypesMgr       & Types,
                               SymTable       & Symbols,
                               TreeDecoration & Decorations) :
  Types{Types},
  Symbols{Symbols},
  Decorations{Decorations} {
  }

// Methods to visit each kind of node:
//
antlrcpp::Any CodeGenVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  code my_code;
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  for (auto ctxFunc : ctx->function()) { 
    subroutine subr = visit(ctxFunc);
    my_code.add_subroutine(subr);
  }
  Symbols.popScope();
  DEBUG_EXIT();
  return my_code;
}

antlrcpp::Any CodeGenVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  subroutine subr(ctx->ID()->getText());
  codeCounters.reset();
  
  
  if(ctx->basic_type()){
    subr.add_param("Ret");
  }
  
  std::vector<std::string> && params = visit(ctx->function_params());
  for(auto & p : params){
    subr.add_param(p);
  }
  
  
  std::vector<var> && lvars = visit(ctx->declarations());
  for (auto & onevar : lvars) {
    subr.add_var(onevar);
  }
  instructionList && code = visit(ctx->statements());
  code = code || instruction(instruction::RETURN());
  subr.set_instructions(code);
  Symbols.popScope();
  DEBUG_EXIT();
  return subr;
}

antlrcpp::Any CodeGenVisitor::visitFunction_call(AslParser::Function_callContext *ctx) {
  DEBUG_ENTER();
  instructionList code = instructionList(instruction::PUSH());
  std::string functionName = ctx->ident()->ID()->getText();
  TypesMgr::TypeId functionType = getTypeDecor(ctx->ident());
  std::vector<TypesMgr::TypeId> paramTypes = Types.getFuncParamsTypes(functionType);
  
  for(uint i = 0; i < ctx->expr().size(); i++){
    CodeAttribs && codAts      = visit(ctx->expr(i));
    std::string addr          = codAts.addr;
    instructionList & codeI   = codAts.code;
    
    code = code || codeI;
    TypesMgr::TypeId paramT = getTypeDecor(ctx->expr(i));
    
    
    if(Types.isArrayTy(paramT)) {
      std::string arrayAddrTemp = "%"+codeCounters.newTEMP();
      code = code || instruction::ALOAD(arrayAddrTemp, addr);
      code = code || instruction::PUSH(arrayAddrTemp);
    }else if(Types.isFloatTy(paramTypes[i]) and Types.isIntegerTy(paramT)){
      std::string floatTemp = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(floatTemp, addr) || instruction::PUSH(floatTemp);
    }else{
      code = code || instruction::PUSH(addr);
    }
  }
  code = code || instruction::CALL(functionName);
  
  for(uint i = 0; i < ctx->expr().size(); i++){ 
    code = code || instruction::POP();
  }
  
  std::string temp = "%"+codeCounters.newTEMP();
  code = code || instruction::POP(temp);
  
  CodeAttribs atts(temp, "", code);
  
  DEBUG_EXIT();
  return atts;
}

antlrcpp::Any CodeGenVisitor::visitReturnStmt(AslParser::ReturnStmtContext *ctx) {
  instructionList code;   
  if(ctx->expr()){
    CodeAttribs && codAts = visit(ctx->expr());
    std::string addr = codAts.addr;
    instructionList & codeR = codAts.code;
    code = codeR || instruction::LOAD("Ret",addr) || instruction::RETURN();
  }
  return code;
}

antlrcpp::Any CodeGenVisitor::visitFunction_params(AslParser::Function_paramsContext *ctx) {
  DEBUG_ENTER();
  std::vector<std::string> params;
  for (auto & p : ctx->ID()){
    params.push_back(p->getText());
  }
  DEBUG_EXIT();
  return params;
}

antlrcpp::Any CodeGenVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
  DEBUG_ENTER();
  std::vector<var> lvars;
  for (auto & varDeclCtx : ctx->variable_decl()) {
    std::vector<var> vars = visit(varDeclCtx);
    for(auto v : vars){
      lvars.push_back(v);
    }
  }
  DEBUG_EXIT();
  return lvars;
}

antlrcpp::Any CodeGenVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId   t1 = getTypeDecor(ctx->type());
  std::size_t      size = Types.getSizeOfType(t1);
  std::vector<var> vars;
  for(uint i = 0; i < ctx->ID().size(); i++){
    vars.push_back(var{ctx->ID(i)->getText(), size});
  }
  
  DEBUG_EXIT();
  return vars;
}

antlrcpp::Any CodeGenVisitor::visitStatements(AslParser::StatementsContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  for (auto stCtx : ctx->statement()) {
    instructionList && codeS = visit(stCtx);
    code = code || codeS;
  }
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE1 = visit(ctx->left_expr());
  std::string           addr1 = codAtsE1.addr;
  std::string           offs1 = codAtsE1.offs;
  instructionList &     code1 = codAtsE1.code;
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->left_expr());
  
  CodeAttribs     && codAtsE2 = visit(ctx->expr());
  std::string           addr2 = codAtsE2.addr;
  // std::string           offs2 = codAtsE2.offs;
  instructionList &     code2 = codAtsE2.code;
  TypesMgr::TypeId tid2 = getTypeDecor(ctx->expr());
  
  std::string addrL = addr1;
  std::string addrR = addr2;
  
  if (Types.isArrayTy(tid1) and Symbols.isParameterClass(addr1)) {
    addrL = "%"+codeCounters.newTEMP();
    code = instruction::LOAD(addrL, addr1);
  }
  if (Types.isArrayTy(tid2) and Symbols.isParameterClass(addr2)) {
    addrR = "%"+codeCounters.newTEMP();
    code = instruction::LOAD(addrR, addr2);
  }
  
  if (Types.isArrayTy(tid1) and offs1.empty()) {
    int arraySize = Types.getArraySize(tid1);
    std::string offsetTemp = "%"+codeCounters.newTEMP();
    std::string arrayAccessTemp = "%"+codeCounters.newTEMP();
    
    for (int i = 0; i < arraySize; i++){
      code = code || instruction::ILOAD(offsetTemp, std::to_string(i)) || instruction::LOADX(arrayAccessTemp, addrR, offsetTemp) || instruction::XLOAD(addrL, offsetTemp, arrayAccessTemp);
    }
  }
  
  bool fl = false;
  std::string temp = "%"+codeCounters.newTEMP();
  
  if(Types.isFloatTy(tid1) and Types.isIntegerTy(tid2)){
    code = code || instruction::FLOAT(temp, addrR);
    fl = true;
  }
  
  if(ctx->left_expr()->expr()){
    code = code || instruction::XLOAD(addrL, offs1, addrR);
  }else{ 
    code = code || instruction::LOAD(addrL, (fl ? temp : addrR));
  }
  DEBUG_EXIT();
  return code1 || code2 || code;
}

antlrcpp::Any CodeGenVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE = visit(ctx->expr());
  std::string          addr1 = codAtsE.addr;
  instructionList &    code1 = codAtsE.code;
  instructionList &&   code2 = visit(ctx->statements(0));
  
  std::string label = codeCounters.newLabelIF();
  std::string labelEndIf = "endif"+label;
  
  if(ctx->statements(1)){
    instructionList && code3 = visit(ctx->statements(1));
    std::string labelElse = "else"+label;
    
    code =   code1 || instruction::FJUMP(addr1, labelElse) ||
      code2 || instruction::LABEL(labelElse) || code3 || instruction::LABEL(labelEndIf);
  }else{
    code =   code1 || instruction::FJUMP(addr1, labelEndIf) || 
      code2 || instruction::LABEL(labelEndIf);
  }
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE = visit(ctx->expr());
  std::string          addr1 = codAtsE.addr;
  instructionList &    code1 = codAtsE.code;
  instructionList &&   code2 = visit(ctx->statements());
  std::string label = "while"+codeCounters.newLabelWHILE();
  std::string labelEndWhile = "end"+label;
  code = instruction::LABEL(label) || code1 || instruction::FJUMP(addr1, labelEndWhile) ||
    code2 || instruction::UJUMP(label) || instruction::LABEL(labelEndWhile);
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string name = ctx->ident()->getText();
  TypesMgr::TypeId procType = getTypeDecor(ctx->ident());
  std::vector<TypesMgr::TypeId> paramTypes = Types.getFuncParamsTypes(procType);
  
  for(uint i = 0; i < ctx->expr().size(); i++){
    CodeAttribs && codAts      = visit(ctx->expr(i));
    std::string addr          = codAts.addr;
    instructionList & codeI   = codAts.code;
    
    code = code || codeI;
    TypesMgr::TypeId paramT = getTypeDecor(ctx->expr(i));
    
    if(Types.isArrayTy(paramT)) {
      std::string arrayAddrTemp = "%"+codeCounters.newTEMP();
      code = code   || instruction::ALOAD(arrayAddrTemp, addr)
                    || instruction::PUSH(arrayAddrTemp);
    }else if(Types.isFloatTy(paramTypes[i]) and Types.isIntegerTy(paramT)){
      std::string floatTemp = "%"+codeCounters.newTEMP();
      code = code   || instruction::FLOAT(floatTemp, addr) 
                    || instruction::PUSH(floatTemp);
    }else{
      code = code   || instruction::PUSH(addr);
    }
  }
  
  if(not Types.isVoidTy(procType)){
    code = code || instruction::PUSH();
  }
  
  code = code || instruction::CALL(name);
  
  for(uint i = 0; i < ctx->expr().size(); i++){ 
    code = code || instruction::POP();
  }
  
  if(not Types.isVoidTy(procType)){
    code = code || instruction::POP();
  }
  
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtsE = visit(ctx->left_expr());
  std::string          addr1 = codAtsE.addr;
  std::string          offs1 = codAtsE.offs;
  instructionList &    code1 = codAtsE.code;
  instructionList &     code = code1;
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->left_expr());
  
  std::string temp = ctx->left_expr()->expr() ? "%"+codeCounters.newTEMP()
    : addr1;
  
  if(Types.isIntegerTy(tid1) or Types.isBooleanTy(tid1)){
    code = code1 || instruction::READI(temp);
  }else if(Types.isFloatTy(tid1)){
    code = code1 || instruction::READF(temp);
  }else{
    code = code1 || instruction::READC(temp);
  }
  if(ctx->left_expr()->expr()){
    code = code || instruction::XLOAD(addr1, offs1, temp);
  }
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr());
  std::string         addr1 = codAt1.addr;
  // std::string         offs1 = codAt1.offs;
  instructionList &   code1 = codAt1.code;
  instructionList &    code = code1;
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->expr());
  if(Types.isCharacterTy(tid1)){
    code = code1 || instruction::WRITEC(addr1);
  }else if(Types.isFloatTy(tid1)){
    code = code1 || instruction::WRITEF(addr1);
  }else{
    code = code1 || instruction::WRITEI(addr1);
  }
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string s = ctx->STRING()->getText();
  std::string temp = "%"+codeCounters.newTEMP();
  int i = 1;
  while (i < int(s.size())-1) {
    if (s[i] != '\\') {
      code = code ||
        instruction::CHLOAD(temp, s.substr(i,1)) ||
        instruction::WRITEC(temp);
      i += 1;
    }
    else {
      assert(i < int(s.size())-2);
      if (s[i+1] == 'n') {
        code = code || instruction::WRITELN();
        i += 2;
      }
      else if (s[i+1] == 't' or s[i+1] == '"' or s[i+1] == '\\') {
        code = code ||
          instruction::CHLOAD(temp, s.substr(i,2)) ||
          instruction::WRITEC(temp);
        i += 2;
      }
      else {
        code = code ||
          instruction::CHLOAD(temp, s.substr(i,1)) ||
          instruction::WRITEC(temp);
        i += 1;
      }
    }
  }
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = visit(ctx->ident());
  instructionList & code = codAts.code;
  std::string addr = codAts.addr;
  std::string offs = "";
  
  if(ctx->expr()){
    CodeAttribs && codExpr = visit(ctx->expr());
    code = code || codExpr.code;
    offs = codExpr.addr; 
    if(Symbols.isParameterClass(addr)){
      std::string temp = "%"+codeCounters.newTEMP();
      code = code || instruction::LOAD(temp, addr);
      addr = temp;
    }
  }
  
  CodeAttribs atts(addr, offs, code);
  
  DEBUG_EXIT();
  return atts;
}

antlrcpp::Any CodeGenVisitor::visitArray_access(AslParser::Array_accessContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAtI = visit(ctx->ident());
  std::string addr = codAtI.addr;
  instructionList & code = codAtI.code;
  CodeAttribs && codAtsE = visit(ctx->expr());
  instructionList & codeExpr = codAtsE.code;
  std::string addrE = codAtsE.addr;
  
  std::string temp = "%"+codeCounters.newTEMP();
  if(Symbols.isParameterClass(addr)){
    std::string refTemp = "%"+codeCounters.newTEMP();
    code =    code || codeExpr || instruction::LOAD(refTemp, addr) || 
      instruction::LOADX(temp, refTemp, addrE);      
  }else{
    code = code || codeExpr || instruction::LOADX(temp, addr, addrE);
  }
  
  CodeAttribs codAts(temp, "", code);
  
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr(0));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = visit(ctx->expr(1));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  TypesMgr::TypeId  t = getTypeDecor(ctx);
  std::string temp = "%"+codeCounters.newTEMP();
  if(Types.isIntegerTy(t)){
    if (ctx->MUL())
      code = code || instruction::MUL(temp, addr1, addr2);
    else if (ctx->DIV())
      code = code || instruction::DIV(temp, addr1, addr2);
    else if (ctx->SUB())
      code = code || instruction::SUB(temp, addr1, addr2);
    else if (ctx->PLUS())
      code = code || instruction::ADD(temp, addr1, addr2);
    else{
      code = code   || instruction::DIV(temp, addr1, addr2)
                    || instruction::MUL(temp, temp, addr2)
                    || instruction::SUB(temp, addr1, temp);
    }
  }else{
    std::string addrF1 = addr1;
    std::string addrF2 = addr2;
    if(Types.isIntegerTy(t1) and Types.isFloatTy(t2)){
      addrF1 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(addrF1, addr1);
    }else if(Types.isIntegerTy(t2) and Types.isFloatTy(t1)){
      addrF2 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(addrF2, addr2);
    }
    if (ctx->MUL())
      code = code || instruction::FMUL(temp, addrF1, addrF2);
    else if (ctx->DIV())
      code = code || instruction::FDIV(temp, addrF1, addrF2);
    else if (ctx->SUB())
      code = code || instruction::FSUB(temp, addrF1, addrF2);
    else
      code = code || instruction::FADD(temp, addrF1, addrF2);
  }
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitRelational(AslParser::RelationalContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr(0));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = visit(ctx->expr(1));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  std::string temp = "%"+codeCounters.newTEMP();
  
  if(not Types.isFloatTy(t1) and not Types.isFloatTy(t2)){
    if(ctx->EQUAL()){
      code = code || instruction::EQ(temp, addr1, addr2);
    }else if(ctx->NE()){
      code = code || instruction::EQ(temp, addr1, addr2);
      code = code || instruction::NOT(temp, temp);
    }else if(ctx->LT()){
      code = code || instruction::LT(temp, addr1, addr2);
    }else if(ctx->LTE()){
      code = code || instruction::LE(temp, addr1, addr2);
    }else if(ctx->GT()){
      code = code || instruction::LE(temp, addr1, addr2);
      code = code || instruction::NOT(temp, temp);
    }else if(ctx->GTE()){
      code = code || instruction::LT(temp, addr1, addr2);
      code = code || instruction::NOT(temp, temp);
    }
  }else{
    std::string addrF1 = addr1;
    std::string addrF2 = addr2;
    if(Types.isIntegerTy(t1) and Types.isFloatTy(t2)){
      addrF1 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(addrF1, addr1);
    }else if(Types.isIntegerTy(t2) and Types.isFloatTy(t1)){
      addrF2 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(addrF2, addr2);
    }
    if(ctx->EQUAL()){
      code = code || instruction::FEQ(temp, addrF1, addrF2);
    }else if(ctx->NE()){
      code = code || instruction::FEQ(temp, addrF1, addrF2);
      code = code || instruction::NOT(temp, temp);
    }else if(ctx->LT()){
      code = code || instruction::FLT(temp, addrF1, addrF2);
    }else if(ctx->LTE()){
      code = code || instruction::FLE(temp, addrF1, addrF2);
    }else if(ctx->GT()){
      code = code || instruction::FLE(temp, addrF1, addrF2);
      code = code || instruction::NOT(temp, temp);
    }else if(ctx->GTE()){
      code = code || instruction::FLT(temp, addrF1, addrF2);
      code = code || instruction::NOT(temp, temp);
    }
  }
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitLogical(AslParser::LogicalContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr(0));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = visit(ctx->expr(1));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;
  std::string temp = "%"+codeCounters.newTEMP();
  
  if(ctx->AND()){
    code = code || instruction::AND(temp, addr1, addr2);
  }else{
    code = code || instruction::OR(temp, addr1, addr2);
  }
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitUnary(AslParser::UnaryContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt = visit(ctx->expr());
  std::string         addr = codAt.addr;
  instructionList &   code = codAt.code;
  
  std::string temp = "%"+codeCounters.newTEMP();
  
  if(ctx->NOT()){
    code = code || instruction::NOT(temp, addr);
  }else if(ctx->SUB()){
    if(not Types.isFloatTy(getTypeDecor(ctx->expr()))){
      code = code || instruction::NEG(temp, addr);
    }else{
      code = code || instruction::FNEG(temp,addr);
    }
  }
  
  CodeAttribs codAts(temp, "", code);
  
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitParenthesis(AslParser::ParenthesisContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAts = visit(ctx->expr());
  DEBUG_EXIT();
  return codAts;
}


antlrcpp::Any CodeGenVisitor::visitValue(AslParser::ValueContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string temp = "%"+codeCounters.newTEMP();
  if(ctx->INTVAL()){
    code = instruction::ILOAD(temp, ctx->getText());
  }else if(ctx->FLOATVAL()){
    code = instruction::FLOAD(temp, ctx->getText());
  }else if(ctx->CHARVAL()){
    code = instruction::CHLOAD(temp, ctx->getText().substr(1, ctx->getText().length()-2));
  }else{
    if(ctx->getText() == "true"){
      code = instruction::LOAD(temp, "1");
    }else{
      code = instruction::LOAD(temp, "0");
    }
  }
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = visit(ctx->ident());
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitIdent(AslParser::IdentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs codAts(ctx->ID()->getText(), "", instructionList());
  DEBUG_EXIT();
  return codAts;
}


// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId CodeGenVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) const {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId CodeGenVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) const {
  return Decorations.getType(ctx);
}


// Constructors of the class CodeAttribs:
//
CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string & addr,
                                         const std::string & offs,
                                         instructionList & code) :
  addr{addr}, offs{offs}, code{code} {
  }

CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string & addr,
                                         const std::string & offs,
                                         instructionList && code) :
  addr{addr}, offs{offs}, code{code} {
  }
