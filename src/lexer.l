%option noyywrap
%option nounput
%option noinput
%top{
    #include <stdarg.h>
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "common.h"
    #include "parser.h"
}
%{
    extern dump_type_t dump_type;

    inline void dump_tokens(const char* format, ...){
        va_list args;
        va_start(args, format);
        if (dump_type == TOKENS)
            vfprintf(yyout, format, args);
        va_end(args);
    }


%}


FLONUM   [0-9]*\.[0-9]+([eE][-+]?[0-9]+)?|[0-9]+[eE][-+]?[0-9]+|0[xX][0-9a-fA-F]*\.[0-9a-fA-F]+([pP][-+]?[0-9]+)?

DECIMIAL ([1-9][0-9]*|0)
OCT     0[0-7]+
HEX     0[xX][0-9a-fA-F]+





IF      if
ELSE    else
WHILE   while
RETURN  return

ALIGNAS     alignas
ALIGNOF     alignof
AUTO        auto
BOOL        bool
BREAK       break
CASE        case
CATCH       catch
CHAR        char
CHAR8_T     char8_t    
CHAR16_T    char16_t
CHAR32_T    char32_t
CLASS       class
CONST       const
CONSTEXPR   constexpr
CONST_CAST  const_cast
CONTINUE    continue
DECLTYPE    decltype
DEFAULT     default
DELETE      delete
DO          do
DOUBLE      double
DYNAMIC_CAST dynamic_cast
ENUM        enum
EXPLICIT    explicit
EXPORT      export   
EXTERN      extern
FALSE       false
FLOAT       "float"
FOR         for
FRIEND      friend
GOTO        goto
INLINE      inline
INT         "int"
LONG        long
MUTABLE     mutable
NAMESPACE   namespace
NEW         new
NOEXCEPT    noexcept
NULLPTR     nullptr
OPERATOR    operator
PRIVATE     private
PROTECTED   protected
PUBLIC      public
REGISTER    register  
REINTERPRET_CAST reinterpret_cast
REQUIRES    requires  
SHORT       short
SIGNED      signed
SIZEOF      sizeof
STATIC      static
STATIC_ASSERT static_assert
STATIC_CAST  static_cast
STRUCT      struct
SWITCH      switch
TEMPLATE    template
THIS        this
THREAD_LOCAL thread_local
THROW       throw
TRUE        true
TRY         try
TYPEDEF     typedef
TYPEID      typeid
TYPENAME    typename
UNION       union
UNSIGNED    unsigned
USING       using
VIRTUAL     virtual
VOID        void
VOLATILE    volatile


ID [[:alpha:]_][[:alpha:][:digit:]_]*
EOL (\r\n|\n|\r)
WHITE [\t ]


EQ      ==
NE      !=
LT      <
LE      <=
GT      >
GE      >=



ASSIGN           "="
PLUSASSIGN       "+="
MINUSASSIGN      "-="
MULTASSIGN       "*="
DIVASSIGN        "/="
MODASSIGN        "%="
ANDASSIGN        "&="
ORASSIGN         "|="
XORASSIGN        "^="
LSHIFTASSIGN     "<<="
RSHIFTASSIGN     ">>="
INCREMENT        "++"
DECREMENT        "--"

BITAND           "&"
BITOR            "|"
BITXOR           "^"
BITNOT           "~"
LSHIFT           "<<"
RSHIFT           ">>"

LOGAND           "&&"
LOGOR            "||"
NOT              "!"



%%
    /* rules section */




{IF} {
    dump_tokens("IF\t%s\n", yytext);
    return IF;
}

{ELSE} {
    dump_tokens("ELSE\t%s\n", yytext);
    return ELSE;
}

{RETURN} {
    dump_tokens("RETURN\t%s\n", yytext);
    return RETURN;
}

{WHILE} {
    dump_tokens("WHILE\t%s\n", yytext);
    return WHILE;
}

{ALIGNAS} {
    dump_tokens("ALIGNAS\t%s\n", yytext);
    return ALIGNAS;
}

{ALIGNOF} {
    dump_tokens("ALIGNOF\t%s\n", yytext);
    return ALIGNOF;
}

