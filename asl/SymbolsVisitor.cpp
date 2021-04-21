#include "SymbolsVisitor.h"

#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/SemErrors.h"

#include <iostream>
#include <string>
#include <vector>

#include <cstddef>    // std::size_t

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"
using namespace std;


// Constructor
SymbolsVisitor::SymbolsVisitor(TypesMgr       & Types,
			       SymTable       & Symbols,
			       TreeDecoration & Decorations,
			       SemErrors      & Errors) :
  Types{Types},
  Symbols{Symbols},
  Decorations{Decorations},
  Errors{Errors} {
}


// Methods to visit each kind of node:
//
antlrcpp::Any SymbolsVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = Symbols.pushNewScope("$global$");
  putScopeDecor(ctx, sc);
  for (auto ctxFunc : ctx->function()) { 
    visit(ctxFunc);
  }
  // Symbols.print();
  Symbols.popScope();
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  string funcName = ctx->ID()->getText();
  SymTable::ScopeId sc = Symbols.pushNewScope(funcName);
  putScopeDecor(ctx, sc);
  visit(ctx->function_params());
  visit(ctx->declarations());
  // Symbols.print();
  Symbols.popScope();
  string ident = ctx->ID()->getText();
  if (Symbols.findInCurrentScope(ident)) {
    Errors.declaredIdent(ctx->ID());
  }else {
    vector<TypesMgr::TypeId> paramTy;
    for (unsigned int i = 0; i < ctx->function_params()->type().size(); i++){
      TypesMgr::TypeId t = getTypeDecor(ctx->function_params()->type(i));
      paramTy.push_back(t);
    }
    TypesMgr::TypeId t_ret;
    if (ctx->basic_type()) {  
      visit(ctx->basic_type());
      t_ret = getTypeDecor(ctx->basic_type());
    }else {
      t_ret = Types.createVoidTy();
    }
    
    TypesMgr::TypeId t_func = Types.createFunctionTy(paramTy, t_ret);
    Symbols.addFunction(ident, t_func);
  }
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitFunction_params(AslParser::Function_paramsContext *ctx) {
  DEBUG_ENTER();
  
  for(unsigned int i = 0; i < ctx->ID().size(); i++){
    visit(ctx->type(i));
    
    string ident = ctx->ID(i)->getText();
    
    if (Symbols.findInCurrentScope(ident)) {
      Errors.declaredIdent(ctx->ID(i));
    }else{
      TypesMgr::TypeId t = getTypeDecor(ctx->type(i));
      Symbols.addParameter(ident, t);
    }
  }
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
  DEBUG_ENTER();
  visitChildren(ctx);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->type());
  
  for(auto const& id : ctx->ID()){
    string ident = id->getText();
    if (Symbols.findInCurrentScope(ident)) {
      Errors.declaredIdent(id);
    }else {
      TypesMgr::TypeId t = getTypeDecor(ctx->type());
      Symbols.addLocalVar(ident, t);
    }
  }
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitType(AslParser::TypeContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId t;
  if (ctx->basic_type()) {
    visit(ctx->basic_type());
    t = getTypeDecor(ctx->basic_type());
  }else {
    visit(ctx->array_type());
    t = getTypeDecor(ctx->array_type());
  }
  putTypeDecor(ctx, t);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitBasic_type(AslParser::Basic_typeContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId t = Types.createErrorTy();
  if(ctx->INT()){
    t = Types.createIntegerTy();
  }else if(ctx->FLOAT()){
    t = Types.createFloatTy();
  }else if(ctx->BOOL()){
    t = Types.createBooleanTy();
  }else if(ctx->CHAR()){
    t = Types.createCharacterTy();
  }
  putTypeDecor(ctx, t);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitArray_type(AslParser::Array_typeContext *ctx) { 
  DEBUG_ENTER();
  int size = stoi(ctx->INTVAL()->getText());
  visit(ctx->basic_type());
  TypesMgr::TypeId eleType = getTypeDecor(ctx->basic_type());
  TypesMgr::TypeId t = Types.createArrayTy(size,eleType);
  putTypeDecor(ctx, t);
  DEBUG_EXIT();
  return 0;
}


// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId SymbolsVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId SymbolsVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getType(ctx);
}

// Setters for the necessary tree node attributes:
//   Scope and Type
void SymbolsVisitor::putScopeDecor(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s) {
  Decorations.putScope(ctx, s);
}
void SymbolsVisitor::putTypeDecor(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t) {
  Decorations.putType(ctx, t);
}
