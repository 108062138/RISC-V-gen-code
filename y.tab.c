/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

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
int ptrType;//1 for pointer type and 0 for normal type
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

#line 172 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    MYCHAR = 259,
    MYSTRING = 260,
    MYNULL = 261,
    DOUBLE = 262,
    INTTYPE = 263,
    CHARTYPE = 264,
    STRINGTYPE = 265,
    DOUBLETYPE = 266,
    FLOATTYPE = 267,
    CONSTTYPE = 268,
    SIGNEDTYPE = 269,
    UNSIGNEDTYPE = 270,
    LONGLONGTYPE = 271,
    LONGTYPE = 272,
    SHORTTYPE = 273,
    VOIDTYPE = 274,
    CHAR4TYPE = 275,
    CHAR8TYPE = 276,
    RETURN = 277,
    BREAK = 278,
    CONTINUE = 279,
    FOR = 280,
    WHILE = 281,
    DO = 282,
    SWITCH = 283,
    CASE = 284,
    DEFAULT = 285,
    IF = 286,
    ELSE = 287,
    IDENT = 288,
    CODEGEN = 289,
    DIGITALWRITE = 290,
    DELAY = 291,
    ASSIGN = 292,
    LOGICALOR = 293,
    LOGICALAND = 294,
    BITWISEOR = 295,
    XOR = 296,
    EQ = 297,
    NOTEQ = 298,
    BIGOREQ = 299,
    SMALLOREQ = 300,
    BIG = 301,
    SMALL = 302,
    SHIFTLEFT = 303,
    SHIFTRIGHT = 304,
    SLASH = 305,
    MOD = 306,
    ADD = 307,
    MINUS = 308,
    TILDA = 309,
    EXCLAMATION = 310,
    BITWISEAND = 311,
    MULSTAR = 312,
    ADDONE = 313,
    MINUSONE = 314,
    COMMA = 315,
    EOL = 316,
    LSQUAREBRACKET = 317,
    RSQUAREBRACKET = 318,
    LBRACE = 319,
    RBRACE = 320,
    LPARENTHESIS = 321,
    RPARENTHESIS = 322,
    COLON = 323,
    TURNEDLEFT = 324,
    TURNEDRIGHT = 325,
    NOASSOCIATIVE = 326,
    LV13 = 327,
    LV12 = 328,
    LV11 = 329,
    LV10 = 330,
    LV9 = 331,
    LV8 = 332,
    LV7 = 333,
    LV6 = 334,
    LV5 = 335,
    LV4 = 336,
    LV3 = 337,
    LV2 = 338,
    LV1 = 339,
    LV0_L = 340,
    LV0_N = 341,
    LV0_R = 342
  };
#endif
/* Tokens.  */
#define INT 258
#define MYCHAR 259
#define MYSTRING 260
#define MYNULL 261
#define DOUBLE 262
#define INTTYPE 263
#define CHARTYPE 264
#define STRINGTYPE 265
#define DOUBLETYPE 266
#define FLOATTYPE 267
#define CONSTTYPE 268
#define SIGNEDTYPE 269
#define UNSIGNEDTYPE 270
#define LONGLONGTYPE 271
#define LONGTYPE 272
#define SHORTTYPE 273
#define VOIDTYPE 274
#define CHAR4TYPE 275
#define CHAR8TYPE 276
#define RETURN 277
#define BREAK 278
#define CONTINUE 279
#define FOR 280
#define WHILE 281
#define DO 282
#define SWITCH 283
#define CASE 284
#define DEFAULT 285
#define IF 286
#define ELSE 287
#define IDENT 288
#define CODEGEN 289
#define DIGITALWRITE 290
#define DELAY 291
#define ASSIGN 292
#define LOGICALOR 293
#define LOGICALAND 294
#define BITWISEOR 295
#define XOR 296
#define EQ 297
#define NOTEQ 298
#define BIGOREQ 299
#define SMALLOREQ 300
#define BIG 301
#define SMALL 302
#define SHIFTLEFT 303
#define SHIFTRIGHT 304
#define SLASH 305
#define MOD 306
#define ADD 307
#define MINUS 308
#define TILDA 309
#define EXCLAMATION 310
#define BITWISEAND 311
#define MULSTAR 312
#define ADDONE 313
#define MINUSONE 314
#define COMMA 315
#define EOL 316
#define LSQUAREBRACKET 317
#define RSQUAREBRACKET 318
#define LBRACE 319
#define RBRACE 320
#define LPARENTHESIS 321
#define RPARENTHESIS 322
#define COLON 323
#define TURNEDLEFT 324
#define TURNEDRIGHT 325
#define NOASSOCIATIVE 326
#define LV13 327
#define LV12 328
#define LV11 329
#define LV10 330
#define LV9 331
#define LV8 332
#define LV7 333
#define LV6 334
#define LV5 335
#define LV4 336
#define LV3 337
#define LV2 338
#define LV1 339
#define LV0_L 340
#define LV0_N 341
#define LV0_R 342

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 107 "parser.y" /* yacc.c:355  */
 
    int iVal;
    double dVal;
    char* sVal;