{AUTO} {
    dump_tokens("AUTO\t%s\n", yytext);
    return AUTO;
}

{BOOL} {
    dump_tokens("BOOL\t%s\n", yytext);
    return BOOL;
}

{BREAK} {
    dump_tokens("BREAK\t%s\n", yytext);
    return BREAK;
}

{CASE} {
    dump_tokens("CASE\t%s\n", yytext);
    return CASE;
}

{CATCH} {
    dump_tokens("CATCH\t%s\n", yytext);
    return CATCH;
}

{CHAR} {
    dump_tokens("CHAR\t%s\n", yytext);
    return CHAR;
}

{CHAR8_T} {
    dump_tokens("CHAR8_T\t%s\n", yytext);
    return CHAR8_T;
}

{CHAR16_T} {
    dump_tokens("CHAR16_T\t%s\n", yytext);
    return CHAR16_T;
}

{CHAR32_T} {
    dump_tokens("CHAR32_T\t%s\n", yytext);
    return CHAR32_T;
}

{CLASS} {
    dump_tokens("CLASS\t%s\n", yytext);
    return CLASS;
}

{CONST} {
    dump_tokens("CONST\t%s\n", yytext);
    return CONST;
}

{CONSTEXPR} {
    dump_tokens("CONSTEXPR\t%s\n", yytext);
    return CONSTEXPR;
}

{CONST_CAST} {
    dump_tokens("CONST_CAST\t%s\n", yytext);
    return CONST_CAST;
}

{CONTINUE} {
    dump_tokens("CONTINUE\t%s\n", yytext);
    return CONTINUE;
}

{DECLTYPE} {
    dump_tokens("DECLTYPE\t%s\n", yytext);
    return DECLTYPE;
}

{DEFAULT} {
    dump_tokens("DEFAULT\t%s\n", yytext);
    return DEFAULT;
}

{DELETE} {
    dump_tokens("DELETE\t%s\n", yytext);
    return DELETE;
}

{DO} {
    dump_tokens("DO\t%s\n", yytext);
    return DO;
}

{DOUBLE} {
    dump_tokens("DOUBLE\t%s\n", yytext);
    return DOUBLE;
}

{DYNAMIC_CAST} {
    dump_tokens("DYNAMIC_CAST\t%s\n", yytext);
    return DYNAMIC_CAST;
}

{ENUM} {
    dump_tokens("ENUM\t%s\n", yytext);
    return ENUM;
}

{EXPLICIT} {
    dump_tokens("EXPLICIT\t%s\n", yytext);
    return EXPLICIT;
}

{EXPORT} {
    dump_tokens("EXPORT\t%s\n", yytext);
    return EXPORT;
}

{EXTERN} {
    dump_tokens("EXTERN\t%s\n", yytext);
    return EXTERN;
}

{FALSE} {
    dump_tokens("FALSE\t%s\n", yytext);
    return FALSE;
}

{FLOAT} {
    dump_tokens("FLOAT\t%s\n", yytext);
    return FLOAT;
}

{FOR} {
    dump_tokens("FOR\t%s\n", yytext);
    return FOR;
}

{FRIEND} {
    dump_tokens("FRIEND\t%s\n", yytext);
    return FRIEND;
}

{GOTO} {
    dump_tokens("GOTO\t%s\n", yytext);
    return GOTO;
}

{INLINE} {
    dump_tokens("INLINE\t%s\n", yytext);
    return INLINE;
}

{INT} {
    dump_tokens("INT\t%s\n", yytext);
    return INT;
}

{LONG} {
    dump_tokens("LONG\t%s\n", yytext);
    return LONG;
}

{MUTABLE} {
    dump_tokens("MUTABLE\t%s\n", yytext);
    return MUTABLE;
}

{NAMESPACE} {
    dump_tokens("NAMESPACE\t%s\n", yytext);
    return NAMESPACE;
}

{NEW} {
    dump_tokens("NEW\t%s\n", yytext);
    return NEW;
}

{NOEXCEPT} {
    dump_tokens("NOEXCEPT\t%s\n", yytext);
    return NOEXCEPT;
}

