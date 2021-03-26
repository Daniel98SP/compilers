
// Generated from Asl.g4 by ANTLR 4.7.1


#include "AslVisitor.h"

#include "AslParser.h"


using namespace antlrcpp;
using namespace antlr4;

AslParser::AslParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

AslParser::~AslParser() {
  delete _interpreter;
}

std::string AslParser::getGrammarFileName() const {
  return "Asl.g4";
}

const std::vector<std::string>& AslParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& AslParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

AslParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AslParser::ProgramContext::EOF() {
  return getToken(AslParser::EOF, 0);
}

std::vector<AslParser::FunctionContext *> AslParser::ProgramContext::function() {
  return getRuleContexts<AslParser::FunctionContext>();
}

AslParser::FunctionContext* AslParser::ProgramContext::function(size_t i) {
  return getRuleContext<AslParser::FunctionContext>(i);
}


size_t AslParser::ProgramContext::getRuleIndex() const {
  return AslParser::RuleProgram;
}

antlrcpp::Any AslParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

AslParser::ProgramContext* AslParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, AslParser::RuleProgram);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(21); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(20);
      function();
      setState(23); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == AslParser::FUNC);
    setState(25);
    match(AslParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

AslParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AslParser::FunctionContext::FUNC() {
  return getToken(AslParser::FUNC, 0);
}

tree::TerminalNode* AslParser::FunctionContext::ID() {
  return getToken(AslParser::ID, 0);
}

AslParser::DeclarationsContext* AslParser::FunctionContext::declarations() {
  return getRuleContext<AslParser::DeclarationsContext>(0);
}

AslParser::StatementsContext* AslParser::FunctionContext::statements() {
  return getRuleContext<AslParser::StatementsContext>(0);
}

tree::TerminalNode* AslParser::FunctionContext::ENDFUNC() {
  return getToken(AslParser::ENDFUNC, 0);
}


size_t AslParser::FunctionContext::getRuleIndex() const {
  return AslParser::RuleFunction;
}

antlrcpp::Any AslParser::FunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitFunction(this);
  else
    return visitor->visitChildren(this);
}

AslParser::FunctionContext* AslParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 2, AslParser::RuleFunction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(27);
    match(AslParser::FUNC);
    setState(28);
    match(AslParser::ID);
    setState(29);
    match(AslParser::LBRAC);
    setState(30);
    match(AslParser::RBRAC);
    setState(31);
    declarations();
    setState(32);
    statements();
    setState(33);
    match(AslParser::ENDFUNC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationsContext ------------------------------------------------------------------

AslParser::DeclarationsContext::DeclarationsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AslParser::Variable_declContext *> AslParser::DeclarationsContext::variable_decl() {
  return getRuleContexts<AslParser::Variable_declContext>();
}

AslParser::Variable_declContext* AslParser::DeclarationsContext::variable_decl(size_t i) {
  return getRuleContext<AslParser::Variable_declContext>(i);
}


size_t AslParser::DeclarationsContext::getRuleIndex() const {
  return AslParser::RuleDeclarations;
}

antlrcpp::Any AslParser::DeclarationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitDeclarations(this);
  else
    return visitor->visitChildren(this);
}

AslParser::DeclarationsContext* AslParser::declarations() {
  DeclarationsContext *_localctx = _tracker.createInstance<DeclarationsContext>(_ctx, getState());
  enterRule(_localctx, 4, AslParser::RuleDeclarations);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(38);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AslParser::VAR) {
      setState(35);
      variable_decl();
      setState(40);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_declContext ------------------------------------------------------------------

AslParser::Variable_declContext::Variable_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AslParser::Variable_declContext::VAR() {
  return getToken(AslParser::VAR, 0);
}

std::vector<tree::TerminalNode *> AslParser::Variable_declContext::ID() {
  return getTokens(AslParser::ID);
}

tree::TerminalNode* AslParser::Variable_declContext::ID(size_t i) {
  return getToken(AslParser::ID, i);
}

AslParser::TypeContext* AslParser::Variable_declContext::type() {
  return getRuleContext<AslParser::TypeContext>(0);
}

std::vector<tree::TerminalNode *> AslParser::Variable_declContext::COMMA() {
  return getTokens(AslParser::COMMA);
}

tree::TerminalNode* AslParser::Variable_declContext::COMMA(size_t i) {
  return getToken(AslParser::COMMA, i);
}


size_t AslParser::Variable_declContext::getRuleIndex() const {
  return AslParser::RuleVariable_decl;
}

antlrcpp::Any AslParser::Variable_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitVariable_decl(this);
  else
    return visitor->visitChildren(this);
}