#line 389 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 406 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   896

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  152
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  275

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   342

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   192,   192,   194,   196,   198,   200,   200,   202,   204,
     204,   206,   210,   214,   225,   227,   228,   229,   230,   232,
     234,   235,   236,   237,   238,   239,   241,   242,   243,   244,
     245,   247,   249,   249,   251,   251,   251,   253,   253,   253,
     253,   255,   257,   259,   259,   261,   261,   263,   263,   265,
     265,   267,   267,   269,   269,   271,   277,   286,   287,   288,
     289,   290,   294,   295,   297,   300,   308,   316,   317,   318,
     319,   324,   325,   326,   327,   329,   339,   349,   351,   360,
     369,   370,   372,   373,   374,   375,   377,   378,   380,   382,
     384,   386,   388,   390,   404,   404,   406,   406,   408,   410,
     416,   423,   435,   436,   438,   438,   440,   441,   443,   449,
     454,   454,   462,   464,   464,   466,   466,   466,   468,   469,
     470,   471,   472,   473,   474,   475,   479,   482,   485,   475,
     491,   495,   498,   491,   506,   507,   508,   509,   511,   513,
     513,   515,   516,   518,   520,   521,   523,   524,   526,   526,
     528,   530,   531
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "MYCHAR", "MYSTRING", "MYNULL",
  "DOUBLE", "INTTYPE", "CHARTYPE", "STRINGTYPE", "DOUBLETYPE", "FLOATTYPE",
  "CONSTTYPE", "SIGNEDTYPE", "UNSIGNEDTYPE", "LONGLONGTYPE", "LONGTYPE",
  "SHORTTYPE", "VOIDTYPE", "CHAR4TYPE", "CHAR8TYPE", "RETURN", "BREAK",
  "CONTINUE", "FOR", "WHILE", "DO", "SWITCH", "CASE", "DEFAULT", "IF",
  "ELSE", "IDENT", "CODEGEN", "DIGITALWRITE", "DELAY", "ASSIGN",
  "LOGICALOR", "LOGICALAND", "BITWISEOR", "XOR", "EQ", "NOTEQ", "BIGOREQ",
  "SMALLOREQ", "BIG", "SMALL", "SHIFTLEFT", "SHIFTRIGHT", "SLASH", "MOD",
  "ADD", "MINUS", "TILDA", "EXCLAMATION", "BITWISEAND", "MULSTAR",
  "ADDONE", "MINUSONE", "COMMA", "EOL", "LSQUAREBRACKET", "RSQUAREBRACKET",
  "LBRACE", "RBRACE", "LPARENTHESIS", "RPARENTHESIS", "COLON",
  "TURNEDLEFT", "TURNEDRIGHT", "NOASSOCIATIVE", "LV13", "LV12", "LV11",
  "LV10", "LV9", "LV8", "LV7", "LV6", "LV5", "LV4", "LV3", "LV2", "LV1",
  "LV0_L", "LV0_N", "LV0_R", "$accept", "startHere", "top",
  "scalarDeclare", "identList", "ident", "id", "type", "type1", "type2",
  "type3", "type4", "mayHaveConst", "mayHaveSign", "mayLongOrShort",
  "arrayDeclare", "array", "arrayList", "lrSquareBracketList", "giveArray",
  "arrayContent", "itemList", "item", "expr", "contiExpr", "exprList",
  "identOrArray", "functionDeclare", "parameters", "parameterList",
  "parameter", "functionDefinition", "$@1", "compoundStmt",
  "stmtOrVarDeclares", "stmtOrVarDeclare", "stmt", "$@2", "$@3", "$@4",
  "$@5", "$@6", "$@7", "$@8", "returnBreakContinueStmt", "forStmt",
  "mayHaveExpr", "whileStmt", "switchStmt", "switchCluses", "switchClue",
  "stmts", "ifOrIfElseStmt", "mayHaveElse", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342
};
# endif

