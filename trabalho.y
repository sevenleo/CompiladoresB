%{
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

%}

//TIPOS
%token _INT _CHAR _BOOL _DOUBLE _FLOAT _STRING

//VALORES DOS TIPOS
%token _ID _CTE_INT _CTE_CHAR _CTE_FLOAT _CTE_DOUBLE _CTE_BOOL_V _CTE_BOOL_F _CTE_STRING

//IF & ELSE
%token _ROLA_SE _END_ROLOU _NAO_ROLOU _END_NAO_ROLOU

//FOR & WHILE
%token _ENROLANDO _END_ENROLANDO _ENROLA_SE _END_ENROLA_SE

//DO - WHILE
%token _FAZ _END_FAZ_DEPOIS_ENROLA

//SWITCH
%token _INVESTIGA _END_INVESTIGA _SUSPEITO _CASO_ENCERRADO _INOCENTE

//MATRIZ & VETOR
%token _GRADE _VETOR

//ENTRADA E SAIDA
%token _CIN _COUT

//FUNCOES
%token _FUNCAO_MAIN _VOID _PROTOTIPO _REF

//COMECO & TERMINO DE BLOCO
%token _ALFA _OMEGA

//RETORNO DE FUNCOES
%token _RETORNA_FUNCAO

//OPERADORES E ATRIBUIÇÃO
%token  _ATRIBUI
%token  _SHIFTR
%token  _SHIFTL
%token  _MENORIGUAL
%token  _MAIORIGUAL
%token  _DIFERENTE
%token  _IGUAL
%token  _AND
%token  _OR
%token  _NOT
%token  _MOD

//Pip
%token _INTERVALO _PIPE _FILTER _FOREACH _X

//ASSOCIATIVIDADE E PRECEDENCIA
%nonassoc '<' '>' _MENORIGUAL _MAIORIGUAL _IGUAL _DIFERENTE
%left '+' '-'
%left '*' '/'
%right _MOD
%%

SL    : S
    {
      cout << "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n//#include <cstring>\n#include <string>\n#include <iostream>\n\nusing namespace std;\n\n" +  $1.c << endl;
    }
    ;

S   :  PROTOTIPO_FUNCOES VARIAVEIS_GLOBAIS BLOCO_PRINCIPAL FUNCTIONS   { $$.c = $1.c + $2.c + $3.c + $4.c;   }
    ;

PROTOTIPO_FUNCOES :  PROTOTIPO_FUNCOES PROTOTIPO ';'  { $$.c += $2.c; }
      |           { $$.c = ""; }
      ;

PROTOTIPO  : _PROTOTIPO RETORNO _ID '('  PARAMETROS ')'
      {
        string aux;
        if (nparams >= 1)
        {
          if ($2.v == "nada")
          {
            aux = "";
            $$.c = "void " + $3.v + "(" + $5.c + ");\n";
          }
          else
          {
            aux = " &RI";
            $$.c = "void " + $3.v + "(" + $5.c + "," + $2.c + aux + ");\n";
          }
          ir = ir + 1;
        }
        else
        {
          if($2.v == "nada")
          {
            $$.c = "void " + $3.v + "();\n";
          }
          else
          {
            aux = " &RI";
            $$.c = "void " + $3.v + "(" + $2.c + aux  + ");\n";
          }
          ir = ir + 1;
        }

        inclui_funcao($3.v,$2.t, $5.p);
        nfuncao++;
        nparams = 0;
      }
      | { }
      ;

PARAMETROS  : LISTAPARAMETROS
      |         { $$.p = ""; }
      ;

LISTAPARAMETROS : LISTAPARAMETROS ',' PARAMETRO { $$.p += "#" + $3.t.tipo_base; $$.c = $$.c + "," + $3.c; }
        | PARAMETRO         { $$.p = "#" + $1.t.tipo_base; }
        ;

PARAMETRO : TIPO _ID
    {
        nparams++;
        $$.t = $1.t;
        $$.c = $1.c + " " + $2.v;
        inclui_parametro($2.v, $1.t);
        $$.p = "#" + $1.t.tipo_base;
    }
      ;

