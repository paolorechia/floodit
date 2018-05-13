**************************************************************************
UFPR - DINF
CI209 - Inteligência Artificial - 2018-1              
**************************************************************************
Trabalho Prático 1                                    
Prof. Fabiano                                         
Alunos: Michel Melo de Souza       - GRR 20159342                                
        Paolo Andreas Stall Rechia - GRR 20135196     
**************************************************************************


Tópicos:

1. Uso
2. Qual testar primeiro?
3. Heuristicas
4. Sobre o código
5. Limite de memória
6. Como melhorar
**************************************************************************

1. Uso

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

2. Qual testar primeiro?

--> A*

Para instâncias semelhantes ao exemplo fornecido na especificação (30x30), 
recomenda-se executar o aestrela3 que resolveu o exemplo em 88 passos.

Para instâncias maiores, o aestrela2 (que é consideravelmente mais rápido),
e consegue utilizar menos memória.

O A* não resolve satisfatoriamente instâncias muito grandes (> 100x100),
ou a heurística utiliza muito espaço em memória (pouco informada) ou toma 
muito tempo de processamento.


--> Guloso

Se a memória estoura, utilizar algum algoritmo guloso como segunda opção.



**************************************************************************

3. Heuristicas:


1 Conta quantas cores ainda existem em jogo e subtrai 1. Essa heurística
   tem um custo de memória intrátavel de explorar com A*.
2 Conta quantas células da matriz são  de diferentes da célula(0,0)
3 Conta quantas células na diagonal são de cor diferente da célula(0,0)
    --> Importante: essa heurística não resolve o problema, apenas ajuda
        a alcançar a outra extremidade do tabuleiro.
4 Realiza uma busca em largura nas fronteiras para contar quantos com-
   ponentes de cor ainda estão em jogo. Conta o número vezes que um 
   possível componente é enfileirado. 
5 Igual ao 4, porém com poluição do resultado para diminuir a superestima-
   ção da distância (embora ainda superestime).
6 (Em desenvolvimento)


**************************************************************************

4. Código Fonte

Todo código foi construída em cima da implementação do floodit fornecida
na especificação do trabalho.
Para implementar o A*, foi necessário implementar duas estruturas de dados:

- tree.c, uma árvore genérica, com ramificação variável, onde cada nó armazena
um mapa (um estado) do jogo, o número de passos utilizados.
- heap.c, uma heap que armazena ponteiros para os nós da árvore de estados, 
utilizando a o número de passos + o valor da heurística para o estado atual
como chave de prioridade. 


**************************************************************************

5. Limite de memória

Os programas que utilizam a tree.c ou a heap.c (todos, exceto o guloso2),
tem no código fonte um limite (aproximado grosseiramente) de memória máxima
que o programa pode utilizar. Atingindo esse limite, o programa encerrará
sua execução imediatamente.

Pode haver casos em que a aproximação erra e o limite é excedido. Utilizar
com cuidado.

Por padrão, deixou-se o limite configurado para 2 gb. No geral, esse limite
parece ser menos importante do que a precisão da heurística utilizada, isto é,
heurísticas pouco informadas consomem toda a memória, independentemente do limite.

**************************************************************************

6. Como melhorar

Sabemos que as soluções encontradas pelo A* estão longe do ideal. Duas ideias
para melhorá-las seriam:

--> Definir heurísticas mais bem informadas e admissíveis.
--> Utilizar um algoritmo de memória limitada para explorar heurísticas pouco
    informadas sem estourar a memória.

**************************************************************************
