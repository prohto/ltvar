%{
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "json.h"

void yyerror( JsonState* state, void *scanner, const char *str ){
  state->setFailed();
}
 
int yywrap(){
  return 1;
} 
  
%}

%pure_parser
%parse-param { JsonState*json_state}
%parse-param {void *scanner}
%lex-param {yyscan_t *scanner}

%token TEXT VALUE OBRACE EBRACE OBRACK EBRACK UNDEF COLON COMMA

%%
json:
  | value
;

members:
  | member
  | members COMMA member
;

object :
  openobject members closeobject
;

openobject:
  OBRACE{
    json_state->push( LType::Type::kHash );
  }
;

closeobject:
  EBRACE{
  }
;


openarray:
  OBRACK{
    json_state->push( LType::Type::kArray );
  }
;

closearray:
  EBRACK{
  }
;

member:
  name value {
    LType value = json_state->pop();
    LType name = json_state->pop();
    json_state->top()[ static_cast<std::string>(name) ] = value;
  }
;


name :
  TEXT COLON
;

value:
  object
  | array
  | VALUE
  | TEXT
;

array:
  openarray values closearray
  | openarray closearray
;

values:
  value {
    LType value = json_state->pop();
    LType& array = json_state->top();
    array[ array.size() ] = std::move(value);
  }
  | values COMMA value {
    LType value = json_state->pop();
    LType& array = json_state->top();
    array[ array.size() ] = std::move(value);
  }
;

%%