VARIAVEIS_GLOBAIS : DECLVARG ';' VARIAVEIS_GLOBAIS  { $$.c = gera_varglobal_temp(); + "\n" + $3.c; }
      |  { 
				$$.c = "\n"; 
			
				
		  }
      ;

//TODO:
DECLVARG  : DECLVARG ',' _ID ARRAY CMD_ATRIBUICAO
      {
        $$.t = $1.t;
        $3.t = $1.t;
        $3.t.ndim = $4.t.ndim;
        $3.t.tam_dim[0] = $4.t.tam_dim[0];
        $3.t.tam_dim[1] = $4.t.tam_dim[1];
        insere_varglobal($3.v , $1.t);
      }
      | TIPO _ID ARRAY CMD_ATRIBUICAO
      {
        $$.t = $1.t;
        $2.t = $1.t;
        $1.t.ndim = $3.t.ndim;
        $1.t.tam_dim[0] = $3.t.tam_dim[0];
        $1.t.tam_dim[1] = $3.t.tam_dim[1];
        insere_varglobal($2.v , $1.t);
      }
      ;

TIPO    : _INT  { $$.t.tipo_base =  "I"; $$.v = $1.v; $$.c = "int"; }
    | _FLOAT    { $$.t.tipo_base = "R"; $$.v = $1.v; $$.c = "float"; }
    | _DOUBLE   { $$.t.tipo_base = "D"; $$.v = $1.v; $$.c = "double"; }
    | _BOOL   { $$.t.tipo_base = "B"; $$.v = $1.v; $$.c = "char"; }
    | _CHAR   { $$.t.tipo_base = "C"; $$.v = $1.v; $$.c = "char"; }
    | _STRING { $$.t.tipo_base = "S"; $$.v = $1.v; $$.c = "string"; }
    ;

ARRAY:   '(' _CTE_INT ')' //TODO: Arrumar arrays
        { $$.t.ndim = 1; $$.t.tam_dim[0] = atoi(($2.v).c_str()); $$.t.tam_dim[1] = 0; }
    | '(' _CTE_INT ',' _CTE_INT ')'
        { $$.t.ndim = 2; $$.t.tam_dim[0] = atoi(($2.v).c_str()); $$.t.tam_dim[1] = atoi(($4.v).c_str()); }
    |
        { $$.t.ndim = 0; $$.t.tam_dim[0] = 0; $$.t.tam_dim[1] = 0; }
    ;

BLOCO_PRINCIPAL   : _FUNCAO_MAIN BLOCO { 
											$$.c = "";
											$$.c += "int main ()\n"; 
											$$.c += $2.c; 
										}
      ;



BLOCO : _ALFA VARS_LOCAIS CMDS _OMEGA
      { $$.c = "{\n\n " + DeclaraVarPipes()+gera_variavellocal_temp() +  $3.c + "\n\n return 0; \n}\n"; }

    ;

VARS_LOCAIS : DECLVARL ';' VARS_LOCAIS {}
      | {}
      ;
//TODO:
DECLVARL  : DECLVARL ',' _ID ARRAY CMD_ATRIBUICAO
      {
        $$.t = $1.t;
        $3.t = $1.t;
        $1.t.ndim = $4.t.ndim;
        $1.t.tam_dim[0] = $4.t.tam_dim[0];
        $1.t.tam_dim[1] = $4.t.tam_dim[1];
        insere_varlocal($3.v , $1.t);

        if($5.v != "")
        {
          inic +=$5.c + $3.v + "=" + $5.v + ";\n";
        }
      }
      | TIPO _ID ARRAY CMD_ATRIBUICAO
      {
        $$.t = $1.t;
        $2.t = $1.t;
        $1.t.ndim = $3.t.ndim;
        $1.t.tam_dim[0] = $3.t.tam_dim[0];
        $1.t.tam_dim[1] = $3.t.tam_dim[1];

        insere_varlocal($2.v , $1.t);

        if ($4.v != "")
        {
          if (($4.v).c_str()[0] == '#')
          {
            inic += quebra_codigo_lista($2.v, $4.v , $4.c);
          }
          else
          {
            inic += $4.c;
            Atributo ss, s1, s2, s3;
            s1 = $2;
            s2.v = "<-";
            s3 = $4;
            gera_codigo_operador(ss, s1,s2 ,s3 );
            inic += ss.c;
          }
        }
      }
      ;

