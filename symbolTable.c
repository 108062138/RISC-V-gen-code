#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <error.h>
#define MAX_TABLE_SIZE 5000
#define T_FUNCTION    1
#define ARGUMENT_MODE 2
#define LOCAL_MODE    3
#define GLOBAL_MODE   4

typedef struct symbol_entry *PTR_SYMB;
struct symbolEntry{
    char* name;
    int scope;
    int memoryLocation;
    int totalParam;
    int totalArg;
    int offset;
    int mode;
    int type;
}table[MAX_TABLE_SIZE];

extern int curScope = 0;
extern int curCounter = 0;//inited as 0. it always points to nothing

void initSymbolTable(){
    bzero(&table[0], sizeof(struct symbolEntry)*MAX_TABLE_SIZE);
}

char *installSymbol(char* s){
    if(curCounter>=MAX_TABLE_SIZE)
        perror("symbol table is not large enough");
    else{
        table[curCounter].scope = curScope;
        int length = strlen(s);
        table[curCounter].name = malloc(sizeof(char)*(length)+5);
        strcpy(table[curCounter].name,s);
        curCounter++;
    }

    return s;
}

void popUpSymbol(int scope){
    int i;
    if(curCounter==0)return;
    for(i=curCounter-1;i>=0;i--)
        if(table[i].scope!=scope)break;
    if(i<0)curCounter = 0;
    curCounter = i + 1;
}

int lookUpSymbol(char* s){
    int i;
    if(curCounter==0)return -1;//not found
    for(i=curCounter-1;i>=0;i--)
        if(!strcmp(s,table[i].name)) return i;
    return -1;
}