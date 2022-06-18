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
#define YYLAST   898

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  276

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
     204,   206,   206,   208,   210,   210,   212,   213,   214,   215,
     217,   219,   220,   221,   222,   223,   224,   226,   227,   228,
     229,   230,   232,   234,   234,   236,   236,   236,   238,   238,
     238,   238,   240,   242,   244,   244,   246,   246,   248,   248,
     250,   250,   252,   252,   254,   254,   256,   257,   266,   267,
     268,   269,   270,   272,   273,   275,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   289,   290,   291,   293,
     294,   296,   297,   299,   300,   301,   302,   304,   305,   307,
     309,   311,   313,   315,   317,   319,   319,   321,   321,   323,
     325,   331,   338,   350,   351,   353,   353,   355,   356,   358,
     364,   369,   369,   377,   379,   379,   381,   381,   381,   383,
     384,   385,   386,   387,   388,   389,   390,   394,   397,   400,
     390,   406,   410,   413,   406,   421,   422,   423,   424,   426,
     428,   428,   430,   431,   433,   435,   436,   438,   439,   441,
     441,   443,   445,   446
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
  "scalarDeclare", "identList", "ident", "id", "giveScalar", "type",
  "type1", "type2", "type3", "type4", "mayHaveConst", "mayHaveSign",
  "mayLongOrShort", "arrayDeclare", "array", "arrayList",
  "lrSquareBracketList", "giveArray", "arrayContent", "itemList", "item",
  "expr", "contiExpr", "exprList", "identOrArray", "functionDeclare",
  "parameters", "parameterList", "parameter", "functionDefinition", "$@1",
  "compoundStmt", "stmtOrVarDeclares", "stmtOrVarDeclare", "stmt", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "returnBreakContinueStmt",
  "forStmt", "mayHaveExpr", "whileStmt", "switchStmt", "switchCluses",
  "switchClue", "stmts", "ifOrIfElseStmt", "mayHaveElse", YY_NULLPTR
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

#define YYPACT_NINF -169

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-169)))

