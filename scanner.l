%{
#include<stdio.h>
#include<string.h>
#include"y.tab.h"
char dest[6600] = "";
char charBuffer[6600] = "";
char stringBuffer[6600] = "";
int debugFlag = 0;//1 for debug, and 0 for produce 
int lineCnt = 0;
int firstLine=1;//1 for first, otherwise 0
int sourceOn = 1;
int tokenOn = 1;
%}
%x MULTIPLELINECOMMENT
%x SINGLELINECOMMENT
%x STRING 
%x CHAR 
MCOMMENTR ("*/")
COMMENT ("//")
MACRO ("NULL"|"__COUNTER__"|"__LINE__"|"INT_MAX"|"INT_MIN"|"CHAR_MAX"|"CHAR_MIN"|"MAX"|"MIN")
ASCII1 (" "|"!"|"\\\""|"#"|"$"|"%"|"&"|"\\\'"|"("|")"|"*"|"+"|","|"-"|"."|"/"|"0"|"1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9"|":"|";"|"<"|"="|">"|"\\\?"|"?")
ASCII2 ("@"|"A"|"B"|"C"|"D"|"E"|"F"|"G"|"H"|"I"|"J"|"K"|"L"|"M"|"N"|"O"|"P"|"Q"|"R"|"S"|"T"|"U"|"V"|"W"|"X"|"Y"|"Z"|"["|"\\"|"]"|"^"|"_")
ASCII3 ("`"|"a"|"b"|"c"|"d"|"e"|"f"|"g"|"h"|"i"|"j"|"k"|"l"|"m"|"n"|"o"|"p"|"q"|"r"|"s"|"t"|"u"|"v"|"w"|"x"|"y"|"z"|"{"|"|"|"}"|"~")
ESC ("\\a"|"\\b"|"\\e"|"\\f"|"\\n"|"\\r"|"\\t"|"\\v"|"\\\\"|"\\\'"|"\\\""|"\\\?")
KEYWORD ("for"|"do"|"while"|"break"|"continue"|"if"|"else"|"return"|"struct"|"switch"|"case"|"default"|"void"|"int"|"double"|"float"|"char"|"const"|"signed"|"unsigned"|"short"|"long"|"char4"|"char8"|"codegen"|"digitalWrite"|"delay"|"HIGH"|"LOW")
PUNC (":"|";"|","|"."|"["|"]"|"("|")"|"{"|"}")
NUMBER ("0"|"1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9")
LOWERCASE ("a"|"b"|"c"|"d"|"e"|"f"|"g"|"h"|"i"|"j"|"k"|"l"|"m"|"n"|"o"|"p"|"q"|"r"|"s"|"t"|"u"|"v"|"w"|"x"|"y"|"z")
UPPERCASE ("A"|"B"|"C"|"D"|"E"|"F"|"G"|"H"|"I"|"J"|"K"|"L"|"M"|"N"|"O"|"P"|"Q"|"R"|"S"|"T"|"U"|"V"|"W"|"X"|"Y"|"Z")
TWOOP ("++"|"--"|"<="|">="|"=="|"!="|"&&"|"||")
ONEOP ("+"|"-"|"*"|"/"|"%"|"<"|">"|"!"|"&"|"|"|"=")
UNDERLINE ("_")
OCT  ("0"|"1"|"2"|"3"|"4"|"5"|"6"|"7")
HEXA ("0"|"1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9"|"a"|"b"|"c"|"d"|"e"|"f"|"A"|"B"|"C"|"D"|"E"|"F")

%%