#define YYPACT_NINF -208

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-208)))

#define YYTABLE_NINF -115

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,   -21,    11,  -208,     6,    59,  -208,  -208,  -208,  -208,
     250,     6,     6,     6,  -208,  -208,    45,    -8,    50,    25,
    -208,    37,  -208,  -208,   -12,    23,  -208,   211,  -208,  -208,
    -208,   318,   318,    21,    21,   -19,  -208,    53,    57,    75,
      72,  -208,   142,   155,   157,  -208,  -208,   159,  -208,  -208,
    -208,  -208,  -208,    99,   318,   318,   318,   318,   318,   318,
     318,   318,    46,   685,  -208,   535,    62,   101,   109,   105,
      21,   145,   150,    25,  -208,   123,    37,  -208,  -208,   318,
    -208,    64,    64,    64,    64,    64,    64,    64,    64,   -52,
     380,   318,   318,   318,   318,   318,   318,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   318,   318,
    -208,  -208,   318,    99,  -208,   154,    67,   177,  -208,   130,
     128,  -208,  -208,   565,   132,   318,  -208,   685,   713,   740,
      96,   765,   813,   813,   825,   825,   825,   825,   302,   302,
      64,    64,   830,   830,   790,    64,   595,   133,   160,  -208,
    -208,   153,  -208,   109,  -208,   137,    71,    99,   318,    64,
     318,  -208,  -208,   138,  -208,   253,   143,   169,   148,   167,
     219,   168,   170,  -208,  -208,  -208,    63,  -208,   625,  -208,
     151,   153,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,    64,   595,   284,  -208,  -208,   655,  -208,
    -208,   318,   318,   209,   318,   318,   171,   172,    47,  -208,
    -208,  -208,  -208,  -208,   179,   685,  -208,   685,   187,   411,
     174,   442,   473,   318,   318,   284,   184,   318,   219,   318,
     139,   137,   685,   685,   179,  -208,   190,  -208,   504,   -13,
     221,   203,   199,  -208,   318,   206,   318,   200,   205,   -13,
     137,  -208,   318,  -208,   212,  -208,   348,   219,  -208,  -208,
    -208,   685,   220,   219,   219,   219,  -208,   213,  -208,  -208,
    -208,  -208,  -208,   223,  -208
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      33,    32,     0,     2,    33,     0,    15,    16,    17,    18,
      36,    33,    33,    33,     1,     3,    14,     0,     0,    10,
      12,    44,    29,    28,    34,    35,    30,    40,     4,     5,
       6,     0,     0,    33,    33,    14,    11,     0,     0,     0,
       0,    23,    20,    21,    22,    24,    25,     0,    56,    58,
      59,    60,    57,    46,     0,     0,     0,     0,     0,     0,
       0,     0,    33,    13,    55,     0,     0,     0,   105,     0,
      33,    14,     0,    10,     8,     0,    44,    41,    19,     0,
      98,    69,    70,    67,    68,    65,    66,    71,    72,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      62,    63,    95,    46,   106,     0,     0,    33,   102,   110,
       0,     9,    43,     0,     0,     0,    61,    93,    92,    91,
      90,    89,    86,    87,    83,    85,    82,    84,    80,    81,
      76,    77,    78,    79,    88,    75,    97,     0,    48,   107,
      99,    33,   108,   105,   101,     0,     0,    46,     0,    74,
       0,    94,    64,    50,    42,     0,     0,     0,     0,     0,
       0,     0,     0,   125,   130,   116,     0,   117,     0,   124,
       0,    33,   115,   123,   122,   121,   120,   119,   104,   111,
     100,   109,    45,    73,    97,    50,    47,   135,     0,   136,
     137,   140,     0,     0,     0,     0,     0,     0,    14,   118,
     112,   113,    96,    54,    52,    53,   134,   139,     0,     0,
       0,     0,     0,     0,     0,    50,     0,   140,     0,     0,
       0,     0,   126,   131,    52,    49,     0,   141,     0,   145,
     152,     0,     0,    51,   140,     0,     0,     0,     0,   145,
       0,   150,     0,   132,     0,   142,     0,   149,   143,   144,
     151,   127,     0,     0,   149,   149,   147,     0,   133,   138,
     146,   148,   128,     0,   129
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -208,  -208,   102,  -143,   222,   245,    17,   -30,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -142,   254,   216,  -103,  -208,
     131,    65,    73,   -31,  -208,   103,  -208,  -208,   -27,   147,
     185,  -208,  -208,  -114,   115,  -208,  -137,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -207,  -208,  -208,    52,
    -208,  -140,  -208,  -208
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    38,    19,    20,     5,     6,     7,
       8,     9,    10,    27,    47,    11,    21,    40,    80,   164,
     213,   226,   214,   178,   147,   161,    64,    12,    67,   118,
      68,    13,   155,   179,   180,   181,   265,   206,   241,   267,
     273,   207,   242,   262,   183,   184,   218,   185,   186,   248,
     249,   266,   187,   251
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      63,    65,   152,    66,    66,   124,    -7,    69,   175,   177,
     148,    14,   -31,   -31,   182,   125,   246,   247,    31,     1,
     236,   -26,   -26,    81,    82,    83,    84,    85,    86,    87,
      88,    90,    89,   203,     1,    36,   -31,   254,   175,   177,
      66,   189,   191,   120,   182,   -26,   -31,    70,   123,    48,
      49,    50,    51,    52,   192,   -26,   -27,   -27,    34,     1,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,    53,
     -27,   146,    31,    35,    31,    37,    71,    66,  -103,    36,
     -27,   237,    16,    17,   159,   114,   208,    39,    54,    55,
      56,    57,    58,    59,    60,    61,    15,    32,    75,    32,
      72,    33,    62,    28,    29,    30,    18,   240,    74,   115,
      72,   176,   110,   111,   270,   271,   269,   193,   150,   194,
     112,   151,   190,    77,   198,   151,   260,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     -37,   176,   108,   109,   110,   111,    48,    49,    50,    51,
      52,    79,   112,   -38,   215,   -39,     1,    78,   116,   117,
     217,   219,   119,   221,   222,   165,   166,   167,   168,   169,
     170,   171,    31,    71,   172,    32,    53,   149,   173,   174,
       1,   154,   232,   233,   215,   156,   217,   163,   238,   158,
     162,   151,   195,   239,   199,    54,    55,    56,    57,    58,
      59,    60,    61,   217,   201,   256,   210,   151,  -114,    62,
      41,   261,    48,    49,    50,    51,    52,    42,    43,    44,
     200,    45,    46,   202,   204,   220,   205,   223,   224,   225,
     229,   165,   166,   167,   168,   169,   170,   171,   227,   235,
     172,   244,    53,   250,   173,   174,    48,    49,    50,    51,
      52,    22,    23,   252,    24,    25,   253,   255,   257,    26,
     258,    54,    55,    56,    57,    58,    59,    60,    61,   263,
     272,   268,    73,   151,   274,    62,    53,    48,    49,    50,
      51,    52,   122,    76,   196,   121,   211,   212,   234,   243,
     188,   259,   153,     0,     0,    54,    55,    56,    57,    58,
      59,    60,    61,     0,   197,     0,     0,    53,     0,    62,
       0,    48,    49,    50,    51,    52,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    54,    55,    56,    57,
      58,    59,    60,    61,     0,     0,     0,     0,   195,     0,
      62,    53,   104,   105,   106,   107,     0,     0,     0,   109,
     110,   111,     0,     0,     0,     0,     0,     0,   112,     0,
      54,    55,    56,    57,    58,    59,    60,    61,     0,     0,
       0,     0,     0,     0,    62,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,     0,     0,   108,   109,   110,   111,     0,     0,
       0,     0,     0,     0,   112,     0,   264,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,   112,   126,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,   112,   228,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,     0,     0,   108,   109,
     110,   111,     0,     0,     0,     0,     0,     0,   112,   230,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,   112,
     231,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,     0,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
     112,   245,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,   113,     0,
       0,   112,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,   157,     0,
       0,   112,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,   160,     0,     0,     0,     0,
       0,   112,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,   209,     0,     0,     0,
       0,   112,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,   216,     0,     0,     0,
       0,   112,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,   112,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,   112,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,   112,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,   112,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
       0,     0,     0,     0,     0,     0,   112,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,     0,     0,     0,
     109,   110,   111,   102,   103,   104,   105,   106,   107,   112,
     104,   105,   109,   110,   111,     0,     0,   109,   110,   111,
       0,   112,     0,     0,     0,     0,   112
};