#define YYTABLE_NINF -116

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      96,   -21,    14,  -169,    96,   -17,  -169,  -169,  -169,  -169,
     251,    96,    96,    96,  -169,  -169,    19,   -18,    60,    51,
    -169,    52,  -169,  -169,    50,    53,  -169,   212,  -169,  -169,
    -169,   319,   319,    22,  -169,    22,   -27,  -169,    57,    55,
      88,    62,  -169,   118,   121,   126,  -169,  -169,   128,  -169,
    -169,  -169,  -169,  -169,    75,   319,   319,   319,   319,   319,
     319,   319,   319,    47,   686,  -169,   536,    58,    84,   102,
      99,    22,   127,   135,    51,  -169,   107,    52,  -169,  -169,
     319,  -169,   125,   125,   125,   125,   125,   125,   125,   125,
     -48,   381,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,  -169,  -169,   319,    75,  -169,   137,   -43,   160,  -169,
     131,   119,  -169,  -169,   566,   129,   319,  -169,   686,   714,
     741,   767,    97,   815,   815,   827,   827,   827,   827,   303,
     303,   125,   125,   832,   832,   792,   125,   596,   133,   151,
    -169,  -169,   154,  -169,   102,  -169,   134,   -41,    75,   319,
     125,   319,  -169,  -169,   138,  -169,   254,   140,   142,   139,
     149,   220,   165,   168,  -169,  -169,  -169,    61,  -169,   626,
    -169,   152,   154,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,   125,   596,   285,  -169,  -169,   656,
    -169,  -169,   319,   319,   178,   319,   319,   169,   170,   -15,
    -169,  -169,  -169,  -169,  -169,   177,   686,  -169,   686,   179,
     412,   172,   443,   474,   319,   319,   285,   174,   319,   220,
     319,   185,   134,   686,   686,   177,  -169,   180,  -169,   505,
      29,   218,   192,   187,  -169,   319,   203,   319,   199,   204,
      29,   134,  -169,   319,  -169,   201,  -169,   349,   220,  -169,
    -169,  -169,   686,   210,   220,   220,   220,  -169,   213,  -169,
    -169,  -169,  -169,  -169,   221,  -169
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      34,    33,     0,     2,    34,     0,    16,    17,    18,    19,
      37,    34,    34,    34,     1,     3,    15,     0,     0,    10,
      12,    45,    30,    29,    35,    36,    31,    41,     4,     5,
       6,     0,     0,    34,    13,    34,    15,    11,     0,     0,
       0,     0,    24,    21,    22,    23,    25,    26,     0,    57,
      59,    60,    61,    58,    47,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    14,    56,     0,     0,     0,   106,
       0,    34,    15,     0,    10,     8,     0,    45,    42,    20,
       0,    99,    70,    71,    68,    69,    66,    67,    72,    73,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    63,    64,    96,    47,   107,     0,     0,    34,   103,
     111,     0,     9,    44,     0,     0,     0,    62,    94,    93,
      92,    91,    90,    87,    88,    84,    86,    83,    85,    81,
      82,    77,    78,    79,    80,    89,    76,    98,     0,    49,
     108,   100,    34,   109,   106,   102,     0,     0,    47,     0,
      75,     0,    95,    65,    51,    43,     0,     0,     0,     0,
       0,     0,     0,     0,   126,   131,   117,     0,   118,     0,
     125,     0,    34,   116,   124,   123,   122,   121,   120,   105,
     112,   101,   110,    46,    74,    98,    51,    48,   136,     0,
     137,   138,   141,     0,     0,     0,     0,     0,     0,    15,
     119,   113,   114,    97,    55,    53,    54,   135,   140,     0,
       0,     0,     0,     0,     0,     0,    51,     0,   141,     0,
       0,     0,     0,   127,   132,    53,    50,     0,   142,     0,
     146,   153,     0,     0,    52,   141,     0,     0,     0,     0,
     146,     0,   151,     0,   133,     0,   143,     0,   150,   144,
     145,   152,   128,     0,     0,   150,   150,   148,     0,   134,
     139,   147,   149,   129,     0,   130
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -169,  -169,   120,  -145,   207,   245,   -16,  -169,   -30,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -144,   253,   208,  -103,
    -169,   130,    63,    69,   -31,  -169,   101,  -169,  -169,   -29,
     143,   181,  -169,  -169,  -113,   122,  -169,  -137,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,  -120,  -169,  -169,
      64,  -169,  -168,  -169,  -169
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    39,    19,    20,    34,     5,     6,
       7,     8,     9,    10,    27,    48,    11,    21,    41,    81,
     165,   214,   227,   215,   179,   148,   162,    65,    12,    68,
     119,    69,    13,   156,   180,   181,   182,   266,   207,   242,
     268,   274,   208,   243,   263,   184,   185,   219,   186,   187,
     249,   250,   267,   188,   252
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,    66,    37,    67,   153,    67,    70,   176,   178,   125,
      31,   149,   -32,   -32,    14,   183,    16,    17,   151,   126,
     191,   152,    31,   152,    82,    83,    84,    85,    86,    87,
      88,    89,    91,    90,   204,     1,   -32,   176,   178,    71,
      18,    67,   121,   190,   192,   183,   -32,    32,    35,   124,
      49,    50,    51,    52,    53,   193,    31,    37,   247,   248,
       1,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
      54,    32,   147,   -27,   -27,    33,   -28,   -28,    67,  -104,
      72,   115,   238,    36,   209,   160,    -7,   271,   272,    55,
      56,    57,    58,    59,    60,    61,    62,   -27,   237,     1,
     -28,    38,    40,    63,    73,   116,    75,   -27,    73,   241,
     -28,    76,   177,    78,    15,   255,   -38,   270,   194,   -39,
     195,    28,    29,    30,   -40,   199,    79,    80,   261,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   117,   177,   109,   110,   111,   112,    49,    50,    51,
      52,    53,   118,   113,    31,   216,   120,     1,    72,    32,
     150,   218,   220,     1,   222,   223,   166,   167,   168,   169,
     170,   171,   172,   111,   112,   173,   157,    54,   164,   174,
     175,   113,   155,   233,   234,   216,   159,   218,   152,   239,
     163,   200,   196,   201,   221,   202,    55,    56,    57,    58,
      59,    60,    61,    62,   218,   203,   257,   211,   152,  -115,
      63,    42,   262,    49,    50,    51,    52,    53,    43,    44,
      45,   205,    46,    47,   206,   224,   225,   226,   230,   236,
     228,   245,   166,   167,   168,   169,   170,   171,   172,   240,
     251,   173,   253,    54,   254,   174,   175,    49,    50,    51,
      52,    53,    22,    23,   256,    24,    25,   258,   264,   259,
      26,   269,    55,    56,    57,    58,    59,    60,    61,    62,
     273,   122,   275,    74,   152,   123,    63,    54,    49,    50,
      51,    52,    53,    77,   197,   235,   213,   189,   244,   154,
       0,     0,     0,     0,   212,     0,    55,    56,    57,    58,
      59,    60,    61,    62,   260,   198,     0,     0,    54,     0,
      63,     0,    49,    50,    51,    52,    53,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    55,    56,    57,
      58,    59,    60,    61,    62,     0,     0,     0,     0,   196,
       0,    63,    54,   105,   106,   107,   108,     0,     0,     0,
     110,   111,   112,     0,     0,     0,     0,     0,     0,   113,
       0,    55,    56,    57,    58,    59,    60,    61,    62,     0,
       0,     0,     0,     0,     0,    63,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,     0,     0,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,   113,     0,   265,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,     0,     0,   109,   110,   111,
     112,     0,     0,     0,     0,     0,     0,   113,   127,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,     0,     0,   109,   110,
     111,   112,     0,     0,     0,     0,     0,     0,   113,   229,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,     0,     0,   109,
     110,   111,   112,     0,     0,     0,     0,     0,     0,   113,
     231,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,     0,     0,
     109,   110,   111,   112,     0,     0,     0,     0,     0,     0,
     113,   232,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,     0,
       0,   109,   110,   111,   112,     0,     0,     0,     0,     0,
       0,   113,   246,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
       0,     0,   109,   110,   111,   112,     0,     0,     0,   114,
       0,     0,   113,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
       0,     0,   109,   110,   111,   112,     0,     0,     0,   158,
       0,     0,   113,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
       0,     0,   109,   110,   111,   112,   161,     0,     0,     0,
       0,     0,   113,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
       0,     0,   109,   110,   111,   112,     0,   210,     0,     0,
       0,     0,   113,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
       0,     0,   109,   110,   111,   112,     0,   217,     0,     0,
       0,     0,   113,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
       0,     0,   109,   110,   111,   112,     0,     0,     0,     0,
       0,     0,   113,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,     0,     0,
     109,   110,   111,   112,     0,     0,     0,     0,     0,     0,
     113,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,     0,     0,   109,   110,   111,
     112,     0,     0,     0,     0,     0,     0,   113,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,     0,     0,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,   113,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,     0,     0,     0,   110,
     111,   112,     0,     0,     0,     0,     0,     0,   113,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,     0,
       0,     0,   110,   111,   112,   103,   104,   105,   106,   107,
     108,   113,   105,   106,   110,   111,   112,     0,     0,   110,
     111,   112,     0,   113,     0,     0,     0,     0,   113
};