{NULLPTR} {
    dump_tokens("NULLPTR\t%s\n", yytext);
    return NULLPTR;
}

{OPERATOR} {
    dump_tokens("OPERATOR\t%s\n", yytext);
    return OPERATOR;
}

{PRIVATE} {
    dump_tokens("PRIVATE\t%s\n", yytext);
    return PRIVATE;
}

{PROTECTED} {
    dump_tokens("PROTECTED\t%s\n", yytext);
    return PROTECTED;
}

{PUBLIC} {
    dump_tokens("PUBLIC\t%s\n", yytext);
    return PUBLIC;
}


{REGISTER} {
    dump_tokens("REGISTER\t%s\n", yytext);
    return REGISTER;
}

{REINTERPRET_CAST} {
    dump_tokens("REINTERPRET_CAST\t%s\n", yytext);
    return REINTERPRET_CAST;
}

{REQUIRES} {
    dump_tokens("REQUIRES\t%s\n", yytext);
    return REQUIRES;
}

{SHORT} {
    dump_tokens("SHORT\t%s\n", yytext);
    return SHORT;
}

{SIGNED} {
    dump_tokens("SIGNED\t%s\n", yytext);
    return SIGNED;
}

{SIZEOF} {
    dump_tokens("SIZEOF\t%s\n", yytext);
    return SIZEOF;
}

{STATIC} {
    dump_tokens("STATIC\t%s\n", yytext);
    return STATIC;
}

{STATIC_ASSERT} {
    dump_tokens("STATIC_ASSERT\t%s\n", yytext);
    return STATIC_ASSERT;
}

{STATIC_CAST} {
    dump_tokens("STATIC_CAST\t%s\n", yytext);
    return STATIC_CAST;
}

{STRUCT} {
    dump_tokens("STRUCT\t%s\n", yytext);
    return STRUCT;
}

{SWITCH} {
    dump_tokens("SWITCH\t%s\n", yytext);
    return SWITCH;
}

{TEMPLATE} {
    dump_tokens("TEMPLATE\t%s\n", yytext);
    return TEMPLATE;
}

{THIS} {
    dump_tokens("THIS\t%s\n", yytext);
    return THIS;
}

{THREAD_LOCAL} {
    dump_tokens("THREAD_LOCAL\t%s\n", yytext);
    return THREAD_LOCAL;
}

{THROW} {
    dump_tokens("THROW\t%s\n", yytext);
    return THROW;
}

{TRUE} {
    dump_tokens("TRUE\t%s\n", yytext);
    return TRUE;
}

{TRY} {
    dump_tokens("TRY\t%s\n", yytext);
    return TRY;
}

{TYPEDEF} {
    dump_tokens("TYPEDEF\t%s\n", yytext);
    return TYPEDEF;
}

{TYPEID} {
    dump_tokens("TYPEID\t%s\n", yytext);
    return TYPEID;
}

{TYPENAME} {
    dump_tokens("TYPENAME\t%s\n", yytext);
    return TYPENAME;
}

{UNION} {
    dump_tokens("UNION\t%s\n", yytext);
    return UNION;
}

{UNSIGNED} {
    dump_tokens("UNSIGNED\t%s\n", yytext);
    return UNSIGNED;
}

{USING} {
    dump_tokens("USING\t%s\n", yytext);
    return USING;
}

{VIRTUAL} {
    dump_tokens("VIRTUAL\t%s\n", yytext);
    return VIRTUAL;
}

{VOID} {
    dump_tokens("VOID\t%s\n", yytext);
    return VOID;
}

{VOLATILE} {
    dump_tokens("VOLATILE\t%s\n", yytext);
    return VOLATILE;
}

{ASSIGN} {
    dump_tokens("ASSIGN\t%s\n", yytext);
    return ASSIGN;
}

{PLUSASSIGN} {
    dump_tokens("PLUSASSIGN\t%s\n", yytext);
    return PLUSASSIGN;
}

{MINUSASSIGN} {
    dump_tokens("MINUSASSIGN\t%s\n", yytext);
    return MINUSASSIGN;
}

{MULTASSIGN} {
    dump_tokens("MULTASSIGN\t%s\n", yytext);
    return MULTASSIGN;
}

