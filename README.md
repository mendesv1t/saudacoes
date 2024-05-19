### Contexto
O programa consiste em praticar definições acerca do uso de variáveis de condição, que realizam as seguintes regras:

* A thread 1 imprime a frase “Oi Maria!”;
* A thread 2 imprime a frase “Oi José!”;
* A thread 3 imprime a frase “Sente-se por favor.”;
* A thread 4 imprime a frase “Até mais José!”;
* A thread 5 imprime a frase “Até mais Maria!”.

- As threads devem ser criadas todas de uma vez na função main. As regras de impressão
das mensagens (execução das threads) serão:
   - (i) A ordem em que as threads 1 e 2 imprimem suas mensagens não importa, mas
ambas devem sempre imprimir suas mensagens antes da thread 3.
   - (ii) A ordem em que as threads 4 e 5 imprimem suas mensagens não importa, mas
ambas devem sempre imprimir suas mensagens depois da thread 3.
