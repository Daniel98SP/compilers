grammar Asl;

//////////////////////////////////////////////////
/// Parser Rules
//////////////////////////////////////////////////

// A program is a list of functions
program : function+ EOF
        ;

// A function has a name, a list of parameters and a list of statements
function
        : FUNC ID '(' ')' declarations statements ENDFUNC
        ;

declarations
        : (variable_decl)*
        ;

variable_decl
        : VAR (ID COMMA)* ID ':' type
        ;

type    : INT
        | FLOAT
        | BOOL
        | CHAR
        ;

statements
        : (statement)*
        ;

// The different types of instructions
statement
          // Assignment
        : left_expr ASSIGN expr SEMI           # assignStmt
          // if-then-else statement (else is optional)
        | IF expr THEN statements ENDIF       # ifStmt
          // A function/procedure call has a list of arguments in parenthesis (possibly empty)
        | ident LBRAC RBRAC SEMI                   # procCall
          // Read a variable
        | READ left_expr SEMI                  # readStmt
          // Write an expression
        | WRITE expr SEMI                      # writeExpr
          // Write a string
        | WRITE STRING SEMI                    # writeString
        ;
// Grammar for left expressions (l-values in C++)
left_expr
        : ident
        ;

// Grammar for expressions with boolean, relational and aritmetic operators
expr    : LBRAC expr RBRAC                    # exprBrac
        | op=NOT expr                         # exprNot
        | op=PLUS expr                        # arithmetic
        | op=MINUS expr                       # arithmetic
        | expr op=MUL expr                    # arithmetic
        | expr op=DIV expr                    # arithmetic
        | expr op=MINUS expr                  # arithmetic
        | expr op=PLUS expr                   # arithmetic
        | expr op=EQ expr                     # relational
        | expr op=NEQ expr                    # relational
        | expr op=LT expr                     # relational
        | expr op=MT expr                     # relational
        | expr op=LET expr                    # relational
        | expr op=MET expr                    # relational
        | INTVAL                              # value
        | FLOATVAL                            # value
        | BOOLVAL                             # value
        | CHARVAL                             # value
        | ident                               # exprIdent
        | expr op=AND expr                    # exprAnd
        | expr op=OR expr                     # exprOr
        ;

ident   : ID
        ;

//////////////////////////////////////////////////
/// Lexer Rules
//////////////////////////////////////////////////

// Assign
ASSIGN    : '=' ;

// Comparation and arithmetic signs
EQ        : '==' ;
NEQ       : '!=' ;
LT        : '<'  ;
MT        : '>'  ;
LET       : '<=' ;
MET       : '>=' ;

// Arithmetic operations
PLUS      : '+'  ;
MINUS     : '-'  ;
MUL       : '*'  ;
DIV       : '/'  ;


AND       : 'and';
OR        : 'or' ;
NOT       : 'not';

// Key words
VAR       : 'var'     ;
INT       : 'int'     ;
FLOAT     : 'float'   ;
BOOL      : 'bool'    ;
CHAR      : 'char'    ;
IF        : 'if'      ;
THEN      : 'then'    ;
ELSE      : 'else'    ;
ENDIF     : 'endif'   ;
FUNC      : 'func'    ;
ENDFUNC   : 'endfunc' ;
READ      : 'read'    ;
WRITE     : 'write'   ;

// ID names
ID        : ('a'..'z'|'A'..'Z') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')* ;

// Data representation
INTVAL    : ('0'..'9')+ ;
FLOATVAL  : ('0'..'9')+ '.' ('0'..'9')+ ;
BOOLVAL   : ('true' | 'false') ;
CHARVAL   : '\'' ('a'..'z'|'A'..'Z'|'0'..'9'|'\n'|'\t'|'\''|' '|'_'|'@') '\'' ;

// Strings (in quotes) with escape sequences
STRING    : '"' ( ESC_SEQ | ~('\\'|'"') )* '"' ;

//
COMMA     : ',' ;
LBRAC     : '(' ;
RBRAC     : ')' ;
SEMI      : ';' ;

fragment
ESC_SEQ   : '\\' ('b'|'t'|'n'|'f'|'r'|'"'|'\''|'\\') ;

// Comments (inline C++-style)
COMMENT   : '//' ~('\n'|'\r')* '\r'? '\n' -> skip ;

// White spaces
WS        : (' '|'\t'|'\r'|'\n')+ -> skip ;
// Alternative description
// WS        : [ \t\r\n]+ -> skip ;
