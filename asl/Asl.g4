//////////////////////////////////////////////////////////////////////
//
//    Asl - Another simple language (grammar)
//
//    Copyright (C) 2017  Universitat Politecnica de Catalunya
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

grammar Asl;

//////////////////////////////////////////////////
/// Parser Rules
//////////////////////////////////////////////////

// A program is a list of functions
program : function+ EOF
        ;

// A function has a name, a list of parameters and a list of statements
function
        : FUNC ID LP function_params RP (':' basic_type)? declarations statements ENDFUNC
        ;
        
function_params
        : (|ID ':' type (COMMA ID ':' type)*)
        ;

declarations
        : (variable_decl)*
        ;

variable_decl
        : VAR ID (COMMA ID)* ':' type
        ;

type    : basic_type
        | array_type
        ;
       
basic_type
        : INT
        | FLOAT
        | BOOL
        | CHAR
        ;
        
array_type
        : ARRAY LS INTVAL RS OF basic_type
        ;

statements
        : (statement)*
        ;

// The different types of instructions
statement
          // Assignment
        : left_expr ASSIGN expr ';'                        # assignStmt
          // if-then-else statement (else is optional)
        | IF expr THEN statements (ELSE statements)? ENDIF # ifStmt
          // while statement
        | WHILE expr DO statements  ENDWHILE               # whileStmt
          // A function/procedure call has a list of arguments in parenthesis (possibly empty)
        | ident LP (expr (COMMA expr)*)? RP ';'            # procCall
          // Read a variable
        | READ left_expr ';'                               # readStmt
          // Write an expression
        | WRITE expr ';'                                   # writeExpr
          // Write a string
        | WRITE STRING ';'                                 # writeString
          // return stuff
        | RETURN (expr)? ';'                                 # returnStmt 
        ;
// Grammar for left expressions (l-values in C++)
left_expr
        : ident (LS expr RS)?
        ;

// Grammar for expressions with boolean, relational and aritmetic operators
expr    : LP expr RP                                    # parenthesis
        | ident LS expr RS                              # array_access
        | ident LP (expr (COMMA expr)*)? RP             # function_call
        | op=(NOT|PLUS|SUB) expr                        # unary
        | expr op=(MUL|DIV|MOD) expr                    # arithmetic
        | expr op=(PLUS|SUB) expr                       # arithmetic
        | expr op=(EQUAL|NE|LT|LTE|GT|GTE) expr         # relational
        | expr op=(AND|OR) expr                         # logical
        | (INTVAL|FLOATVAL|BOOLVAL|CHARVAL)             # value
        | ident                                         # exprIdent
        ;

ident   : ID
        ;

//////////////////////////////////////////////////
/// Lexer Rules
//////////////////////////////////////////////////

LP        : '(' ;
RP        : ')' ;
LS        : '[' ;
RS        : ']' ;
ASSIGN    : '=' ;
EQUAL     : '==' ;
NE        : '!=' ;
NOT       : 'not' ;
LT        : '<' ;
GT        : '>' ;
GTE       : '>=' ;
LTE       : '<=' ;
PLUS      : '+' ;
SUB       : '-' ;
MUL       : '*' ;
MOD       : '%' ;
DIV       : '/' ;
VAR       : 'var' ;
ARRAY     : 'array' ;
OF        : 'of' ;
INT       : 'int' ;
BOOL      : 'bool' ;
FLOAT     : 'float' ;
CHAR      : 'char' ;
AND       : 'and' ;
OR        : 'or' ;
IF        : 'if' ;
THEN      : 'then' ;
ELSE      : 'else' ;
ENDIF     : 'endif' ;
FUNC      : 'func' ;
ENDFUNC   : 'endfunc' ;
RETURN    : 'return' ;
WHILE     : 'while' ;
DO        : 'do' ;
ENDWHILE  : 'endwhile';
READ      : 'read' ;
WRITE     : 'write' ;
ID        : ('a'..'z'|'A'..'Z') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')* ;
INTVAL    : ('0'..'9')+ ;
FLOATVAL  : ('0'..'9')+ ('.' ('0'..'9')+)? ;
CHARVAL   : '\'' (ESC_SEQ| ~('\\'|'\'') ) '\'' ;
BOOLVAL   : ('true'|'false') ;
COMMA     : ',' ;

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
