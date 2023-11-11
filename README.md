# 2023lab4-构造语法分析器
For 2023Fall NKUCS Course - Principle of Compilers Lab4

> Author: Emanual20 YoungCoder
> 
> Date: 2023/9/15

## 编译器命令
```
Usage：build/compiler [options] infile
Options:
    -o <file>   Place the output into <file>.
    -t          Print tokens.
```

## Makefile使用

* 修改测试路径：

默认测试路径为test，你可以修改为任意要测试的路径。我们已将最终所有测试样例分级上传。

如：要测试level1-1下所有sy文件，可以将makefile中的

```
TEST_PATH ?= test
```

修改为

```
TEST_PATH ?= test/level1-1
```

* 编译：

```
    make
```
编译出我们的编译器。

* 运行：
```
    make run
```
以example.sy文件为输入，输出相应的语法分析结果到example.ast文件中。

* 测试：
```
    make testlab4
```
该命令会默认搜索test目录下所有的.sy文件，逐个输入到编译器中，生成相应的语法分析结果.ast文件到test目录中。你还可以指定测试目录：
```
    make testlab4 TEST_PATH=dirpath
```

* 清理:
```
    make clean
```
清除所有可执行文件和测试输出。

### 分工说明

刘诺铭同学负责的部分主要是：

- 函数相关：包括函数声明、函数定义、函数调用、函数使用（可以支持将一个函数调用当作表达式来用）以及函数参数的处理（支持多种函数参数的形式）
- 数组相关：包括数组定义、声明、数组的使用以及多维数组，还支持多种数组下标的类型
- 初始化列表的使用，可以支持几乎所有方式的初始化当时，包括大括号、多个变量连续定义的等方式
- 多种声明语句的支持

赵廷枫同学主要负责的部分是：

- 运行时库的支持
- 浮点数的支持以及浮点数的运算、赋值、比较等功能
- 注释功能（包括单行注释以及块注释）
- 多种功能语句的编写：主要是if else语句，continue语句、break语句、while语句、for循环语句等关键语句
- 支持全部类型的数值运算、逻辑运算、关系运算

### 数据结构说明

好的，我会详细解释 `parser.y` 和 `Ast.h` 中定义的数据结构。

### `parser.y` 文件中的数据结构

#### 符号联合（%union）
在 `parser.y` 中，`%union` 定义了 Bison 解析器使用的数据类型。这些类型对应于语法分析过程中识别的不同元素。例如：
- `int itype`：整数类型。
- `float ftype`：浮点数类型。
- `char* strtype`：字符串类型，用于存储词素。
- `StmtNode* stmttype`：语句节点类型。
- `ExprNode* exprtype`：表达式节点类型。
- `ConstExprNode* constexprtype`：常量表达式节点类型。
- `Type* type`：类型节点，用于表示数据类型。
- `DimList* dimList`：维度列表，用于数组类型。
- `InitList* initList`：初始化列表。
- `InitValues* initValues`：初始化值。
- `InitValueNode* initValueNode`：初始化值节点。
- `FuncCall* funcUse`：函数调用。
- `InitDeclarator* initDeclarator`：初始化声明符。
- `MultiDecl* multiDecl`：多重声明。

### `Ast.h` 文件中的数据结构

#### 基础节点（Node）
- `Node` 是所有 AST 节点的基类，包含一个序列号 `seq` 和一个纯虚函数 `output`，用于输出节点信息。

#### 表达式节点（ExprNode）
- `ExprNode` 是所有表达式节点的基类，包含一个 `SymbolEntry` 指针和整数值 `interger`。它派生出 `BinaryExpr` 和 `UnaryExpr` 等。
- `BinaryExpr` 表示二元表达式，包含操作符 `op`、两个子表达式 `expr1` 和 `expr2`。
- `UnaryExpr` 表示一元表达式，包含操作符 `op` 和一个子表达式 `expr`。