AslParser::Variable_declContext* AslParser::variable_decl() {
  Variable_declContext *_localctx = _tracker.createInstance<Variable_declContext>(_ctx, getState());
  enterRule(_localctx, 6, AslParser::RuleVariable_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(41);
    match(AslParser::VAR);
    setState(46);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(42);
        match(AslParser::ID);
        setState(43);
        match(AslParser::COMMA); 
      }
      setState(48);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
    setState(49);
    match(AslParser::ID);
    setState(50);
    match(AslParser::T__0);
    setState(51);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

AslParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AslParser::TypeContext::INT() {
  return getToken(AslParser::INT, 0);
}

tree::TerminalNode* AslParser::TypeContext::FLOAT() {
  return getToken(AslParser::FLOAT, 0);
}

tree::TerminalNode* AslParser::TypeContext::BOOL() {
  return getToken(AslParser::BOOL, 0);
}

tree::TerminalNode* AslParser::TypeContext::CHAR() {
  return getToken(AslParser::CHAR, 0);
}


size_t AslParser::TypeContext::getRuleIndex() const {
  return AslParser::RuleType;
}

antlrcpp::Any AslParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

AslParser::TypeContext* AslParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 8, AslParser::RuleType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(53);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << AslParser::INT)
      | (1ULL << AslParser::FLOAT)
      | (1ULL << AslParser::BOOL)
      | (1ULL << AslParser::CHAR))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementsContext ------------------------------------------------------------------

AslParser::StatementsContext::StatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AslParser::StatementContext *> AslParser::StatementsContext::statement() {
  return getRuleContexts<AslParser::StatementContext>();
}

AslParser::StatementContext* AslParser::StatementsContext::statement(size_t i) {
  return getRuleContext<AslParser::StatementContext>(i);
}


size_t AslParser::StatementsContext::getRuleIndex() const {
  return AslParser::RuleStatements;
}

antlrcpp::Any AslParser::StatementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitStatements(this);
  else
    return visitor->visitChildren(this);
}

