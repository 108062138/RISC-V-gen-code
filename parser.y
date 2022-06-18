%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbolTable.c"

char* _SCALAR_LEFT = "<scalar_decl>";
char* _SCALAR_RIGHT = "</scalar_decl>";
char* _ARRAY_LEFT = "<array_decl>";
char* _ARRAY_RIGHT = "</array_decl>";
char* _FUNC_DECL_LEFT = "<func_decl>";
char* _FUNC_DECL_RIGHT = "</func_decl>";
char* _FUNCT_DEF_LEFT = "<func_def>";
char* _FUNCT_DEF_RIGHT = "</func_def>";
char* _EXPR_LEFT = "<expr>";
char* _EXPR_RIGHT = "</expr>";
char* _STMT_LEFT = "<stmt>";
char* _STMT_RIGHT = "</stmt>";

FILE* codegen;

//it convert an int to string
char* intToString(int x) {
    int y = x;
    int l = 1;
    while (y > 9) {
        y /= 10;
        l += 1;
    }
    char* t = malloc(sizeof(char) * l);
    sprintf(t, "%d", x);
    return t;
}
char* doubleToString(double x) {
    char* s = malloc(sizeof(char) * 30);
    sprintf(s, "%f", x);
    return s;
}
char* reserveStr(int size){
    char* s = malloc(sizeof(char)*(size+30)); strcpy(s,"");
    return s;
}
void setScopeAndOffsetOfParam(char* s){
    int i,j,index;
    int totalArg;
    index = lookUpSymbol(s);
    if(index<0) perror("part C fuck up");
    else{
        table[index].type = T_FUNCTION;
        totalArg = curCounter - index - 1;
        table[index].totalArg = totalArg;
        for(j=totalArg,i=curCounter-1;i>index;i--,j--){
            table[i].scope = curScope;
            table[i].offset = j;
            table[i].mode = ARGUMENT_MODE;
        }
    }
}

void codeGenFuncHeader(char *functor)//modify this when I am going to implement level A
{
    fprintf(codegen, "%s:\n", functor);
    fprintf(codegen, "  // BEGIN PROLOGUE\n");
    fprintf(codegen,"addi sp, sp, -104\n");
    fprintf(codegen,"sd sp, 96(sp)    \n");
    fprintf(codegen,"sd s0, 88(sp)    \n");
    fprintf(codegen,"sd s1, 80(sp)    \n");
    fprintf(codegen,"sd s2, 72(sp)    \n");
    fprintf(codegen,"sd s3, 64(sp)    \n");
    fprintf(codegen,"sd s4, 56(sp)    \n");
    fprintf(codegen,"sd s5, 48(sp)    \n");
    fprintf(codegen,"sd s6, 40(sp)    \n");
    fprintf(codegen,"sd s7, 32(sp)    \n");
    fprintf(codegen,"sd s8, 24(sp)    \n");
    fprintf(codegen,"sd s9, 16(sp)    \n");
    fprintf(codegen,"sd s10, 8(sp)    \n");
    fprintf(codegen,"sd s11, 0(sp)    \n");
    fprintf(codegen,"addi s0, sp, 104 \n");
    fprintf(codegen, "  // END PROLOGUE\n");
    fprintf(codegen, "  \n");
}

void codeGenAtEndOfFunctionBody(char* functor){
    fprintf(codegen,"// BEGIN EPILOGUE: restore callee-saved registers                              \n");
    fprintf(codegen,"// note that here we assume that the stack is properly maintained, which means \n");   
    fprintf(codegen,"// $sp should point to the same address as when the function prologue exits    \n");    
    fprintf(codegen,"ld sp, 96(sp)                                                                  \n");    
    fprintf(codegen,"ld s0, 88(sp)                                                                  \n");    
    fprintf(codegen,"ld s1, 80(sp)                                                                  \n");    
    fprintf(codegen,"ld s2, 72(sp)                                                                  \n");    
    fprintf(codegen,"ld s3, 64(sp)                                                                  \n");    
    fprintf(codegen,"ld s4, 56(sp)                                                                  \n");    
    fprintf(codegen,"ld s5, 48(sp)                                                                  \n");    
    fprintf(codegen,"ld s6, 40(sp)                                                                  \n");    
    fprintf(codegen,"ld s7, 32(sp)                                                                  \n");    
    fprintf(codegen,"ld s8, 24(sp)                                                                  \n");    
    fprintf(codegen,"ld s9, 16(sp)                                                                  \n");    
    fprintf(codegen,"ld s10, 8(sp)                                                                  \n");    
    fprintf(codegen,"ld s11, 0(sp)                                                                  \n");    
    fprintf(codegen,"addi sp, sp, 104                                                               \n");   
    fprintf(codegen,"// END EPILOGUE                                                                \n");   

    fprintf(codegen,"jalr zero, 0(ra)\n");   
}
%}

