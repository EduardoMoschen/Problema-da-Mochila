#include "funcoes.h"

int main(){
    srand((unsigned) time(NULL)); //Usada para fornecer valores totalmente aleatórios.

    Mochila dados;

    abrirArquivo("teste1.txt", &dados);

    printf("\n");
    imprimirDados(dados);

    /* Solução força bruta */
    forcaBruta(&dados);

    /* Solução menor peso */
    solucaoMelhorPeso(dados);

    /* Solução melhor benefício */
    solucaoMelhorBeneficio(dados);

    /* Solução melhor custo benefício */
    solucaoCustoBeneficio(dados);

    /* Solução Aleatória */
    solucaoAleatoria(&dados, 5000);

    liberacaoMemoria(&dados);

    return 0;
}