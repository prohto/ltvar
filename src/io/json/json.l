%{
#include <stdio.h>
#include "json.h"
#include "json_bison.hpp"


#define FLEX_VALUE_LEN  1024
#define parser_state    yyget_extra(yyscanner)

#define YY_INPUT(buffer, res, max_size)             \
do { \
  res = parser_state->readBuffer( buffer, max_size ); \
  if( res == 0  ){ \
    res = YY_NULL; \
  } \
} while (0)

int json_get_lineno (yyscan_t yyscanner );
int32_t json_lineno_get( void *scanner ){
  return json_get_lineno( scanner );
}

%}

%option yylineno
%option reentrant stack bison-bridge
%option noyywrap
%option nounput

true              [Tt][Rr][Uu][Ee]
false             [Ff][Aa][Ll][Ss][Ee]
null              [Nn][Uu][Ll][Ll]
integer           [-+]?[0-9]+
float             ([-+]?([0-9]*)?\.[0-9]*([eE][-+]?[0-9]+)?)|([-+]?([0-9]+)(\.[0-9]*)?[eE][-+]?[0-9]+)
hexchar           [0-9a-fA-F]{4}
hexnum            (0x)?[0-9a-fA-F]+

%x STRING

%%

\"                      { yy_push_state(STRING, yyscanner); }
<STRING>([^\"\\]|\\\"|\\\\|\\\/|\\b|\\f|\\n|\\r|\\t|\\u[0-9,a-f,A-F]{4})*	{ JsonState::unescape(yytext); parser_state->push( yytext ); }
<STRING>\"              { yy_pop_state(yyscanner); return TEXT;}

{true}                  { parser_state->push( true ); return VALUE;}
{false}                 { parser_state->push( false ); return VALUE;}
{null}                  { parser_state->push( LType::Type::kVoid ); return VALUE; }

[a-zA-Z][a-zA-Z0-9_]+	{ JsonState::unescape( yytext ); parser_state->push( yytext ); return TEXT;}

{integer}		{ parser_state->push( std::stoi( yytext )); return VALUE;}
{hexnum}		{ parser_state->push( std::stoi( yytext, 0, 16 )); return VALUE;}
{float}			{ parser_state->push( std::stod(yytext)); return VALUE; }

\[			return OBRACK;
\]			return EBRACK;
\{			return OBRACE;
\}			return EBRACE;
\:			return COLON;
\,			return COMMA;

\n						/* ignore newline */;
[ \t]+                  /* ignore whitespace */;

%%