static const yytype_int16 yycheck[] =
{
      31,    32,    18,    33,   117,    35,    35,   152,   152,    57,
      37,   114,    33,    34,     0,   152,    33,    34,    61,    67,
      61,    64,    37,    64,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    63,   171,    13,    57,   182,   182,    66,
      57,    71,    71,   156,   157,   182,    67,    62,    66,    80,
       3,     4,     5,     6,     7,   158,    37,    73,    29,    30,
      13,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
      33,    62,   113,    33,    34,    66,    33,    34,   118,    67,
      33,    33,   229,    33,    33,   126,     0,   265,   266,    52,
      53,    54,    55,    56,    57,    58,    59,    57,   228,    13,
      57,    60,    60,    66,    57,    57,    61,    67,    57,   232,
      67,    33,   152,    61,     4,   245,     8,   264,   159,     8,
     161,    11,    12,    13,     8,   166,     8,    62,   251,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    67,   182,    56,    57,    58,    59,     3,     4,     5,
       6,     7,    60,    66,    37,   196,    67,    13,    33,    62,
      33,   202,   203,    13,   205,   206,    22,    23,    24,    25,
      26,    27,    28,    58,    59,    31,    67,    33,    37,    35,
      36,    66,    61,   224,   225,   226,    67,   228,    64,   230,
      67,    61,    64,    61,    26,    66,    52,    53,    54,    55,
      56,    57,    58,    59,   245,    66,   247,    65,    64,    65,
      66,     9,   253,     3,     4,     5,     6,     7,    16,    17,
      18,    66,    20,    21,    66,    66,    66,    60,    66,    65,
      61,    61,    22,    23,    24,    25,    26,    27,    28,    64,
      32,    31,    60,    33,    67,    35,    36,     3,     4,     5,
       6,     7,    11,    12,    61,    14,    15,    68,    67,    65,
      19,    61,    52,    53,    54,    55,    56,    57,    58,    59,
      67,    74,    61,    38,    64,    77,    66,    33,     3,     4,
       5,     6,     7,    40,   164,   226,   195,   154,   235,   118,
      -1,    -1,    -1,    -1,   182,    -1,    52,    53,    54,    55,
      56,    57,    58,    59,   250,    61,    -1,    -1,    33,    -1,
      66,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    64,
      -1,    66,    33,    50,    51,    52,    53,    -1,    -1,    -1,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    -1,    -1,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    68,    37,    38,
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
      -1,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    56,    57,    58,    59,    -1,    -1,    -1,    63,
      -1,    -1,    66,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    56,    57,    58,    59,    -1,    -1,    -1,    63,
      -1,    -1,    66,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    66,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    56,    57,    58,    59,    -1,    61,    -1,    -1,
      -1,    -1,    66,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    56,    57,    58,    59,    -1,    61,    -1,    -1,
      -1,    -1,    66,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    -1,    -1,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    -1,    -1,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    66,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    -1,    -1,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    -1,    -1,    -1,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    66,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    -1,    57,    58,    59,    48,    49,    50,    51,    52,
      53,    66,    50,    51,    57,    58,    59,    -1,    -1,    57,
      58,    59,    -1,    66,    -1,    -1,    -1,    -1,    66
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    89,    90,    91,    96,    97,    98,    99,   100,
     101,   104,   116,   120,     0,    90,    33,    34,    57,    93,
      94,   105,    11,    12,    14,    15,    19,   102,    90,    90,
      90,    37,    62,    66,    95,    66,    33,    94,    60,    92,
      60,   106,     9,    16,    17,    18,    20,    21,   103,     3,
       4,     5,     6,     7,    33,    52,    53,    54,    55,    56,
      57,    58,    59,    66,   112,   115,   112,    96,   117,   119,
     117,    66,    33,    57,    93,    61,    33,   105,    61,     8,
      62,   107,   112,   112,   112,   112,   112,   112,   112,   112,
      96,   112,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    56,
      57,    58,    59,    66,    63,    33,    57,    67,    60,   118,
      67,   117,    92,   106,   112,    57,    67,    67,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   113,   107,
      33,    61,    64,   122,   119,    61,   121,    67,    63,    67,
     112,    60,   114,    67,    37,   108,    22,    23,    24,    25,
      26,    27,    28,    31,    35,    36,    91,    96,   104,   112,
     122,   123,   124,   125,   133,   134,   136,   137,   141,   118,
     122,    61,   122,   107,   112,   112,    64,   109,    61,   112,
      61,    61,    66,    66,   125,    66,    66,   126,   130,    33,
      61,    65,   123,   114,   109,   111,   112,    61,   112,   135,
     112,    26,   112,   112,    66,    66,    60,   110,    61,    67,
      66,    67,    67,   112,   112,   111,    65,   135,   125,   112,
      64,   122,   127,   131,   110,    61,    67,    29,    30,   138,
     139,    32,   142,    60,    67,   135,    61,   112,    68,    65,
     138,   122,   112,   132,    67,    68,   125,   140,   128,    61,
     125,   140,   140,    67,   129,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    90,    90,    90,    90,    90,    91,    92,
      92,    93,    93,    94,    95,    95,    96,    96,    96,    96,
      97,    98,    98,    98,    98,    98,    98,    99,    99,    99,
      99,    99,   100,   101,   101,   102,   102,   102,   103,   103,
     103,   103,   104,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   110,   110,   111,   111,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   113,   113,   114,   114,   115,
     116,   116,   116,   117,   117,   118,   118,   119,   119,   120,
     120,   121,   120,   122,   123,   123,   124,   124,   124,   125,
     125,   125,   125,   125,   125,   125,   126,   127,   128,   129,
     125,   130,   131,   132,   125,   133,   133,   133,   133,   134,
     135,   135,   136,   136,   137,   138,   138,   139,   139,   140,
     140,   141,   142,   142
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     0,     4,     3,
       0,     2,     1,     2,     2,     0,     1,     1,     1,     1,
       4,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       2,     2,     1,     1,     0,     1,     1,     0,     1,     1,
       1,     0,     4,     6,     3,     0,     4,     0,     2,     0,
       4,     0,     3,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     2,     4,     2,     2,     2,     2,
       2,     2,     2,     2,     5,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     0,     3,     0,     2,
       6,     7,     6,     2,     0,     3,     0,     2,     3,     6,
       7,     0,     7,     3,     2,     0,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     0,     0,     0,     0,
      11,     0,     0,     0,     8,     3,     2,     2,     2,     9,
       1,     0,     5,     7,     7,     2,     0,     4,     3,     2,
       0,     6,     2,     0
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
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 206 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 208 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 210 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s; }
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 210 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 212 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 1908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 213 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 214 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 215 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 217 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 219 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 220 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 221 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 222 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 223 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1962 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 224 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 226 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 227 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 228 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 229 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1992 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 230 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 232 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[0].sVal));  (yyval.sVal)=s;}
#line 2004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 234 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 234 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2016 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 236 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 236 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 236 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2034 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 238 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2040 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 238 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 238 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2052 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 238 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2058 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 240 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_ARRAY_LEFT);strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));strcat(s,_ARRAY_RIGHT);(yyval.sVal)=s;}
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 242 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2070 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 244 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 244 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 246 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2088 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 246 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 248 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 248 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 250 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2112 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 250 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 252 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 252 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2130 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 254 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 254 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 256 "parser.y" /* yacc.c:1646  */
    {char*s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[0].sVal));                 strcat(s,_EXPR_RIGHT);(yyval.sVal)=s;}
