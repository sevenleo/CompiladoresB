DELIM   [\t ]
LINHA   [\n]
NUMERO  [0-9]
LETRA   [A-Za-z_]
INT     {NUMERO}+

FLOAT   {NUMERO}+("."{NUMERO}+)f?
DOUBLE  {NUMERO}+("."{NUMERO}+)d?
ID      {LETRA}({LETRA}|{NUMERO})*
STRING  \"[^"\n]*\"
CHAR	"\'"."\'"
COMMENT "//".*
BOOLV    "yang"
BOOLF    "yin"


%option noyywrap

%%

{LINHA}    	{ nlinha++; }
{DELIM}    	{}
{COMMENT}	{}

"int"						{  yylval = Atributo( "", yytext ); return _INT; }
"char"						{  yylval = Atributo( "", yytext ); return _CHAR; }
"bool"						{  yylval = Atributo( "", yytext ); return _BOOL; }
"double"					{  yylval = Atributo( "", yytext ); return _DOUBLE; }
"float"						{  yylval = Atributo( "", yytext ); return _FLOAT; }
"string"					{  yylval = Atributo( "", yytext ); return _STRING; }

"mostre"					{  yylval = Atributo( yytext ); return _COUT; }
"leia"						{  yylval = Atributo( yytext ); return _CIN; }
"<<" 						{  yylval = Atributo( yytext ); return _SHIFTL; }
">>" 						{  yylval = Atributo( yytext ); return _SHIFTR; }
"<-"						{  yylval = Atributo( yytext ); return _ATRIBUI; }
"<="						{  yylval = Atributo( yytext ); return _MENORIGUAL; }
">="						{  yylval = Atributo( yytext ); return _MAIORIGUAL; }
"!="						{  yylval = Atributo( yytext ); return _DIFERENTE; }
"=="						{  yylval = Atributo( yytext ); return _IGUAL; }
"&&"						{  yylval = Atributo( yytext ); return _AND; }
"||"						{  yylval = Atributo( yytext ); return _OR; }
"!"							{  yylval = Atributo( yytext ); return _NOT; }
"%"							{  yylval = Atributo( yytext ); return _MOD; }
"@"							{  yylval = Atributo( yytext ); return _REF; }

{INT}      					{ yylval = Atributo( yytext ); return _CTE_INT; }
{DOUBLE}   					{ yylval = Atributo( yytext ); return _CTE_DOUBLE; }
{STRING}   					{ yylval = Atributo( yytext ); return _CTE_STRING; }
{BOOLV}   					{ yylval = Atributo( yytext ); return _CTE_BOOL_V; }
{BOOLF}   					{ yylval = Atributo( yytext ); return _CTE_BOOL_F; }
{FLOAT}   					{ yylval = Atributo( yytext ); return _CTE_FLOAT; }
{CHAR}   					{ yylval = Atributo( yytext ); return _CTE_CHAR; }

"prototype"					{ yylval = Atributo( yytext );  return _PROTOTIPO ; }

"rola se"  					{ yylval = Atributo( yytext );  return _ROLA_SE ; }
"rolou"						{ yylval = Atributo( yytext );  return _END_ROLOU; }
"nao rolou"					{ yylval = Atributo( yytext );  return _NAO_ROLOU; }
"end nao rolou"				{ yylval = Atributo( yytext );  return _END_NAO_ROLOU; }


"enrolando"					{ yylval = Atributo( yytext );  return _ENROLANDO; }
"end enrolando"				{ yylval = Atributo( yytext );  return _END_ENROLANDO; }
"enrola se"					{ yylval = Atributo( yytext );  return _ENROLA_SE; }
"end enrola se"				{ yylval = Atributo( yytext );  return _END_ENROLA_SE; }

		
"faz"						{ yylval = Atributo( yytext );  return _FAZ; }
"end faz depois enrola" 	{ yylval = Atributo( yytext );  return _END_FAZ_DEPOIS_ENROLA; }

"investiga"					{ yylval = Atributo( yytext );  return _INVESTIGA; }
"end investiga"				{ yylval = Atributo( yytext );  return _END_INVESTIGA; }
"suspeito"					{ yylval = Atributo( yytext );  return _SUSPEITO; }
"caso encerrado"			{ yylval = Atributo( yytext );  return _CASO_ENCERRADO; }
"inocente"					{ yylval = Atributo( yytext );  return _INOCENTE; }

"vetor"						{ yylval = Atributo( yytext );  return _VETOR; }
"grade"						{ yylval = Atributo( yytext );  return _GRADE; }
"LetTheGamesBegin()"		{ yylval = Atributo( yytext );  return _FUNCAO_MAIN; }
"nada"						{ yylval = Atributo( yytext );  return _VOID; }

"alfa"						{ yylval = Atributo( yytext );  return _ALFA; }
"omega"						{ yylval = Atributo( yytext );  return _OMEGA; }
"respondo"					{ yylval = Atributo( yytext );  return _RETORNA_FUNCAO; }


"INTERVALO"					{ yylval = Atributo( yytext );  return _INTERVALO; }
"=>"						{ yylval = Atributo( yytext );  return _PIPE; }
"FILTER"					{ yylval = Atributo( yytext );  return _FILTER; }
"FOREACH"					{ yylval = Atributo( yytext );  return _FOREACH; }
"x"							{ yylval = Atributo( yytext ); return _X; }


{ID}       					{ yylval = Atributo( yytext ); return _ID; }
.          					{ yylval = Atributo( yytext ); return *yytext; }

%%