({NUMBER}+) {
    if(tokenOn==1){
        if(firstLine==1){
            //printf("#integer:%s", yytext);
            firstLine=0;
        }else{ 
            //printf("\n#integer:%s", yytext);
        }
    }
    strcat(dest,yytext);
    yylval.iVal = atoi(yytext); 
    return INT;
}
([0-9]+\.[0-9]*)|(\.[0-9]+)  {
    if(tokenOn==1){
        if(firstLine==1){
            //printf("#f");
            //printf("loat:%s", yytext);
            firstLine=0;
        }else {
            //printf("\n#f");
            //printf("loat:%s", yytext);
        }
    }
    strcat(dest,yytext);
    yylval.dVal = atof(yytext); 
    return DOUBLE;
}
"#pragma"([[:space:]]|'\t')+"source"([[:space:]]|'\t')+"on"   {
    sourceOn=1;
    strcat(dest,yytext);
}
"#pragma"([[:space:]]|'\t')+"source"([[:space:]]|'\t')+"off"   {
    sourceOn=0;
    strcat(dest,yytext);
}
"#pragma"([[:space:]]|'\t')+"token"([[:space:]]|'\t')+"on"   {
    tokenOn=1;
    strcat(dest,yytext);
}
"#pragma"([[:space:]]|'\t')+"token"([[:space:]]|'\t')+"off"   {
    tokenOn=0;
    strcat(dest,yytext);
}
"/*"    {
    strcat(dest,yytext);
    BEGIN MULTIPLELINECOMMENT;
}
<MULTIPLELINECOMMENT>\n {
    lineCnt++;
    if(sourceOn==1){
        if(firstLine==1){
            //printf("%d:%s", lineCnt,dest);
            firstLine = 0;
        }else{
            //printf("\n%d:%s", lineCnt,dest);
        }
    }
    strcpy(dest,"");
}
<MULTIPLELINECOMMENT>"*/"    {
    strcat(dest,yytext);
    BEGIN 0;
}
<MULTIPLELINECOMMENT>.  {
    strcat(dest,yytext);
}
{COMMENT} {
    strcat(dest,yytext);
    BEGIN SINGLELINECOMMENT;    
}
<SINGLELINECOMMENT>\n {
    lineCnt++;
    if(sourceOn==1){
        if(firstLine==1){
            //printf("%d:%s", lineCnt,dest);
            firstLine = 0;
        }else{
            //printf("\n%d:%s", lineCnt,dest);
        }
    }
    strcpy(dest,"");
    BEGIN 0;
}
<SINGLELINECOMMENT>. {
    strcat(dest,yytext);
}
\'  {
    if(tokenOn==1){
        if(firstLine==1){
                //printf("#c");
                //printf("har:%s", yytext);
                firstLine=0;
        }else {
            //printf("\n#c");
            //printf("har:%s", yytext);
        }
    }
    strcpy(charBuffer,"");
    strcat(charBuffer,yytext);
    strcat(dest,yytext);
    BEGIN CHAR;
}
<CHAR>(\\"U"{HEXA}{HEXA}{HEXA}{HEXA}{HEXA}{HEXA}{HEXA}{HEXA})|(\\"u"{HEXA}{HEXA}{HEXA}{HEXA}|(\\"x"{HEXA}+)|(\\{OCT}{OCT}?{OCT}?))  {
    if(tokenOn==1){
        //printf("%s", yytext);
    }
    strcat(dest,yytext);
    strcat(charBuffer,yytext);
}
<CHAR>{ASCII1}|{ASCII2}|{ASCII3}|{ESC}  {
    if(tokenOn==1){
        //printf("%s", yytext);
    }
    strcat(dest,yytext);
    strcat(charBuffer,yytext);
}
<CHAR>\'  {
    if(tokenOn==1){
        //printf("%s", yytext);
    }
    strcat(dest,yytext);
    strcat(charBuffer,yytext);
    BEGIN 0;
    yylval.sVal = strdup(charBuffer); 
    return MYCHAR;
}
"++" { yylval.sVal = strdup(yytext); return ADDONE;}
"--" { yylval.sVal = strdup(yytext); return MINUSONE;}
"<<" { yylval.sVal = strdup(yytext); return SHIFTLEFT;}
">>" { yylval.sVal = strdup(yytext); return SHIFTRIGHT;}
">=" { yylval.sVal = strdup(yytext); return BIGOREQ;}
"<=" { yylval.sVal = strdup(yytext); return SMALLOREQ;}
"==" { yylval.sVal = strdup(yytext); return EQ;}
"!=" { yylval.sVal = strdup(yytext); return NOTEQ;}
"&&" { yylval.sVal = strdup(yytext); return LOGICALAND;}
"||" { yylval.sVal = strdup(yytext); return LOGICALOR;}

