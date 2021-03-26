
// Generated from Asl.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  AslLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, ASSIGN = 2, EQ = 3, NEQ = 4, LT = 5, MT = 6, LET = 7, MET = 8, 
    PLUS = 9, MINUS = 10, MUL = 11, DIV = 12, AND = 13, OR = 14, NOT = 15, 
    VAR = 16, INT = 17, FLOAT = 18, BOOL = 19, CHAR = 20, IF = 21, THEN = 22, 
    ELSE = 23, ENDIF = 24, FUNC = 25, ENDFUNC = 26, READ = 27, WRITE = 28, 
    ID = 29, INTVAL = 30, FLOATVAL = 31, BOOLVAL = 32, CHARVAL = 33, STRING = 34, 
    COMMA = 35, LBRAC = 36, RBRAC = 37, SEMI = 38, COMMENT = 39, WS = 40
  };

  AslLexer(antlr4::CharStream *input);
  ~AslLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

