#include "funcoes.h"

int main(){
    srand((unsigned) time(NULL)); //Usada para fornecer valores totalmente aleatórios.

    Mochila dados;

    abrirArquivo("teste1.txt", &dados);

    printf("\n");
    imprimirDados(dados);

    /* Solução força bruta */
    printf("\n");
    forcaBruta(&dados);

    /* Solução menor peso */
    printf("\n");
    solucaoMelhorPeso(dados);

    /* Solução melhor benefício */
    printf("\n");
    solucaoMelhorBeneficio(dados);

    /* Solução melhor custo benefício */
    printf("\n");
    solucaoCustoBeneficio(dados);

    /* Solução Aleatória */
    printf("\n");
    solucaoAleatoria(&dados, 5000);

    liberacaoMemoria(&dados);

    return 0;
}