"=" { yylval.sVal = strdup(yytext); return ASSIGN;}
"*" { yylval.sVal = strdup(yytext); return MULSTAR;}
"-" { yylval.sVal = strdup(yytext); return MINUS;}
"+" { yylval.sVal = strdup(yytext); return ADD;}
"~" { yylval.sVal = strdup(yytext); return TILDA;}
"!" { yylval.sVal = strdup(yytext); return EXCLAMATION;}
"&" { yylval.sVal = strdup(yytext); return BITWISEAND;}
"/" { yylval.sVal = strdup(yytext); return SLASH;}
"%" { yylval.sVal = strdup(yytext); return MOD;}
">" { yylval.sVal = strdup(yytext); return BIG;}
"<" { yylval.sVal = strdup(yytext); return SMALL;}
"^" { yylval.sVal = strdup(yytext); return XOR;}
"|" { yylval.sVal = strdup(yytext); return BITWISEOR;}

"char4" { yylval.sVal = strdup(yytext); return CHAR4TYPE;}
"char8" { yylval.sVal = strdup(yytext); return CHAR8TYPE;}

"int" { yylval.sVal = strdup(yytext); return INTTYPE;}
"char" { yylval.sVal = strdup(yytext); return CHARTYPE;}
"string" { yylval.sVal = strdup(yytext); return STRINGTYPE;}
"double" { yylval.sVal = strdup(yytext); return DOUBLETYPE;}
"float" { yylval.sVal = strdup(yytext); return FLOATTYPE;}
"const" { yylval.sVal = strdup(yytext); return CONSTTYPE;}
"signed" { yylval.sVal = strdup(yytext); return SIGNEDTYPE;}
"unsigned" { yylval.sVal = strdup(yytext); return UNSIGNEDTYPE;}
"long long" { yylval.sVal = strdup("longlong"); return LONGLONGTYPE;}
"long" { yylval.sVal = strdup(yytext); return LONGTYPE;}
"short" { yylval.sVal = strdup(yytext); return SHORTTYPE;}
"void" { yylval.sVal = strdup(yytext); return VOIDTYPE;}

"return" { yylval.sVal = strdup(yytext); return RETURN;}
"break" { yylval.sVal = strdup(yytext); return BREAK;}
"continue" { yylval.sVal = strdup(yytext); return CONTINUE;}
"for" { yylval.sVal = strdup(yytext); return FOR;}
"while" { yylval.sVal = strdup(yytext); return WHILE;}
"do" { yylval.sVal = strdup(yytext); return DO;}
"switch" { yylval.sVal = strdup(yytext); return SWITCH;}
"case" { yylval.sVal = strdup(yytext); return CASE;}
"default" { yylval.sVal = strdup(yytext); return DEFAULT;}
"if" { yylval.sVal = strdup(yytext); return IF;}
"else" { yylval.sVal = strdup(yytext); return ELSE;}
"codegen" { yylval.sVal = strdup(yytext); return CODEGEN;}
"digitalWrite" { yylval.sVal = strdup(yytext); return DIGITALWRITE;}
"delay" { yylval.sVal = strdup(yytext); return DELAY;}
"HIGH" { yylval.iVal = 1; return INT;}
"LOW"  { yylval.iVal = 0; return INT;}

{KEYWORD} {
    if(tokenOn==1){
        if(firstLine==1){
            firstLine=0;
            //printf("#key:%s",yytext);
        }else {
            //printf("\n#key:%s",yytext);
        }
    }
    strcat(dest,yytext);
}