#line 2148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 257 "parser.y" /* yacc.c:1646  */
    {
            char*s = reserveStr(strlen(intToString((yyvsp[0].iVal)))); strcat(s,_EXPR_LEFT); strcat(s,intToString((yyvsp[0].iVal)));    strcat(s,_EXPR_RIGHT);(yyval.sVal)=s;
            //fprintf(codegen,"li t0, %d       \n",$1);
            //fprintf(codegen,"addi sp, sp, -4 \n");
            //fprintf(codegen,"sw t0, 0(sp)    \n",$1);
            fprintf(codegen, "li t0, %d       \n", (yyvsp[0].iVal));
            fprintf(codegen, "addi sp, sp, -4 \n");
            fprintf(codegen, "sw t0, 0(sp)    \n");
            }
#line 2162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 266 "parser.y" /* yacc.c:1646  */
    {char*s = reserveStr(strlen(doubleToString((yyvsp[0].dVal)))); strcat(s,_EXPR_LEFT); strcat(s,doubleToString((yyvsp[0].dVal))); strcat(s,_EXPR_RIGHT);(yyval.sVal)=s;}
#line 2168 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 267 "parser.y" /* yacc.c:1646  */
    {char*s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[0].sVal));                 strcat(s,_EXPR_RIGHT);(yyval.sVal)=s;}
