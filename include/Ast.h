#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include <vector>
class SymbolEntry;
class Type;

class Node
{
private:
    static int counter;
    int seq;
public:
    Node();
    int getSeq() const {return seq;};
    virtual void output(int level) = 0;
};
class InitValueNode : public Node {
public:
    void output(int level);
};
class ConstExprNode : public InitValueNode
{
protected:
    SymbolEntry *symbolEntry;
public:
    int interger;
public:
    ConstExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry){};
    ConstExprNode(){};
    ConstExprNode(int interger):interger(interger){};
    void output(int level) {}
};
class ExprNode : public InitValueNode
{
protected:
    SymbolEntry *symbolEntry;
public:
    int interger;
public:
    ExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry){};
    ExprNode(){};
    ExprNode(int interger):interger(interger){};
    Type* getType();
    void output(int level) {}
};

class BinaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr1, *expr2;
public:
    enum {ADD, SUB, MUL, DIV, MOD, LOGAND, LOGOR,BITAND,BITOR,BITXOR, LESS, EQ, GT, LT, GE, LE, NE, NOT};
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : ExprNode(se), op(op), expr1(expr1), expr2(expr2){};
    void output(int level);
};


class UnaryExpr : public ExprNode
{
private:
    int op;  // using the same enum as BinaryExpr
    ExprNode *expr;
public:
    enum {ADD, SUB, MUL, DIV, MOD, AND,  LESS, EQ, GT, LT, GE, LE, NE, NOT};
    UnaryExpr(SymbolEntry *se, int op, ExprNode *expr) : ExprNode(se), op(op), expr(expr) {};
    void output(int level) ;
};

class Comment : public Node
{
private:
    std::string content;
    bool isBlockComment;  // true for block comments, false for line comments
public:
    Comment(const std::string &content, bool isBlock) : content(content), isBlockComment(isBlock) {};
    void output(int level) ;
};







class Constant : public ExprNode , public ConstExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se){};
    Constant(SymbolEntry *se,int interger) : ExprNode(se),ConstExprNode(interger){};
    void output(int level);
};
class StmtNode : public Node
{};
class ExprStmtNode : public StmtNode
{
private:
    std::vector<ExprNode*> exprList;
public:
    ExprStmtNode(){};
    void addNext(ExprNode* next);
    void output(int level);
};
class DimList;
class Id : public ExprNode
{
private:
    ExprStmtNode* Indices;
    DimList * dimList ;
public:
    Id(SymbolEntry *se) : ExprNode(se), Indices(nullptr){};
    Id(SymbolEntry *se,DimList * dimList) : ExprNode(se), Indices(nullptr),dimList(dimList){};
    SymbolEntry* getSymbolEntry() {return symbolEntry;}
    bool isArray();
    void addIndices(ExprStmtNode* idx) {Indices = idx;}
    DimList* getdims(){return dimList;}
    void output(int level);
};

class ConstId : public ConstExprNode
{
public:
    ConstId(SymbolEntry *se) : ConstExprNode(se){};
    void output(int level);
};


class CompoundStmt : public StmtNode
{
private:
    StmtNode *stmt;
public:
    CompoundStmt(StmtNode *stmt) : stmt(stmt) {};
 
    void output(int level);
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
};
class ExpInitValue;
class DefNode : public StmtNode
{
private:
    bool isConst;
    bool isArray;
    Id* id;
    Node* initVal;//对于非数组，是ExprNode；对于数组，是InitValueNode
public:
    DimList * selectDimList;
    DefNode(Id* id, Node* initVal, bool isConst, bool isArray) : 
        isConst(isConst), isArray(isArray), id(id), initVal(initVal){};
        DefNode(Id* id, Node* initVal, bool isConst, bool isArray,DimList * selectDimList) : 
        isConst(isConst), isArray(isArray), id(id), initVal(initVal),selectDimList(selectDimList){};
    Id* getId() {return id;}
    void output(int level);
};


