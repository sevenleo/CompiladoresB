/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "trabalho.y"

/*
 PRIMEIRA PARTE DO TRABALHO DE COMPILADORES - 2014/2 - PROFESSOR ZIMBRÃO

 Grupo: Felipe Lohnefink               DRE: 110027665
        Jonathan Rangel Porto          DRE: 110196757
        Leonardo Neves                 DRE: 110155777
 */
#include <cstring>
#include <string>
#include <iostream>
#include <map>

using namespace std;

/* Tamanhos máximos */
#define TAM_MAX_OPERADORES 256
#define TAM_MAX_VARS 1024
#define TAM_MAX_PARAMS 1024
#define TAM_MAX_FUNCOES 1024


const int MAX_STR = 256;

/* Tipos auxiliares, para a construcao do compilador */
struct Tipo {
  string nome;

  string tipo_base;
  int ndim;
  int tam_dim[2];

  Tipo() {}
  Tipo( string nome ) {
    this->nome = nome;
  }
};
struct Atributo {
  string v;  // Valor
  Tipo   t;  // tipo
  string c;  // codigo
  string p;  //VER PQ ELES COLOCARAM ISSO!!!!

  Atributo() {}  // inicializacao automatica para vazio ""
  Atributo( string v, string t = "", string c = "", string p = "") { //!!!
    this->v = v;
    this->t.nome = t;
    this->c = c;
    this->p = p; //!!!!
  }
};


typedef struct _TIPO_OPER
{
  string operador, op1, op2, resultado;
} TIPO_OPER;

typedef struct _SIMBOLO_VAR
{
  string nome;
  Tipo t;
} SIMBOLO_VAR;

typedef struct _PARAM
{
  string nome;
  Tipo t;
} PARAM;

typedef struct _SIMBOLO_FUNCAO
{
  string nome;
  Tipo retorno;
  int nparam;
  PARAM parametro[TAM_MAX_PARAMS];
  string lista_parametros;
} SIMBOLO_FUNCAO;

struct _NTEMP
{
  int i, r, c, s, b, d; //int, real, char, string, boolean, double
} NTEMP = {0, 0, 0, 0, 0, 0};

struct _NTEMP_GLOBAL
{
  int i, r, c, s, b, d; //int, real, char, string, boolean, double
} NTEMP_GLOBAL = {0, 0, 0, 0, 0, 0};




/* Operacoes validas */
TIPO_OPER tipo_operador[TAM_MAX_OPERADORES] = {
            {"+", "I", "I", "I"},
            {"+", "I", "R", "R"},
            {"+", "R", "R", "R"},
            {"+", "R", "I", "R"},
            {"+", "C", "C", "S"},
            {"+", "S", "C", "S"},
            {"+", "S", "S", "S"},
            {"+", "C", "I", "C"},


            {"-", "I", "I", "I"},
            {"-", "I", "R", "R"},
            {"-", "R", "R", "R"},
            {"-", "R", "I", "R"},

            {"*", "I", "I", "I"},
            {"*", "I", "R", "R"},
            {"*", "R", "I", "R"},
            {"*", "R", "R", "R"},


            {"/", "I", "I", "I"},
            {"/", "I", "R", "R"},
            {"/", "R", "I", "R"},
            {"/", "R", "R", "R"},

            {"==", "I", "I", "B"},
            {"==", "I", "R", "B"},
            {"==", "R", "I", "B"},
            {"==", "R", "R", "B"},
            {"==", "C", "C", "B"},
            {"==", "C", "S", "B"},
            {"==", "S", "C", "B"},
            {"==", "S", "S", "B"},
            {"==", "S", "S", "B"},

            {"<>", "I", "I", "B"},
            {"<>", "I", "R", "B"},
            {"<>", "R", "I", "B"},
            {"<>", "R", "R", "B"},
            {"<>", "C", "C", "B"},
            {"<>", "C", "S", "B"},
            {"<>", "S", "C", "B"},
            {"<>", "S", "S", "B"},
            {"<>", "S", "S", "B"},

            {">", "I", "I", "B"},
            {">", "I", "R", "B"},
            {">", "R", "I", "B"},
            {">", "R", "R", "B"},
            {">", "C", "C", "B"},
            {">", "C", "S", "B"},
            {">", "S", "C", "B"},
            {">", "S", "S", "B"},
            {">", "S", "S", "B"},

            {"<", "I", "I", "B"},
            {"<", "I", "R", "B"},
            {"<", "R", "I", "B"},
            {"<", "R", "R", "B"},
            {"<", "C", "C", "B"},
            {"<", "C", "S", "B"},
            {"<", "S", "C", "B"},
            {"<", "S", "S", "B"},
            {"<", "S", "S", "B"},

            {">=", "I", "I", "B"},
            {">=", "I", "R", "B"},
            {">=", "R", "I", "B"},
            {">=", "R", "R", "B"},
            {">=", "C", "C", "B"},
            {">=", "C", "S", "B"},
            {">=", "S", "C", "B"},
            {">=", "S", "S", "B"},
            {">=", "S", "S", "B"},

            {"<=", "I", "I", "B"},
            {"<=", "I", "R", "B"},
            {"<=", "R", "I", "B"},
            {"<=", "R", "R", "B"},
            {"<=", "C", "C", "B"},
            {"<=", "C", "S", "B"},
            {"<=", "S", "C", "B"},
            {"<=", "S", "S", "B"},
            {"<=", "S", "S", "B"},

            {"<-", "I", "I", "I"},
            {"<-", "R", "I", "R"},
            {"<-", "R", "R", "R"},
            {"<-", "C", "C", "C"},
            {"<-", "S", "C", "S"},
            {"<-", "S", "S", "S"},
            {"<-", "B", "B", "B"},

            {"OU", "B", "B", "B"},
            {"OU", "B", "I", "B"},
            {"OU", "I", "I", "B"},
            {"OU", "B", "C", "B"},
            {"OU", "C", "C", "B"},
            {"OU", "B", "R", "B"},
            {"OU", "R", "R", "B"},
            {"OU", "I", "B", "B"},
            {"OU", "C", "B", "B"},
            {"OU", "R", "B", "B"},
            {"E", "B", "B", "B"},
            {"E", "B", "I", "B"},
            {"E", "I", "I", "B"},
            {"E", "B", "C", "B"},
            {"E", "C", "C", "B"},
            {"E", "B", "R", "B"},
            {"E", "R", "R", "B"},
            {"E", "I", "B", "B"},
            {"E", "C", "B", "B"},
            {"E", "R", "B", "B"},

            {"+", "I", "D", "D"},
            {"+", "D", "D", "D"},
            {"+", "D", "I", "D"},
            {"-", "I", "D", "D"},
            {"-", "D", "D", "D"},
            {"-", "D", "I", "D"},
            {"*", "I", "D", "D"},
            {"*", "D", "I", "D"},
            {"*", "D", "D", "D"},
            {"*", "I", "D", "D"},
            {"*", "D", "I", "D"},
            {"*", "D", "D", "D"},
            {"*", "I", "D", "D"},
            {"*", "D", "I", "D"},
            {"*", "D", "D", "D"},
            {"==", "D", "I", "B"},
            {"==", "D", "D", "B"},
            {"<>", "I", "D", "B"},
            {"<>", "D", "I", "B"},
            {"<>", "D", "D", "B"},
            {">", "I", "D", "B"},
            {">", "D", "I", "B"},
            {">", "D", "D", "B"},
            {"<", "I", "D", "B"},
            {"<", "D", "I", "B"},
            {"<", "D", "D", "B"},
            {">=", "I", "D", "B"},
            {">=", "D", "I", "B"},
            {">=", "D", "D", "B"},
            {"<=", "I", "D", "B"},
            {"<=", "D", "I", "B"},
            {"<=", "D", "D", "B"},
            {"<-", "D", "I", "D"},
            {"<-", "D", "D", "D"},
            {"OU", "B", "D", "B"},
            {"OU", "D", "D", "B"},
            {"OU", "D", "B", "B"},
            {"E", "B", "D", "B"},
            {"E", "D", "D", "B"},
            {"E", "B", "D", "B"},
            {"E", "D", "D", "B"},

            {"+", "R", "D", "D"},
            {"+", "D", "R", "D"},
            {"-", "R", "D", "D"},
            {"-", "D", "R", "D"},
            {"*", "R", "D", "D"},
            {"*", "D", "R", "D"},
            {"/", "R", "D", "D"},
            {"/", "D", "R", "D"},
            {"==", "R", "D", "D"},
            {"==", "D", "R", "D"},
            {"<>", "R", "D", "D"},
            {"<>", "D", "R", "D"},
            {">", "R", "D", "D"},
            {">", "D", "R", "D"},
            {"<", "R", "D", "D"},
            {"<", "D", "R", "D"},
            {">=", "R", "D", "D"},
            {">=", "D", "R", "D"},
            {"<=", "R", "D", "D"},
            {"<=", "D", "R", "D"},
            {"<-", "R", "D", "D"},
            {"<-", "D", "R", "D"},
            {"OU", "R", "D", "D"},
            {"OU", "D", "R", "D"},
            {"E", "R", "D", "D"},
            {"E", "D", "R", "D"}
            };

/* Variaveis de controle, globais */
SIMBOLO_VAR TS_varlocal[TAM_MAX_VARS];
SIMBOLO_VAR TS_varglobal[TAM_MAX_VARS];
SIMBOLO_FUNCAO TS_funcao[TAM_MAX_FUNCOES];

int nrotulos = 0;
int nvarlocal = 0;
int nvarglobal = 0;
int nfuncao = 0;
int ir = 0;
int nparams = 0;

//funcoes para switch
string id_switch;
string fim_switch;
string inic;

string pipeAtivo; // Tipo do pipe ativo
string passoPipeAtivo; // Label 'fim' do pipe ativo


//funcoes
void yyerror(const char*);
int yylex();
int yyparse();

void erro(string msg);
void tipo_resultado(string operador, Atributo op1, Atributo op2, Atributo &resultado);
void gera_codigo_operador(Atributo &ss, Atributo &s1, Atributo &s2, Atributo &s3);
void insere_varglobal (string nome, Tipo t);
void insere_varlocal (string nome, Tipo t);
void inclui_funcao(string nome, Tipo retorno, string lista_parametros);
void inclui_parametro(string nome, Tipo t);

int string_inteiro(string s);

bool busca_variavelglobal (string nome, Tipo *t);
bool pode_inserir_varglobal (string nome);
bool busca_varlocal (string nome, Tipo *t);
bool busca_varparametro(string nome, Tipo *t);
bool pode_inserir_varlocal (string nome);
bool existe_funcao(string nome);
bool existe_parametro(string nome);
bool busca_funcao(string nome, Tipo *tr);
bool compara_parametros(string nome, string parametros);
bool compara_resultado(string resultado);

