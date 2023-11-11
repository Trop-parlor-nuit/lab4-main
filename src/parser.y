%code top{
    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    int itype;
    float ftype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    ConstExprNode* constexprtype;
    Type* type;
    DimList* dimList;
    InitList* initList;
    InitValues* initValues;
    InitValueNode* initValueNode;
    FuncCall* funcUse;
    InitDeclarator* initDeclarator;
    MultiDecl * multiDecl;
}

%start Program
%token <strtype> ID 
%token <itype> INTEGER
%token <ftype> FLO
%token IF ELSE
%token INT VOID FLOAT CHAR 
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA
%token ADD SUB ASSIGN
%token RETURN
%token LBRACKET RBRACKET
%token ALIGNAS ALIGNOF AUTO BOOL BREAK CASE CATCH CHAR8_T CHAR16_T
%token CHAR32_T CLASS CONST CONSTEXPR CONST_CAST CONTINUE DECLTYPE DEFAULT
%token DELETE DO DOUBLE DYNAMIC_CAST ENUM EXPLICIT EXPORT EXTERN FALSE
%token FOR FRIEND GOTO INLINE LONG MUTABLE NAMESPACE NEW NOEXCEPT NULLPTR
%token OPERATOR PRIVATE PROTECTED PUBLIC REGISTER REINTERPRET_CAST REQUIRES 
%token SHORT SIGNED SIZEOF STATIC STATIC_ASSERT STATIC_CAST STRUCT SWITCH
%token TEMPLATE THIS THREAD_LOCAL THROW TRUE TRY TYPEDEF TYPEID TYPENAME
%token UNION UNSIGNED USING VIRTUAL VOLATILE

%token WHILE MUL DIV MOD
%token EQ LT NEQ LE GT GE NE
%token PLUSASSIGN MINUSASSIGN MULTASSIGN DIVASSIGN MODASSIGN ANDASSIGN
%token ORASSIGN XORASSIGN LSHIFTASSIGN RSHIFTASSIGN INCREMENT DECREMENT
%token BITAND BITOR BITXOR BITNOT MODULO LSHIFT RSHIFT 
%token LOGAND LOGOR NOT


%nterm <stmttype> Stmts Stmt AssignStmt BlockStmt IfStmt ReturnStmt DeclStmt FuncDef FuncParams FuncParam BreakStmt ContinueStmt WhileStmt ExprStmt FuncCallParams FuncCallParam EmptyStmt 

%nterm <initDeclarator> InitDeclarator
%nterm <multiDecl> MultiDecl
%type <dimList> DimList SelectDimlist
%type <initList> InitList
%type <initValues> InitValues
%type <initValueNode> InitValue
%nterm <exprtype> Exp AddExp Cond LOrExp PrimaryExp UnaryExp LVal RelExp LAndExp ArrayAccess FuncUse 
%nterm <type> Type

%precedence THEN
%precedence ELSE
%%
Program
    : Stmts {
        ast.setRoot($1);
    }
    ;
Stmts
    : Stmt {$$=$1;}
    | Stmts Stmt{
        $$ = new SeqNode($1, $2);
    }
    ;
Stmt
    : AssignStmt {$$=$1;}
    | BlockStmt {$$=$1;}
    | IfStmt {$$=$1;}
    | WhileStmt {$$=$1;}
    | BreakStmt {$$=$1;}
    | ContinueStmt {$$=$1;}
    | ReturnStmt {$$=$1;}
    | DeclStmt {$$=$1;}
    | FuncDef {$$=$1;}
    | ExprStmt{ $$ = $1;}
    |EmptyStmt{$$ = $1;}
    ;
LVal
    : ID {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new Id(se);
        delete []$1;
    }
    | ArrayAccess{$$ = $1;}
    ;
AssignStmt
    :
    LVal ASSIGN Exp SEMICOLON {
        $$ = new AssignStmt($1, $3);
    }
    ;
BlockStmt
    :   LBRACE 
        {identifiers = new SymbolTable(identifiers);
         constidentifiers = new SymbolTable(constidentifiers);
        } 
        Stmts RBRACE 
        {
            $$ = new CompoundStmt($3);
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
            SymbolTable *top1 = constidentifiers;
            constidentifiers = constidentifiers->getPrev();
            delete top1;
        }
    | LBRACE RBRACE{
        $$ = new EmptyStmt();
    }
    ;
IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        $$ = new IfElseStmt($3, $5, $7);
    }
    ;
WhileStmt
    : WHILE LPAREN Cond RPAREN Stmt {
        $$ = new WhileStmt($3, $5);
    }
    ;