static const yytype_int16 yycheck[] =
{
      31,    32,   116,    33,    34,    57,     0,    34,   151,   151,
     113,     0,    33,    34,   151,    67,    29,    30,    37,    13,
     227,    33,    34,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    62,   170,    13,    18,    57,   244,   181,   181,
      70,   155,   156,    70,   181,    57,    67,    66,    79,     3,
       4,     5,     6,     7,   157,    67,    33,    34,    66,    13,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,    33,
      57,   112,    37,    33,    37,    60,    33,   117,    67,    72,
      67,   228,    33,    34,   125,    33,    33,    60,    52,    53,
      54,    55,    56,    57,    58,    59,     4,    62,    33,    62,
      57,    66,    66,    11,    12,    13,    57,   231,    61,    57,
      57,   151,    58,    59,   264,   265,   263,   158,    61,   160,
      66,    64,    61,    61,   165,    64,   250,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
       8,   181,    56,    57,    58,    59,     3,     4,     5,     6,
       7,    62,    66,     8,   195,     8,    13,     8,    67,    60,
     201,   202,    67,   204,   205,    22,    23,    24,    25,    26,
      27,    28,    37,    33,    31,    62,    33,    33,    35,    36,
      13,    61,   223,   224,   225,    67,   227,    37,   229,    67,
      67,    64,    64,    64,    61,    52,    53,    54,    55,    56,
      57,    58,    59,   244,    66,   246,    65,    64,    65,    66,
       9,   252,     3,     4,     5,     6,     7,    16,    17,    18,
      61,    20,    21,    66,    66,    26,    66,    66,    66,    60,
      66,    22,    23,    24,    25,    26,    27,    28,    61,    65,
      31,    61,    33,    32,    35,    36,     3,     4,     5,     6,
       7,    11,    12,    60,    14,    15,    67,    61,    68,    19,
      65,    52,    53,    54,    55,    56,    57,    58,    59,    67,
      67,    61,    37,    64,    61,    66,    33,     3,     4,     5,
       6,     7,    76,    39,   163,    73,   181,   194,   225,   234,
     153,   249,   117,    -1,    -1,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    61,    -1,    -1,    33,    -1,    66,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    64,    -1,
      66,    33,    50,    51,    52,    53,    -1,    -1,    -1,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    -1,    -1,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    68,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    -1,    -1,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    -1,    -1,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    -1,    -1,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    -1,    -1,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    56,    57,    58,    59,    -1,    -1,    -1,    63,    -1,
      -1,    66,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    56,    57,    58,    59,    -1,    -1,    -1,    63,    -1,
      -1,    66,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    66,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    56,    57,    58,    59,    -1,    61,    -1,    -1,    -1,
      -1,    66,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    56,    57,    58,    59,    -1,    61,    -1,    -1,    -1,
      -1,    66,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    -1,    -1,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    -1,    -1,    -1,
      57,    58,    59,    48,    49,    50,    51,    52,    53,    66,
      50,    51,    57,    58,    59,    -1,    -1,    57,    58,    59,
      -1,    66,    -1,    -1,    -1,    -1,    66
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    89,    90,    91,    95,    96,    97,    98,    99,
     100,   103,   115,   119,     0,    90,    33,    34,    57,    93,
      94,   104,    11,    12,    14,    15,    19,   101,    90,    90,
      90,    37,    62,    66,    66,    33,    94,    60,    92,    60,
     105,     9,    16,    17,    18,    20,    21,   102,     3,     4,
       5,     6,     7,    33,    52,    53,    54,    55,    56,    57,
      58,    59,    66,   111,   114,   111,    95,   116,   118,   116,
      66,    33,    57,    93,    61,    33,   104,    61,     8,    62,
     106,   111,   111,   111,   111,   111,   111,   111,   111,    95,
     111,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    56,    57,
      58,    59,    66,    63,    33,    57,    67,    60,   117,    67,
     116,    92,   105,   111,    57,    67,    67,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   112,   106,    33,
      61,    64,   121,   118,    61,   120,    67,    63,    67,   111,
      60,   113,    67,    37,   107,    22,    23,    24,    25,    26,
      27,    28,    31,    35,    36,    91,    95,   103,   111,   121,
     122,   123,   124,   132,   133,   135,   136,   140,   117,   121,
      61,   121,   106,   111,   111,    64,   108,    61,   111,    61,
      61,    66,    66,   124,    66,    66,   125,   129,    33,    61,
      65,   122,   113,   108,   110,   111,    61,   111,   134,   111,
      26,   111,   111,    66,    66,    60,   109,    61,    67,    66,
      67,    67,   111,   111,   110,    65,   134,   124,   111,    64,
     121,   126,   130,   109,    61,    67,    29,    30,   137,   138,
      32,   141,    60,    67,   134,    61,   111,    68,    65,   137,
     121,   111,   131,    67,    68,   124,   139,   127,    61,   124,
     139,   139,    67,   128,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    90,    90,    90,    90,    90,    91,    92,
      92,    93,    93,    94,    94,    95,    95,    95,    95,    96,
      97,    97,    97,    97,    97,    97,    98,    98,    98,    98,
      98,    99,   100,   100,   101,   101,   101,   102,   102,   102,
     102,   103,   104,   105,   105,   106,   106,   107,   107,   108,
     108,   109,   109,   110,   110,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   112,   112,   113,   113,   114,   115,
     115,   115,   116,   116,   117,   117,   118,   118,   119,   119,
     120,   119,   121,   122,   122,   123,   123,   123,   124,   124,
     124,   124,   124,   124,   124,   125,   126,   127,   128,   124,
     129,   130,   131,   124,   132,   132,   132,   132,   133,   134,
     134,   135,   135,   136,   137,   137,   138,   138,   139,   139,
     140,   141,   141
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     0,     4,     3,
       0,     2,     1,     3,     1,     1,     1,     1,     1,     4,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
       2,     1,     1,     0,     1,     1,     0,     1,     1,     1,
       0,     4,     6,     3,     0,     4,     0,     2,     0,     4,
       0,     3,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     2,     4,     2,     2,     2,     2,     2,
       2,     2,     2,     5,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     0,     3,     0,     2,     6,
       7,     6,     2,     0,     3,     0,     2,     3,     6,     7,
       0,     7,     3,     2,     0,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     0,     0,     0,     0,    11,
       0,     0,     0,     8,     3,     2,     2,     2,     9,     1,
       0,     5,     7,     7,     2,     0,     4,     3,     2,     0,
       6,     2,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 192 "parser.y" /* yacc.c:1646  */
    {printf("%s",(yyvsp[0].sVal));}
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 194 "parser.y" /* yacc.c:1646  */
    {char* s = malloc(sizeof(char)*(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))+20)); strcpy(s,""); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 196 "parser.y" /* yacc.c:1646  */
    {char* s = malloc(sizeof(char)*(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))+20)); strcpy(s,""); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 198 "parser.y" /* yacc.c:1646  */
    {char* s = malloc(sizeof(char)*(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))+20)); strcpy(s,""); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 200 "parser.y" /* yacc.c:1646  */
    {char* s = malloc(sizeof(char)*(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))+20)); strcpy(s,""); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 200 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 202 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_SCALAR_LEFT);strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));strcat(s,_SCALAR_RIGHT);(yyval.sVal)=s;}
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 204 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 204 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 206 "parser.y" /* yacc.c:1646  */
    {
            char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;
            ptrType = 1;
            }
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 210 "parser.y" /* yacc.c:1646  */
    {
            (yyval.sVal)=(yyvsp[0].sVal);
            ptrType = 0;}
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 214 "parser.y" /* yacc.c:1646  */
    {
        installSymbol((yyvsp[-2].sVal));
        int index = lookUpSymbol((yyvsp[-2].sVal));
        setSymbolType(index,ptrType);
        fprintf(codegen,"//start type ident \n");
        fprintf(codegen,"lw t0, 0(sp)  \n");
        fprintf(codegen,"addi sp,sp, 4 \n");
        fprintf(codegen,"sw t0, %d(fp) \n", -1*index*4-16);
        fprintf(codegen,"//finish type ident \n\n");
        setSymbolMemory(index,-1*index*4-16);
        }
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 225 "parser.y" /* yacc.c:1646  */
    {}
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 228 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 1923 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 229 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 230 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 1935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 232 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 234 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 235 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 236 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1959 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 237 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 238 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 239 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 241 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1983 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 242 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 243 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 244 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 245 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 247 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[0].sVal));  (yyval.sVal)=s;}
#line 2013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 249 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2019 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 249 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2025 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 251 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 251 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 251 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 253 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 253 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 253 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2061 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 253 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 255 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_ARRAY_LEFT);strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));strcat(s,_ARRAY_RIGHT);(yyval.sVal)=s;}
#line 2073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 257 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 259 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2085 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 259 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 261 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2097 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 261 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 263 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 263 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 265 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2121 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 265 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2127 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 267 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2133 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 267 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 269 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2145 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 269 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2151 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 271 "parser.y" /* yacc.c:1646  */
    {char*s = reserveStr(strlen((yyvsp[0].sVal)));(yyval.sVal)=s;
            int index = lookUpSymbol((yyvsp[0].sVal));
            int memoryLocation = getSymbolMemory(index);
            fprintf(codegen,"lw t0, %d(fp)  \n", memoryLocation);
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n\n");}
#line 2162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 277 "parser.y" /* yacc.c:1646  */
    {
            char*s = reserveStr(strlen(intToString((yyvsp[0].iVal)))); strcat(s,_EXPR_LEFT); strcat(s,intToString((yyvsp[0].iVal)));    strcat(s,_EXPR_RIGHT);(yyval.sVal)=s;
            //fprintf(codegen,"li t0, %d       \n",$1);
            //fprintf(codegen,"addi sp, sp, -4 \n");
            //fprintf(codegen,"sw t0, 0(sp)    \n",$1);
            fprintf(codegen, "li t0, %d       \n", (yyvsp[0].iVal));
            fprintf(codegen, "addi sp, sp, -4 \n");
            fprintf(codegen, "sw t0, 0(sp)    \n");
            }
#line 2176 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 286 "parser.y" /* yacc.c:1646  */
    {char*s = reserveStr(strlen(doubleToString((yyvsp[0].dVal)))); strcat(s,_EXPR_LEFT); strcat(s,doubleToString((yyvsp[0].dVal))); strcat(s,_EXPR_RIGHT);(yyval.sVal)=s;}
#line 2182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 287 "parser.y" /* yacc.c:1646  */
    {char*s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[0].sVal));                 strcat(s,_EXPR_RIGHT);(yyval.sVal)=s;}
