#define INT 257
#define MYCHAR 258
#define MYSTRING 259
#define MYNULL 260
#define DOUBLE 261
#define INTTYPE 262
#define CHARTYPE 263
#define STRINGTYPE 264
#define DOUBLETYPE 265
#define FLOATTYPE 266
#define CONSTTYPE 267
#define SIGNEDTYPE 268
#define UNSIGNEDTYPE 269
#define LONGLONGTYPE 270
#define LONGTYPE 271
#define SHORTTYPE 272
#define VOIDTYPE 273
#define CHAR4TYPE 274
#define CHAR8TYPE 275
#define RETURN 276
#define BREAK 277
#define CONTINUE 278
#define FOR 279
#define WHILE 280
#define DO 281
#define SWITCH 282
#define CASE 283
#define DEFAULT 284
#define IF 285
#define ELSE 286
#define IDENT 287
#define CODEGEN 288
#define DIGITALWRITE 289
#define DELAY 290
#define ASSIGN 291
#define LOGICALOR 292
#define LOGICALAND 293
#define BITWISEOR 294
#define XOR 295
#define EQ 296
#define NOTEQ 297
#define BIGOREQ 298
#define SMALLOREQ 299
#define BIG 300
#define SMALL 301
#define SHIFTLEFT 302
#define SHIFTRIGHT 303
#define SLASH 304
#define MOD 305
#define ADD 306
#define MINUS 307
#define TILDA 308
#define EXCLAMATION 309
#define BITWISEAND 310
#define MULSTAR 311
#define ADDONE 312
#define MINUSONE 313
#define COMMA 314
#define EOL 315
#define LSQUAREBRACKET 316
#define RSQUAREBRACKET 317
#define LBRACE 318
#define RBRACE 319
#define LPARENTHESIS 320
#define RPARENTHESIS 321
#define COLON 322
#define TURNEDLEFT 323
#define TURNEDRIGHT 324
#define NOASSOCIATIVE 325
#define LV13 326
#define LV12 327
#define LV11 328
#define LV10 329
#define LV9 330
#define LV8 331
#define LV7 332
#define LV6 333
#define LV5 334
#define LV4 335
#define LV3 336
#define LV2 337
#define LV1 338
#define LV0_L 339
#define LV0_N 340
#define LV0_R 341
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union { 
    int iVal;
    double dVal;
    char* sVal;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