#### 语句节点（StmtNode）
- `StmtNode` 是所有语句节点的基类。
- `ExprStmtNode` 表示表达式语句，包含一个表达式列表 `exprList`。
- `CompoundStmt` 表示复合语句，包含一个子语句 `stmt`。
- `SeqNode` 表示顺序节点，包含两个子语句 `stmt1` 和 `stmt2`。
- `AssignStmt` 表示赋值语句，包含左值 `lval` 和表达式 `expr`。
- `IfStmt`、`WhileStmt` 和 `IfElseStmt` 分别表示 if 语句、while 循环和 if-else 语句。

#### 其他重要节点
- `Id` 表示标识符，包含一个 `SymbolEntry` 指针和可选的维度列表 `dimList`。
- `ConstId` 表示常量标识符。
- `DimList` 表示维度列表，用于数组类型。
- `InitDeclarator` 和 `MultiDecl` 分别表示初始化声明符和多重声明。
- `DeclStmt` 表示声明语句，包含声明列表 `decls`。
- `FunctionDef` 表示函数定义，包含符号条目 `se`、参数列表 `params` 和语句 `stmt`。

#### 常量表达式节点（ConstExprNode）
- `ConstExprNode` 是常量表达式的基类，包含一个指向 `SymbolEntry` 的指针和一个整数值 `interger`，用于表示常量值。

#### 二元表达式节点（BinaryExpr）
- `BinaryExpr` 用于表示二元运算，例如加法、减法、乘法等。它包含一个操作符 `op` 和两个表达式子节点 `expr1` 和 `expr2`。这个类用于构建诸如算术和逻辑运算的复杂表达式。

#### 一元表达式节点（UnaryExpr）
- `UnaryExpr` 表示一元运算，例如取反。它包含一个操作符 `op` 和一个子表达式 `expr`。这个类用于构建单个操作符作用于一个表达式的情况。

#### 标识符节点（Id）
- `Id` 表示源代码中的标识符，如变量名。它包含一个指向 `SymbolEntry` 的指针和一个维度列表 `dimList`（对于数组类型的变量）。

#### 维度列表节点（DimList）
- `DimList` 用于表示数组的维度信息。它包含一个维度数组 `dimensions`，每个元素表示数组的一个维度大小。

#### 初始化声明符节点（InitDeclarator）
- `InitDeclarator` 用于表示变量的初始化声明，例如在变量声明时提供的初始值。它可以包含一个表达式 `expr` 或一个初始化列表 `initList`，以及变量名 `name` 和维度信息 `dimList`。

#### 多重声明节点（MultiDecl）
- `MultiDecl` 用于表示多个变量的声明，例如在同一行中声明多个变量。它包含一个 `InitDeclarator` 类型的列表 `decls`。

#### 声明语句节点（DeclStmt）
- `DeclStmt` 用于表示变量声明的语句。它包含一个多重声明节点 `decls` 和一个标识符列表 `idlist`。

#### 函数定义节点（FunctionDef）
- `FunctionDef` 用于表示函数定义。它包含一个指向 `SymbolEntry` 的指针 `se`，表示函数的符号条目，一个参数列表 `params` 和一个函数体语句 `stmt`。

#### 函数调用节点（FuncCall）
- `FuncCall` 表示函数调用表达式。它包含一个指向 `SymbolEntry` 的指针，表示被调用的函数，和一个参数列表 `params`，表示传递给函数的实参。

#### 初始化值节点（InitValueNode）
- `InitValueNode` 是初始化值的基类，用于表示变量初始化时的值。它是其他初始化相关节点的基类。

#### 初始化列表节点（InitList）
- `InitList` 用于表示复杂的初始化，如数组或结构体的初始化。它包含一个初始化值节点的列表 `initValues`。

#### 表达式初始化值节点（ExpInitValue）
- `ExpInitValue` 表示以表达式形式给出的初始化值，包含一个表达式节点 `expr`。