#line 2188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 288 "parser.y" /* yacc.c:1646  */
    {char*s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[0].sVal));                 strcat(s,_EXPR_RIGHT);(yyval.sVal)=s;}
#line 2194 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 289 "parser.y" /* yacc.c:1646  */
    {char*s = reserveStr(5); strcat(s,_EXPR_LEFT); strcat(s,"0");                strcat(s,_EXPR_RIGHT);(yyval.sVal)=s;}
#line 2200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 290 "parser.y" /* yacc.c:1646  */
    {
            char*s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;
            }
#line 2208 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 294 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2214 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 295 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2220 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 297 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2226 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 300 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;
            int index = lookUpSymbol((yyvsp[0].sVal));
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"li t0, %d      \n", index);
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n");
            }
#line 2239 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 308 "parser.y" /* yacc.c:1646  */
    {
            char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;
            int index = lookUpSymbol((yyvsp[0].sVal));
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"lw t1, %d(fp)\n", index);
            fprintf(codegen,"addi sp,sp, -4  \n");
            fprintf(codegen,"sw t1, 0(sp)\n");}
#line 2252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 316 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2258 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 317 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2264 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 318 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2270 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 319 "parser.y" /* yacc.c:1646  */
    {
            char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;
            int index = lookUpSymbol((yyvsp[0].sVal));
            fprintf(codegen,"lw t0, 0(sp)   \n");
            }
