#include "Ast.h"
#include "SymbolTable.h"
#include <string>
#include "Type.h"

extern FILE *yyout;
int Node::counter = 0;

Node::Node()
{
    seq = counter++;
}

void Ast::output()
{
    fprintf(yyout, "program\n");
    if(root != nullptr)
        root->output(4);
}

void BinaryExpr::output(int level)
{
    std::string op_str;
    switch(op)
{
    case ADD: // +
        op_str = "add";
        break;
    case SUB: // -
        op_str = "sub";
        break;
    case MUL: // *
        op_str = "mul";
        break;
    case DIV: // /
        op_str = "div";
        break;
    case MOD: // %
        op_str = "mod";
        break;
    case LOGAND: // &&
        op_str = "logand";
        break;
    case LOGOR: // ||
        op_str = "logor";
        break;
    case NOT: // !
        op_str = "not";
        break;
    

    case EQ: // ==
        op_str = "equal";
        break;
    case GT: // >
        op_str = "greater";
        break;
    case LT: // <
        op_str = "less";
        break;
    case GE: // >=
        op_str = "greater_equal";
        break;
    case LE: // <=
        op_str = "less_equal";
        break;
    case NE: // !=
        op_str = "not_equal";
        break;
    case BITAND : 
        op_str = "bit_and";
        break;
    case BITOR  : 
        op_str = "bit_or";
        break;
    case BITXOR   :
        op_str = "bit_xor";
        break;
    default:
        // 处理默认情况或者错误
        break;
}

    fprintf(yyout, "%*cBinaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}

void Constant::output(int level)
{
    std::string type, value,valuef;
    type = ExprNode::symbolEntry->getType()->toStr();
    value = ExprNode::symbolEntry->toStr();
    valuef = ExprNode::symbolEntry->toStrf();
    
    if(type == "float"){
            fprintf(yyout, "%*cFloatLiteral\tvalue: %s\ttype: %s\n", level, ' ',
            valuef.c_str(), type.c_str());
    }
    else{
            fprintf(yyout, "%*cIntegerLiteral\tvalue: %s\ttype: %s\n", level, ' ',
            value.c_str(), type.c_str());
    }
    
}

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();

    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    if(symbolEntry->is_a_const()==1){
            fprintf(yyout, "%*cconstId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
    }
    else{
        fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
    }
    if(dimList != NULL){
        dimList->output(level+4);
    }
    if(isArray() && Indices!=nullptr){
        Indices->output(level+4);
    }
    
}

void CompoundStmt::output(int level)
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    stmt->output(level + 4);
}

void SeqNode::output(int level)
{
    fprintf(yyout, "%*cSequence\n", level, ' ');
    stmt1->output(level + 4);
    stmt2->output(level + 4);
}

void DeclStmt::output(int level)
{
    fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    if(decls != NULL){
        decls->output(level+4);
    }
   // for(auto id : idlist)
   //     id->output(level + 4);
}
Type* ExprNode::getType()
{
    return symbolEntry->getType();
}
void DimList::output(int level){
    fprintf(yyout, "%*cdim: ", level, ' ');
    for (int dim : dimensions) {
        fprintf(yyout, "%d   ", dim);
    }
    fprintf(yyout, "\n");
    if(omit == 1)
        fprintf(yyout, "%*comitdimension", level+4, ' ');
}
void ArrDeclStmt::output(int level)
{
    fprintf(yyout, "%*cArrDeclStm ", level, ' ');
    dimList->output(level);
    id->output(level + 4);
}

void IfStmt::output(int level)
{
    fprintf(yyout, "%*cIfStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
}
void WhileStmt::output(int level)
{
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
}

void IfElseStmt::output(int level)
{
    fprintf(yyout, "%*cIfElseStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
    elseStmt->output(level + 4);
}

void ReturnStmt::output(int level)
{
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    retValue->output(level + 4);
}
void BreakStmt::output(int level)
{
    fprintf(yyout, "%*cBreakStmt\n", level, ' ');
 
}
void ContinueStmt::output(int level)
{
    fprintf(yyout, "%*cContinueStmt\n", level, ' ');
   
}
void EmptyStmt::output(int level)
{
    fprintf(yyout, "%*cEmptyStmt\n", level, ' ');
   
}
void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}
void ParamStmt::output(int level)
{
    fprintf(yyout, "%*cParamStmt\n", level, ' ');
    primary->output(level + 4);
}
void ExprStmtNode::addNext(ExprNode* next)
{
    exprList.push_back(next);
}

void ExprStmtNode::output(int level)
{
    fprintf(yyout, "%*cExprStmtNode\n", level, ' ');
    for(auto expr : exprList)
    {
        expr->output(level+4);
    }
}

void FunctionDefParas::output(int level)
{
    fprintf(yyout, "%*cFunctionDefParas\n", level, ' ');
    for(auto para : parameters){
        para->output(level+4);
    }
}
bool Id::isArray()
{
    return getType()->isArray();
}

void FunctionDefParas::addParameter(Id* param)
{
    parameters.push_back(param);
}
std::vector<Type*> FunctionDefParas::getParamsType()
{
    std::vector<Type*> typeArray;
    for(auto param : parameters){
        typeArray.push_back(param->getType());
    }
    return typeArray;
}

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    if(params!=NULL)
        params->output(level+4);
    stmt->output(level + 4);
}
void FuncCall::output(int level)
{
    std::string name, type;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    fprintf(yyout, "%*cFunctionCall function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    if(params != NULL)
    params->output(level+4);
}

void DefNode::output(int level)
{
    std::string constStr = isConst ? "true" : "false";
    std::string arrayStr = isArray ? "true" : "false";
    fprintf(yyout, "%*cDefNode\tisConst:%s\tisArray:%s\n", level, ' ', constStr.c_str(), arrayStr.c_str());
    id->output(level+4);
    if(initVal == nullptr){
        fprintf(yyout, "%*cnull\n", level+4, ' ');
    }
    else{
        initVal->output(level+4);
    }
    if(selectDimList != NULL){
        selectDimList->output(level+4);
    }
}

void UnaryExpr::output(int level)
{
    std::string op_str;
    switch(op)
    {
        case ADD:
            op_str = "positive";  // for unary +
            break;
        case SUB:
            op_str = "negative";  // for unary -
            break;
        case NOT:
            op_str = "not";  // for logical not
            break;
        default:
            op_str = "unknown";
            break;
    }
    fprintf(yyout, "%*cUnaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr->output(level + 4);
}


void Comment::output(int level)
{
    const char *type_str = isBlockComment ? "BlockComment" : "LineComment";
    fprintf(yyout, "%*c%s\tcontent: %s\n", level, ' ', type_str, content.c_str());
}


void ArrayAccessNode:: output(int level) {
    std::string name;
    name = symbolEntry->toStr();
    fprintf(yyout, "%*cArrUse  Arrname: %s\n", level, ' ',name.c_str());
    dimensions->output(level+4);

}
void InitValues::output(int level){
    fprintf(yyout, "%*cInitValues\n", level, ' ');
    for (auto& value : values) {  // 假设 values 是一个存储 InitValueNode 指针的容器
        value->output(level + 4);
    }
}

void InitList::output(int level){
    fprintf(yyout, "%*cInitList\n", level, ' ');
    if (initValues) {  // 假设 initValues 是一个指向 InitValues 对象的指针
        initValues->output(level + 4);
    }
}

void ExpInitValue::output(int level){
    fprintf(yyout, "%*cExpInitValue\n", level, ' ');
    if (expr) {  // 假设 expr 是一个指向 ExprNode 对象的指针
        expr->output(level + 4);
    }
}

void ArrInitDeclStmt::output(int level){
    fprintf(yyout, "%*cArrInitDeclStmt\n", level, ' ');
    id->output(level+4);
    initList->output(level + 4);
}

void  InitValueNode ::output(int level){

}


void ExprStmt:: output(int level){
    fprintf(yyout, "%*cFunCallStmt\n", level, ' ');
    expr->output(level + 4);
}
void ConstUnaryExpr::output(int level)
{
    std::string op_str;
    switch(op)
    {
        case ADD:
            op_str = "positive";  // for unary +
            break;
        case SUB:
            op_str = "negative";  // for unary -
            break;
        case NOT:
            op_str = "not";  // for logical not
            break;
        default:
            op_str = "unknown";
            break;
    }
    fprintf(yyout, "%*cUnaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr->output(level + 4);
}


void ConstBinaryExpr::output(int level)
{
    std::string op_str;
    switch(op)
{
    case ADD: // +
        op_str = "add";
        break;
    case SUB: // -
        op_str = "sub";
        break;
    case MUL: // *
        op_str = "mul";
        break;
    case DIV: // /
        op_str = "div";
        break;
    case MOD: // %
        op_str = "mod";
        break;
    case LOGAND: // &&
        op_str = "logand";
        break;
    case LOGOR: // ||
        op_str = "logor";
        break;
    case NOT: // !
        op_str = "not";
        break;
    

    case EQ: // ==
        op_str = "equal";
        break;
    case GT: // >
        op_str = "greater";
        break;
    case LT: // <
        op_str = "less";
        break;
    case GE: // >=
        op_str = "greater_equal";
        break;
    case LE: // <=
        op_str = "less_equal";
        break;
    case NE: // !=
        op_str = "not_equal";
        break;
    case BITAND : 
        op_str = "bit_and";
        break;
    case BITOR  : 
        op_str = "bit_or";
        break;
    case BITXOR   :
        op_str = "bit_xor";
        break;
    default:
        // 处理默认情况或者错误
        break;
}

    fprintf(yyout, "%*cBinaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}
void ConstId::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();

    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    if(symbolEntry->is_a_const()==1){
            fprintf(yyout, "%*cconstId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
    }
    else{
        fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
    }
    
}
void InitDeclarator::output(int level){
    fprintf(yyout, "%*cInitDeclarator,name :%s\n", level, ' ',name.c_str());
    if(dimList != NULL){
        level+=4;
        fprintf(yyout, "%*cArrInitDeclStmt\n", level, ' ');
        level+=4;
        dimList->output(level);
        if(initList != NULL){
            level+=4;
            initList->output(level);
        }
    }
    else{
        if(expr != NULL){
            level+=4;
            expr->output(level+4);
        }
    }
}
void MultiDecl::output(int level){
    
    fprintf(yyout, "%*cMultiDecl\n", level, ' ');
    for(auto decl : decls){
        decl->output(level+4);
    }
}