#line 2174 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 268 "parser.y" /* yacc.c:1646  */
    {char*s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[0].sVal));                 strcat(s,_EXPR_RIGHT);(yyval.sVal)=s;}
#line 2180 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 269 "parser.y" /* yacc.c:1646  */
    {char*s = reserveStr(5); strcat(s,_EXPR_LEFT); strcat(s,"0");                strcat(s,_EXPR_RIGHT);(yyval.sVal)=s;}
#line 2186 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 270 "parser.y" /* yacc.c:1646  */
    {char*s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2192 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 272 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2198 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 273 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2204 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 275 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2210 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 278 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2216 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 279 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2222 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 280 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2228 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 281 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2234 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 282 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2240 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 283 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2246 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 284 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 285 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2258 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 286 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2264 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 287 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2270 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 289 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2276 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 290 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2282 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 291 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2288 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 293 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2294 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 294 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2300 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 296 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2306 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 297 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2312 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 299 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2318 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 300 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2324 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 301 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2330 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 302 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2336 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 304 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2342 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 305 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2348 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 307 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2354 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 309 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2360 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 311 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2366 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 313 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2372 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 315 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2378 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 317 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_EXPR_LEFT); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_EXPR_RIGHT); (yyval.sVal)=s;}
#line 2384 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 319 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2390 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 319 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2396 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 321 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2402 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 321 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2408 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 323 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2414 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 325 "parser.y" /* yacc.c:1646  */
    {
                        char* s = reserveStr(strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); 
                        strcat(s,_FUNC_DECL_LEFT);
                        strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));
                        strcat(s,_FUNC_DECL_RIGHT);
                        (yyval.sVal)=s;}