string inteiro_string(int n);
string gera_temp(string tipo);
string gera_rotulo();
string gera_decl_temp(string tipo, string tipo_base, int &n);
string gera_varglobal_temp();
string gera_variavellocal_temp();
string parte_vetor(Tipo t);
string quebra_codigo_lista(string vetorid, string lsttemp , string lstcodtemp);
string quebra_codigo_parametro(string nometemp, string vetorid, string lsttemp, string lstcodtemp, string tiporet);
void geraDeclaracaoVariavel( Atributo* SS, const Atributo& tipo, const Atributo& id);

string DeclaraVarPipes() {
		string ss = "";
		ss +="// *uso do pipe \n";
		ss +="bool x_boolean;\n";
		ss +="char x_string[256];\n";
		ss +="char x_char;\n";
		ss +="int x_int;\n";
		ss +="double x_double;\n";
		ss +="// uso do pipe* \n";
		ss +="float x_float;\n\n";
		
		return ss;
}

//TESTE
void geraCodigoFilter( Atributo* SS, const Atributo& condicao ) ;
void geraCodigoFor( Atributo* SS, const Atributo& inicial,
                                  const Atributo& condicao,
                                  const Atributo& passo,
                                  const Atributo& cmds );
//TESTE


string toStr( int n );

#define YYSTYPE Atributo



/* Line 268 of yacc.c  */
#line 438 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     _INT = 258,
     _CHAR = 259,
     _BOOL = 260,
     _DOUBLE = 261,
     _FLOAT = 262,
     _STRING = 263,
     _ID = 264,
     _CTE_INT = 265,
     _CTE_CHAR = 266,
     _CTE_FLOAT = 267,
     _CTE_DOUBLE = 268,
     _CTE_BOOL_V = 269,
     _CTE_BOOL_F = 270,
     _CTE_STRING = 271,
     _ROLA_SE = 272,
     _END_ROLOU = 273,
     _NAO_ROLOU = 274,
     _END_NAO_ROLOU = 275,
     _ENROLANDO = 276,
     _END_ENROLANDO = 277,
     _ENROLA_SE = 278,
     _END_ENROLA_SE = 279,
     _FAZ = 280,
     _END_FAZ_DEPOIS_ENROLA = 281,
     _INVESTIGA = 282,
     _END_INVESTIGA = 283,
     _SUSPEITO = 284,
     _CASO_ENCERRADO = 285,
     _INOCENTE = 286,
     _GRADE = 287,
     _VETOR = 288,
     _CIN = 289,
     _COUT = 290,
     _FUNCAO_MAIN = 291,
     _VOID = 292,
     _PROTOTIPO = 293,
     _REF = 294,
     _ALFA = 295,
     _OMEGA = 296,
     _RETORNA_FUNCAO = 297,
     _ATRIBUI = 298,
     _SHIFTR = 299,
     _SHIFTL = 300,
     _MENORIGUAL = 301,
     _MAIORIGUAL = 302,
     _DIFERENTE = 303,
     _IGUAL = 304,
     _AND = 305,
     _OR = 306,
     _NOT = 307,
     _MOD = 308,
     _INTERVALO = 309,
     _PIPE = 310,
     _FILTER = 311,
     _FOREACH = 312,
     _X = 313
   };
