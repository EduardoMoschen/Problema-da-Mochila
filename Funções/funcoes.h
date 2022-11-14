#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct mochila{ //Struct para armazenar os dados.
    int n; //Tamanho do vetor.
    int limiteMochila;  //Limite da mochila.
    int *peso; //Vetor que irá ser alocado dinamicamente para os pesos.
    int *beneficio; //Vetor que irá ser alocado dinamicamente para os benefícios.
}Mochila;

typedef struct item{
    int peso;  // Ponteiro a ser alocado como vetor de peso dos itens respectivamente
    int beneficio;  // Ponteiro a ser alocado como vetor de valor dos itens respectivamente
}Item;

/*
Função para alocação de memória que recebe por parâmetro um dado contido na struct e armazenado
em um vetor. Esse vetor é alocado dinamicamente do tamanho do parâmetro n, e retornado por endereço
de memória.
*/
void alocacaoMemoria(Mochila *dados);

/*
Função que recebe por parâmetro um dado contido na struct, definido pela variável "dados". Libera
a memória alocada para esses vetores que estão dentro da struct.
*/
void liberacaoMemoria(Mochila *dados);

/*
Função que recebe como parâmetro um dado contido na struct, definido pela variável "dados", imprimindo
assim os dados na tela. Também há um veotr que foi alocado dinamicamente dentro da struct.
*/
void imprimirDados(Mochila dados);

/*
Função de abertura de arquivo que recebe por parâmetro o endereço do arquivo, que está contido na
variável "path". Após a abertura, são lidos os valores, salvando e retornando no endereço de memória
da variável "dados".
*/
void abrirArquivo(char *path, Mochila *dados);

/*
Função que recebe como parâmetro um dado contido na struct, definido pela variável "n" e o
endereço de memória da variável "solução" que contem as soluções.
*/
int imprimeVetorSolucao(int n, int *solucao);

/*
Função que recebe como parâmetro um dado contido na struct, definido pela variável "dados" e o
endereço de memória da variável "bin", que cria as soluções aleatórias.
*/
void calculaSolucaoAleatoria(int *bin, int n);

/*
Função que recebe como parâmetro um dado contido na struct, definido pela variável "dados", e o
endereço de memória da variável "solução" que contem as soluções. Por fim, retorna o melhor peso que
foi gerado na solução.
*/
int pesoSolucao(int *solucao, Mochila dados);

/*
Função que recebe como parâmetro um dado contido na struct, definido pela variável "dados", e o
endereço de memória da variável "solução" que contem as soluções. Por fim, retorna o melhor benefício
que foi gerado na solução.
*/
int beneficioSolucao(int *solucao, Mochila dados);

/*
Função que recebe como parâmetro um dado contido na struct, definido pela variável "n" e o
endereço de memória da variável "destino" e "origem" que copiará o conteúdo do vetor de origem para
o vetor de destino.
*/
void copiaVetor(int n, int *destino, int *origem);

/*
Função que recebe por parâmetro um dado contido na struct, definido pela variável "dados" e a
quantidade máxima de iterações para a quantidade de soluções aleatórias geradas. Por fim, ela imprime
a quantidade de soluções geradas, o vetor solução com a melhor solução criada e quais os itens que
estão nela, além do melhor peso e benefício gerado.
*/
void solucaoAleatoria(Mochila *dados, int maximoIteracoes);

/*
Função que soma o peso de todos os itens disponíveis para adicionar na mochila.
*/
int pesoTotal(Mochila dados);

/*
Função que cria o vetor binário que indica quais itens serão colocados na mochila.
*/
void calculaSolucaoMelhorPeso(Mochila dados, int *bin);

/*
Calcula a relação dos itens a partir do peso e benefício de cada item e guarda em um vetor.
*/
void relacaoPesoBeneficio(Mochila dados, float *vetor);

/*
Função que cria o vetor binário que indica quais itens podem ser colocados na mochila.
*/
void calculaCustoBeneficio(Mochila dados, int *solucao);

/*
Função que cria o vetor binário que indica quais itens podem ser colocados na mochila.
*/
void calculaMelhorBeneficio(Mochila dados, int *bin);

/*
Função responsável por gerar o resultado da heurística de melhor benefício.
*/
void solucaoMelhorBeneficio(Mochila dados);

/*
Função responsável por gerar o resultado da heurística de menor peso.
*/
void solucaoMelhorPeso(Mochila dados);

/*
Função responsável por gerar o resultado da heurística de melhor custo benefício. 
*/
void solucaoCustoBeneficio(Mochila dados);
    
/*
Função principal do Forca Bruta, recebendo a struct do tipo Mochila contendo a instância
do problema da mochila.
*/
void forcaBruta(Mochila *dados);

/*
Função para imprimir a solução, recebendo como parâmetro a quantidade de itens, o vetor solução e o vetor de itens. 
*/
void imprimeSolucao(int QtdItens,int *vetor_Solucao,Item *vetorItem); 

/*
Função que explorar todas as soluções e salva a melhor, recebendo como parametro a quantidade de
itens, a capacidade da mochila, o vetor solução e o vetor de itens.
*/
void solucaoForcaBruta(int QtdItens, int capacidade, int *vetor_Solucao, Item *vetorItem) ;

/*
Função que converte a posição recebida em um vetor de valores binários únicos para determinada posição.
*/
void conversaoParaBinario (int QtdItens, int posicao, int *vetorsolucao);

/*
Função de troca de valores, utilizada para fazer o ajuste no vetor binário de forma a gerar um vetor
solução único para determinada posição com determinada quantidade de itens.
*/
void trocar(int *metade, int *outrametade);

/*
Função para copiar um vetor para o outro. Utilizada para copiar a solução gerada para a variável
que armazena o "A melhor Solução".
*/
void armazenaMelhorSolucao(int QtdItens, int *vetor_Solucao, int *solucao);

#endif