#line 2425 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 331 "parser.y" /* yacc.c:1646  */
    {
                        char* s = reserveStr(strlen((yyvsp[-6].sVal))+strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); 
                        strcat(s,_FUNC_DECL_LEFT);
                        strcat(s,(yyvsp[-6].sVal)); strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));
                        strcat(s,_FUNC_DECL_RIGHT);
                        (yyval.sVal)=s;}
#line 2436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 338 "parser.y" /* yacc.c:1646  */
    {
                        char* s = reserveStr(strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); 
                        strcat(s,_FUNC_DECL_LEFT);
                        strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));
                        strcat(s,_FUNC_DECL_RIGHT);
                        (yyval.sVal)=s;
                        installSymbol((yyvsp[-4].sVal));
                        int index = lookUpSymbol((yyvsp[-4].sVal));
                        table[index].totalParam = 0;
                        }
#line 2451 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 350 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 351 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2463 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 353 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 353 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 355 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 356 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 358 "parser.y" /* yacc.c:1646  */
    {
                        char* s = reserveStr(strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal)));
                        strcat(s,_FUNCT_DEF_LEFT);
                        strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));
                        strcat(s,_FUNCT_DEF_RIGHT);
                        (yyval.sVal)=s;}
#line 2498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 364 "parser.y" /* yacc.c:1646  */
    {
                        char* s = reserveStr(strlen((yyvsp[-6].sVal))+strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal)));
                        strcat(s,_FUNCT_DEF_LEFT);strcat(s,(yyvsp[-6].sVal)); strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal));strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));
                        strcat(s,_FUNCT_DEF_RIGHT);
                        (yyval.sVal)=s;}