%union { 
    int iVal;
    double dVal;
    char* sVal;
}

%token <iVal> INT
%token <sVal> MYCHAR MYSTRING MYNULL
%token <dVal> DOUBLE
//KEY-TYPE
%token <sVal> INTTYPE CHARTYPE STRINGTYPE DOUBLETYPE FLOATTYPE CONSTTYPE SIGNEDTYPE UNSIGNEDTYPE LONGLONGTYPE LONGTYPE SHORTTYPE VOIDTYPE CHAR4TYPE CHAR8TYPE
//KEY GRAM..
%token <sVal> RETURN BREAK CONTINUE FOR WHILE DO SWITCH CASE DEFAULT IF ELSE
%token <sVal> IDENT
%token <sVal> CODEGEN DIGITALWRITE DELAY
%left INT
%left MYCHAR MYSTRING MYNULL
%left DOUBLE
%left INTTYPE CHARTYPE STRINGTYPE DOUBLETYPE FLOATTYPE CONSTTYPE SIGNEDTYPE UNSIGNEDTYPE LONGLONGTYPE LONGTYPE SHORTTYPE VOIDTYPE
%left RETURN BREAK CONTINUE FOR WHILE DO SWITCH CASE DEFAULT IF ELSE
%left IDENT

//OPER VALUE
//ORDER 14
%token<sVal> ASSIGN
//ORDER 12
%token<sVal> LOGICALOR
//ORDER 11
%token<sVal> LOGICALAND
//ORDER 10
%token<sVal> BITWISEOR
//ORDER 09
%token<sVal> XOR
//ORDER 08

//ORDER 07
%token<sVal> EQ NOTEQ
//ORDER 06
%token<sVal> BIGOREQ SMALLOREQ BIG SMALL
//ORDER 05
%token<sVal> SHIFTLEFT SHIFTRIGHT
//ORDER 04

//ORDER 03
%token<sVal> SLASH MOD
//ORDER 02
%token<sVal> ADD MINUS TILDA EXCLAMATION BITWISEAND MULSTAR
//PRECE 01
%token<sVal> ADDONE MINUSONE    
//PUNC
%token<sVal> COMMA EOL LSQUAREBRACKET RSQUAREBRACKET LBRACE RBRACE LPARENTHESIS RPARENTHESIS COLON

%left TURNEDLEFT
%right TURNEDRIGHT
%nonassoc NOASSOCIATIVE

%right ASSIGN LV13
%left LOGICALOR LV12
%left LOGICALAND LV11
%left BITWISEOR LV10
%left XOR LV9
%left BITWISEAND LV8
%left EQ NOTEQ LV7
%left BIGOREQ SMALLOREQ BIG SMALL LV6
%left SHIFTLEFT SHIFTRIGHT LV5
%left ADD MINUS LV4
%left SLASH MOD MULSTAR LV3
%right TILDA EXCLAMATION ADDONE MINUSONE LV2
%left LV1 LPARENTHESIS RPARENTHESIS
%left LV0_L
%nonassoc LV0_N
%right LV0_R

%type <sVal> id ident identList scalarDeclare type type1 type2 type3 type4 mayHaveConst mayHaveSign mayLongOrShort 
%type <sVal> arrayDeclare lrSquareBracketList giveArray arrayContent item itemList array arrayList
%type <sVal> functionDeclare parameters parameter parameterList functionDefinition
%type <sVal> compoundStmt stmtOrVarDeclares stmtOrVarDeclare
%type <sVal> stmt ifOrIfElseStmt switchStmt whileStmt forStmt returnBreakContinueStmt switchCluses switchClue stmts mayHaveElse
%type <sVal> mayHaveExpr /*element*/
%type <sVal> expr identOrArray /*opMid prefixOp suffixOp*/ contiExpr exprList
%type <sVal> top
%start startHere

%%
//main
startHere: top {printf("%s",$1);};

top: scalarDeclare top {char* s = malloc(sizeof(char)*(strlen($1)+strlen($2)+20)); strcpy(s,""); strcat(s,$1); strcat(s,$2); $$=s;} | 

