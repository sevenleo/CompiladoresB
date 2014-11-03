all: trabalho
	@echo ____________________________________________________________________Cria
	@./trabalho < entrada.cc 
	@./trabalho < entrada.cc > saida.c
	@echo ____________________________________________________________________compila
	cat saida.c -n
	@echo ------------
	g++ saida.c 
	@echo ____________________________________________________________________Executa
	@./a.out
 	
lex.yy.c: trabalho.lex
	@echo ____________________________________________________________________1/4
	flex trabalho.lex

y.tab.c: trabalho.y
	@echo ____________________________________________________________________2/4
	yacc trabalho.y

trabalho: lex.yy.c y.tab.c
	@echo ____________________________________________________________________3/4
	g++ -o trabalho y.tab.c -lfl

clean: 
	rm y.tab.c
	rm lex.yy.c
	rm trabalho
	