#line 2508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 369 "parser.y" /* yacc.c:1646  */
    {
                        curScope++;
                        setScopeAndOffsetOfParam((yyvsp[-3].sVal));
                        codeGenFuncHeader((yyvsp[-3].sVal));
                    }
#line 2518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 373 "parser.y" /* yacc.c:1646  */
    {
                        codeGenAtEndOfFunctionBody((yyvsp[-5].sVal));
                        fprintf(codegen,"\n");}
#line 2526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 377 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 379 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 379 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 381 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 381 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 381 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 383 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 384 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 385 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 386 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2586 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 387 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 388 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 389 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[0].sVal))); strcat(s,_STMT_LEFT);strcat(s,(yyvsp[0].sVal)); strcat(s,_STMT_RIGHT);(yyval.sVal)=s;}
#line 2604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 390 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"addi sp, sp, -8  \n");
            fprintf(codegen,"sd ra, 0(sp)  \n");
        }
#line 2613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 394 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"ld a0, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 4  \n");}
#line 2621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 397 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"ld a1, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 4  \n");}
#line 2629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 400 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"jal ra,digitalWrite  \n");}
#line 2636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 402 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"ld ra, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 8\n\n");
        }
#line 2645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 406 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"addi sp, sp, -8  \n");
            fprintf(codegen,"sd ra, 0(sp)  \n");
        }
#line 2654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 410 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"ld a0, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 4  \n");}
#line 2662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 413 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"jal ra, delay  \n");}
#line 2669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 415 "parser.y" /* yacc.c:1646  */
    {
            fprintf(codegen,"ld ra, 0(sp)  \n");
            fprintf(codegen,"addi sp, sp, 8\n\n");
        }
#line 2678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 421 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 422 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 423 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 424 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal)); (yyval.sVal)=s;}
#line 2702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 426 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-8].sVal))+strlen((yyvsp[-7].sVal))+strlen((yyvsp[-6].sVal))+strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-8].sVal)); strcat(s,(yyvsp[-7].sVal)); strcat(s,(yyvsp[-6].sVal)); strcat(s,(yyvsp[-5].sVal));strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 428 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)=(yyvsp[0].sVal);}
#line 2714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 428 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 430 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal)); strcat(s,(yyvsp[-2].sVal)); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 431 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-6].sVal))+strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-6].sVal)); strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 433 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-6].sVal))+strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-6].sVal)); strcat(s,(yyvsp[-5].sVal)); strcat(s,(yyvsp[-4].sVal)); strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 435 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 436 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 438 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 439 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 441 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 441 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 443 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-5].sVal))+strlen((yyvsp[-4].sVal))+strlen((yyvsp[-3].sVal))+strlen((yyvsp[-2].sVal))+strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-5].sVal));strcat(s,(yyvsp[-4].sVal));strcat(s,(yyvsp[-3].sVal));strcat(s,(yyvsp[-2].sVal));strcat(s,(yyvsp[-1].sVal)); strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 445 "parser.y" /* yacc.c:1646  */
    {char* s = reserveStr(strlen((yyvsp[-1].sVal))+strlen((yyvsp[0].sVal))); strcat(s,(yyvsp[-1].sVal));strcat(s,(yyvsp[0].sVal));(yyval.sVal)=s;}
#line 2786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 446 "parser.y" /* yacc.c:1646  */
    {(yyval.sVal)="";}
#line 2792 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2796 "y.tab.c" /* yacc.c:1646  */
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
#line 448 "parser.y" /* yacc.c:1906  */

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

    yyparse();
    return 0;
}
int yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
    return 0;
}