"," {yylval.sVal = strdup(yytext); return COMMA;}
";" {yylval.sVal = strdup(yytext); return EOL;}
"[" {yylval.sVal = strdup(yytext); return LSQUAREBRACKET;}
"]" {yylval.sVal = strdup(yytext); return RSQUAREBRACKET;}
"{" {yylval.sVal = strdup(yytext); return LBRACE;}
"}" {yylval.sVal = strdup(yytext); return RBRACE;}
"(" {yylval.sVal = strdup(yytext); return LPARENTHESIS;}
")" {yylval.sVal = strdup(yytext); return RPARENTHESIS;}
":" {yylval.sVal = strdup(yytext); return COLON;}
{PUNC}    {
    if(tokenOn==1){
        if(firstLine==1){
            firstLine=0;
            //printf("#punc:%s",yytext);
        }else {
            //printf("\n#punc:%s",yytext);
        }
    }
    strcat(dest,yytext);
}

"NULL" {yylval.sVal = strdup(yytext); return MYNULL;}

{MACRO}   {
    if(tokenOn==1){
        if(firstLine==1){
            firstLine=0;
            //printf("#macro:%s",yytext);
        }else {
            //printf("\n#macro:%s",yytext);
        }
    }
    strcat(dest,yytext);
}
({KEYWORD})+({LOWERCASE}|{UPPERCASE}|{UNDERLINE}|{KEYWORD}|{NUMBER})+  {
    if(tokenOn==1){
        if(firstLine==1){
            firstLine=0;
            //printf("#id:%s",yytext);
        }else {
            //printf("\n#id:%s",yytext);
        }
    }
    strcat(dest,yytext);
    yylval.sVal = strdup(yytext); 
    return IDENT;
}

({LOWERCASE}|{UPPERCASE}|{UNDERLINE})+({KEYWORD}|{LOWERCASE}|{UPPERCASE}|{UNDERLINE}|{NUMBER})*   {
    if(tokenOn==1){
        if(firstLine==1){
            firstLine=0;
            //printf("#id:%s",yytext);
        }else {
            //printf("\n#id:%s",yytext);
        }
    }
    strcat(dest,yytext);
    yylval.sVal = strdup(yytext); 
    return IDENT;
}

\"  {
    if(tokenOn==1){
        if(firstLine==1){
            firstLine=0;
            //printf("#string:%s",yytext);
        }else {
            //printf("\n#string:%s",yytext);
        }
    }
    strcat(dest,yytext);
    strcpy(stringBuffer,"");
    strcat(stringBuffer,yytext);
    BEGIN STRING;
}
<STRING>"\\""\""   {
    if(tokenOn==1){
        //printf("%s",yytext);
    }
    strcat(dest,yytext);
    strcat(stringBuffer,yytext);
}
<STRING>"\\""\\"   {
    if(tokenOn==1){
        //printf("%s",yytext);
    }
    strcat(dest,yytext);
    strcat(stringBuffer,yytext);
}
<STRING>\"   {
    if(tokenOn==1){
        //printf("%s",yytext);
    }
    strcat(dest,yytext);
    strcat(stringBuffer,yytext);
    BEGIN 0;
    yylval.sVal = strdup(stringBuffer); 
    return MYSTRING;
}
<STRING>.   {
    if(tokenOn==1){
        //printf("%s",yytext);
    }
    strcat(dest,yytext);
    strcat(stringBuffer,yytext);
}

\n {
    lineCnt++;
    if(sourceOn==1){
        if(firstLine==1){
            //printf("%d:%s", lineCnt,dest);
            firstLine = 0;
        }else{
            //printf("\n%d:%s", lineCnt,dest);
        }
    }
    strcpy(dest,"");
}

\t|" " {
    strcat(dest,yytext);
}

. {
    strcat(dest,yytext);
}

%%

//int main(int argc, char* argv[]){
//    yylex();
//    //printf("\n");
//    return 0;
//}