#line 2280 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 324 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 325 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2292 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 326 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2298 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 327 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2304 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 329 "parser.y" /* yacc.c:1646  */
    {
            char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"lw t1, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"mul t0, t0, t1 \n");
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n\n");
            }
#line 2319 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 339 "parser.y" /* yacc.c:1646  */
    {
            char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"lw t1, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"div t0, t1, t0 \n");
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n\n");
            }
#line 2334 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 349 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2340 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 351 "parser.y" /* yacc.c:1646  */
    {
            char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"lw t1, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"add t0, t0, t1 \n");
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n\n");}
#line 2354 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 360 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"lw t1, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"sub t0, t1, t0 \n");
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n\n");}
#line 2367 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 369 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2373 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 370 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2379 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 372 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2385 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 373 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2391 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 374 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2397 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 375 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2403 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 377 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2409 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 378 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2415 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 380 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2421 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 382 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2427 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 384 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2433 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 386 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2439 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 388 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 390 "parser.y" /* yacc.c:1646  */
    {
            char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;
            int index = lookUpSymbol((yyvsp[-2].sVal));
            int memoryLocation = getSymbolMemory(index);
            fprintf(codegen,"//enter expr assign \n");
            fprintf(codegen,"lw t0, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"lw t1, 0(sp)   \n");
            fprintf(codegen,"addi sp,sp, 4  \n");
            fprintf(codegen,"sw t0, %d(fp)  \n", memoryLocation);
            fprintf(codegen,"addi sp,sp, -4 \n");
            fprintf(codegen,"sw t0, 0(sp)   \n");
            fprintf(codegen,"//finish expr assign \n\n");}
#line 2463 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 404 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 404 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 406 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 406 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 408 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 410 "parser.y" /* yacc.c:1646  */
    {
                        char* s = reserveStr(strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); 
                        strcat(s,_FUNC_DECL_LEFT);
                        strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));
                        strcat(s,_FUNC_DECL_RIGHT);
                        (yyval.sVal)=s;}
