%{
#include <string>
#include "node.h"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
%}

%start COMMENT
%%

<INITIAL>[ \t\n] {}
<INITIAL>[a-zA-Z_][a-zA-Z0-9_]* {SAVE_TOKEN; return IDENTIFIER;}
<INITIAL>[-+]?[0-9]+.[0-9]*          {SAVA_TOKEN; return DOUBLE;}
<INITIAL>[-+]?[0-9]+                 {SAVE_TOKEN; return INTEGER;}
<INITIAL>"return" { return RETURN;}
<INITIAL>"false"  { return FALSE;}
<INITIAL>"if"     { return IF; }
<INITIAL>"lambda" { return LAMBDA;}
<INITIAL>"true"   { return TRUE;}
<INITIAL>"bool"   { return BOOL;}
<INITIAL>"string" { return STRING;}
<INITIAL>

<INITIAL>"(" { return LP; }
<INITIAL>")" { return RP; }
<INITIAL>"{" { return LC; }
<INITIAL>"}" { return RC; }

<INITIAL>"-\>" {return RARROW;}


%%