CMD_ATRIBUICAO  : _ATRIBUI E        { $$.v = $2.v; $$.t = $2.t; $$.c = $2.c; }
    | _ATRIBUI  '(' LST_E ')'   { $$.v = $3.v; $$.c = $3.c; }
    | _ATRIBUI  '(' LST_LST_E ')' { }
    |         { $$.v = ""; $$.c = ""; }
    ;

//TODO:
LST_LST_E : LST_LST_E ',' '(' LST_E ')'   { }
    | '(' LST_E ')'       { }
    ;

CMDS: CMDS CMD  { $$.c = $1.c + $2.c; }
      |         { $$.c = ""; }
      ;

CMD   : CMD_E ';'     { }
      | CMD_FOR   { }
      | CMD_WHILE   { }
      | CMD_IF      { }
      | CMD_RETURN    { }
      | CMD_IN ';'    { }
      | CMD_OUT ';'   { }
      | CMD_DO_WHILE   { }
      | CMD_SWITCH { }
      | CMD_PIPE  { }
      ;

CMD_IN  : _CIN F     { $$.c = $2.c + "cin >>" + $2.v + " ;\n"; }
      ;


CMD_OUT : _COUT E
{
        if (($2.t.ndim != 0) && ($2.t.tipo_base == "S"))
        {
            $$.c = $2.c + "cout << " + $2.v  + "<< endl;\n ";
        }
        else
        {
            $$.c = $2.c + "cout << " + $2.v  + "<< endl;\n ";
        }
}
    ;

CMD_RETURN  : _RETORNA_FUNCAO E ';'
      {
          $$.c = $2.c + "RI = " + $2.v + ";\nreturn;\n";
          //compara_resultado($2.t.tipo_base);  VER ISSO AQUI!!!!!!!!
      }
    | _RETORNA_FUNCAO _VOID ';' { }
      ;


CMD_WHILE : _ENROLA_SE '(' E ')' VARS_LOCAIS CMDS _END_ENROLA_SE
      {
        string rotulo = gera_rotulo();
        string rotulo_aux = gera_rotulo();
        string teste = gera_temp("B");
        string codigo;
        codigo += $3.c;
        codigo += teste + " =" + $3.v + ";\n";

        codigo += "if (!(" + teste + ")) \n";
        codigo += "goto " + rotulo_aux + ";\n";

        codigo += rotulo + ": ";
        codigo += $6.c;

        codigo += $3.c;
        codigo += teste + " =" + $3.v + ";\n";

        codigo += "if (" + teste + " ) \n";
        codigo += "goto " + rotulo + ";\n";
        codigo += rotulo_aux + ": ";
        $$.c = codigo;
      }
      ;

CMD_DO_WHILE: _FAZ VARS_LOCAIS CMDS _ENROLA_SE '(' E ')' ';'
{
    string varTeste = gera_temp( "B" );
    string labelFim = gera_rotulo();
    string labelTeste = gera_rotulo();

    $$.v = "";
    $$.c = "\t" + labelTeste + ":\n" + $6.c +
    "\t" + varTeste + " = !" + $6.v + ";\n" +
    "\tif( " + varTeste + " ) goto " + labelFim +";\n" +
    $3.c +
    "\tgoto " + labelTeste + ";\n" +
    "\t" + labelFim + ":\n";
}
;