arrayDeclare top       {char* s = malloc(sizeof(char)*(strlen($1)+strlen($2)+20)); strcpy(s,""); strcat(s,$1); strcat(s,$2); $$=s;} | 

functionDeclare top    {char* s = malloc(sizeof(char)*(strlen($1)+strlen($2)+20)); strcpy(s,""); strcat(s,$1); strcat(s,$2); $$=s;} | 

functionDefinition top {char* s = malloc(sizeof(char)*(strlen($1)+strlen($2)+20)); strcpy(s,""); strcat(s,$1); strcat(s,$2); $$=s;} | {$$="";};

scalarDeclare: type ident identList EOL {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)); strcat(s,_SCALAR_LEFT);strcat(s,$1); strcat(s,$2); strcat(s,$3);strcat(s,$4);strcat(s,_SCALAR_RIGHT);$$=s;} 

identList: COMMA ident identList {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;} | {$$="";};

ident:  MULSTAR id {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2); $$=s;} |
        id {$$=$1;};

id: IDENT ASSIGN expr   {
        installSymbol($1);
        int index = lookUpSymbol($1);
        fprintf(codegen,"lw t0, 0(sp)  \n");
        fprintf(codegen,"addi sp,sp, 4 \n");
        fprintf(codegen,"sw t0, %d(fp)  //assign at id \n", -1*index*4-16);
        setSymbolMemory(index,-1*index*4-16);
        } | 
    IDENT   {};

type:   type1 {$$=$1;} | 
        type2 {$$=$1;} | 
        type3 {$$=$1;} | 
        type4 {$$=$1;};

type1: mayHaveConst mayHaveSign mayLongOrShort INTTYPE {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4); $$=s;}

type2:  mayHaveConst mayHaveSign LONGLONGTYPE {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;} | 
        mayHaveConst mayHaveSign LONGTYPE {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;} | 
        mayHaveConst mayHaveSign SHORTTYPE {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;} |
        mayHaveConst mayHaveSign CHARTYPE {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;} |
        mayHaveConst mayHaveSign CHAR4TYPE {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;} |
        mayHaveConst mayHaveSign CHAR8TYPE {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;}

type3:  mayHaveConst SIGNEDTYPE {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2); $$=s;} | 
        mayHaveConst UNSIGNEDTYPE {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2); $$=s;} |
        mayHaveConst FLOATTYPE {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2); $$=s;}| 
        mayHaveConst DOUBLETYPE {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2); $$=s;} |
        mayHaveConst VOIDTYPE {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2); $$=s;};

type4: CONSTTYPE {char* s = reserveStr(strlen($1)); strcat(s,$1);  $$=s;};

mayHaveConst: CONSTTYPE {$$=$1;} | {$$="";};

mayHaveSign: SIGNEDTYPE {$$=$1;} | UNSIGNEDTYPE {$$=$1;} | {$$="";};

mayLongOrShort: LONGLONGTYPE {$$=$1;} | LONGTYPE {$$=$1;} | SHORTTYPE {$$=$1;} | {$$="";};

arrayDeclare: type array arrayList EOL {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)); strcat(s,_ARRAY_LEFT);strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4);strcat(s,_ARRAY_RIGHT);$$=s;};

array: IDENT LSQUAREBRACKET expr RSQUAREBRACKET lrSquareBracketList giveArray {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)+strlen($6)); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4);strcat(s,$5); strcat(s,$6);$$=s;};

arrayList: COMMA array arrayList {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;} | {$$="";};

lrSquareBracketList: LSQUAREBRACKET expr RSQUAREBRACKET lrSquareBracketList {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4);$$=s;}| {$$="";};

giveArray: ASSIGN arrayContent {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2);$$=s;} | {$$="";};

arrayContent: LBRACE item itemList RBRACE {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)); strcat(s,$1); strcat(s,$2);strcat(s,$3); strcat(s,$4);$$=s;} | {$$="";};

itemList: COMMA item itemList {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;}| {$$="";};

item: expr {$$=$1;} | arrayContent {$$=$1;};

