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
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    fprintf(yyout, "%*cIntegerLiteral\tvalue: %s\ttype: %s\n", level, ' ',
            value.c_str(), type.c_str());
}

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
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
    id->output(level + 4);
}

void IfStmt::output(int level)
{
    fprintf(yyout, "%*cIfStmt\n", level, ' ');
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

void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    stmt->output(level + 4);
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