{DIVASSIGN} {
    dump_tokens("DIVASSIGN\t%s\n", yytext);
    return DIVASSIGN;
}

{MODASSIGN} {
    dump_tokens("MODASSIGN\t%s\n", yytext);
    return MODASSIGN;
}

{ANDASSIGN} {
    dump_tokens("ANDASSIGN\t%s\n", yytext);
    return ANDASSIGN;
}

{ORASSIGN} {
    dump_tokens("ORASSIGN\t%s\n", yytext);
    return ORASSIGN;
}

{XORASSIGN} {
    dump_tokens("XORASSIGN\t%s\n", yytext);
    return XORASSIGN;
}

{LSHIFTASSIGN} {
    dump_tokens("LSHIFTASSIGN\t%s\n", yytext);
    return LSHIFTASSIGN;
}

{RSHIFTASSIGN} {
    dump_tokens("RSHIFTASSIGN\t%s\n", yytext);
    return RSHIFTASSIGN;
}

{INCREMENT} {
    dump_tokens("INCREMENT\t%s\n", yytext);
    return INCREMENT;
}

{DECREMENT} {
    dump_tokens("DECREMENT\t%s\n", yytext);
    return DECREMENT;
}

{BITAND} {
    dump_tokens("BITAND\t%s\n", yytext);
    return BITAND;
}

{BITOR} {
    dump_tokens("BITOR\t%s\n", yytext);
    return BITOR;
}

{BITXOR} {
    dump_tokens("BITXOR\t%s\n", yytext);
    return BITXOR;
}

{BITNOT} {
    dump_tokens("BITNOT\t%s\n", yytext);
    return BITNOT;
}

{LSHIFT} {
    dump_tokens("LSHIFT\t%s\n", yytext);
    return LSHIFT;
}

{RSHIFT} {
    dump_tokens("RSHIFT\t%s\n", yytext);
    return RSHIFT;
}

{LOGAND} {
    dump_tokens("LOGAND\t%s\n", yytext);
    return LOGAND;
}

{LOGOR} {
    dump_tokens("LOGOR\t%s\n", yytext);
    return LOGOR;
}

{NOT} {
    dump_tokens("NOT\t%s\n", yytext);
    return NOT;
}

{LT} {
    dump_tokens("LT\t%s\n", yytext);
    return LT;
}
{EQ} {
    dump_tokens("EQ\t%s\n", yytext);
    return EQ;
}

{NE} {
    dump_tokens("NE\t%s\n", yytext);
    return NE;
}

{LE} {
    dump_tokens("LE\t%s\n", yytext);
    return LE;
}

{GT} {
    dump_tokens("GT\t%s\n", yytext);
    return GT;
}

{GE} {
    dump_tokens("GE\t%s\n", yytext);
    return GE;
}





"+" {
    dump_tokens("ADD\t%s\n", yytext);
    return ADD;
}
"-" {

    dump_tokens("SUB\t%s\n", yytext);
    return SUB;
}
"*" {
    dump_tokens("MUL\t%s\n", yytext);
    return MUL;
}
"/" {
    dump_tokens("DIV\t%s\n", yytext);
    return DIV;
}
"%" {
    dump_tokens("MOD\t%s\n", yytext);
    return MOD;
}

";" {
    dump_tokens("SEMICOLON\t%s\n", yytext);
    return SEMICOLON;
}

"(" {
    dump_tokens("LPAREN\t%s\n", yytext);
    return LPAREN;
}

")" {
    dump_tokens("RPAREN\t%s\n", yytext);
    return RPAREN;
}

"{" {
    dump_tokens("LBRACE\t%s\n", yytext);
    return LBRACE;
}

"}" {
    dump_tokens("RBRACE\t%s\n", yytext);
    return RBRACE;
}

{DECIMIAL} {
    int decimal;
    decimal = atoi(yytext);
    dump_tokens("DECIMAL\t%s\t%d\n", yytext, decimal);
    yylval.itype = decimal;
    return INTEGER;
}


{ID} {
    char *lexeme;
    dump_tokens("ID\t%s\n", yytext);
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    return ID;
}












