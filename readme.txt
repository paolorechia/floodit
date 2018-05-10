**************************************************************************
UFPR - DINF
CI209 - Inteligência Artificial - 2018-1              
**************************************************************************
Trabalho Prático 1                                    
Prof. Fabiano                                         
Alunos: Michel ... GRR                                
        Paolo Andreas Stall Rechia - GRR 20135196     
**************************************************************************

Uso:

$ make

Compilará diversos executáveis no diretório corrente:

1. guloso
2. guloso2
3. aestrela
4. aestrela2
5. aestrela3

Os programas 1 a 3 recebem como parâmetro o número da função de heurística, por
exemplo:

$ ./guloso 4 < exemplo_mapa.txt


Os programas 4 e 5 tem as heurísticas definidas em código fonte:


$ ./aestrela2 < exemplo_mapa.txt


O programa 1 é um algoritmo guloso que aplica a função heurística passada,
e, se todos os nós tem mesma distância, escolhe um aleatoriamente.

O programa 2 apenas aplica a heurística sem aleatoriedade.

O programa 3 aplica uma única função de heurística para resolver o problema

Os programas 4 e 5 aplicam uma combinação pré-definida de heurísticas.


**************************************************************************

Qual testar primeiro?

1. A*

Para instâncias semelhantes ao exemplo fornecido na especificação (30x30), 
recomenda-se executar o aestrela3 que resolveu o exemplo em 88 passos.

Para instâncias maiores, o aestrela2 (que é consideravelmente mais rápido),
e consegue utilizar menos memória.

O A* não resolve satisfatoriamente instâncias muito grandes (> 100x100),
ou a heurística utiliza muito espaço em memória (pouco informada) ou toma 
muito tempo de processamento.


2. Guloso

Se a memória estoura, utilizar algum algoritmo guloso como segunda opção.



**************************************************************************

Heuristicas:

1. 
2. 
3. 
4. 
5. 
6. 
7. 


**************************************************************************

