grammar Asl;

//////////////////////////////////////////////////
/// Parser Rules
//////////////////////////////////////////////////

// A program is a list of functions
program  : function+ EOF
         ;

// A function has a name, a list of parameters and a list of statements
function : FUNC ID '(' ')' declarations statements ENDFUNC
         ;

declarations
         : (variable_decl)*
         ;

variable_decl
         : VAR (ID COMMA)* ID ':' type
         ;

type     : INT
         | FLOAT
         | BOOL
         | CHAR
         ;

statements
         : (statement)*
         ;

// The different types of instructions
statement: left_expr ASSIGN expr SEMI          # assignStmt         // Assignment
         | IF expr THEN statements ENDIF       # ifStmt             // if-then-else statement (else is optional)
         | ident LBRAC RBRAC SEMI              # procCall           // A function/procedure call has a list of arguments in parenthesis (possibly empty)
         | READ left_expr SEMI                 # readStmt           // Read a variable
         | WRITE expr SEMI                     # writeExpr          // Write an expression
         | WRITE STRING SEMI                   # writeString        // Write a string
         ;
// Grammar for left expressions (l-values in C++)
left_expr
         : ident
         ;

// Grammar for expressions with boolean, relational and aritmetic operators
expr     : op=NOT expr                         # exprBooleanUnary
         | op=PLUS expr                        # exprArithmeticUnary
         | op=MINUS expr                       # exprArithmeticUnary
         | expr op=MUL expr                    # exprArithmetic
         | expr op=DIV expr                    # exprArithmetic
         | expr op=MINUS expr                  # exprArithmetic
         | expr op=PLUS expr                   # exprArithmetic
         | expr op=EQ expr                     # exprRelational
         | expr op=NEQ expr                    # exprRelational
         | expr op=LT expr                     # exprRelational
         | expr op=MT expr                     # exprRelational
         | expr op=LET expr                    # exprRelational
         | expr op=MET expr                    # exprRelational
         | INTVAL                              # exprValue
         | FLOATVAL                            # exprValue
         | BOOLVAL                             # exprValue
         | CHARVAL                             # exprValue
         | ident                               # exprIdent
         | expr op=AND expr                    # exprBoolean
         | expr op=OR expr                     # exprBoolean
         | LBRAC expr RBRAC                    # exprBrac
         ;

ident    : ID
         ;

//////////////////////////////////////////////////
/// Lexer Rules
//////////////////////////////////////////////////

// Assign
ASSIGN    : '=' ;

// Relational operations
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

// Boolean operations
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

// Key characters
COMMA     : ',' ;
LBRAC     : '(' ;
RBRAC     : ')' ;
SEMI      : ';' ;

// Data representation
INTVAL    : ('0'..'9')+ ;
FLOATVAL  : ('0'..'9')+ '.' ('0'..'9')+ ;
BOOLVAL   : ('true' | 'false') ;
CHARVAL   : '\'' ('a'..'z'|'A'..'Z'|'0'..'9'|'\n'|'\t'|'\''|' '|'_'|'@') '\'' ;

// ID names
ID        : ('a'..'z'|'A'..'Z') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')* ;

// Strings (in quotes) with escape sequences
STRING    : '"' ( ESC_SEQ | ~('\\'|'"') )* '"' ;

fragment
ESC_SEQ   : '\\' ('b'|'t'|'n'|'f'|'r'|'"'|'\''|'\\') ;

// Comments (inline C++-style)
COMMENT   : '//' ~('\n'|'\r')* '\r'? '\n' -> skip ;

// White spaces
WS        : (' '|'\t'|'\r'|'\n')+ -> skip ;
// Alternative description
// WS        : [ \t\r\n]+ -> skip ;