ReturnStmt
    :
    RETURN Exp SEMICOLON{
        $$ = new ReturnStmt($2);
    }
    ;
BreakStmt
    :
    BREAK SEMICOLON{
        $$ = new BreakStmt();
    }
    ;
ContinueStmt
    :
    CONTINUE SEMICOLON{
        $$ = new ContinueStmt();
    }
    ;
EmptyStmt
    :
    SEMICOLON{
        $$ = new EmptyStmt();
    }
    ;
Exp
    :
    AddExp {$$ = $1;}
    ;
Cond
    :
    LOrExp {$$ = $1;}
    ;
    





PrimaryExp
    :
    LVal {
        $$ = $1;
    }
    | INTEGER {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, $1);
        $$ = new Constant(se);
    }
    | FLO{
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::floatType, $1);
        $$ = new Constant(se);
    }
    |FuncUse{
        $$ = $1;
    }
    | LPAREN Exp RPAREN {
        $$ = $2;
    }

    ;
UnaryExp
    : PrimaryExp {
        $$ = $1;
    }
    | NOT UnaryExp {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::NOT, $2);
    }
    | ADD UnaryExp {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::ADD, $2);
    }
    | SUB UnaryExp {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::SUB, $2);
    }
    ;

AddExp
    :

    UnaryExp{$$ = $1;}
    |
    AddExp ADD UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
    }
    |
    AddExp SUB UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
    }
    |
    AddExp MUL UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
    }
    |
    AddExp DIV UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
    }
    |
    AddExp BITAND UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::BITAND, $1, $3);
    }
    |
    AddExp BITOR UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::BITOR, $1, $3);
    }
    |
    AddExp BITXOR UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::BITXOR, $1, $3);
    }
    |
    AddExp MOD UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
    }
    ;



RelExp
    :
    AddExp {$$ = $1;}
    |
    RelExp LT AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LT, $1, $3);
    }
    |
    RelExp GT AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GT, $1, $3);
    }
    |
    RelExp EQ AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQ, $1, $3);
    }
    |
    RelExp GE AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GE, $1, $3);
    }
    |
    RelExp LE AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LE, $1, $3);
    }
    |
    RelExp NE AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::NE, $1, $3);
    }

    ;
LAndExp
    :
    RelExp {$$ = $1;}
    |
    LAndExp LOGAND RelExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LOGAND, $1, $3);
    }
    ;
LOrExp
    :
    LAndExp {$$ = $1;}
    |
    LOrExp LOGOR LAndExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LOGOR, $1, $3);
    }
    ;
Type
    : INT {
        $$ = TypeSystem::intType;
    }
    | VOID {
        $$ = TypeSystem::voidType;
    }
    | FLOAT{
        $$ = TypeSystem::floatType;
    }
    | CHAR{
        $$= TypeSystem::charType;
    }
    ;
InitDeclarator
    : ID ASSIGN Exp{
        ExpInitValue* expr = new ExpInitValue($3);
        $$ = new InitDeclarator(expr,$1);
    }
    | ID{
        $$ = new InitDeclarator($1);
    }
    | ID DimList{
        $$ = new InitDeclarator($1,$2);
    }
    | ID DimList ASSIGN InitList{
        $$ = new InitDeclarator($4,$1,$2);
    }
    ;
MultiDecl
    : InitDeclarator{
        $$ = new MultiDecl($1);
    }
    | MultiDecl COMMA InitDeclarator{
         $1->addname($3);
         $$ = $1;
    }
    ;


DeclStmt
    :

    Type MultiDecl SEMICOLON  { 
        std::vector<Id *> idlist;
        for(auto decl : $2->decls){
            SymbolEntry * se;
            se= new IdentifierSymbolEntry($1, decl->getname(), identifiers->getLevel());
            identifiers->install(decl->getname(), se);
            if(decl->getdimList() == NULL)
                idlist.push_back(new Id(se));  
            else{
                idlist.push_back(new Id(se,decl->getdimList())); 
            }
        }

        $$ = new DeclStmt(idlist,$2);
       // delete []$2;
        }
    |
    CONST Type MultiDecl SEMICOLON  { 
        std::vector<Id *> idlist;
        for(auto decl : $3->decls){
            SymbolEntry * se;
            se= new IdentifierSymbolEntry($2, decl->getname(), identifiers->getLevel(),1);
            identifiers->install(decl->getname(), se);
            idlist.push_back(new Id(se));  
        }

        $$ = new DeclStmt(idlist,$3);
       // delete []$3;
        }
    ;