//No nosso for nao declaramos variavel, a variavel ja tem que ter sido declarada! Temos que incrementar manualmente.
CMD_FOR   : _ENROLANDO '(' _ID _ATRIBUI _CTE_INT ';' E ')' VARS_LOCAIS CMDS _END_ENROLANDO
      {

          string varTeste = gera_temp( "B" );
          string labelFim = gera_rotulo();
          string labelTeste = gera_rotulo();

          $$.v = "";
          $$.c = $5.c + "\t" + labelTeste + ":\n" + $7.c +
          "\t" + varTeste + " = !" + $7.v + ";\n" +
          "\tif( " + varTeste + " ) goto " + labelFim +";\n" +
          $10.c +
          "\tgoto " + labelTeste + ";\n" +
          "\t" + labelFim + ":\n ;";
      }
      ;


CMD_IF  : _ROLA_SE '(' E ')'  VARS_LOCAIS CMDS _END_ROLOU
    {
      string codigo;
      string rotulo = gera_rotulo();
      string teste = gera_temp("B");

      codigo += $3.c;
      codigo += teste +" =  ! " + $3.v + " ;\n";
      codigo += "if("  +  teste  +   ")\n";
      codigo += "goto " + rotulo + ";\n";
      codigo += $6.c;
      codigo += rotulo + ": ;\n";

      $$.c = codigo;
    }
    | _ROLA_SE '(' E ')' VARS_LOCAIS CMDS _NAO_ROLOU VARS_LOCAIS CMDS _END_NAO_ROLOU
    {
      string codigo;
      string rotulo = gera_rotulo();
      string teste = gera_temp("B");
      string rotulo2 = gera_rotulo();

      codigo += $3.c;
      codigo += teste +" =  ! " + $3.v + " ;\n";
      codigo += "if("  +  teste  +   ")\n";
      codigo += "goto " + rotulo + ";\n";
      codigo += $6.c;
      codigo += "goto " + rotulo2 + ";\n";
      codigo += rotulo + ": ;\n";
      codigo += $9.c;
      codigo += rotulo2 + ": ;\n";

      $$.c = codigo;
    }
    ;



//SWITCH
CMD_SWITCH : _INVESTIGA '(' ID_LABEL ')' _ALFA CASES DEFAULT _OMEGA
{

    string codigo;

    codigo += $6.c;
    codigo += $7.c;

    codigo += fim_switch +": ";
    $$.c = codigo;
}

;


//SWITCH
ID_LABEL: _ID
{
		  fim_switch = gera_rotulo();
          id_switch = $1.v;
          $$.c = $1.c;
}
;

CASES : CASES CASE { $$.c = $1.c + $2.c; }
|   CASE   { $$.c = $1.c; }
;

CASE : _SUSPEITO _CTE_INT ':' VARS_LOCAIS CMDS _CASO_ENCERRADO ';'
{
    string codigo;
    string endcase = gera_rotulo();

    codigo += "\nif (" + id_switch +" != "+ $2.v + ") goto "+
    endcase+";\n";
    codigo += $4.c;
    codigo += $5.c;
    codigo+= "goto "+fim_switch + "; \n";
    codigo+= endcase + ": \n";

    $$.c = codigo;
}
;

DEFAULT : _INOCENTE ':' VARS_LOCAIS CMDS _CASO_ENCERRADO ';'
{
    string codigo;
    codigo += $3.c;
    codigo += $4.c;
    $$.c = codigo;

}
;


/**
 INTERVALO< 1.0 : 20.0 >
-    //=>FILTER[ x % 2 == 0 ]
+  INTERVALO[ 0 .. 20 ]
+    =>FILTER[ (x*x) % 3 == 0 ] =>FILTER[ x % 2 == 0 ]
     =>FOREACH[ COUT << x << "\n" ];
 */

//PIPES

CMD_PIPE : _INTERVALO '[' E '.' INI_PIPE ']' PROCS CONSOME
          {
            Atributo inicio, condicao, passo, cmd;

            inicio.c = $3.c + $5.c +
                       "  x_" + pipeAtivo + " = " + $3.v + ";\n";
            condicao.t.nome = "bool";
            condicao.v = gera_temp("B"); //geraTemp( Tipo( "bool" ) );
            condicao.c = "  " + condicao.v + " = " + "x_" + pipeAtivo + " <= " + $5.v + ";\n";
            passo.c = passoPipeAtivo + ":\n" + "  x_" + pipeAtivo + " = x_" + pipeAtivo + " + 1;\n";
            cmd.c = $7.c + $8.c;

            //FAZER
            //geraCodigoFor( &$$, inicio, condicao, passo, cmd );

            pipeAtivo = ""; }
        ;