expr:   identOrArray                                  %prec LV0_L   {char*s = reserveStr(strlen($1)); strcat(s,_EXPR_LEFT); strcat(s,$1);                 strcat(s,_EXPR_RIGHT);$$=s;
            int index = lookUpSymbol($1);
            int memoryLocation = getSymbolMemory(index);
            fprintf(codegen,"lw t0, %d(fp)  \n", memoryLocation);
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n\n");} | //????
        INT                                           %prec LV0_L   {
            char*s = reserveStr(strlen(intToString($1))); strcat(s,_EXPR_LEFT); strcat(s,intToString($1));    strcat(s,_EXPR_RIGHT);$$=s;
            //fprintf(codegen,"li t0, %d       \n",$1);
            //fprintf(codegen,"addi sp, sp, -4 \n");
            //fprintf(codegen,"sw t0, 0(sp)    \n",$1);
            fprintf(codegen, "li t0, %d       \n", $1);
            fprintf(codegen, "addi sp, sp, -4 \n");
            fprintf(codegen, "sw t0, 0(sp)    \n");
            } | 
        DOUBLE                                        %prec LV0_L   {char*s = reserveStr(strlen(doubleToString($1))); strcat(s,_EXPR_LEFT); strcat(s,doubleToString($1)); strcat(s,_EXPR_RIGHT);$$=s;} | 
        MYCHAR                                        %prec LV0_L   {char*s = reserveStr(strlen($1)); strcat(s,_EXPR_LEFT); strcat(s,$1);                 strcat(s,_EXPR_RIGHT);$$=s;} | 
        MYSTRING                                      %prec LV0_L   {char*s = reserveStr(strlen($1)); strcat(s,_EXPR_LEFT); strcat(s,$1);                 strcat(s,_EXPR_RIGHT);$$=s;} | 
        MYNULL                                        %prec LV0_L   {char*s = reserveStr(5); strcat(s,_EXPR_LEFT); strcat(s,"0");                strcat(s,_EXPR_RIGHT);$$=s;} |
        LPARENTHESIS expr RPARENTHESIS                %prec LV0_L   {
            char*s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;
            }; |

        expr ADDONE                                   %prec LV1   {char* s = reserveStr(strlen($1)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,_EXPR_RIGHT); $$=s;} | 
        expr MINUSONE                                 %prec LV1   {char* s = reserveStr(strlen($1)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,_EXPR_RIGHT); $$=s;} |
        //expr LPARENTHESIS expr RPARENTHESIS           %prec LV1   {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4); strcat(s,_EXPR_RIGHT); $$=s;} |
        expr LPARENTHESIS contiExpr RPARENTHESIS                 {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4); strcat(s,_EXPR_RIGHT); $$=s;} |
        //IDENT LPARENTHESIS contiExpr RPARENTHESIS     %prec LV1   {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)); strcat(s,_EXPR_LEFT); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,_EXPR_RIGHT); strcat(s,$2); strcat(s,$3); strcat(s,$4); strcat(s,_EXPR_RIGHT); $$=s;} |

        BITWISEAND expr                               %prec LV2  {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,_EXPR_RIGHT); $$=s;} |
        MULSTAR expr                                  %prec LV2  {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,_EXPR_RIGHT); $$=s;} |
        TILDA expr                                               {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,_EXPR_RIGHT); $$=s;} |
        EXCLAMATION expr                                         {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,_EXPR_RIGHT); $$=s;} | 
        ADD expr                                      %prec LV2  {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,_EXPR_RIGHT); $$=s;} |
        MINUS expr                                    %prec LV2  {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,_EXPR_RIGHT); $$=s;} |
        ADDONE expr                                              {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,_EXPR_RIGHT); $$=s;} |
        MINUSONE expr                                            {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,_EXPR_RIGHT); $$=s;} |
        LPARENTHESIS type MULSTAR RPARENTHESIS expr   %prec LV2  {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4); strcat(s,$5); strcat(s,_EXPR_RIGHT); $$=s;} |
        LPARENTHESIS type RPARENTHESIS expr           %prec LV2  {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4); strcat(s,_EXPR_RIGHT); $$=s;} |

        expr MULSTAR    expr                          %prec LV3  {
            char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"lw t1, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"mul t0, t0, t1 \n");
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n\n");
            } |
        expr SLASH      expr                          {
            char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"lw t1, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"div t0, t1, t0 \n");
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n\n");
            } |
        expr MOD        expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |

        expr ADD        expr                          {
            char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"lw t1, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"add t0, t0, t1 \n");
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n\n");} |
        expr MINUS      expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"lw t1, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"sub t0, t1, t0 \n");
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n\n");} |
        
        expr SHIFTLEFT  expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |
        expr SHIFTRIGHT expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |

        expr BIG        expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |
        expr BIGOREQ    expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |
        expr SMALL      expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |
        expr SMALLOREQ  expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |

        expr EQ         expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |
        expr NOTEQ      expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |

        expr BITWISEAND expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |

        expr XOR        expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |

        expr BITWISEOR  expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |
        
        expr LOGICALAND expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |

        expr LOGICALOR  expr                          {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;} |

        expr ASSIGN     expr                          {
            char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,_EXPR_LEFT); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,_EXPR_RIGHT); $$=s;
            int index = lookUpSymbol($1);
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"lw t1, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"sw t0, %d(fp)  //assign at expr\n", -1*index*4-16);
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n\n");}; 