FuncDef
    :
    Type ID {
        Type *funcType;
        funcType = new FunctionType($1,{});
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        identifiers->install($2, se);
        identifiers = new SymbolTable(identifiers);
    }
    LPAREN FuncParams{
        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);
        if($5!=nullptr){
            ((FunctionType*)(se->getType()))->SetParamsType(((FunctionDefParas*)$5)->getParamsType());
        }   
    }
    RPAREN BlockStmt
    {
        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);
        $$ = new FunctionDef(se, (FunctionDefParas*)$5, $8);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    |
    CONST Type ID {
        Type *funcType;
        funcType = new FunctionType($2,{});
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $3, identifiers->getLevel(),1);
        identifiers->install($3, se);
        identifiers = new SymbolTable(identifiers);
    }
    LPAREN FuncParams{
        SymbolEntry *se;
        se = identifiers->lookup($3);
        assert(se != nullptr);
        if($6!=nullptr){
            ((FunctionType*)(se->getType()))->SetParamsType(((FunctionDefParas*)$6)->getParamsType());
        }   
    }
    RPAREN BlockStmt
    {
        SymbolEntry *se;
        se = identifiers->lookup($3);
        assert(se != nullptr);
        $$ = new FunctionDef(se, (FunctionDefParas*)$6, $9);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$3;
    }
    ;
FuncParams
    :
    FuncParam {
        FunctionDefParas* node = new FunctionDefParas();
        node->addParameter(((DefNode*)$1)->getId());
        $$ = node;
    }
    |
    FuncParams COMMA FuncParam {
        FunctionDefParas* node = (FunctionDefParas*)$1;
        node->addParameter(((DefNode*)$3)->getId());
        $$ = node;
    }
    |
    %empty {
        $$ = nullptr;
    }
    ;
FuncParam
    :   Type ID {
            SymbolEntry *se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
            identifiers->install($2, se);
            $$ = new DefNode(new Id(se), nullptr,0,0);
        }
        |
        Type ID SelectDimlist{
            SymbolEntry *se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
            identifiers->install($2, se);
            $$ = new DefNode(new Id(se), nullptr,0,0,$3);
        }
    ;
FuncCallParams
    :
    FuncCallParam {
        FunctionDefParas* node = new FunctionDefParas();
        node->addParameter(((DefNode*)$1)->getId());
        $$ = node;
    }
    |
    FuncCallParams COMMA FuncCallParam {
        FunctionDefParas* node = (FunctionDefParas*)$1;
        node->addParameter(((DefNode*)$3)->getId());
        $$ = node;
    }
    |
    %empty {
        $$ = nullptr;
    }
    ;

FuncCallParam
    : Exp{
        $$ = new ParamStmt($1);
    }
    ;

FuncUse
    : ID LPAREN FuncCallParams RPAREN 
    {
        SymbolEntry *globalse = globals->lookup($1);
        if(globalse==nullptr)
        {
            SymbolEntry *se = identifiers->lookup($1);
            assert(se != nullptr );
            $$ = new FuncCall(se,(FunctionDefParas*)$3);
        }
        else
        {
            assert(globalse != nullptr );
            $$ = new FuncCall(globalse,(FunctionDefParas*)$3);
        }
        
    }

    ;
InitList
    :
    LBRACE RBRACE { $$ = new InitList(); } 
    |
    LBRACE InitValues RBRACE { $$ = new InitList($2); } 
    ;

InitValues
    :
    InitValue { $$ = new InitValues($1); } 
    |
    InitValues COMMA InitValue { $$->addValue($3); } 
    ;

InitValue
    :
    LBRACE InitValues RBRACE { $$ = new InitList($2); } 
    |
    LBRACE RBRACE { $$ = new InitList(); } 
    |
    Exp { $$ = new ExpInitValue($1); } 
    ;



DimList
    :
    LBRACKET Exp RBRACKET { $$ = new DimList($2);$$->addDimension($2->interger); }
    |
    DimList LBRACKET Exp RBRACKET {
        $1->addDims($3);
        $1->addDimension($3->interger);
        $$ = $1;
    }
    ;
SelectDimlist
    :
    DimList { $$ = $1; }
    |
    LBRACKET RBRACKET DimList  {
        $3->omit=1;
        $$ = $3;
    }
    |LBRACKET RBRACKET{
        DimList * dim = new DimList;
        dim->omit=1;
        $$ =dim;
    }
    ;


ArrayAccess
    : ID DimList
    {


        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
                $$ = new ArrayAccessNode(se, $2);
        delete []$1;
    }
    ;
 ExprStmt
    : Exp SEMICOLON
    {
        $$ = new ExprStmt($1);
    }
    ;
%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
