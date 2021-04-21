#include "TypeCheckVisitor.h"

#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/SemErrors.h"

#include <iostream>
#include <string>

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"

using namespace std;


// Constructor
TypeCheckVisitor::TypeCheckVisitor(TypesMgr       & Types,
				   SymTable       & Symbols,
				   TreeDecoration & Decorations,
				   SemErrors      & Errors) :
  Types{Types},
  Symbols {Symbols},
  Decorations{Decorations},
  Errors{Errors} {
}

// Methods to visit each kind of node:
//
antlrcpp::Any TypeCheckVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);  
  for (auto ctxFunc : ctx->function()) { 
    visit(ctxFunc);
  }
  if (Symbols.noMainProperlyDeclared())
    Errors.noMainProperlyDeclared(ctx);
  Symbols.popScope();
  Errors.print();
  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId t = Types.createVoidTy();
  vector<TypesMgr::TypeId> paramTy;
  if(ctx->basic_type()){
    t = getTypeDecor(ctx->basic_type());
  }
  TypesMgr::TypeId t_func = Types.createFunctionTy(paramTy, t);
  Symbols.setCurrentFunctionTy(t_func);
  
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  // Symbols.print();
  visit(ctx->statements());
  Symbols.popScope();
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitStatements(AslParser::StatementsContext *ctx) {
  DEBUG_ENTER();
  visitChildren(ctx);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->left_expr());
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isErrorTy(t2)) and
      (not Types.copyableTypes(t1, t2)))
    Errors.incompatibleAssignment(ctx->ASSIGN());
  if ((not Types.isErrorTy(t1)) and (not getIsLValueDecor(ctx->left_expr())))
    Errors.nonReferenceableLeftExpr(ctx->left_expr());
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
    Errors.booleanRequired(ctx);
  visit(ctx->statements(0));
  if(ctx->ELSE()) {
    visit(ctx->statements(1));
  }
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t)) and (not Types.isBooleanTy(t))){
    Errors.booleanRequired(ctx);
  }
  visit(ctx->statements());
  DEBUG_EXIT();
  return 0;
}