#endif
/* Tokens.  */
#define _INT 258
#define _CHAR 259
#define _BOOL 260
#define _DOUBLE 261
#define _FLOAT 262
#define _STRING 263
#define _ID 264
#define _CTE_INT 265
#define _CTE_CHAR 266
#define _CTE_FLOAT 267
#define _CTE_DOUBLE 268
#define _CTE_BOOL_V 269
#define _CTE_BOOL_F 270
#define _CTE_STRING 271
#define _ROLA_SE 272
#define _END_ROLOU 273
#define _NAO_ROLOU 274
#define _END_NAO_ROLOU 275
#define _ENROLANDO 276
#define _END_ENROLANDO 277
#define _ENROLA_SE 278
#define _END_ENROLA_SE 279
#define _FAZ 280
#define _END_FAZ_DEPOIS_ENROLA 281
#define _INVESTIGA 282
#define _END_INVESTIGA 283
#define _SUSPEITO 284
#define _CASO_ENCERRADO 285
#define _INOCENTE 286
#define _GRADE 287
#define _VETOR 288
#define _CIN 289
#define _COUT 290
#define _FUNCAO_MAIN 291
#define _VOID 292
#define _PROTOTIPO 293
#define _REF 294
#define _ALFA 295
#define _OMEGA 296
#define _RETORNA_FUNCAO 297
#define _ATRIBUI 298
#define _SHIFTR 299
#define _SHIFTL 300
#define _MENORIGUAL 301
#define _MAIORIGUAL 302
#define _DIFERENTE 303
#define _IGUAL 304
#define _AND 305
#define _OR 306
#define _NOT 307
#define _MOD 308
#define _INTERVALO 309
#define _PIPE 310
#define _FILTER 311
#define _FOREACH 312
#define _X 313




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 596 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   627

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  113
/* YYNRULES -- Number of states.  */
#define YYNSTATES  249

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   313

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      66,    67,    63,    61,    68,    62,    71,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    69,    65,
      59,     2,    60,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,    72,     2,     2,     2,     2,     2,     2,
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
      55,    56,    57,    58
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,    10,    14,    15,    22,    23,    25,
      26,    30,    32,    35,    39,    40,    46,    51,    53,    55,
      57,    59,    61,    63,    67,    73,    74,    77,    82,    86,
      87,    93,    98,   101,   106,   111,   112,   118,   122,   125,
     126,   129,   131,   133,   135,   137,   140,   143,   145,   147,
     149,   152,   155,   159,   163,   171,   180,   192,   200,   211,
     220,   222,   225,   227,   235,   242,   251,   253,   257,   259,
     264,   269,   271,   272,   276,   278,   282,   286,   288,   292,
     296,   300,   304,   308,   312,   314,   318,   322,   324,   328,
     332,   334,   337,   339,   341,   345,   350,   355,   362,   366,
     368,   370,   372,   374,   376,   378,   380,   382,   386,   388,
     391,   392,   399,   401
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      74,     0,    -1,    75,    -1,    76,    81,    85,   119,    -1,
      76,    77,    65,    -1,    -1,    38,   121,     9,    66,    78,
      67,    -1,    -1,    79,    -1,    -1,    79,    68,    80,    -1,
      80,    -1,    83,     9,    -1,    82,    65,    81,    -1,    -1,
      82,    68,     9,    84,    89,    -1,    83,     9,    84,    89,
      -1,     3,    -1,     7,    -1,     6,    -1,     5,    -1,     4,
      -1,     8,    -1,    66,    10,    67,    -1,    66,    10,    68,
      10,    67,    -1,    -1,    36,    86,    -1,    40,    87,    91,
      41,    -1,    88,    65,    87,    -1,    -1,    88,    68,     9,
      84,    89,    -1,    83,     9,    84,    89,    -1,    43,   111,
      -1,    43,    66,   118,    67,    -1,    43,    66,    90,    67,
      -1,    -1,    90,    68,    66,   118,    67,    -1,    66,   118,
      67,    -1,    91,    92,    -1,    -1,   110,    65,    -1,    98,
      -1,    96,    -1,    99,    -1,    95,    -1,    93,    65,    -1,
      94,    65,    -1,    97,    -1,   100,    -1,   105,    -1,    34,
     117,    -1,    35,   111,    -1,    42,   111,    65,    -1,    42,
      37,    65,    -1,    23,    66,   111,    67,    87,    91,    24,
      -1,    25,    87,    91,    23,    66,   111,    67,    65,    -1,
      21,    66,     9,    43,    10,    65,   111,    67,    87,    91,
      22,    -1,    17,    66,   111,    67,    87,    91,    18,    -1,
      17,    66,   111,    67,    87,    91,    19,    87,    91,    20,
      -1,    27,    66,   101,    67,    40,   102,   104,    41,    -1,
       9,    -1,   102,   103,    -1,   103,    -1,    29,    10,    69,
      87,    91,    30,    65,    -1,    31,    69,    87,    91,    30,
      65,    -1,    54,    70,   111,    71,   106,    72,   107,   109,
      -1,   111,    -1,    55,   108,   107,    -1,    55,    -1,    56,
      70,   111,    72,    -1,    57,    70,    92,    72,    -1,   111,
      -1,    -1,   111,    43,   112,    -1,   112,    -1,   112,    51,
     113,    -1,   112,    50,   113,    -1,   113,    -1,   113,    60,
     114,    -1,   113,    59,   114,    -1,   113,    47,   114,    -1,
     113,    46,   114,    -1,   113,    49,   114,    -1,   113,    48,
     114,    -1,   114,    -1,   114,    61,   115,    -1,   114,    62,
     115,    -1,   115,    -1,   115,    63,   116,    -1,   115,    64,
     116,    -1,   117,    -1,    52,   117,    -1,   117,    -1,     9,
      -1,     9,    66,    67,    -1,     9,    66,   118,    67,    -1,
       9,    66,   111,    67,    -1,     9,    66,   111,    68,   111,
      67,    -1,    66,   111,    67,    -1,    10,    -1,    12,    -1,
      13,    -1,    14,    -1,    15,    -1,    11,    -1,    16,    -1,
      58,    -1,   118,    68,   111,    -1,   111,    -1,   119,   120,
      -1,    -1,   121,     9,    66,    78,    67,    86,    -1,    83,
      -1,    37,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   423,   423,   429,   432,   433,   436,   471,   474,   475,
     478,   479,   482,   492,   493,   501,   510,   521,   522,   523,
     524,   525,   526,   529,   531,   534,   537,   546,   551,   552,
     555,   569,   599,   600,   601,   602,   606,   607,   610,   611,
     614,   615,   616,   617,   618,   619,   620,   621,   622,   623,
     626,   630,   643,   648,   652,   677,   694,   712,   727,   751,
     767,   775,   776,   779,   795,   816,   833,   841,   843,   847,
     854,   863,   864,   867,   868,   871,   872,   873,   876,   877,
     878,   879,   880,   881,   882,   885,   886,   887,   890,   891,
     892,   895,   896,   899,   907,   915,   934,   963,  1001,  1007,
    1008,  1009,  1010,  1011,  1012,  1013,  1014,  1026,  1032,  1041,
    1042,  1045,  1086,  1087
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_INT", "_CHAR", "_BOOL", "_DOUBLE",
  "_FLOAT", "_STRING", "_ID", "_CTE_INT", "_CTE_CHAR", "_CTE_FLOAT",
  "_CTE_DOUBLE", "_CTE_BOOL_V", "_CTE_BOOL_F", "_CTE_STRING", "_ROLA_SE",
  "_END_ROLOU", "_NAO_ROLOU", "_END_NAO_ROLOU", "_ENROLANDO",
  "_END_ENROLANDO", "_ENROLA_SE", "_END_ENROLA_SE", "_FAZ",
  "_END_FAZ_DEPOIS_ENROLA", "_INVESTIGA", "_END_INVESTIGA", "_SUSPEITO",
  "_CASO_ENCERRADO", "_INOCENTE", "_GRADE", "_VETOR", "_CIN", "_COUT",
  "_FUNCAO_MAIN", "_VOID", "_PROTOTIPO", "_REF", "_ALFA", "_OMEGA",
  "_RETORNA_FUNCAO", "_ATRIBUI", "_SHIFTR", "_SHIFTL", "_MENORIGUAL",
  "_MAIORIGUAL", "_DIFERENTE", "_IGUAL", "_AND", "_OR", "_NOT", "_MOD",
  "_INTERVALO", "_PIPE", "_FILTER", "_FOREACH", "_X", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "';'", "'('", "')'", "','", "':'", "'['", "'.'",
  "']'", "$accept", "SL", "S", "PROTOTIPO_FUNCOES", "PROTOTIPO",
  "PARAMETROS", "LISTAPARAMETROS", "PARAMETRO", "VARIAVEIS_GLOBAIS",
  "DECLVARG", "TIPO", "ARRAY", "BLOCO_PRINCIPAL", "BLOCO", "VARS_LOCAIS",
  "DECLVARL", "CMD_ATRIBUICAO", "LST_LST_E", "CMDS", "CMD", "CMD_IN",
  "CMD_OUT", "CMD_RETURN", "CMD_WHILE", "CMD_DO_WHILE", "CMD_FOR",
  "CMD_IF", "CMD_SWITCH", "ID_LABEL", "CASES", "CASE", "DEFAULT",
  "CMD_PIPE", "INI_PIPE", "PROCS", "PROC", "CONSOME", "CMD_E", "E", "E1",
  "E2", "E3", "E4", "E5", "F", "LST_E", "FUNCTIONS", "FUNCTION", "RETORNO", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,    60,
      62,    43,    45,    42,    47,    59,    40,    41,    44,    58,
      91,    46,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    75,    76,    76,    77,    77,    78,    78,
      79,    79,    80,    81,    81,    82,    82,    83,    83,    83,
      83,    83,    83,    84,    84,    84,    85,    86,    87,    87,
      88,    88,    89,    89,    89,    89,    90,    90,    91,    91,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      93,    94,    95,    95,    96,    97,    98,    99,    99,   100,
     101,   102,   102,   103,   104,   105,   106,   107,   107,   108,
     109,   110,   110,   111,   111,   112,   112,   112,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   114,   115,   115,
     115,   116,   116,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   118,   118,   119,
     119,   120,   121,   121
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     4,     3,     0,     6,     0,     1,     0,
       3,     1,     2,     3,     0,     5,     4,     1,     1,     1,
       1,     1,     1,     3,     5,     0,     2,     4,     3,     0,
       5,     4,     2,     4,     4,     0,     5,     3,     2,     0,
       2,     1,     1,     1,     1,     2,     2,     1,     1,     1,
       2,     2,     3,     3,     7,     8,    11,     7,    10,     8,
       1,     2,     1,     7,     6,     8,     1,     3,     1,     4,
       4,     1,     0,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     2,     1,     1,     3,     4,     4,     6,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     2,
       0,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     2,     7,     1,    17,    21,    20,    19,    18,
      22,     0,     0,     0,     0,     0,   113,   112,     0,     4,
       0,   110,    14,     0,    25,     0,    29,    26,     3,    13,
      25,     0,    35,     9,     0,    39,     0,   109,     0,    35,
       0,     0,    16,     0,     8,    11,     0,    25,    72,    29,
       0,     0,    15,    23,     0,    93,    99,   104,   100,   101,
     102,   103,   105,   106,     0,    32,    74,    77,    84,    87,
      90,     6,     0,    12,    35,     0,     0,     0,    29,     0,
       0,     0,    27,     0,     0,     0,    38,     0,     0,    44,
      42,    47,    41,    43,    48,    49,     0,    71,    28,    25,
       9,     0,     0,     0,     0,   108,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      10,    31,     0,     0,     0,    39,     0,    50,    51,     0,
       0,     0,     0,    45,    46,    40,    35,     0,    24,    94,
       0,     0,     0,    34,     0,    98,    33,     0,    73,    76,
      75,    81,    80,    83,    82,    79,    78,    85,    86,     0,
      88,    92,    89,     0,     0,     0,    72,    60,     0,    53,
      52,     0,    30,     0,    96,     0,    95,    37,     0,   107,
      91,    29,     0,    29,     0,     0,     0,   111,     0,   108,
       0,    39,     0,    39,     0,     0,     0,    66,    97,    36,
      72,     0,    72,     0,     0,     0,    62,     0,    57,    29,
       0,    54,    29,     0,     0,    61,     0,    68,     0,    39,
      29,    55,    29,    29,    59,     0,     0,     0,    65,    72,
      39,    39,    39,     0,    67,    72,    58,    72,    72,    72,
       0,     0,    56,     0,     0,    69,    70,    63,    64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    12,    43,    44,    45,    13,    14,
      34,    32,    21,    27,   193,    36,    42,   104,    48,    86,
      87,    88,    89,    90,    91,    92,    93,    94,   168,   205,
     206,   216,    95,   196,   218,   226,   228,    96,    97,    66,
      67,    68,    69,   160,    70,   106,    28,    37,    18
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -123
static const yytype_int16 yypact[] =
{
    -123,    32,  -123,    50,  -123,  -123,  -123,  -123,  -123,  -123,
    -123,   172,   -31,    -6,     2,    29,  -123,  -123,    51,  -123,
      41,  -123,   159,    74,    19,    36,   159,  -123,   172,  -123,
      19,    86,    55,   159,    95,  -123,    11,  -123,   125,    55,
     -55,   503,  -123,    69,    72,  -123,   133,    19,   116,   159,
     140,    90,  -123,  -123,   149,   107,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,  -123,   523,   138,   -29,    46,    28,   -35,
    -123,  -123,   159,  -123,    55,   122,   123,   124,   159,   126,
     561,   561,  -123,   465,   121,   561,  -123,   130,   146,  -123,
    -123,  -123,  -123,  -123,  -123,  -123,   148,   138,  -123,    19,
     159,   150,   102,   561,    33,   -16,    77,   561,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   494,   494,
    -123,  -123,   561,   206,   561,  -123,   209,  -123,   138,   154,
     -32,   561,   -16,  -123,  -123,  -123,    55,   153,  -123,  -123,
      -3,    80,    85,  -123,   155,  -123,  -123,   561,   -29,    46,
      46,    28,    28,    28,    28,    28,    28,   -35,   -35,   561,
    -123,  -123,  -123,    -1,   179,     1,   397,  -123,   158,  -123,
    -123,   -36,  -123,    41,  -123,   561,  -123,  -123,   561,   138,
    -123,   159,   216,   159,   161,   188,   561,  -123,     5,   138,
     104,  -123,   164,  -123,   561,   201,   160,   138,  -123,  -123,
     189,   561,   225,     6,   223,    30,  -123,   190,  -123,   159,
       7,  -123,    12,   175,   182,  -123,   212,   198,   199,  -123,
     159,  -123,   159,   159,  -123,   187,   190,   191,  -123,   261,
    -123,  -123,  -123,   561,  -123,   431,  -123,   295,   329,   363,
     -33,   186,  -123,   197,   200,  -123,  -123,  -123,  -123
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -123,  -123,  -123,  -123,  -123,   163,  -123,   192,   244,  -123,
       3,   -21,  -123,    96,   -26,  -123,   -37,  -123,  -122,    45,
    -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,
      63,  -123,  -123,  -123,    59,  -123,  -123,  -123,   -40,   180,
      76,     9,    70,   170,   -72,   -98,  -123,  -123,   262
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -15
static const yytype_int16 yytable[] =
{
      35,    65,    52,   166,   141,   142,    15,   107,   127,    39,
     107,   107,    53,    54,    17,     5,     6,     7,     8,     9,
      10,   108,   109,    98,   105,    15,    74,   107,   118,   119,
      20,    17,     4,   170,    19,   186,    46,   121,    24,   245,
     107,   128,   107,   130,   107,   132,   161,   161,   107,   107,
     107,   145,   125,     5,     6,     7,     8,     9,    10,   204,
      25,   214,   140,   105,   174,   175,   181,    22,   183,   200,
      23,   202,   198,   212,   220,    46,    49,   221,   136,    50,
     190,    26,   163,    30,   165,    31,   -14,   180,    11,   116,
     117,   171,   110,   111,   112,   113,    40,   229,    41,   172,
     143,   144,    33,    46,    47,   114,   115,   179,   237,   238,
     239,    55,    56,    57,    58,    59,    60,    61,    62,   151,
     152,   153,   154,   155,   156,    55,    56,    57,    58,    59,
      60,    61,    62,    75,    51,   188,    71,    76,   189,    77,
      72,    78,    73,    79,   146,   147,   197,   176,   147,    99,
      80,    81,   177,   147,   203,   191,   100,    82,    83,   101,
      63,   210,     5,     6,     7,     8,     9,    10,    85,   139,
      84,   199,   147,   102,    63,     5,     6,     7,     8,     9,
      10,   107,    85,   219,   149,   150,   157,   158,   122,   123,
     124,   131,   126,   240,   230,   133,   231,   232,    55,    56,
      57,    58,    59,    60,    61,    62,    75,   208,   209,    16,
      76,   134,    77,   135,    78,   164,    79,   138,   167,   169,
     173,   178,   182,    80,    81,   185,   192,   194,   195,   201,
     204,    83,   207,   213,    55,    56,    57,    58,    59,    60,
      61,    62,    75,    84,   222,   217,    76,    63,    77,   211,
      78,   223,    79,   224,   225,    85,   227,   233,   246,    80,
      81,   235,   247,   137,   120,   248,    29,    83,   215,   187,
      55,    56,    57,    58,    59,    60,    61,    62,    75,    84,
     241,   236,    76,    63,    77,   234,    78,   148,    79,   162,
      38,    85,     0,     0,     0,    80,    81,     0,     0,     0,
       0,     0,     0,    83,    55,    56,    57,    58,    59,    60,
      61,    62,    75,     0,     0,    84,    76,   242,    77,    63,
      78,     0,    79,     0,     0,     0,     0,    85,     0,    80,
      81,     0,     0,     0,     0,     0,     0,    83,    55,    56,
      57,    58,    59,    60,    61,    62,    75,     0,     0,    84,
      76,     0,    77,    63,    78,     0,    79,     0,     0,   243,
       0,    85,     0,    80,    81,     0,     0,     0,     0,     0,
       0,    83,    55,    56,    57,    58,    59,    60,    61,    62,
      75,     0,     0,    84,    76,     0,    77,    63,    78,     0,
      79,     0,     0,   244,     0,    85,     0,    80,    81,     0,
       0,     0,     0,     0,     0,    83,    55,    56,    57,    58,
      59,    60,    61,    62,    75,     0,     0,    84,    76,     0,
     184,    63,    78,     0,    79,     0,     0,     0,     0,    85,
       0,    80,    81,     0,     0,     0,     0,     0,     0,    83,
      55,    56,    57,    58,    59,    60,    61,    62,    75,     0,
       0,    84,    76,     0,    77,    63,    78,     0,    79,     0,
       0,     0,     0,    85,     0,    80,    81,     0,     0,     0,
       0,     0,     0,    83,    55,    56,    57,    58,    59,    60,
      61,    62,     0,     0,     0,    84,     0,     0,     0,    63,
       0,     0,     0,     0,     0,     0,     0,    85,     0,     0,
       0,     0,   129,    55,    56,    57,    58,    59,    60,    61,
      62,     0,    55,    56,    57,    58,    59,    60,    61,    62,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
       0,    85,    55,    56,    57,    58,    59,    60,    61,    62,
       0,     0,     0,     0,     0,     0,   159,     0,     0,     0,
       0,     0,    63,     0,     0,     0,     0,     0,     0,     0,
      85,    63,     0,     0,     0,     0,     0,     0,     0,    64,
      55,    56,    57,    58,    59,    60,    61,    62,     0,     0,
       0,    63,     0,     0,     0,     0,     0,     0,     0,   103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    63,
       0,     0,     0,     0,     0,     0,     0,    85
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-123))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      26,    41,    39,   125,   102,   103,     3,    43,    80,    30,
      43,    43,    67,    68,    11,     3,     4,     5,     6,     7,
       8,    50,    51,    49,    64,    22,    47,    43,    63,    64,
      36,    28,     0,    65,    65,    71,    33,    74,     9,    72,
      43,    81,    43,    83,    43,    85,   118,   119,    43,    43,
      43,    67,    78,     3,     4,     5,     6,     7,     8,    29,
       9,    31,   102,   103,    67,    68,    67,    65,    67,   191,
      68,   193,    67,    67,    67,    72,    65,    65,    99,    68,
     178,    40,   122,     9,   124,    66,    36,   159,    38,    61,
      62,   131,    46,    47,    48,    49,    10,   219,    43,   136,
      67,    68,    66,   100,     9,    59,    60,   147,   230,   231,
     232,     9,    10,    11,    12,    13,    14,    15,    16,   110,
     111,   112,   113,   114,   115,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     9,   175,    67,    21,   178,    23,
      68,    25,     9,    27,    67,    68,   186,    67,    68,     9,
      34,    35,    67,    68,   194,   181,    66,    41,    42,    10,
      58,   201,     3,     4,     5,     6,     7,     8,    66,    67,
      54,    67,    68,    66,    58,     3,     4,     5,     6,     7,
       8,    43,    66,   209,   108,   109,   116,   117,    66,    66,
      66,    70,    66,   233,   220,    65,   222,   223,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    37,
      21,    65,    23,    65,    25,     9,    27,    67,     9,    65,
      67,    66,    43,    34,    35,    67,    10,    66,    40,    65,
      29,    42,    72,    10,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    54,    69,    55,    21,    58,    23,    24,
      25,    69,    27,    41,    56,    66,    57,    70,    72,    34,
      35,    70,    65,   100,    72,    65,    22,    42,   205,   173,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    54,
     235,    20,    21,    58,    23,   226,    25,   107,    27,   119,
      28,    66,    -1,    -1,    -1,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    42,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    54,    21,    22,    23,    58,
      25,    -1,    27,    -1,    -1,    -1,    -1,    66,    -1,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    42,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    54,
      21,    -1,    23,    58,    25,    -1,    27,    -1,    -1,    30,
      -1,    66,    -1,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    42,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    54,    21,    -1,    23,    58,    25,    -1,
      27,    -1,    -1,    30,    -1,    66,    -1,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    42,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    54,    21,    -1,
      23,    58,    25,    -1,    27,    -1,    -1,    -1,    -1,    66,
      -1,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    42,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    54,    21,    -1,    23,    58,    25,    -1,    27,    -1,
      -1,    -1,    -1,    66,    -1,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    42,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    37,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    74,    75,    76,     0,     3,     4,     5,     6,     7,
       8,    38,    77,    81,    82,    83,    37,    83,   121,    65,
      36,    85,    65,    68,     9,     9,    40,    86,   119,    81,
       9,    66,    84,    66,    83,    87,    88,   120,   121,    84,
      10,    43,    89,    78,    79,    80,    83,     9,    91,    65,
      68,     9,    89,    67,    68,     9,    10,    11,    12,    13,
      14,    15,    16,    58,    66,   111,   112,   113,   114,   115,
     117,    67,    68,     9,    84,    17,    21,    23,    25,    27,
      34,    35,    41,    42,    54,    66,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   105,   110,   111,    87,     9,
      66,    10,    66,    66,    90,   111,   118,    43,    50,    51,
      46,    47,    48,    49,    59,    60,    61,    62,    63,    64,
      80,    89,    66,    66,    66,    87,    66,   117,   111,    37,
     111,    70,   111,    65,    65,    65,    84,    78,    67,    67,
     111,   118,   118,    67,    68,    67,    67,    68,   112,   113,
     113,   114,   114,   114,   114,   114,   114,   115,   115,    52,
     116,   117,   116,   111,     9,   111,    91,     9,   101,    65,
      65,   111,    89,    67,    67,    68,    67,    67,    66,   111,
     117,    67,    43,    67,    23,    67,    71,    86,   111,   111,
     118,    87,    10,    87,    66,    40,   106,   111,    67,    67,
      91,    65,    91,   111,    29,   102,   103,    72,    18,    19,
     111,    24,    67,    10,    31,   103,   104,    55,   107,    87,
      67,    65,    69,    69,    41,    56,   108,    57,   109,    91,
      87,    87,    87,    70,   107,    70,    20,    91,    91,    91,
     111,    92,    22,    30,    30,    72,    72,    65,    65
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1806 of yacc.c  */
#line 424 "trabalho.y"
    {
      cout << "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n//#include <cstring>\n#include <string>\n#include <iostream>\n\nusing namespace std;\n\n" +  (yyvsp[(1) - (1)]).c << endl;
    }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 429 "trabalho.y"
    { (yyval).c = (yyvsp[(1) - (4)]).c + (yyvsp[(2) - (4)]).c + (yyvsp[(3) - (4)]).c + (yyvsp[(4) - (4)]).c;   }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 432 "trabalho.y"
    { (yyval).c += (yyvsp[(2) - (3)]).c; }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 433 "trabalho.y"
    { (yyval).c = ""; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 437 "trabalho.y"
    {
        string aux;
        if (nparams >= 1)
        {
          if ((yyvsp[(2) - (6)]).v == "nada")
          {
            aux = "";
            (yyval).c = "void " + (yyvsp[(3) - (6)]).v + "(" + (yyvsp[(5) - (6)]).c + ");\n";
          }
          else
          {
            aux = " &RI";
            (yyval).c = "void " + (yyvsp[(3) - (6)]).v + "(" + (yyvsp[(5) - (6)]).c + "," + (yyvsp[(2) - (6)]).c + aux + ");\n";
          }
          ir = ir + 1;
        }
        else
        {
          if((yyvsp[(2) - (6)]).v == "nada")
          {
            (yyval).c = "void " + (yyvsp[(3) - (6)]).v + "();\n";
          }
          else
          {
            aux = " &RI";
            (yyval).c = "void " + (yyvsp[(3) - (6)]).v + "(" + (yyvsp[(2) - (6)]).c + aux  + ");\n";
          }
          ir = ir + 1;
        }

        inclui_funcao((yyvsp[(3) - (6)]).v,(yyvsp[(2) - (6)]).t, (yyvsp[(5) - (6)]).p);
        nfuncao++;
        nparams = 0;
      }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 471 "trabalho.y"
    { }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 475 "trabalho.y"
    { (yyval).p = ""; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 478 "trabalho.y"
    { (yyval).p += "#" + (yyvsp[(3) - (3)]).t.tipo_base; (yyval).c = (yyval).c + "," + (yyvsp[(3) - (3)]).c; }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 479 "trabalho.y"
    { (yyval).p = "#" + (yyvsp[(1) - (1)]).t.tipo_base; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 483 "trabalho.y"
    {
        nparams++;
        (yyval).t = (yyvsp[(1) - (2)]).t;
        (yyval).c = (yyvsp[(1) - (2)]).c + " " + (yyvsp[(2) - (2)]).v;
        inclui_parametro((yyvsp[(2) - (2)]).v, (yyvsp[(1) - (2)]).t);
        (yyval).p = "#" + (yyvsp[(1) - (2)]).t.tipo_base;
    }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 492 "trabalho.y"
    { (yyval).c = gera_varglobal_temp(); + "\n" + (yyvsp[(3) - (3)]).c; }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 493 "trabalho.y"
    { 
				(yyval).c = "\n"; 
			
				
		  }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 502 "trabalho.y"
    {
        (yyval).t = (yyvsp[(1) - (5)]).t;
        (yyvsp[(3) - (5)]).t = (yyvsp[(1) - (5)]).t;
        (yyvsp[(3) - (5)]).t.ndim = (yyvsp[(4) - (5)]).t.ndim;
        (yyvsp[(3) - (5)]).t.tam_dim[0] = (yyvsp[(4) - (5)]).t.tam_dim[0];
        (yyvsp[(3) - (5)]).t.tam_dim[1] = (yyvsp[(4) - (5)]).t.tam_dim[1];
        insere_varglobal((yyvsp[(3) - (5)]).v , (yyvsp[(1) - (5)]).t);
      }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 511 "trabalho.y"
    {
        (yyval).t = (yyvsp[(1) - (4)]).t;
        (yyvsp[(2) - (4)]).t = (yyvsp[(1) - (4)]).t;
        (yyvsp[(1) - (4)]).t.ndim = (yyvsp[(3) - (4)]).t.ndim;
        (yyvsp[(1) - (4)]).t.tam_dim[0] = (yyvsp[(3) - (4)]).t.tam_dim[0];
        (yyvsp[(1) - (4)]).t.tam_dim[1] = (yyvsp[(3) - (4)]).t.tam_dim[1];
        insere_varglobal((yyvsp[(2) - (4)]).v , (yyvsp[(1) - (4)]).t);
      }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 521 "trabalho.y"
    { (yyval).t.tipo_base =  "I"; (yyval).v = (yyvsp[(1) - (1)]).v; (yyval).c = "int"; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 522 "trabalho.y"
    { (yyval).t.tipo_base = "R"; (yyval).v = (yyvsp[(1) - (1)]).v; (yyval).c = "float"; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 523 "trabalho.y"
    { (yyval).t.tipo_base = "D"; (yyval).v = (yyvsp[(1) - (1)]).v; (yyval).c = "double"; }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 524 "trabalho.y"
    { (yyval).t.tipo_base = "B"; (yyval).v = (yyvsp[(1) - (1)]).v; (yyval).c = "char"; }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 525 "trabalho.y"
    { (yyval).t.tipo_base = "C"; (yyval).v = (yyvsp[(1) - (1)]).v; (yyval).c = "char"; }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 526 "trabalho.y"
    { (yyval).t.tipo_base = "S"; (yyval).v = (yyvsp[(1) - (1)]).v; (yyval).c = "string"; }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 530 "trabalho.y"
    { (yyval).t.ndim = 1; (yyval).t.tam_dim[0] = atoi(((yyvsp[(2) - (3)]).v).c_str()); (yyval).t.tam_dim[1] = 0; }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 532 "trabalho.y"
    { (yyval).t.ndim = 2; (yyval).t.tam_dim[0] = atoi(((yyvsp[(2) - (5)]).v).c_str()); (yyval).t.tam_dim[1] = atoi(((yyvsp[(4) - (5)]).v).c_str()); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 534 "trabalho.y"
    { (yyval).t.ndim = 0; (yyval).t.tam_dim[0] = 0; (yyval).t.tam_dim[1] = 0; }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 537 "trabalho.y"
    { 
											(yyval).c = "";
											(yyval).c += "int main ()\n"; 
											(yyval).c += (yyvsp[(2) - (2)]).c; 
										}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 547 "trabalho.y"
    { (yyval).c = "{\n\n " + DeclaraVarPipes()+gera_variavellocal_temp() +  (yyvsp[(3) - (4)]).c + "\n\n return 0; \n}\n"; }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 551 "trabalho.y"
    {}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 552 "trabalho.y"
    {}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 556 "trabalho.y"
    {
        (yyval).t = (yyvsp[(1) - (5)]).t;
        (yyvsp[(3) - (5)]).t = (yyvsp[(1) - (5)]).t;
        (yyvsp[(1) - (5)]).t.ndim = (yyvsp[(4) - (5)]).t.ndim;
        (yyvsp[(1) - (5)]).t.tam_dim[0] = (yyvsp[(4) - (5)]).t.tam_dim[0];
        (yyvsp[(1) - (5)]).t.tam_dim[1] = (yyvsp[(4) - (5)]).t.tam_dim[1];
        insere_varlocal((yyvsp[(3) - (5)]).v , (yyvsp[(1) - (5)]).t);

        if((yyvsp[(5) - (5)]).v != "")
        {
          inic +=(yyvsp[(5) - (5)]).c + (yyvsp[(3) - (5)]).v + "=" + (yyvsp[(5) - (5)]).v + ";\n";
        }
      }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 570 "trabalho.y"
    {
        (yyval).t = (yyvsp[(1) - (4)]).t;
        (yyvsp[(2) - (4)]).t = (yyvsp[(1) - (4)]).t;
        (yyvsp[(1) - (4)]).t.ndim = (yyvsp[(3) - (4)]).t.ndim;
        (yyvsp[(1) - (4)]).t.tam_dim[0] = (yyvsp[(3) - (4)]).t.tam_dim[0];
        (yyvsp[(1) - (4)]).t.tam_dim[1] = (yyvsp[(3) - (4)]).t.tam_dim[1];

        insere_varlocal((yyvsp[(2) - (4)]).v , (yyvsp[(1) - (4)]).t);

        if ((yyvsp[(4) - (4)]).v != "")
        {
          if (((yyvsp[(4) - (4)]).v).c_str()[0] == '#')
          {
            inic += quebra_codigo_lista((yyvsp[(2) - (4)]).v, (yyvsp[(4) - (4)]).v , (yyvsp[(4) - (4)]).c);
          }
          else
          {
            inic += (yyvsp[(4) - (4)]).c;
            Atributo ss, s1, s2, s3;
            s1 = (yyvsp[(2) - (4)]);
            s2.v = "<-";
            s3 = (yyvsp[(4) - (4)]);
            gera_codigo_operador(ss, s1,s2 ,s3 );
            inic += ss.c;
          }
        }
      }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 599 "trabalho.y"
    { (yyval).v = (yyvsp[(2) - (2)]).v; (yyval).t = (yyvsp[(2) - (2)]).t; (yyval).c = (yyvsp[(2) - (2)]).c; }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 600 "trabalho.y"
    { (yyval).v = (yyvsp[(3) - (4)]).v; (yyval).c = (yyvsp[(3) - (4)]).c; }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 601 "trabalho.y"
    { }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 602 "trabalho.y"
    { (yyval).v = ""; (yyval).c = ""; }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 606 "trabalho.y"
    { }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 607 "trabalho.y"
    { }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 610 "trabalho.y"
    { (yyval).c = (yyvsp[(1) - (2)]).c + (yyvsp[(2) - (2)]).c; }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 611 "trabalho.y"
    { (yyval).c = ""; }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 614 "trabalho.y"
    { }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 615 "trabalho.y"
    { }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 616 "trabalho.y"
    { }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 617 "trabalho.y"
    { }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 618 "trabalho.y"
    { }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 619 "trabalho.y"
    { }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 620 "trabalho.y"
    { }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 621 "trabalho.y"
    { }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 622 "trabalho.y"
    { }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 623 "trabalho.y"
    { }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 626 "trabalho.y"
    { (yyval).c = (yyvsp[(2) - (2)]).c + "cin >>" + (yyvsp[(2) - (2)]).v + " ;\n"; }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 631 "trabalho.y"
    {
        if (((yyvsp[(2) - (2)]).t.ndim != 0) && ((yyvsp[(2) - (2)]).t.tipo_base == "S"))
        {
            (yyval).c = (yyvsp[(2) - (2)]).c + "cout << " + (yyvsp[(2) - (2)]).v  + "<< endl;\n ";
        }
        else
        {
            (yyval).c = (yyvsp[(2) - (2)]).c + "cout << " + (yyvsp[(2) - (2)]).v  + "<< endl;\n ";
        }
}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 644 "trabalho.y"
    {
          (yyval).c = (yyvsp[(2) - (3)]).c + "RI = " + (yyvsp[(2) - (3)]).v + ";\nreturn;\n";
          //compara_resultado($2.t.tipo_base);  VER ISSO AQUI!!!!!!!!
      }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 648 "trabalho.y"
    { }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 653 "trabalho.y"
    {
        string rotulo = gera_rotulo();
        string rotulo_aux = gera_rotulo();
        string teste = gera_temp("B");
        string codigo;
        codigo += (yyvsp[(3) - (7)]).c;
        codigo += teste + " =" + (yyvsp[(3) - (7)]).v + ";\n";

        codigo += "if (!(" + teste + ")) \n";
        codigo += "goto " + rotulo_aux + ";\n";

        codigo += rotulo + ": ";
        codigo += (yyvsp[(6) - (7)]).c;

        codigo += (yyvsp[(3) - (7)]).c;
        codigo += teste + " =" + (yyvsp[(3) - (7)]).v + ";\n";

        codigo += "if (" + teste + " ) \n";
        codigo += "goto " + rotulo + ";\n";
        codigo += rotulo_aux + ": ";
        (yyval).c = codigo;
      }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 678 "trabalho.y"
    {
    string varTeste = gera_temp( "B" );
    string labelFim = gera_rotulo();
    string labelTeste = gera_rotulo();

    (yyval).v = "";
    (yyval).c = "\t" + labelTeste + ":\n" + (yyvsp[(6) - (8)]).c +
    "\t" + varTeste + " = !" + (yyvsp[(6) - (8)]).v + ";\n" +
    "\tif( " + varTeste + " ) goto " + labelFim +";\n" +
    (yyvsp[(3) - (8)]).c +
    "\tgoto " + labelTeste + ";\n" +
    "\t" + labelFim + ":\n";
}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 695 "trabalho.y"
    {

          string varTeste = gera_temp( "B" );
          string labelFim = gera_rotulo();
          string labelTeste = gera_rotulo();

          (yyval).v = "";
          (yyval).c = (yyvsp[(5) - (11)]).c + "\t" + labelTeste + ":\n" + (yyvsp[(7) - (11)]).c +
          "\t" + varTeste + " = !" + (yyvsp[(7) - (11)]).v + ";\n" +
          "\tif( " + varTeste + " ) goto " + labelFim +";\n" +
          (yyvsp[(10) - (11)]).c +
          "\tgoto " + labelTeste + ";\n" +
          "\t" + labelFim + ":\n ;";
      }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 713 "trabalho.y"
    {
      string codigo;
      string rotulo = gera_rotulo();
      string teste = gera_temp("B");

      codigo += (yyvsp[(3) - (7)]).c;
      codigo += teste +" =  ! " + (yyvsp[(3) - (7)]).v + " ;\n";
      codigo += "if("  +  teste  +   ")\n";
      codigo += "goto " + rotulo + ";\n";
      codigo += (yyvsp[(6) - (7)]).c;
      codigo += rotulo + ": ;\n";

      (yyval).c = codigo;
    }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 728 "trabalho.y"
    {
      string codigo;
      string rotulo = gera_rotulo();
      string teste = gera_temp("B");
      string rotulo2 = gera_rotulo();

      codigo += (yyvsp[(3) - (10)]).c;
      codigo += teste +" =  ! " + (yyvsp[(3) - (10)]).v + " ;\n";
      codigo += "if("  +  teste  +   ")\n";
      codigo += "goto " + rotulo + ";\n";
      codigo += (yyvsp[(6) - (10)]).c;
      codigo += "goto " + rotulo2 + ";\n";
      codigo += rotulo + ": ;\n";
      codigo += (yyvsp[(9) - (10)]).c;
      codigo += rotulo2 + ": ;\n";

      (yyval).c = codigo;
    }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 752 "trabalho.y"
    {

    string codigo;

    codigo += (yyvsp[(6) - (8)]).c;
    codigo += (yyvsp[(7) - (8)]).c;

    codigo += fim_switch +": ";
    (yyval).c = codigo;
}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 768 "trabalho.y"
    {
		  fim_switch = gera_rotulo();
          id_switch = (yyvsp[(1) - (1)]).v;
          (yyval).c = (yyvsp[(1) - (1)]).c;
}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 775 "trabalho.y"
    { (yyval).c = (yyvsp[(1) - (2)]).c + (yyvsp[(2) - (2)]).c; }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 776 "trabalho.y"
    { (yyval).c = (yyvsp[(1) - (1)]).c; }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 780 "trabalho.y"
    {
    string codigo;
    string endcase = gera_rotulo();

    codigo += "\nif (" + id_switch +" != "+ (yyvsp[(2) - (7)]).v + ") goto "+
    endcase+";\n";
    codigo += (yyvsp[(4) - (7)]).c;
    codigo += (yyvsp[(5) - (7)]).c;
    codigo+= "goto "+fim_switch + "; \n";
    codigo+= endcase + ": \n";

    (yyval).c = codigo;
}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 796 "trabalho.y"
    {
    string codigo;
    codigo += (yyvsp[(3) - (6)]).c;
    codigo += (yyvsp[(4) - (6)]).c;
    (yyval).c = codigo;

}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 817 "trabalho.y"
    {
            Atributo inicio, condicao, passo, cmd;

            inicio.c = (yyvsp[(3) - (8)]).c + (yyvsp[(5) - (8)]).c +
                       "  x_" + pipeAtivo + " = " + (yyvsp[(3) - (8)]).v + ";\n";
            condicao.t.nome = "bool";
            condicao.v = gera_temp("B"); //geraTemp( Tipo( "bool" ) );
            condicao.c = "  " + condicao.v + " = " + "x_" + pipeAtivo + " <= " + (yyvsp[(5) - (8)]).v + ";\n";
            passo.c = passoPipeAtivo + ":\n" + "  x_" + pipeAtivo + " = x_" + pipeAtivo + " + 1;\n";
            cmd.c = (yyvsp[(7) - (8)]).c + (yyvsp[(8) - (8)]).c;

            //FAZER
            //geraCodigoFor( &$$, inicio, condicao, passo, cmd );

            pipeAtivo = ""; }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 834 "trabalho.y"
    {
			(yyval) = (yyvsp[(1) - (1)]);
			pipeAtivo =  (yyvsp[(1) - (1)]).t.nome;
			passoPipeAtivo = gera_rotulo();
		}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 842 "trabalho.y"
    { (yyval).c = (yyvsp[(2) - (3)]).c + (yyvsp[(3) - (3)]).c; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 844 "trabalho.y"
    { (yyval) = Atributo(); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 848 "trabalho.y"
    {
		   //FAZER
		   //geraCodigoFilter( &$$, $3 );
	   }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 855 "trabalho.y"
    { (yyval).c = (yyvsp[(3) - (4)]).c; }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 863 "trabalho.y"
    { }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 864 "trabalho.y"
    { }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 867 "trabalho.y"
    { (yyval).c = (yyvsp[(1) - (3)]).c;  (yyvsp[(2) - (3)]).v = "<-"; gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 868 "trabalho.y"
    { }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 871 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 872 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 873 "trabalho.y"
    { }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 876 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 877 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 878 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 879 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 880 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 881 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 882 "trabalho.y"
    { }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 885 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 886 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 887 "trabalho.y"
    { }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 890 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 891 "trabalho.y"
    { gera_codigo_operador((yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 892 "trabalho.y"
    { }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 895 "trabalho.y"
    { }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 896 "trabalho.y"
    { }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 900 "trabalho.y"
    {
      busca_variavelglobal((yyvsp[(1) - (1)]).v, & (yyvsp[(1) - (1)]).t);
      busca_varlocal((yyvsp[(1) - (1)]).v, & (yyvsp[(1) - (1)]).t);
      busca_varparametro((yyvsp[(1) - (1)]).v, & (yyvsp[(1) - (1)]).t);

      (yyval).t = (yyvsp[(1) - (1)]).t;
    }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 908 "trabalho.y"
    {
      busca_funcao((yyvsp[(1) - (3)]).v, & (yyvsp[(1) - (3)]).t);
      (yyval) = (yyvsp[(1) - (3)]);
      (yyval).v = gera_temp((yyvsp[(1) - (3)]).t.tipo_base);
      (yyval).c = quebra_codigo_parametro((yyval).v, (yyvsp[(1) - (3)]).v,  "" , "", (yyvsp[(1) - (3)]).t.tipo_base);
      compara_parametros((yyvsp[(1) - (3)]).v, "");
    }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 916 "trabalho.y"
    {

      busca_funcao((yyvsp[(1) - (4)]).v, & (yyvsp[(1) - (4)]).t);
      (yyval) = (yyvsp[(1) - (4)]);

      if ((yyvsp[(1) - (4)]).t.tipo_base == "V")
      {
        (yyval).v = "";
      }
      else
      {
        (yyval).v = gera_temp((yyvsp[(1) - (4)]).t.tipo_base);
      }

      (yyval).c = quebra_codigo_parametro((yyval).v, (yyvsp[(1) - (4)]).v,  (yyvsp[(3) - (4)]).v , (yyvsp[(3) - (4)]).c, (yyvsp[(1) - (4)]).t.tipo_base);

      compara_parametros((yyvsp[(1) - (4)]).v, (yyvsp[(3) - (4)]).p);
    }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 935 "trabalho.y"
    {
      busca_variavelglobal((yyvsp[(1) - (4)]).v, & (yyvsp[(1) - (4)]).t);
      busca_varlocal((yyvsp[(1) - (4)]).v, & (yyvsp[(1) - (4)]).t);

      (yyval).t = (yyvsp[(1) - (4)]).t;

      (yyval).c = (yyvsp[(3) - (4)]).c;

      string aux = gera_temp((yyvsp[(3) - (4)]).t.tipo_base);

      if ((yyvsp[(3) - (4)]).t.ndim !=0 )
      {
        (yyval).c += aux + " = " + (yyvsp[(3) - (4)]).v + ";\n";
        (yyvsp[(3) - (4)]).v = aux;
      }

      if ((yyvsp[(1) - (4)]).t.tipo_base == "S")
      {
        (yyval).c += aux + " = " + (yyvsp[(3) - (4)]).v + "* 256" + ";\n";
        (yyvsp[(3) - (4)]).v = aux;

        (yyval).v =  (yyvsp[(1) - (4)]).v + "[" + (yyvsp[(3) - (4)]).v + "]";
      }
      else
      {
        (yyval).v =  (yyvsp[(1) - (4)]).v + "[" + (yyvsp[(3) - (4)]).v + "]";
      }
    }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 964 "trabalho.y"
    {
      busca_variavelglobal((yyvsp[(1) - (6)]).v, & (yyvsp[(1) - (6)]).t);
      busca_varlocal((yyvsp[(1) - (6)]).v, & (yyvsp[(1) - (6)]).t);
      (yyval).t = (yyvsp[(1) - (6)]).t;

      string codigo;

      string i = gera_temp("I");
      codigo += i + " = " + (yyvsp[(3) - (6)]).v + ";\n";
      codigo += i + " = " + i + " * " + inteiro_string((yyvsp[(1) - (6)]).t.tam_dim[1]) + ";\n";

      Atributo ss, s1, s2, s3;
      s1.v = i;
      s1.t.tipo_base = "I";
      s2.v = "+";
      s3 = (yyvsp[(5) - (6)]);
      gera_codigo_operador(ss,s1,s2,s3);

      codigo += ss.c;

      (yyval).c = (yyvsp[(3) - (6)]).c + (yyvsp[(5) - (6)]).c + codigo;

      string aux = gera_temp((yyvsp[(3) - (6)]).t.tipo_base);

      if ((yyvsp[(1) - (6)]).t.tipo_base == "S")
      {
        (yyval).c += aux + " = " + ss.v + "* 256" + ";\n";
        (yyvsp[(3) - (6)]).v = aux;

        (yyval).v =  (yyvsp[(1) - (6)]).v + "[" + aux + "]";
      }
      else
      {
        (yyval).v =  (yyvsp[(1) - (6)]).v + "[" + ss.v + "]";
      }

    }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1002 "trabalho.y"
    {
      (yyval).t.tipo_base = (yyvsp[(2) - (3)]).t.tipo_base;
      (yyval).v = (yyvsp[(2) - (3)]).v;
      (yyval).c =  (yyvsp[(2) - (3)]).c;
    }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1007 "trabalho.y"
    { (yyval).t.tipo_base = "I";  }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1008 "trabalho.y"
    { (yyval).t.tipo_base = "R"; }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1009 "trabalho.y"
    { (yyval).t.tipo_base = "D"; }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1010 "trabalho.y"
    { (yyval).v = inteiro_string(1); (yyval).t.tipo_base = "B"; }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1011 "trabalho.y"
    { (yyval).v = inteiro_string(0); (yyval).t.tipo_base = "B"; }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1012 "trabalho.y"
    { (yyval).t.tipo_base = "C"; }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1013 "trabalho.y"
    { (yyval).t.tipo_base = "S"; }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1015 "trabalho.y"
    { 
		
		pipeAtivo = "int";
			
		if( pipeAtivo != "" )
				(yyval) = Atributo( "x_" + pipeAtivo, pipeAtivo );
		else
				erro( "Variavel 'x' so pode ser usada dentro de pipe" );
    }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1027 "trabalho.y"
    {
    (yyval).v += "#" + (yyvsp[(3) - (3)]).v;
    (yyval).c += "#" + (yyvsp[(3) - (3)]).c;
    (yyval).p += "#" + (yyvsp[(3) - (3)]).t.tipo_base;
}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1033 "trabalho.y"
    {
    (yyval).v = "#" + (yyvsp[(1) - (1)]).v;
    (yyval).c = "#" + (yyvsp[(1) - (1)]).c;
    (yyval).p += "#" + (yyvsp[(1) - (1)]).t.tipo_base;
}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1041 "trabalho.y"
    { (yyval).c = (yyvsp[(1) - (2)]).c + (yyvsp[(2) - (2)]).c; }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1042 "trabalho.y"
    { (yyval).c = ""; }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1046 "trabalho.y"
    {
      string retorno;
      string aux;
      if (nparams >= 1)
      {
        if ((yyvsp[(1) - (6)]).v == "nada")
        {
          aux = "";
          (yyval).c = "void " + (yyvsp[(2) - (6)]).v + "(" + (yyvsp[(4) - (6)]).c + ")\n" + (yyvsp[(6) - (6)]).c;
        }
        else
        {
          aux = " &RI";
          (yyval).c = "void " + (yyvsp[(2) - (6)]).v + "(" + (yyvsp[(4) - (6)]).c + "," + (yyvsp[(1) - (6)]).c + aux + ")\n" + (yyvsp[(6) - (6)]).c;
        }
        ir = ir + 1;
      }
      else
      {
        if((yyvsp[(1) - (6)]).v == "nada")
        {
          (yyval).c = "void " + (yyvsp[(2) - (6)]).v + "()\n" + (yyvsp[(6) - (6)]).c;
        }
        else
        {
          aux = " &RI";
          (yyval).c = "void " + (yyvsp[(2) - (6)]).v + "(" + (yyvsp[(1) - (6)]).c + aux  + ")\n" + (yyvsp[(6) - (6)]).c;
        }
        ir = ir + 1;
      }
      if(busca_funcao((yyvsp[(2) - (6)]).v, &(yyvsp[(2) - (6)]).t) == false)
      {
        inclui_funcao((yyvsp[(2) - (6)]).v, (yyvsp[(1) - (6)]).t, (yyvsp[(4) - (6)]).p);
        nfuncao++;
      }

      nparams = 0;
    }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1086 "trabalho.y"
    { (yyval).t = (yyvsp[(1) - (1)]).t; (yyval).c = (yyvsp[(1) - (1)]).c; }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1087 "trabalho.y"
    { (yyval).t.tipo_base = "V"; }
    break;



/* Line 1806 of yacc.c  */
#line 3291 "y.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 1093 "trabalho.y"


int nlinha = 1;
map<string,int> n_var_temp;
map<string,int> label;

#include "lex.yy.c"


/* **** FUNCOES AUXILIARES **** */
int main(int argc, char* argv[])
{
  yyparse();
}

string gera_rotulo()
{
  char rotulo[200];

  sprintf(rotulo,"ROT%d", nrotulos++);

  return rotulo;
}



string gera_varglobal_temp()
{
  int i, aux;
  string c;

  for (i = 0; i < nvarglobal; i++)
  {
    if (TS_varglobal[i].t.tipo_base == "B" || TS_varglobal[i].t.tipo_base == "I")
    {
      c += "int " + TS_varglobal[i].nome + parte_vetor(TS_varglobal[i].t) + ";\n";
    }
    else if (TS_varglobal[i].t.tipo_base == "S" )
    {
      c += "char " + TS_varglobal[i].nome + parte_vetor(TS_varglobal[i].t) + ";\n";
    }
    else if (TS_varglobal[i].t.tipo_base == "C" )
    {
      c+= "char " + TS_varglobal[i].nome +  parte_vetor(TS_varglobal[i].t) + ";\n";
    }
    else if (TS_varglobal[i].t.tipo_base == "R" )
    {
      c+= "float " + TS_varglobal[i].nome + parte_vetor(TS_varglobal[i].t) +";\n";
    }
    else if (TS_varglobal[i].t.tipo_base == "D" )
    {
        c+= "double " + TS_varglobal[i].nome + parte_vetor(TS_varglobal[i].t) +";\n";
    }
    else
    {
      erro("Erro na gramatica");
    }
  }

  c += gera_decl_temp("int", "I", NTEMP_GLOBAL.i);
  c += gera_decl_temp("float", "R", NTEMP_GLOBAL.r);
  c += gera_decl_temp("double", "D", NTEMP_GLOBAL.d);
  c += gera_decl_temp("int", "B", NTEMP_GLOBAL.b);
  c += gera_decl_temp("char", "C", NTEMP_GLOBAL.c);

  aux = NTEMP_GLOBAL.s;
  c += gera_decl_temp("char", "S", NTEMP_GLOBAL.s);

  for (i = 0; i < aux; i++)
  {
    c += "TS" + inteiro_string(i) + "[255] = '\\0';\n";
  }

  return c;
}


bool pode_inserir_varglobal (string nome)
{
  if (nvarglobal > TAM_MAX_VARS)
  {
    erro("Numero de variaveis globais maximo atingido.");
  }

  if (busca_variavelglobal(nome, NULL))
  {
    erro("Variavel global ja definida.");
  }

  return true;
}

void tipo_resultado(string operador, Atributo op1, Atributo op2, Atributo &resultado)
{
  int i;
  for(i = 0; i < TAM_MAX_OPERADORES; i++)
  {
    if (tipo_operador[i].operador == operador && op1.t.tipo_base == tipo_operador[i].op1 && op2.t.tipo_base == tipo_operador[i].op2)
    {
          resultado.t.tipo_base = tipo_operador[i].resultado;
          return;
    }
  }
  resultado.t.tipo_base = "ERRO";
}

bool busca_varlocal (string nome, Tipo *t)
{
  int i;
  for(i = 0 ; i < nvarlocal; i++)
  {
    if(TS_varlocal[i].nome == nome)
    {
      if (t != NULL)
      {
        *t = TS_varlocal[i].t;
      }
      return true;
    }
  }
  return false;
}

bool busca_varparametro(string nome, Tipo *t)
{
  if (nfuncao != 0)
  {
    int i, j;
    i = nfuncao - 1;
    for(j = 0 ; j < TS_funcao[i].nparam; j++)
    {
      if (TS_funcao[i].parametro[j].nome == nome )
      {
        if (t != NULL)
        {
          *t = TS_funcao[i].parametro[j].t;
        }
        return true;
      }
    }
    return false;
  }
}

void insere_varlocal (string nome, Tipo t)
{
  if (pode_inserir_varlocal(nome) )
  {
    TS_varlocal[nvarlocal].nome = nome;
    TS_varlocal[nvarlocal].t = t;
    nvarlocal++;
  }
  else
  {
    erro("Nao foi possivel declarar a variavel local" +  nome + ".");
  }
}

string gera_decl_temp(string tipo, string tipo_base, int &n)
{
  string c;
  int i;
  for (i = 0; i < n; i++)
  {
    if(tipo_base == "S")
    {
      c += tipo + " " + "Temp_" + tipo_base +  inteiro_string(i) + "[256];\n";
    }
    else
    {
      c += tipo + " " + "Temp_" + tipo_base +  inteiro_string(i) + ";\n";
    }
  }
  n = 0;
  return c;
}

string quebra_codigo_lista(string vetorid, string lsttemp , string lstcodtemp)
{
  string saida;
  string a;
  string b;

  int i = 0;
  int j = 0;
  int contador = 0;

  getchar();

  while(1)
  {
    a = "";
    b = "";

    while(lsttemp[i] != '#' && lsttemp[i] != '\0')
    {
      a += lsttemp[i];
      i++;
    }

    while(lstcodtemp[j] != '#' && lstcodtemp[j] != '\0')
    {
      b += lstcodtemp[j];
      j++;
    }

    if (a[0] != '\0' || b[0] != '\0')
    {
      saida += b  + vetorid + "[" + inteiro_string(contador)+ "]" + "=" + a + ";\n";
      contador++;
    }

    if (lstcodtemp[j] == '\0')
    {
      break;
    }
    i++;
    j++;

  }
  return saida;
}

string parte_vetor(Tipo t)
{
  string codigo;

  int ehString = 1;

  if(t.tipo_base == "S")
  {
    ehString = 256;
  }

  if (t.ndim == 0)
  {
    if(ehString == 1)
    {
      codigo = "";
    }
    else
    {
      codigo = "[256]";
    }
  }
  else if (t.ndim == 1)
  {
    codigo = "[" + inteiro_string(t.tam_dim[0] * ehString) + "]";

  }
  else if (t.ndim == 2)
  {
    codigo = "[" + inteiro_string(t.tam_dim[0] * t.tam_dim[1] * ehString ) + "]";
  }
  return codigo;
}

bool busca_variavelglobal (string nome, Tipo *t)
{
  int i;
  for(i = 0; i < nvarglobal; i++)
  {
    if(TS_varglobal[i].nome == nome)
    {
      if (t != NULL)
      {
        *t = TS_varglobal[i].t;
      }
      return true;
    }
  }
  return false;
}

void inclui_parametro(string nome, Tipo t)
{
  int p;
  if(existe_parametro(nome))
  {
    erro("Parametro ja declarado.");
  }
  p = TS_funcao[nfuncao].nparam;
  TS_funcao[nfuncao].parametro[p].nome = nome;
  TS_funcao[nfuncao].parametro[p].t = t;
  TS_funcao[nfuncao].nparam++;
}

bool busca_funcao(string nome, Tipo *tr)
{
  int i;
  for(i = 0 ; i < nfuncao; i++)
  {
    if(TS_funcao[i].nome == nome)
    {
      if(tr != NULL)
      {
        *tr = TS_funcao[i].retorno;
      }

      return true;
    }
  }
  return false;
}

bool existe_parametro(string nome)
{
  int i;
  int j;

  for (i = 0; i < nfuncao; i++)
  {
    if (TS_funcao[i].nome == nome)
    {

      for (j = 0; j < TS_funcao[i].nparam; j++)
      {
        if (TS_funcao[i].parametro[j].nome == nome)
        {
          return true;
        }
      }

    }

  }
  return false;
}



void geraDeclaracaoVariavel( Atributo* SS, const Atributo& tipo,
const Atributo& id ) {
    SS->v = "";
    SS->t = tipo.t;
    if( tipo.t.nome == "string" ) {
        SS->c = tipo.c +
        "char " + id.v + "["+ toStr( MAX_STR ) +"];\n";
    }
    else {
        SS->c = tipo.c +
        tipo.t.nome + " " + id.v + ";\n";
    }
}

void inclui_funcao(string nome, Tipo retorno, string lista_parametros)
{
  if(existe_funcao(nome))
  {
    erro("Funcao ja declarada.");
  }
  TS_funcao[nfuncao].nome = nome;
  TS_funcao[nfuncao].retorno = retorno;
  TS_funcao[nfuncao].lista_parametros = lista_parametros;

}

string quebra_codigo_parametro(string nometemp, string vetorid, string lsttemp, string lstcodtemp, string tiporet)
{

  string saida;
  string a;
  string b;
  string lista;
  string lista_completa;

  int i = 0, j = 0, contador = 0;

  getchar();

  while(1)
  {
    a = "";
    b = "";

    while (lsttemp[i] != '#' && lsttemp[i] != '\0')
    {
      a += lsttemp[i];
      i++;
    }

    while (lstcodtemp[j] != '#' && lstcodtemp[j] != '\0')
    {
      b += lstcodtemp[j];
      j++;
    }

    if(a[0] != '\0' || b[0] != '\0')
    {
      saida += b;
      if (a != "")
      {
        lista += a + ", ";
      }
      contador++;
    }

    if (lstcodtemp[j] == '\0')
    {
      break;
    }
    i++;
    j++;
  }


  if(tiporet != "V")
  {
    lista_completa = vetorid + "(" + lista + nometemp + ");\n";
    saida+= lista_completa;
    return saida;
  }
  else
  {

    int len = lista.length();
    lista[len - 2] = ' ';
    string saida = vetorid + "("+  lista + ");\n";
    return saida;
  }

}

bool pode_inserir_varlocal (string nome)
{
  if (nvarlocal > TAM_MAX_VARS)
  {
    erro("Numero de variaveis maximo atingido.");
  }
  if (busca_varlocal(nome, NULL) )
  {
    erro("Variavel ja definida.");
  }
  return true;
}

bool compara_resultado(string resultado)
{
  if (TS_funcao[nfuncao-1].retorno.tipo_base == resultado)
  {
    return true;
  }
  else
  {
    erro("Valor retornado invalido");
    cout << nvarlocal << endl;
  }
}

bool existe_funcao(string nome)
{
  int i;
  for (i = 0; i < nfuncao; i++)
  {
    if (TS_funcao[i].nome == nome)
    {
      return true;
    }

  }
  return false;

}

string toStr( int n ) {
    char buf[1024] = "";

    sprintf( buf, "%d", n );

    return buf;
}

bool compara_parametros(string nome, string parametros)
{
  int i;
  for(i = 0; i < nfuncao; i++)
  {
    if (TS_funcao[i].nome == nome && TS_funcao[i].lista_parametros == parametros)
    {
      return true;
    }
  }

  erro("Parametros invalidos.");
  return false;
}



string inteiro_string(int n)
{
  char linha[20];
  sprintf(linha, "%d", n);
  return linha;
}

string gera_temp(string tipo)
{
  char variavel[200];

  if (tipo == "I")
  {
    sprintf(variavel, "Temp_I%d", NTEMP.i++);
  }
  else if (tipo == "R")
  {
    sprintf(variavel, "Temp_R%d", NTEMP.r++);
  }
  else if (tipo == "C")
  {
    sprintf(variavel, "Temp_C%d", NTEMP.c++);
  }
  else if (tipo == "S")
  {
    sprintf(variavel, "Temp_S%d", NTEMP.s++);
  }
  else if (tipo == "B")
  {
    sprintf(variavel, "Temp_B%d", NTEMP.b++);
  }
  else if (tipo == "D")
  {
      sprintf(variavel, "Temp_D%d", NTEMP.d++);
  }
  return variavel;
}

int string_inteiro(string s)
{
  int n;
  sscanf(s.c_str(), "%d", &n);
  return n;
}

void yyerror (const char * st)
{
    puts(st);
    cout << "Linha: " << nlinha << " Perto de: " << yytext << endl;
}



string gera_variavellocal_temp()
{
  int i, aux;
  string c;

  for (i = 0; i < nvarlocal; i++)
  {

    if (TS_varlocal[i].t.tipo_base == "B" || TS_varlocal[i].t.tipo_base == "I")
    {
      c += "int " + TS_varlocal[i].nome + parte_vetor(TS_varlocal[i].t) + ";\n";
    }
    else if (TS_varlocal[i].t.tipo_base == "S" )
    {
      c += "char " + TS_varlocal[i].nome + parte_vetor(TS_varlocal[i].t) + ";\n";
    }
    else if (TS_varlocal[i].t.tipo_base == "C" )
    {
      c+= "char " + TS_varlocal[i].nome + parte_vetor(TS_varlocal[i].t) + ";\n";
    }
    else if (TS_varlocal[i].t.tipo_base == "R" )
    {
      c+= "float " + TS_varlocal[i].nome + parte_vetor(TS_varlocal[i].t) + ";\n";
    }
    else if (TS_varlocal[i].t.tipo_base == "D" )
    {
        c+= "double " + TS_varlocal[i].nome + parte_vetor(TS_varlocal[i].t) + ";\n";
    }
    else
    {
      erro("Erro na gramatica");
    }

  }

  c += gera_decl_temp("int", "I", NTEMP.i);
  c += gera_decl_temp("float", "R", NTEMP.r);
  c += gera_decl_temp("double", "D", NTEMP.d);
  c += gera_decl_temp("int", "B", NTEMP.b);
  c += gera_decl_temp("char", "C", NTEMP.c);

  aux = NTEMP.s;
  c += gera_decl_temp("char", "S", NTEMP.s);

  for (i = 0; i < aux; i++)
  {
    c += "Temp_S" + inteiro_string(i) + "[255] = '\\0';\n";
  }

  nvarlocal = 0;

  c+= inic;
  inic = "";

  return c;
}

void erro(string msg)
{
  cout << msg << endl;
  exit(-1);
}

void insere_varglobal (string nome, Tipo t)
{
  if (pode_inserir_varglobal(nome))
  {
    TS_varglobal[nvarglobal].nome = nome;
    TS_varglobal[nvarglobal].t = t;
    nvarglobal++;
  }
  else
  {
    erro("Nao foi possivel declarar a variavel global" +  nome + ".");
  }
}

void gera_codigo_operador(Atributo &ss, Atributo &s1, Atributo &s2, Atributo &s3)
{
  tipo_resultado(s2.v,s1,s3,ss);
  if (ss.t.tipo_base == "ERRO")
  {
    if(s1.t.tipo_base == "")
    {
      erro("'" + s1.v + "'" + " nao foi declarada.");
    }
    else if (s3.t.tipo_base == "")
    {
      erro("'" + s3.v + "'" + " nao foi declarada.");
    }
    else
    {
      erro("O operador " + s2.v + " nao se aplica a " + s1.t.tipo_base + " e " + s3.t.tipo_base + ".");
    }
  }
  else
  {
    if (s2.v == "<-")
    {
      if (s3.t.ndim != 0)
      {
        string aux = gera_temp(s3.t.tipo_base);
        ss.c = s1.c + s3.c + aux + " = " + s3.v + ";\n"+  s1.v + " = " + aux + ";\n";

        if (s1.t.tipo_base == "S")
        {
          string aux = gera_temp(s1.t.tipo_base);
          ss.c = s1.c + s3.c;
          if (s1.t.ndim != 0)
          {
            ss.c += "strncpy(" + aux + ", " + s3.v + ", 256);\n";
            ss.c += "strncpy(" + s1.v+", " + aux + ", 256);\n";
          }
          else
          {
            ss.c += "strncpy(" + aux + ", " + s3.v + ", 256);\n";
            ss.c += "strncpy(" + s1.v + "," + aux + ", 256);\n";
          }
        }
      }
      else
      {
        if (s3.t.tipo_base == "S")
        {
          string aux = gera_temp(s3.t.tipo_base);
          ss.c = s1.c + s3.c + "strncpy(" + aux + "," + s3.v + ", 256);\n";
          if (s1.t.ndim != 0)
          {
            ss.c += "strncpy(" + s1.v + ", " + aux + ", 256);\n";
          }
          else
          {
            ss.c += "strncpy(" + s1.v + ", " + aux + ", 256);\n";
          }
        }
        else
        {
          ss.c = s1.c + s3.c + s1.v + " = " + s3.v + ";\n";
        }
      }
    }
    else
    {
      if ((s1.t.ndim != 0) && (s3.t.ndim != 0))
      {
        ss.v = gera_temp(ss.t.tipo_base);
        string aux1 = gera_temp(s3.t.tipo_base);
        string aux2 = gera_temp(s3.t.tipo_base);
        ss.c = s1.c + s3.c + aux1 + " = " + s1.v + ";\n" + aux2 + " = " + s3.v + ";\n"+ ss.v + " = " + aux1 + s2.v + aux2 + ";\n";
      }
      else if (s1.t.ndim != 0)
      {
        ss.v = gera_temp(ss.t.tipo_base);
        string aux1 = gera_temp(s1.t.tipo_base);
        ss.c = s1.c + s3.c + aux1 + " = " + s1.v + ";\n" + ss.v + " = " + aux1 + s2.v + s3.v + ";\n";
      }
      else if (s3.t.ndim != 0)
      {
        ss.v = gera_temp(ss.t.tipo_base);
        string aux1 = gera_temp(s3.t.tipo_base);
        ss.c = s1.c + s3.c + aux1 + " = " + s3.v + ";\n" + ss.v + " = " + s1.v + s2.v + aux1 + ";\n";
      }
      else
      {
        if (( s1.t.tipo_base == "S") || ( s3.t.tipo_base == "S"))
        {
          if (s2.v == "+")
          {
            ss.v = gera_temp(ss.t.tipo_base);
            ss.c = s1.c + s3.c + "strncpy(" + ss.v + "," + s1.v + ",256);\n" + "strcat(" + ss.v + "," + s3.v + ");\n";
            ss.t.tipo_base = "S";
          }
        }
        else
        {
          ss.v = gera_temp(ss.t.tipo_base);
          if(s2.v == "<>")
            ss.c = s1.c + s3.c + ss.v + " = " + s1.v + "==" + s3.v + ";\n";
          else if(s2.v == "OU")
            ss.c = s1.c + s3.c + ss.v + " = " + s1.v + "||" + s3.v + ";\n";
          else if(s2.v == "E")
            ss.c = s1.c + s3.c + ss.v + " = " + s1.v + "&&" + s3.v + ";\n";
          else
            ss.c = s1.c + s3.c + ss.v + " = " + s1.v + s2.v + s3.v + ";\n";
        }
      }
    }
  }
}

void geraCodigoFilter( Atributo* SS, const Atributo& condicao ) {
  *SS = Atributo();
  SS->v = gera_temp("B");
  SS->c = condicao.c +
          "  " + SS->v + " = !" + condicao.v + ";\n" +
          "  if( " + SS->v + " ) goto " + passoPipeAtivo + ";\n";
}



//COMPARAR COM O NOSSO FOR E APAGAR
void geraCodigoFor( Atributo* SS, const Atributo& inicial,
                                  const Atributo& condicao,
                                  const Atributo& passo,
                                  const Atributo& cmds ) {
  string forCond = gera_rotulo(),
         forFim = gera_rotulo();
  string valorNotCond = gera_temp("B");

  *SS = Atributo();
  if( condicao.t.nome != "bool" )
    erro( "A expressão de teste deve ser booleana: " + condicao.t.nome );

  // Funciona apenas para filtro, sem pipe que precisa de buffer
  // (sort, por exemplo, não funciona)
  SS->c = inicial.c + forCond + ":\n" + condicao.c +
          "  " + valorNotCond + " = !" + condicao.v + ";\n" +
          "  if( " + valorNotCond + " ) goto " + forFim + ";\n" +
          cmds.c +
          passo.c +
          "  goto " + forCond + ";\n" +
          forFim + ":\n";
}