contiExpr: expr exprList{char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2); $$=s;} | {$$="";};

exprList: COMMA expr exprList {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;} | {$$="";};

identOrArray: IDENT lrSquareBracketList {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2);$$=s;};

functionDeclare:    type IDENT LPARENTHESIS parameters RPARENTHESIS EOL {
                        char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)+strlen($6)); 
                        strcat(s,_FUNC_DECL_LEFT);
                        strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4);strcat(s,$5); strcat(s,$6);
                        strcat(s,_FUNC_DECL_RIGHT);
                        $$=s;} | 
                    type MULSTAR IDENT LPARENTHESIS parameters RPARENTHESIS EOL {
                        char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)+strlen($6)+strlen($7)); 
                        strcat(s,_FUNC_DECL_LEFT);
                        strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4);strcat(s,$5); strcat(s,$6);strcat(s,$7);
                        strcat(s,_FUNC_DECL_RIGHT);
                        $$=s;} |
                    
                    type CODEGEN LPARENTHESIS parameters RPARENTHESIS EOL {
                        char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)+strlen($6)); 
                        strcat(s,_FUNC_DECL_LEFT);
                        strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4);strcat(s,$5); strcat(s,$6);
                        strcat(s,_FUNC_DECL_RIGHT);
                        $$=s;
                        installSymbol($2);
                        int index = lookUpSymbol($2);
                        setTotalSymbolParam(index,0);
                        };
                    

parameters: parameter parameterList {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1);strcat(s,$2);$$=s;} | 
            {$$="";};

parameterList: COMMA parameter parameterList {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;}| {$$="";};

parameter:  type IDENT         {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2);$$=s;} | 
            type MULSTAR IDENT {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3);$$=s;};

functionDefinition: type IDENT LPARENTHESIS parameters RPARENTHESIS compoundStmt {
                        char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)+strlen($6));
                        strcat(s,_FUNCT_DEF_LEFT);
                        strcat(s,$1); strcat(s,$2); strcat(s,$3);strcat(s,$4); strcat(s,$5); strcat(s,$6);
                        strcat(s,_FUNCT_DEF_RIGHT);
                        $$=s;} | 
                    type MULSTAR IDENT LPARENTHESIS parameters RPARENTHESIS compoundStmt {
                        char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)+strlen($6)+strlen($7));
                        strcat(s,_FUNCT_DEF_LEFT);strcat(s,$1); strcat(s,$2); strcat(s,$3);strcat(s,$4); strcat(s,$5); strcat(s,$6);strcat(s,$7);
                        strcat(s,_FUNCT_DEF_RIGHT);
                        $$=s;} |
                    type CODEGEN LPARENTHESIS parameters RPARENTHESIS {
                        curScope++;
                        setScopeAndOffsetOfParam($2);
                        codeGenFuncHeader($2);
                    } compoundStmt {
                        codeGenAtEndOfFunctionBody($2);
                        fprintf(codegen,"\n");};

compoundStmt: LBRACE stmtOrVarDeclares RBRACE {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;};

stmtOrVarDeclares: stmtOrVarDeclare stmtOrVarDeclares {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2); $$=s;} | {$$="";};

stmtOrVarDeclare: stmt {$$=$1;} | scalarDeclare {$$=$1;} | arrayDeclare {$$=$1;};