class DimList : public Node {
public:
    bool omit;
    std::vector<int> dimensions;
    std::vector<ExprNode*>dims;
    DimList(){}
    DimList(int initialDim) {
        dimensions.push_back(initialDim);
    }
    DimList(ExprNode* expr){
        dims.push_back(expr);
    }
    void addDims(ExprNode* expr) {
        dims.push_back(expr);
    }
    void addDimension(int dim) {
        dimensions.push_back(dim);
    }

    void output(int level) ;
};
// 修改 Ast.h 中的 ArrDeclStmt 类定义

class ArrDeclStmt : public StmtNode {
public:
    Id *id;
    DimList *dimList;

    ArrDeclStmt(Id *id, DimList *dimList) : id(id), dimList(dimList) {}

    void output(int level) ;

};


class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
};
class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    WhileStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
};

class IfElseStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
    StmtNode *elseStmt;
public:
    IfElseStmt(ExprNode *cond, StmtNode *thenStmt, StmtNode *elseStmt) : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {};
    void output(int level);
};

class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
    ConstExprNode * constretValue;
public:
    ReturnStmt(ExprNode*retValue) : retValue(retValue) {};
    ReturnStmt(ConstExprNode*retValue) : constretValue(retValue) {};
    void output(int level);
};


class BreakStmt : public StmtNode
{
private:
   
public:
    BreakStmt() {};
    void output(int level);
};
class ContinueStmt : public StmtNode
{
private:

public:
    ContinueStmt() {};
    void output(int level);
};
class EmptyStmt : public StmtNode
{
private:

public:
    EmptyStmt() {};
    void output(int level);
};
class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr) {};
    void output(int level);
};
class ParamStmt : public StmtNode
{
private:
    ExprNode *primary;
public:
    ParamStmt(ExprNode *primary) : primary(primary){}
    void output(int level);
};
class FunctionDefParas:public StmtNode{
private:
    std::vector<Id*> parameters; // A vector to hold pointers to Id nodes, representing function parameters.
public:
    // Default constructor
    FunctionDefParas(){};
    // Add a parameter to the function parameters list
    void addParameter(Id* param);
    std::vector<Type*> getParamsType();
    // Output the parameter list (implementation can vary based on requirements)
    void output(int level) ;
};
class FunctionDef : public StmtNode
{
private:
    SymbolEntry *se;
    FunctionDefParas *params;
    StmtNode *stmt;
public:
    FunctionDef(SymbolEntry *se, FunctionDefParas *params, StmtNode *stmt) : se(se), params(params), stmt(stmt){};
    void output(int level);
};


class FuncCall : public ExprNode
{
private:
    //ArgsList *args; // 指向实参列表的指针，即便是空的调用，也可以用nullptr表示没有参数
    FunctionDefParas *params;
public:
    // 构造函数，用于不带参数的函数调用
    FuncCall(SymbolEntry *se) :ExprNode(se){};
    FuncCall(SymbolEntry *se,FunctionDefParas *params) :ExprNode(se),params(params){};
    void output(int level);
    
};
class ExprStmt : public StmtNode
{
private:
    ExprNode *expr;
    //ArgsList *args; // 指向实参列表的指针，即便是空的调用，也可以用nullptr表示没有参数

public:
    // 构造函数，用于不带参数的函数调用
    ExprStmt(ExprNode *expr) : expr(expr){};
    void output(int level);
    
};
class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
};




class IoStmt : public StmtNode
{
private:
    enum IoType { INPUT, OUTPUT } type;
    ExprNode *expr;  // The expression to be input/output
public:
    IoStmt(IoType t, ExprNode *e) : type(t), expr(e) {};
    void output(int level) {}
};


// 假设 ExprNode 是表达式的基类
class ArrayAccessNode : public ExprNode {
private:
    DimList* dimensions;

public:
    ArrayAccessNode(SymbolEntry * se, DimList* dimensions)
        : ExprNode(se), dimensions(dimensions) {}

    // 访问数组名

    // 访问维度列表
    DimList* getDimensions() const { return dimensions; }
    void output(int level) ;
    // 这里还需要定义其他的函数，比如虚拟析构函数，输出函数等
};