//probably correct but maybe not
antlrcpp::Any TypeCheckVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->ident());
  TypesMgr::TypeId t_id = getTypeDecor(ctx->ident());
  
  //not callable
  if (not Types.isFunctionTy(t_id) and not Types.isErrorTy(t_id)) {
    Errors.isNotCallable(ctx->ident());
  }else if (not Types.isErrorTy(t_id)){
    for(unsigned int i = 0; i < ctx->expr().size(); i++){
      visit(ctx->expr(i));
    }
    //same as function_call
    if (Types.getNumOfParameters(t_id) != (ctx->expr()).size() ){
      Errors.numberOfParameters(ctx->ident());
    }else {
      for (unsigned int i = 0; i < ctx->expr().size(); i++) {
        visit(ctx->expr(i));
        TypesMgr::TypeId t_par = getTypeDecor(ctx->expr(i));
        TypesMgr::TypeId t_par_2 = Types.getParameterType(t_id, i);
        if (not Types.equalTypes(t_par, t_par_2)) {
          if (not (Types.isIntegerTy(t_par) and Types.isFloatTy(t_par_2))){
            Errors.incompatibleParameter(ctx->expr(i), i+1, ctx);
          }
        }
      }
    }
  }
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->left_expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isPrimitiveTy(t1)) and
      (not Types.isFunctionTy(t1)))
    Errors.readWriteRequireBasic(ctx);
  if ((not Types.isErrorTy(t1)) and (not getIsLValueDecor(ctx->left_expr())))
    Errors.nonReferenceableExpression(ctx);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isPrimitiveTy(t1)))
    Errors.readWriteRequireBasic(ctx);
  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitReturnStmt(AslParser::ReturnStmtContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId t_func = Symbols.getCurrentFunctionTy();
  
  if (ctx->expr()) {
    visit(ctx->expr());
    TypesMgr::TypeId t = getTypeDecor(ctx->expr());
    TypesMgr::TypeId t_ret = Types.getFuncReturnType(t_func);
    
    //void function trying to return something
    if (Types.isErrorTy(t) and (not Types.isVoidFunction(t_func))) {
      Errors.incompatibleReturn(ctx->RETURN());
    }
    //function trying to return something wrong
    else if ((not Types.isErrorTy(t)) and (not Types.equalTypes(t, t_ret))){
      if (not (Types.isIntegerTy(t) and Types.isFloatTy(t_ret))) {
        Errors.incompatibleReturn(ctx->RETURN());
      }      
    }
  }
  else if (not Types.isVoidFunction(t_func)) {
    Errors.incompatibleReturn(ctx->RETURN());
  }
  
  DEBUG_EXIT();
  
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitParenthesis(AslParser::ParenthesisContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t = getTypeDecor(ctx->expr());
  putTypeDecor(ctx, t);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->ident());
  TypesMgr::TypeId t_id = getTypeDecor(ctx->ident());
  bool isL = getIsLValueDecor(ctx->ident());
  
  if (ctx->expr()) {  //if it's an array
    visit(ctx->expr());
    TypesMgr::TypeId t_index = getTypeDecor(ctx->expr());
    bool checkArr = true;
    //not type array
    if ((not Types.isErrorTy(t_id)) and (not Types.isArrayTy(t_id))){
      checkArr = false;
      isL = false;
      Errors.nonArrayInArrayAccess(ctx->ident());
      t_id = Types.createErrorTy();
    }
    //non integer index
    if ((not Types.isErrorTy(t_index)) and (not Types.isIntegerTy(t_index))){  
      checkArr = false;
      Errors.nonIntegerIndexInArrayAccess(ctx->expr());
    }
    if ((not Types.isErrorTy(t_id)) and checkArr) {
      t_id = Types.getArrayElemType(t_id);
    }
  }
  
  putTypeDecor(ctx, t_id);
  putIsLValueDecor(ctx, isL);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitArray_access(AslParser::Array_accessContext *ctx) {
  DEBUG_ENTER();
  
  visit(ctx->ident());
  TypesMgr::TypeId t_id = getTypeDecor(ctx->ident());
  visit(ctx->expr());
  TypesMgr::TypeId t_index = getTypeDecor(ctx->expr());
  bool checkArr = true;
  
  //identifier non array type
  if ((not Types.isErrorTy(t_id)) and (not Types.isArrayTy(t_id))){  
    checkArr = false;
    Errors.nonArrayInArrayAccess(ctx);
    t_id = Types.createErrorTy();    
  }
  //non integer index
  if ((not Types.isErrorTy(t_index)) and (not Types.isIntegerTy(t_index))){
    checkArr = false;
    Errors.nonIntegerIndexInArrayAccess(ctx->expr());
    t_id = Types.createErrorTy();
  }
  if ((not Types.isErrorTy(t_id)) and checkArr) {
    t_id = Types.getArrayElemType(t_id);
  }
  
  putTypeDecor(ctx, t_id);
  putIsLValueDecor(ctx, true);
  
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitFunction_call(AslParser::Function_callContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->ident());

  TypesMgr::TypeId t_id = getTypeDecor(ctx->ident());
  TypesMgr::TypeId t = Types.createErrorTy();
  
  //not a function
  if (not Types.isFunctionTy(t_id) and not Types.isErrorTy(t_id)) {
    Errors.isNotCallable(ctx->ident());
  }else { //is a function
    t = Types.getFuncReturnType(t_id);
    //can't be void returning
    if (Types.isVoidFunction(t_id)){
      Errors.isNotFunction(ctx->ident());
      t = Types.createErrorTy();
    }
    //wrong number of params
    if (Types.getNumOfParameters(t_id) != (ctx->expr()).size() ){
      Errors.numberOfParameters(ctx->ident());
    }
    else {
      vector<TypesMgr::TypeId> paramTy = Types.getFuncParamsTypes(t_id);
      for (size_t i = 0; i < paramTy.size(); ++i) {
        visit(ctx->expr(i));
        TypesMgr::TypeId t_par = getTypeDecor(ctx->expr(i));
        TypesMgr::TypeId t_par_2 = Types.getParameterType(t_id,i);
        //compare each pair of params
        if (not Types.equalTypes(t_par, t_par_2)) {
          if (not (Types.isIntegerTy(t_par) and Types.isFloatTy(t_par_2)))
            Errors.incompatibleParameter(ctx->expr(i), i+1, ctx);
        }
      }
    }
  }
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);
  
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitUnary(AslParser::UnaryContext *ctx) {
  visit(ctx->expr());
  TypesMgr::TypeId t = getTypeDecor(ctx->expr());
  
  if (ctx->NOT()) {
    if ((not Types.isErrorTy(t)) and (not Types.isBooleanTy(t)){
      Errors.incompatibleOperator(ctx->op);
    }
    t = Types.createBooleanTy();
  }else {
    if ((not Types.isErrorTy(t)) and (not Types.isNumericTy(t)){
      Errors.incompatibleOperator(ctx->op);
    }
  }
  
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);
  
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  
  TypesMgr::TypeId t = Types.createIntegerTy();
  
  if (ctx->MOD()) {
    if (((not Types.isErrorTy(t1)) and (not Types.isIntegerTy(t1))) or 
          ((not Types.isErrorTy(t2)) and (not Types.isIntegerTy(t2))))
      Errors.incompatibleOperator(ctx->op);
  }else {
    if (((not Types.isErrorTy(t1)) and (not Types.isNumericTy(t1))) or 
          ((not Types.isErrorTy(t2)) and (not Types.isNumericTy(t2))))
      Errors.incompatibleOperator(ctx->op);
    if (((not Types.isErrorTy(t1)) and (not Types.isErrorTy(t2))) and 
          (Types.isFloatTy(t1) or Types.isFloatTy(t2)))
      t = Types.createFloatTy();
  }
  
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitRelational(AslParser::RelationalContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr(0));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));

  string op = ctx->op->getText();
  if ((not Types.isErrorTy(t1)) and (not Types.isErrorTy(t2)) and
      (not Types.comparableTypes(t1, t2, op)))
    Errors.incompatibleOperator(ctx->op);

  putTypeDecor(ctx, Types.createBooleanTy());
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitLogical(AslParser::LogicalContext *ctx) {	
  DEBUG_ENTER();
  visit(ctx->expr(0));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  if (((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1))) or
        ((not Types.isErrorTy(t2)) and (not Types.isBooleanTy(t2))))
    Errors.incompatibleOperator(ctx->op);
  TypesMgr::TypeId t = Types.createBooleanTy();
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitValue(AslParser::ValueContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId t;
  if (ctx->INTVAL()) {
    t = Types.createIntegerTy();
  }else if (ctx->FLOATVAL()) {
    t = Types.createFloatTy();
  }else if (ctx->BOOLVAL()) {
    t = Types.createBooleanTy();
  }else if (ctx->CHARVAL()) {
    t = Types.createCharacterTy();
  }
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->ident());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());
  putTypeDecor(ctx, t1);
  bool b = getIsLValueDecor(ctx->ident());
  putIsLValueDecor(ctx, b);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitIdent(AslParser::IdentContext *ctx) {
  DEBUG_ENTER();
  string ident = ctx->getText();
  if (Symbols.findInStack(ident) == -1) {
    Errors.undeclaredIdent(ctx->ID());
    TypesMgr::TypeId te = Types.createErrorTy();
    putTypeDecor(ctx, te);
    putIsLValueDecor(ctx, true);
  }
  else {
    TypesMgr::TypeId t1 = Symbols.getType(ident);
    putTypeDecor(ctx, t1);
    if (Symbols.isFunctionClass(ident))
      putIsLValueDecor(ctx, false);
    else
      putIsLValueDecor(ctx, true);
  }
  DEBUG_EXIT();
  return 0;
}


// Getters for the necessary tree node atributes:
//   Scope, Type ans IsLValue
SymTable::ScopeId TypeCheckVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId TypeCheckVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getType(ctx);
}
bool TypeCheckVisitor::getIsLValueDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getIsLValue(ctx);
}

// Setters for the necessary tree node attributes:
//   Scope, Type ans IsLValue
void TypeCheckVisitor::putScopeDecor(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s) {
  Decorations.putScope(ctx, s);
}
void TypeCheckVisitor::putTypeDecor(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t) {
  Decorations.putType(ctx, t);
}
void TypeCheckVisitor::putIsLValueDecor(antlr4::ParserRuleContext *ctx, bool b) {
  Decorations.putIsLValue(ctx, b);
}