stmt:   expr EOL                {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,_STMT_LEFT);strcat(s,$1); strcat(s,$2); strcat(s,_STMT_RIGHT);$$=s;} |
        ifOrIfElseStmt          {char* s = reserveStr(strlen($1)); strcat(s,_STMT_LEFT);strcat(s,$1); strcat(s,_STMT_RIGHT);$$=s;} | 
        switchStmt              {char* s = reserveStr(strlen($1)); strcat(s,_STMT_LEFT);strcat(s,$1); strcat(s,_STMT_RIGHT);$$=s;} | 
        whileStmt               {char* s = reserveStr(strlen($1)); strcat(s,_STMT_LEFT);strcat(s,$1); strcat(s,_STMT_RIGHT);$$=s;} | 
        forStmt                 {char* s = reserveStr(strlen($1)); strcat(s,_STMT_LEFT);strcat(s,$1); strcat(s,_STMT_RIGHT);$$=s;} | 
        returnBreakContinueStmt {char* s = reserveStr(strlen($1)); strcat(s,_STMT_LEFT);strcat(s,$1); strcat(s,_STMT_RIGHT);$$=s;} | 
        compoundStmt            {char* s = reserveStr(strlen($1)); strcat(s,_STMT_LEFT);strcat(s,$1); strcat(s,_STMT_RIGHT);$$=s;} |
        DIGITALWRITE {
            fprintf(codegen,"addi sp, sp, -8  \n");
            fprintf(codegen,"sd ra, 0(sp)  \n");
        } 
        LPARENTHESIS expr {
            fprintf(codegen,"ld a0, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 4  \n");} 
        COMMA expr {
            fprintf(codegen,"ld a1, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 4  \n");} 
        RPARENTHESIS {
            fprintf(codegen,"jal ra,digitalWrite  \n");} 
        EOL {
            fprintf(codegen,"ld ra, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 8\n\n");
        } | 
        DELAY {
            fprintf(codegen,"addi sp, sp, -8  \n");
            fprintf(codegen,"sd ra, 0(sp)  \n");
        } 
        LPARENTHESIS expr {
            fprintf(codegen,"ld a0, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 4  \n");}  
        RPARENTHESIS      {
            fprintf(codegen,"jal ra, delay  \n");} 
        EOL {
            fprintf(codegen,"ld ra, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 8\n\n");
        };


returnBreakContinueStmt: RETURN expr EOL {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1); strcat(s,$2); strcat(s,$3); $$=s;} |
                         RETURN EOL      {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2); $$=s;} | 
                         BREAK EOL       {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2); $$=s;} |
                         CONTINUE EOL    {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1); strcat(s,$2); $$=s;};

forStmt: FOR LPARENTHESIS mayHaveExpr EOL mayHaveExpr EOL mayHaveExpr RPARENTHESIS stmt {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)+strlen($6)+strlen($7)+strlen($8)+strlen($9)); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4);strcat(s,$5); strcat(s,$6); strcat(s,$7); strcat(s,$8);strcat(s,$9);$$=s;};

mayHaveExpr: expr {$$=$1;} | {$$="";};

whileStmt: WHILE LPARENTHESIS expr RPARENTHESIS stmt {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4);strcat(s,$5);$$=s;} | 
           DO stmt WHILE LPARENTHESIS expr RPARENTHESIS EOL {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)+strlen($6)+strlen($7)); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4);strcat(s,$5);strcat(s,$6);strcat(s,$7);$$=s;};

switchStmt: SWITCH LPARENTHESIS expr RPARENTHESIS LBRACE switchCluses RBRACE {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)+strlen($6)+strlen($7)); strcat(s,$1); strcat(s,$2); strcat(s,$3); strcat(s,$4);strcat(s,$5);strcat(s,$6);strcat(s,$7);$$=s;};

switchCluses:   switchClue switchCluses {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1);strcat(s,$2);$$=s;} | 
                {$$="";};

switchClue: CASE expr COLON stmts{char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)); strcat(s,$1);strcat(s,$2);strcat(s,$3);strcat(s,$4);$$=s;} | 
            DEFAULT COLON stmts  {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)); strcat(s,$1);strcat(s,$2);strcat(s,$3);$$=s;};

stmts: stmt stmts {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1);strcat(s,$2);$$=s;}| {$$="";};

ifOrIfElseStmt: IF LPARENTHESIS expr RPARENTHESIS compoundStmt mayHaveElse {char* s = reserveStr(strlen($1)+strlen($2)+strlen($3)+strlen($4)+strlen($5)+strlen($6)); strcat(s,$1);strcat(s,$2);strcat(s,$3);strcat(s,$4);strcat(s,$5); strcat(s,$6);$$=s;};

mayHaveElse:    ELSE compoundStmt {char* s = reserveStr(strlen($1)+strlen($2)); strcat(s,$1);strcat(s,$2);$$=s;} | 
                {$$="";};

%%
int yylex();
int main(void) {
    /*
    handle input file
    */
    if ((codegen = fopen("codegen.S", "w")) == NULL) {
        printf("Error\n");
        exit(1);
    }
    fprintf(codegen, ".global codegen\n");
    initSymbolTable();
    initStack();
    yyparse();
    return 0;
}
int yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
    return 0;
}