#line 2504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 416 "parser.y" /* yacc.c:1646  */
    {
                        char* s = reserveStr(strlen((yyvsp[-6].sVal))+strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); 
                        strcat(s,_FUNC_DECL_LEFT);
                        strcat(s,(yyvsp[-6].sVal)); strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));
                        strcat(s,_FUNC_DECL_RIGHT);
                        (yyval.sVal)=s;}
#line 2515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 423 "parser.y" /* yacc.c:1646  */
    {
                        char* s = reserveStr(strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); 
                        strcat(s,_FUNC_DECL_LEFT);
                        strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));
                        strcat(s,_FUNC_DECL_RIGHT);
                        (yyval.sVal)=s;
                        installSymbol((yyvsp[-4].sVal));
                        int index = lookUpSymbol((yyvsp[-4].sVal));
                        setTotalSymbolParam(index,0);
                        }
#line 2530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 435 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 436 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 438 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 438 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 440 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 441 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 443 "parser.y" /* yacc.c:1646  */
    {
                        char* s = reserveStr(strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal)));
                        strcat(s,_FUNCT_DEF_LEFT);
                        strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));
                        strcat(s,_FUNCT_DEF_RIGHT);
                        (yyval.sVal)=s;}
#line 2577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 449 "parser.y" /* yacc.c:1646  */
    {
                        char* s = reserveStr(strlen((yyvsp[-6].sVal))+strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal)));
                        strcat(s,_FUNCT_DEF_LEFT);strcat(s,(yyvsp[-6].sVal)); strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal));strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));
                        strcat(s,_FUNCT_DEF_RIGHT);
                        (yyval.sVal)=s;}