class InitValues : public Node {
private:
    std::vector<InitValueNode*> values;
public:
    InitValues() = default;
    explicit InitValues(InitValueNode* value) { values.push_back(value); }
    void addValue(InitValueNode* value) { values.push_back(value); }
    const std::vector<InitValueNode*>& getValues() const { return values; }
    void output(int level) override;
    // ... 可能还需要其他成员函数 ...
};

class InitList : public InitValueNode  {
private:
    InitValues* initValues;
public:
    // 可能的构造函数，用于不同情况的初始化列表
    InitList() : initValues(new InitValues()) {}

    // 用于非空初始化列表的构造函数
    InitList(InitValues* initValues) : initValues(initValues) {}

    InitValues* getInitValues() const { return initValues; }

    void output(int level) ;
};


class ExpInitValue : public InitValueNode {
private:
    ExprNode* expr;  // 用于存储表达式节点

public:
    explicit ExpInitValue(ExprNode* expr) : expr(expr) {}  // 构造函数

    // 获取存储的表达式节点
    ExprNode* getExpr() const { return expr; }

    // 重载输出函数，用于输出表达式初始化值的信息
    void output(int level);

};

class ArrInitDeclStmt : public StmtNode {
public:
    Id *id;               // 指向数组名称的指针
    DimList *dimList;     // 指向数组维度列表的指针
    InitList *initList;   // 指向初始化列表的指针

    // 构造函数
    ArrInitDeclStmt(Id *id, DimList *dimList, InitList *initList)
        : id(id), dimList(dimList), initList(initList) {}

    // 输出函数（需实现，与 ArrDeclStmt 类似）
    void output(int level);

};




class ConstBinaryExpr : public ConstExprNode
{
private:
    int op;
    ConstExprNode *expr1, *expr2;
public:
    enum {ADD, SUB, MUL, DIV, MOD, LOGAND, LOGOR,BITAND,BITOR,BITXOR, LESS, EQ, GT, LT, GE, LE, NE, NOT};
    ConstBinaryExpr(SymbolEntry *se, int op, ConstExprNode*expr1, ConstExprNode*expr2) : ConstExprNode(se), op(op), expr1(expr1), expr2(expr2){};
    void output(int level);
};


class ConstUnaryExpr : public ConstExprNode
{
private:
    int op;  // using the same enum as BinaryExpr
    ConstExprNode *expr;
public:
    enum {ADD, SUB, MUL, DIV, MOD, AND,  LESS, EQ, GT, LT, GE, LE, NE, NOT};
    ConstUnaryExpr(SymbolEntry *se, int op, ConstExprNode *expr) : ConstExprNode(se), op(op), expr(expr) {};
    void output(int level) ;
};

class InitDeclarator: public StmtNode
{
private:
    ExpInitValue* expr;
    InitList *initList;  
    std::string name;
    DimList *dimList;
  
public:
    InitDeclarator(ExpInitValue*expr,std::string name):expr(expr),name(name){}
    InitDeclarator(std::string name):name(name){}
    InitDeclarator(std::string name,DimList *dimList):name(name),dimList(dimList){}
    InitDeclarator(InitList *initList,std::string name,DimList *dimList):initList(initList),name(name),dimList(dimList){}
    void output(int level) ;
    std::string getname(){return name;}
    DimList * getdimList(){return dimList;}


};
class MultiDecl: public StmtNode
{

public:
    std::vector<InitDeclarator*> decls;
public:
    MultiDecl(InitDeclarator * decl){decls.push_back(decl);}
    MultiDecl(){}
    void addname(InitDeclarator * decl){decls.push_back(decl);}
    void output(int level) ;
};
class DeclStmt : public StmtNode
{
private:
    MultiDecl* decls;
    std::vector<Id *> idlist;
public:
    DeclStmt(Id *id) {idlist.push_back(id);}
    DeclStmt(std::vector<Id *> idlist ,MultiDecl* decls) :decls(decls),idlist(idlist){}
    void output(int level);
};
#endif