INI_PIPE : E
        {
			$$ = $1;
			pipeAtivo =  $1.t.nome;
			passoPipeAtivo = gera_rotulo();
		}
	 ;

PROCS : _PIPE PROC PROCS
        { $$.c = $2.c + $3.c; }
      | _PIPE
        { $$ = Atributo(); }
      ;

PROC : _FILTER '[' E ']'
       {
		   //FAZER
		   //geraCodigoFilter( &$$, $3 );
	   }
     ;

CONSOME : _FOREACH '[' CMD ']'
          { $$.c = $3.c; }
        ;


//end_PIPES



CMD_E : E { }
    | { }
    ;

E   : E _ATRIBUI E1   { $$.c = $1.c;  $2.v = "<-"; gera_codigo_operador($$,$1,$2,$3); }
    | E1          { }
    ;

E1    : E1 _OR E2       { gera_codigo_operador($$,$1,$2,$3); }
    | E1 _AND E2      { gera_codigo_operador($$,$1,$2,$3); }
    | E2          { }
    ;

E2    : E2 '>' E3     { gera_codigo_operador($$,$1,$2,$3); }
    | E2 '<' E3     { gera_codigo_operador($$,$1,$2,$3); }
    | E2 _MAIORIGUAL E3   { gera_codigo_operador($$,$1,$2,$3); }
    | E2 _MENORIGUAL E3   { gera_codigo_operador($$,$1,$2,$3); }
    | E2 _IGUAL E3      { gera_codigo_operador($$,$1,$2,$3); }
    | E2 _DIFERENTE E3      { gera_codigo_operador($$,$1,$2,$3); }
    | E3              { }
    ;

E3    : E3 '+' E4   { gera_codigo_operador($$,$1,$2,$3); }
    | E3 '-' E4   { gera_codigo_operador($$,$1,$2,$3); }
    | E4          { }
    ;

E4    : E4 '*' E5   { gera_codigo_operador($$,$1,$2,$3); }
    | E4 '/' E5     { gera_codigo_operador($$,$1,$2,$3); }
    | F         { }
    ;

E5    : _NOT F  { }
    | F     { }
    ;

