%{
    #include "node.h"
    NBlock *program_block;
    extern int yylex();
    void yyerror(const char *s) {
        printf("Error: %s\n", s);
    }
%}

%union{
    Node *node;
    BlockNode  *block;
    Expression *expr;
    Statement  *stmt;
    IdentifierNode *ident;
    VariableDeclaration *var_decl;
    std::vector<VariableDeclaration> *var_vec;
    std::vector<Expression> *expr_vec;
    std::string *string;
    int token;
}

%token <string> IDENTIFIER INTEGER DOUBLE BOOLEAN
%token <token>
%token <token>
%token <token>