#line 2587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 454 "parser.y" /* yacc.c:1646  */
    {
                        curScope++;
                        setScopeAndOffsetOfParam((yyvsp[-3].sVal));
                        codeGenFuncHeader((yyvsp[-3].sVal));
                    }
#line 2597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 458 "parser.y" /* yacc.c:1646  */
    {
                        codeGenAtEndOfFunctionBody((yyvsp[-5].sVal));
                        fprintf(codegen,"\n");}
#line 2605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 462 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2611 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 464 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 464 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2623 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 466 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 466 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 466 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 468 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 469 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 470 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 471 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 472 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2671 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 473 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 474 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 475 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"addi sp, sp, -8  \n");
            fprintf(codegen,"sd ra, 0(sp)  \n");
        }
#line 2692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 479 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"ld a0, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 4  \n");}
#line 2700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 482 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"ld a1, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 4  \n");}
#line 2708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 485 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"jal ra,digitalWrite  \n");}
#line 2715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 487 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"ld ra, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 8\n\n");
        }
#line 2724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 491 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"addi sp, sp, -8  \n");
            fprintf(codegen,"sd ra, 0(sp)  \n");
        }
#line 2733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 495 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"ld a0, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 4  \n");}
#line 2741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 498 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"jal ra, delay  \n");}
#line 2748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 500 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"ld ra, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 8\n\n");
        }
#line 2757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 506 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2763 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 507 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 508 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 509 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 511 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-8].sVal))+strlen((yyvsp[-7].sVal))+strlen((yyvsp[-6].sVal))+strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-8].sVal)); strcat(s,(yyvsp[-7].sVal)); strcat(s,(yyvsp[-6].sVal)); strcat(s,(yyvsp[-5].sVal));strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 513 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 513 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 515 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 516 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-6].sVal))+strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-6].sVal)); strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 518 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-6].sVal))+strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-6].sVal)); strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 520 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 521 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 523 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 524 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 526 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 526 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 528 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-5].sVal));strcat(s,(yyvsp[-4].sVal));strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 530 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 531 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2871 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2875 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 533 "parser.y" /* yacc.c:1906  */

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