F   : _ID
    {
      busca_variavelglobal($1.v, & $1.t);
      busca_varlocal($1.v, & $1.t);
      busca_varparametro($1.v, & $1.t);

      $$.t = $1.t;
    }
    | _ID '(' ')'
    {
      busca_funcao($1.v, & $1.t);
      $$ = $1;
      $$.v = gera_temp($1.t.tipo_base);
      $$.c = quebra_codigo_parametro($$.v, $1.v,  "" , "", $1.t.tipo_base);
      compara_parametros($1.v, "");
    }
    | _ID '(' LST_E ')'
    {

      busca_funcao($1.v, & $1.t);
      $$ = $1;

      if ($1.t.tipo_base == "V")
      {
        $$.v = "";
      }
      else
      {
        $$.v = gera_temp($1.t.tipo_base);
      }

      $$.c = quebra_codigo_parametro($$.v, $1.v,  $3.v , $3.c, $1.t.tipo_base);

      compara_parametros($1.v, $3.p);
    }
    | _ID '(' E ')'
    {
      busca_variavelglobal($1.v, & $1.t);
      busca_varlocal($1.v, & $1.t);

      $$.t = $1.t;

      $$.c = $3.c;

      string aux = gera_temp($3.t.tipo_base);

      if ($3.t.ndim !=0 )
      {
        $$.c += aux + " = " + $3.v + ";\n";
        $3.v = aux;
      }

      if ($1.t.tipo_base == "S")
      {
        $$.c += aux + " = " + $3.v + "* 256" + ";\n";
        $3.v = aux;

        $$.v =  $1.v + "[" + $3.v + "]";
      }
      else
      {
        $$.v =  $1.v + "[" + $3.v + "]";
      }
    }
    | _ID '(' E ',' E ')'
    {
      busca_variavelglobal($1.v, & $1.t);
      busca_varlocal($1.v, & $1.t);
      $$.t = $1.t;

      string codigo;

      string i = gera_temp("I");
      codigo += i + " = " + $3.v + ";\n";
      codigo += i + " = " + i + " * " + inteiro_string($1.t.tam_dim[1]) + ";\n";

      Atributo ss, s1, s2, s3;
      s1.v = i;
      s1.t.tipo_base = "I";
      s2.v = "+";
      s3 = $5;
      gera_codigo_operador(ss,s1,s2,s3);

      codigo += ss.c;

      $$.c = $3.c + $5.c + codigo;

      string aux = gera_temp($3.t.tipo_base);

      if ($1.t.tipo_base == "S")
      {
        $$.c += aux + " = " + ss.v + "* 256" + ";\n";
        $3.v = aux;

        $$.v =  $1.v + "[" + aux + "]";
      }
      else
      {
        $$.v =  $1.v + "[" + ss.v + "]";
      }

    }
    | '(' E ')'
    {
      $$.t.tipo_base = $2.t.tipo_base;
      $$.v = $2.v;
      $$.c =  $2.c;
    }
    | _CTE_INT        { $$.t.tipo_base = "I";  }
    | _CTE_FLOAT      { $$.t.tipo_base = "R"; }
    | _CTE_DOUBLE     { $$.t.tipo_base = "D"; }
    | _CTE_BOOL_V     { $$.v = inteiro_string(1); $$.t.tipo_base = "B"; }
    | _CTE_BOOL_F     { $$.v = inteiro_string(0); $$.t.tipo_base = "B"; }
    | _CTE_CHAR       { $$.t.tipo_base = "C"; }
    | _CTE_STRING     { $$.t.tipo_base = "S"; }
    | _X
	{ 
		
		pipeAtivo = "int";
			
		if( pipeAtivo != "" )
				$$ = Atributo( "x_" + pipeAtivo, pipeAtivo );
		else
				erro( "Variavel 'x' so pode ser usada dentro de pipe" );
    }
    ;

LST_E	: LST_E ',' E
{
    $$.v += "#" + $3.v;
    $$.c += "#" + $3.c;
    $$.p += "#" + $3.t.tipo_base;
}
| E
{
    $$.v = "#" + $1.v;
    $$.c = "#" + $1.c;
    $$.p += "#" + $1.t.tipo_base;
}
;


FUNCTIONS : FUNCTIONS FUNCTION    { $$.c = $1.c + $2.c; }
    |         { $$.c = ""; }
    ;

FUNCTION  : RETORNO _ID '(' PARAMETROS ')' BLOCO
    {
      string retorno;
      string aux;
      if (nparams >= 1)
      {
        if ($1.v == "nada")
        {
          aux = "";
          $$.c = "void " + $2.v + "(" + $4.c + ")\n" + $6.c;
        }
        else
        {
          aux = " &RI";
          $$.c = "void " + $2.v + "(" + $4.c + "," + $1.c + aux + ")\n" + $6.c;
        }
        ir = ir + 1;
      }
      else
      {
        if($1.v == "nada")
        {
          $$.c = "void " + $2.v + "()\n" + $6.c;
        }
        else
        {
          aux = " &RI";
          $$.c = "void " + $2.v + "(" + $1.c + aux  + ")\n" + $6.c;
        }
        ir = ir + 1;
      }
      if(busca_funcao($2.v, &$2.t) == false)
      {
        inclui_funcao($2.v, $1.t, $4.p);
        nfuncao++;
      }

      nparams = 0;
    }
    ;

RETORNO : TIPO  { $$.t = $1.t; $$.c = $1.c; }
    | _VOID   { $$.t.tipo_base = "V"; }
    ;




%%

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