AslParser::StatementsContext* AslParser::statements() {
  StatementsContext *_localctx = _tracker.createInstance<StatementsContext>(_ctx, getState());
  enterRule(_localctx, 10, AslParser::RuleStatements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << AslParser::IF)
      | (1ULL << AslParser::READ)
      | (1ULL << AslParser::WRITE)
      | (1ULL << AslParser::ID))) != 0)) {
      setState(55);
      statement();
      setState(60);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

AslParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t AslParser::StatementContext::getRuleIndex() const {
  return AslParser::RuleStatement;
}

void AslParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ProcCallContext ------------------------------------------------------------------

AslParser::IdentContext* AslParser::ProcCallContext::ident() {
  return getRuleContext<AslParser::IdentContext>(0);
}

tree::TerminalNode* AslParser::ProcCallContext::LBRAC() {
  return getToken(AslParser::LBRAC, 0);
}

tree::TerminalNode* AslParser::ProcCallContext::RBRAC() {
  return getToken(AslParser::RBRAC, 0);
}

tree::TerminalNode* AslParser::ProcCallContext::SEMI() {
  return getToken(AslParser::SEMI, 0);
}

AslParser::ProcCallContext::ProcCallContext(StatementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::ProcCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitProcCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WriteExprContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::WriteExprContext::WRITE() {
  return getToken(AslParser::WRITE, 0);
}

AslParser::ExprContext* AslParser::WriteExprContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

tree::TerminalNode* AslParser::WriteExprContext::SEMI() {
  return getToken(AslParser::SEMI, 0);
}

AslParser::WriteExprContext::WriteExprContext(StatementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::WriteExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitWriteExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStmtContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::IfStmtContext::IF() {
  return getToken(AslParser::IF, 0);
}

AslParser::ExprContext* AslParser::IfStmtContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

tree::TerminalNode* AslParser::IfStmtContext::THEN() {
  return getToken(AslParser::THEN, 0);
}

AslParser::StatementsContext* AslParser::IfStmtContext::statements() {
  return getRuleContext<AslParser::StatementsContext>(0);
}

tree::TerminalNode* AslParser::IfStmtContext::ENDIF() {
  return getToken(AslParser::ENDIF, 0);
}

AslParser::IfStmtContext::IfStmtContext(StatementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReadStmtContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::ReadStmtContext::READ() {
  return getToken(AslParser::READ, 0);
}

AslParser::Left_exprContext* AslParser::ReadStmtContext::left_expr() {
  return getRuleContext<AslParser::Left_exprContext>(0);
}

tree::TerminalNode* AslParser::ReadStmtContext::SEMI() {
  return getToken(AslParser::SEMI, 0);
}

AslParser::ReadStmtContext::ReadStmtContext(StatementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::ReadStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitReadStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStmtContext ------------------------------------------------------------------

AslParser::Left_exprContext* AslParser::AssignStmtContext::left_expr() {
  return getRuleContext<AslParser::Left_exprContext>(0);
}

tree::TerminalNode* AslParser::AssignStmtContext::ASSIGN() {
  return getToken(AslParser::ASSIGN, 0);
}

AslParser::ExprContext* AslParser::AssignStmtContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

tree::TerminalNode* AslParser::AssignStmtContext::SEMI() {
  return getToken(AslParser::SEMI, 0);
}

AslParser::AssignStmtContext::AssignStmtContext(StatementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::AssignStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitAssignStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WriteStringContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::WriteStringContext::WRITE() {
  return getToken(AslParser::WRITE, 0);
}

tree::TerminalNode* AslParser::WriteStringContext::STRING() {
  return getToken(AslParser::STRING, 0);
}

tree::TerminalNode* AslParser::WriteStringContext::SEMI() {
  return getToken(AslParser::SEMI, 0);
}

AslParser::WriteStringContext::WriteStringContext(StatementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::WriteStringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitWriteString(this);
  else
    return visitor->visitChildren(this);
}
AslParser::StatementContext* AslParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 12, AslParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(88);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<AslParser::AssignStmtContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(61);
      left_expr();
      setState(62);
      match(AslParser::ASSIGN);
      setState(63);
      expr(0);
      setState(64);
      match(AslParser::SEMI);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<AslParser::IfStmtContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(66);
      match(AslParser::IF);
      setState(67);
      expr(0);
      setState(68);
      match(AslParser::THEN);
      setState(69);
      statements();
      setState(70);
      match(AslParser::ENDIF);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<AslParser::ProcCallContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(72);
      ident();
      setState(73);
      match(AslParser::LBRAC);
      setState(74);
      match(AslParser::RBRAC);
      setState(75);
      match(AslParser::SEMI);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<AslParser::ReadStmtContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(77);
      match(AslParser::READ);
      setState(78);
      left_expr();
      setState(79);
      match(AslParser::SEMI);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<AslParser::WriteExprContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(81);
      match(AslParser::WRITE);
      setState(82);
      expr(0);
      setState(83);
      match(AslParser::SEMI);
      break;
    }

    case 6: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<AslParser::WriteStringContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(85);
      match(AslParser::WRITE);
      setState(86);
      match(AslParser::STRING);
      setState(87);
      match(AslParser::SEMI);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Left_exprContext ------------------------------------------------------------------

AslParser::Left_exprContext::Left_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AslParser::IdentContext* AslParser::Left_exprContext::ident() {
  return getRuleContext<AslParser::IdentContext>(0);
}


size_t AslParser::Left_exprContext::getRuleIndex() const {
  return AslParser::RuleLeft_expr;
}

antlrcpp::Any AslParser::Left_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitLeft_expr(this);
  else
    return visitor->visitChildren(this);
}

AslParser::Left_exprContext* AslParser::left_expr() {
  Left_exprContext *_localctx = _tracker.createInstance<Left_exprContext>(_ctx, getState());
  enterRule(_localctx, 14, AslParser::RuleLeft_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    ident();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

AslParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t AslParser::ExprContext::getRuleIndex() const {
  return AslParser::RuleExpr;
}

void AslParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprBracContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::ExprBracContext::LBRAC() {
  return getToken(AslParser::LBRAC, 0);
}

AslParser::ExprContext* AslParser::ExprBracContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

tree::TerminalNode* AslParser::ExprBracContext::RBRAC() {
  return getToken(AslParser::RBRAC, 0);
}

AslParser::ExprBracContext::ExprBracContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::ExprBracContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitExprBrac(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprOrContext ------------------------------------------------------------------

std::vector<AslParser::ExprContext *> AslParser::ExprOrContext::expr() {
  return getRuleContexts<AslParser::ExprContext>();
}

AslParser::ExprContext* AslParser::ExprOrContext::expr(size_t i) {
  return getRuleContext<AslParser::ExprContext>(i);
}

tree::TerminalNode* AslParser::ExprOrContext::OR() {
  return getToken(AslParser::OR, 0);
}

AslParser::ExprOrContext::ExprOrContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::ExprOrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitExprOr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprNotContext ------------------------------------------------------------------

AslParser::ExprContext* AslParser::ExprNotContext::expr() {
  return getRuleContext<AslParser::ExprContext>(0);
}

tree::TerminalNode* AslParser::ExprNotContext::NOT() {
  return getToken(AslParser::NOT, 0);
}

AslParser::ExprNotContext::ExprNotContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::ExprNotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitExprNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprAndContext ------------------------------------------------------------------

std::vector<AslParser::ExprContext *> AslParser::ExprAndContext::expr() {
  return getRuleContexts<AslParser::ExprContext>();
}

AslParser::ExprContext* AslParser::ExprAndContext::expr(size_t i) {
  return getRuleContext<AslParser::ExprContext>(i);
}

tree::TerminalNode* AslParser::ExprAndContext::AND() {
  return getToken(AslParser::AND, 0);
}

AslParser::ExprAndContext::ExprAndContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::ExprAndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitExprAnd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArithmeticContext ------------------------------------------------------------------

std::vector<AslParser::ExprContext *> AslParser::ArithmeticContext::expr() {
  return getRuleContexts<AslParser::ExprContext>();
}

AslParser::ExprContext* AslParser::ArithmeticContext::expr(size_t i) {
  return getRuleContext<AslParser::ExprContext>(i);
}

tree::TerminalNode* AslParser::ArithmeticContext::PLUS() {
  return getToken(AslParser::PLUS, 0);
}

tree::TerminalNode* AslParser::ArithmeticContext::MINUS() {
  return getToken(AslParser::MINUS, 0);
}

tree::TerminalNode* AslParser::ArithmeticContext::MUL() {
  return getToken(AslParser::MUL, 0);
}

tree::TerminalNode* AslParser::ArithmeticContext::DIV() {
  return getToken(AslParser::DIV, 0);
}

AslParser::ArithmeticContext::ArithmeticContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::ArithmeticContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitArithmetic(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprIdentContext ------------------------------------------------------------------

AslParser::IdentContext* AslParser::ExprIdentContext::ident() {
  return getRuleContext<AslParser::IdentContext>(0);
}

AslParser::ExprIdentContext::ExprIdentContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::ExprIdentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitExprIdent(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RelationalContext ------------------------------------------------------------------

std::vector<AslParser::ExprContext *> AslParser::RelationalContext::expr() {
  return getRuleContexts<AslParser::ExprContext>();
}

AslParser::ExprContext* AslParser::RelationalContext::expr(size_t i) {
  return getRuleContext<AslParser::ExprContext>(i);
}

tree::TerminalNode* AslParser::RelationalContext::EQ() {
  return getToken(AslParser::EQ, 0);
}

tree::TerminalNode* AslParser::RelationalContext::NEQ() {
  return getToken(AslParser::NEQ, 0);
}

tree::TerminalNode* AslParser::RelationalContext::LT() {
  return getToken(AslParser::LT, 0);
}

tree::TerminalNode* AslParser::RelationalContext::MT() {
  return getToken(AslParser::MT, 0);
}

tree::TerminalNode* AslParser::RelationalContext::LET() {
  return getToken(AslParser::LET, 0);
}

tree::TerminalNode* AslParser::RelationalContext::MET() {
  return getToken(AslParser::MET, 0);
}

AslParser::RelationalContext::RelationalContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::RelationalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitRelational(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ValueContext ------------------------------------------------------------------

tree::TerminalNode* AslParser::ValueContext::INTVAL() {
  return getToken(AslParser::INTVAL, 0);
}

tree::TerminalNode* AslParser::ValueContext::FLOATVAL() {
  return getToken(AslParser::FLOATVAL, 0);
}

tree::TerminalNode* AslParser::ValueContext::BOOLVAL() {
  return getToken(AslParser::BOOLVAL, 0);
}

tree::TerminalNode* AslParser::ValueContext::CHARVAL() {
  return getToken(AslParser::CHARVAL, 0);
}

AslParser::ValueContext::ValueContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any AslParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

AslParser::ExprContext* AslParser::expr() {
   return expr(0);
}

AslParser::ExprContext* AslParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  AslParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  AslParser::ExprContext *previousContext = _localctx;
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, AslParser::RuleExpr, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(108);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AslParser::LBRAC: {
        _localctx = _tracker.createInstance<ExprBracContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(93);
        match(AslParser::LBRAC);
        setState(94);
        expr(0);
        setState(95);
        match(AslParser::RBRAC);
        break;
      }

      case AslParser::NOT: {
        _localctx = _tracker.createInstance<ExprNotContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(97);
        dynamic_cast<ExprNotContext *>(_localctx)->op = match(AslParser::NOT);
        setState(98);
        expr(20);
        break;
      }

      case AslParser::PLUS: {
        _localctx = _tracker.createInstance<ArithmeticContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(99);
        dynamic_cast<ArithmeticContext *>(_localctx)->op = match(AslParser::PLUS);
        setState(100);
        expr(19);
        break;
      }

      case AslParser::MINUS: {
        _localctx = _tracker.createInstance<ArithmeticContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(101);
        dynamic_cast<ArithmeticContext *>(_localctx)->op = match(AslParser::MINUS);
        setState(102);
        expr(18);
        break;
      }

      case AslParser::INTVAL: {
        _localctx = _tracker.createInstance<ValueContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(103);
        match(AslParser::INTVAL);
        break;
      }

      case AslParser::FLOATVAL: {
        _localctx = _tracker.createInstance<ValueContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(104);
        match(AslParser::FLOATVAL);
        break;
      }

      case AslParser::BOOLVAL: {
        _localctx = _tracker.createInstance<ValueContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(105);
        match(AslParser::BOOLVAL);
        break;
      }

      case AslParser::CHARVAL: {
        _localctx = _tracker.createInstance<ValueContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(106);
        match(AslParser::CHARVAL);
        break;
      }

      case AslParser::ID: {
        _localctx = _tracker.createInstance<ExprIdentContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(107);
        ident();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(148);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(146);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ArithmeticContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(110);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(111);
          dynamic_cast<ArithmeticContext *>(_localctx)->op = match(AslParser::MUL);
          setState(112);
          expr(18);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ArithmeticContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(113);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(114);
          dynamic_cast<ArithmeticContext *>(_localctx)->op = match(AslParser::DIV);
          setState(115);
          expr(17);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ArithmeticContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(116);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(117);
          dynamic_cast<ArithmeticContext *>(_localctx)->op = match(AslParser::MINUS);
          setState(118);
          expr(16);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ArithmeticContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(119);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(120);
          dynamic_cast<ArithmeticContext *>(_localctx)->op = match(AslParser::PLUS);
          setState(121);
          expr(15);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<RelationalContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(122);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(123);
          dynamic_cast<RelationalContext *>(_localctx)->op = match(AslParser::EQ);
          setState(124);
          expr(14);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<RelationalContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(125);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(126);
          dynamic_cast<RelationalContext *>(_localctx)->op = match(AslParser::NEQ);
          setState(127);
          expr(13);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<RelationalContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(128);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(129);
          dynamic_cast<RelationalContext *>(_localctx)->op = match(AslParser::LT);
          setState(130);
          expr(12);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<RelationalContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(131);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(132);
          dynamic_cast<RelationalContext *>(_localctx)->op = match(AslParser::MT);
          setState(133);
          expr(11);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<RelationalContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(134);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(135);
          dynamic_cast<RelationalContext *>(_localctx)->op = match(AslParser::LET);
          setState(136);
          expr(10);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<RelationalContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(137);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(138);
          dynamic_cast<RelationalContext *>(_localctx)->op = match(AslParser::MET);
          setState(139);
          expr(9);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<ExprAndContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(140);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(141);
          dynamic_cast<ExprAndContext *>(_localctx)->op = match(AslParser::AND);
          setState(142);
          expr(3);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<ExprOrContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(143);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(144);
          dynamic_cast<ExprOrContext *>(_localctx)->op = match(AslParser::OR);
          setState(145);
          expr(2);
          break;
        }

        } 
      }
      setState(150);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- IdentContext ------------------------------------------------------------------

AslParser::IdentContext::IdentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AslParser::IdentContext::ID() {
  return getToken(AslParser::ID, 0);
}


size_t AslParser::IdentContext::getRuleIndex() const {
  return AslParser::RuleIdent;
}

antlrcpp::Any AslParser::IdentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AslVisitor*>(visitor))
    return parserVisitor->visitIdent(this);
  else
    return visitor->visitChildren(this);
}

AslParser::IdentContext* AslParser::ident() {
  IdentContext *_localctx = _tracker.createInstance<IdentContext>(_ctx, getState());
  enterRule(_localctx, 18, AslParser::RuleIdent);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(151);
    match(AslParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool AslParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 8: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool AslParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 17);
    case 1: return precpred(_ctx, 16);
    case 2: return precpred(_ctx, 15);
    case 3: return precpred(_ctx, 14);
    case 4: return precpred(_ctx, 13);
    case 5: return precpred(_ctx, 12);
    case 6: return precpred(_ctx, 11);
    case 7: return precpred(_ctx, 10);
    case 8: return precpred(_ctx, 9);
    case 9: return precpred(_ctx, 8);
    case 10: return precpred(_ctx, 2);
    case 11: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> AslParser::_decisionToDFA;
atn::PredictionContextCache AslParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN AslParser::_atn;
std::vector<uint16_t> AslParser::_serializedATN;

std::vector<std::string> AslParser::_ruleNames = {
  "program", "function", "declarations", "variable_decl", "type", "statements", 
  "statement", "left_expr", "expr", "ident"
};

std::vector<std::string> AslParser::_literalNames = {
  "", "':'", "'='", "'=='", "'!='", "'<'", "'>'", "'<='", "'>='", "'+'", 
  "'-'", "'*'", "'/'", "'and'", "'or'", "'not'", "'var'", "'int'", "'float'", 
  "'bool'", "'char'", "'if'", "'then'", "'else'", "'endif'", "'func'", "'endfunc'", 
  "'read'", "'write'", "", "", "", "", "", "", "','", "'('", "')'", "';'"
};

std::vector<std::string> AslParser::_symbolicNames = {
  "", "", "ASSIGN", "EQ", "NEQ", "LT", "MT", "LET", "MET", "PLUS", "MINUS", 
  "MUL", "DIV", "AND", "OR", "NOT", "VAR", "INT", "FLOAT", "BOOL", "CHAR", 
  "IF", "THEN", "ELSE", "ENDIF", "FUNC", "ENDFUNC", "READ", "WRITE", "ID", 
  "INTVAL", "FLOATVAL", "BOOLVAL", "CHARVAL", "STRING", "COMMA", "LBRAC", 
  "RBRAC", "SEMI", "COMMENT", "WS"
};

dfa::Vocabulary AslParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> AslParser::_tokenNames;

AslParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x2a, 0x9c, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x3, 0x2, 0x6, 0x2, 0x18, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x19, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x7, 0x4, 0x27, 0xa, 0x4, 0xc, 0x4, 
    0xe, 0x4, 0x2a, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x2f, 
    0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x32, 0xb, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x7, 0x7, 0x3b, 0xa, 0x7, 
    0xc, 0x7, 0xe, 0x7, 0x3e, 0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x5b, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x6f, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x95, 
    0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x98, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x2, 0x3, 0x12, 0xc, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 
    0x14, 0x2, 0x3, 0x3, 0x2, 0x13, 0x16, 0x2, 0xae, 0x2, 0x17, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x6, 0x28, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xa, 0x37, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3c, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x10, 0x5c, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x14, 0x99, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0x18, 0x5, 0x4, 0x3, 0x2, 0x17, 0x16, 0x3, 0x2, 0x2, 
    0x2, 0x18, 0x19, 0x3, 0x2, 0x2, 0x2, 0x19, 0x17, 0x3, 0x2, 0x2, 0x2, 
    0x19, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1b, 
    0x1c, 0x7, 0x2, 0x2, 0x3, 0x1c, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1e, 
    0x7, 0x1b, 0x2, 0x2, 0x1e, 0x1f, 0x7, 0x1f, 0x2, 0x2, 0x1f, 0x20, 0x7, 
    0x26, 0x2, 0x2, 0x20, 0x21, 0x7, 0x27, 0x2, 0x2, 0x21, 0x22, 0x5, 0x6, 
    0x4, 0x2, 0x22, 0x23, 0x5, 0xc, 0x7, 0x2, 0x23, 0x24, 0x7, 0x1c, 0x2, 
    0x2, 0x24, 0x5, 0x3, 0x2, 0x2, 0x2, 0x25, 0x27, 0x5, 0x8, 0x5, 0x2, 
    0x26, 0x25, 0x3, 0x2, 0x2, 0x2, 0x27, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x28, 
    0x26, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x3, 0x2, 0x2, 0x2, 0x29, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x2a, 0x28, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x30, 0x7, 
    0x12, 0x2, 0x2, 0x2c, 0x2d, 0x7, 0x1f, 0x2, 0x2, 0x2d, 0x2f, 0x7, 0x25, 
    0x2, 0x2, 0x2e, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x32, 0x3, 0x2, 0x2, 
    0x2, 0x30, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x3, 0x2, 0x2, 0x2, 
    0x31, 0x33, 0x3, 0x2, 0x2, 0x2, 0x32, 0x30, 0x3, 0x2, 0x2, 0x2, 0x33, 
    0x34, 0x7, 0x1f, 0x2, 0x2, 0x34, 0x35, 0x7, 0x3, 0x2, 0x2, 0x35, 0x36, 
    0x5, 0xa, 0x6, 0x2, 0x36, 0x9, 0x3, 0x2, 0x2, 0x2, 0x37, 0x38, 0x9, 
    0x2, 0x2, 0x2, 0x38, 0xb, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3b, 0x5, 0xe, 
    0x8, 0x2, 0x3a, 0x39, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3e, 0x3, 0x2, 0x2, 
    0x2, 0x3c, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x3, 0x2, 0x2, 0x2, 
    0x3d, 0xd, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3f, 
    0x40, 0x5, 0x10, 0x9, 0x2, 0x40, 0x41, 0x7, 0x4, 0x2, 0x2, 0x41, 0x42, 
    0x5, 0x12, 0xa, 0x2, 0x42, 0x43, 0x7, 0x28, 0x2, 0x2, 0x43, 0x5b, 0x3, 
    0x2, 0x2, 0x2, 0x44, 0x45, 0x7, 0x17, 0x2, 0x2, 0x45, 0x46, 0x5, 0x12, 
    0xa, 0x2, 0x46, 0x47, 0x7, 0x18, 0x2, 0x2, 0x47, 0x48, 0x5, 0xc, 0x7, 
    0x2, 0x48, 0x49, 0x7, 0x1a, 0x2, 0x2, 0x49, 0x5b, 0x3, 0x2, 0x2, 0x2, 
    0x4a, 0x4b, 0x5, 0x14, 0xb, 0x2, 0x4b, 0x4c, 0x7, 0x26, 0x2, 0x2, 0x4c, 
    0x4d, 0x7, 0x27, 0x2, 0x2, 0x4d, 0x4e, 0x7, 0x28, 0x2, 0x2, 0x4e, 0x5b, 
    0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x1d, 0x2, 0x2, 0x50, 0x51, 0x5, 
    0x10, 0x9, 0x2, 0x51, 0x52, 0x7, 0x28, 0x2, 0x2, 0x52, 0x5b, 0x3, 0x2, 
    0x2, 0x2, 0x53, 0x54, 0x7, 0x1e, 0x2, 0x2, 0x54, 0x55, 0x5, 0x12, 0xa, 
    0x2, 0x55, 0x56, 0x7, 0x28, 0x2, 0x2, 0x56, 0x5b, 0x3, 0x2, 0x2, 0x2, 
    0x57, 0x58, 0x7, 0x1e, 0x2, 0x2, 0x58, 0x59, 0x7, 0x24, 0x2, 0x2, 0x59, 
    0x5b, 0x7, 0x28, 0x2, 0x2, 0x5a, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x44, 
    0x3, 0x2, 0x2, 0x2, 0x5a, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x4f, 0x3, 
    0x2, 0x2, 0x2, 0x5a, 0x53, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x57, 0x3, 0x2, 
    0x2, 0x2, 0x5b, 0xf, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x5, 0x14, 0xb, 
    0x2, 0x5d, 0x11, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x8, 0xa, 0x1, 0x2, 
    0x5f, 0x60, 0x7, 0x26, 0x2, 0x2, 0x60, 0x61, 0x5, 0x12, 0xa, 0x2, 0x61, 
    0x62, 0x7, 0x27, 0x2, 0x2, 0x62, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 
    0x7, 0x11, 0x2, 0x2, 0x64, 0x6f, 0x5, 0x12, 0xa, 0x16, 0x65, 0x66, 0x7, 
    0xb, 0x2, 0x2, 0x66, 0x6f, 0x5, 0x12, 0xa, 0x15, 0x67, 0x68, 0x7, 0xc, 
    0x2, 0x2, 0x68, 0x6f, 0x5, 0x12, 0xa, 0x14, 0x69, 0x6f, 0x7, 0x20, 0x2, 
    0x2, 0x6a, 0x6f, 0x7, 0x21, 0x2, 0x2, 0x6b, 0x6f, 0x7, 0x22, 0x2, 0x2, 
    0x6c, 0x6f, 0x7, 0x23, 0x2, 0x2, 0x6d, 0x6f, 0x5, 0x14, 0xb, 0x2, 0x6e, 
    0x5e, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x63, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x65, 
    0x3, 0x2, 0x2, 0x2, 0x6e, 0x67, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x69, 0x3, 
    0x2, 0x2, 0x2, 0x6e, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6b, 0x3, 0x2, 
    0x2, 0x2, 0x6e, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6d, 0x3, 0x2, 0x2, 
    0x2, 0x6f, 0x96, 0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 0xc, 0x13, 0x2, 0x2, 
    0x71, 0x72, 0x7, 0xd, 0x2, 0x2, 0x72, 0x95, 0x5, 0x12, 0xa, 0x14, 0x73, 
    0x74, 0xc, 0x12, 0x2, 0x2, 0x74, 0x75, 0x7, 0xe, 0x2, 0x2, 0x75, 0x95, 
    0x5, 0x12, 0xa, 0x13, 0x76, 0x77, 0xc, 0x11, 0x2, 0x2, 0x77, 0x78, 0x7, 
    0xc, 0x2, 0x2, 0x78, 0x95, 0x5, 0x12, 0xa, 0x12, 0x79, 0x7a, 0xc, 0x10, 
    0x2, 0x2, 0x7a, 0x7b, 0x7, 0xb, 0x2, 0x2, 0x7b, 0x95, 0x5, 0x12, 0xa, 
    0x11, 0x7c, 0x7d, 0xc, 0xf, 0x2, 0x2, 0x7d, 0x7e, 0x7, 0x5, 0x2, 0x2, 
    0x7e, 0x95, 0x5, 0x12, 0xa, 0x10, 0x7f, 0x80, 0xc, 0xe, 0x2, 0x2, 0x80, 
    0x81, 0x7, 0x6, 0x2, 0x2, 0x81, 0x95, 0x5, 0x12, 0xa, 0xf, 0x82, 0x83, 
    0xc, 0xd, 0x2, 0x2, 0x83, 0x84, 0x7, 0x7, 0x2, 0x2, 0x84, 0x95, 0x5, 
    0x12, 0xa, 0xe, 0x85, 0x86, 0xc, 0xc, 0x2, 0x2, 0x86, 0x87, 0x7, 0x8, 
    0x2, 0x2, 0x87, 0x95, 0x5, 0x12, 0xa, 0xd, 0x88, 0x89, 0xc, 0xb, 0x2, 
    0x2, 0x89, 0x8a, 0x7, 0x9, 0x2, 0x2, 0x8a, 0x95, 0x5, 0x12, 0xa, 0xc, 
    0x8b, 0x8c, 0xc, 0xa, 0x2, 0x2, 0x8c, 0x8d, 0x7, 0xa, 0x2, 0x2, 0x8d, 
    0x95, 0x5, 0x12, 0xa, 0xb, 0x8e, 0x8f, 0xc, 0x4, 0x2, 0x2, 0x8f, 0x90, 
    0x7, 0xf, 0x2, 0x2, 0x90, 0x95, 0x5, 0x12, 0xa, 0x5, 0x91, 0x92, 0xc, 
    0x3, 0x2, 0x2, 0x92, 0x93, 0x7, 0x10, 0x2, 0x2, 0x93, 0x95, 0x5, 0x12, 
    0xa, 0x4, 0x94, 0x70, 0x3, 0x2, 0x2, 0x2, 0x94, 0x73, 0x3, 0x2, 0x2, 
    0x2, 0x94, 0x76, 0x3, 0x2, 0x2, 0x2, 0x94, 0x79, 0x3, 0x2, 0x2, 0x2, 
    0x94, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x94, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x94, 
    0x82, 0x3, 0x2, 0x2, 0x2, 0x94, 0x85, 0x3, 0x2, 0x2, 0x2, 0x94, 0x88, 
    0x3, 0x2, 0x2, 0x2, 0x94, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x94, 0x8e, 0x3, 
    0x2, 0x2, 0x2, 0x94, 0x91, 0x3, 0x2, 0x2, 0x2, 0x95, 0x98, 0x3, 0x2, 
    0x2, 0x2, 0x96, 0x94, 0x3, 0x2, 0x2, 0x2, 0x96, 0x97, 0x3, 0x2, 0x2, 
    0x2, 0x97, 0x13, 0x3, 0x2, 0x2, 0x2, 0x98, 0x96, 0x3, 0x2, 0x2, 0x2, 
    0x99, 0x9a, 0x7, 0x1f, 0x2, 0x2, 0x9a, 0x15, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x19, 0x28, 0x30, 0x3c, 0x5a, 0x6e, 0x94, 0x96, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

AslParser::Initializer AslParser::_init;
