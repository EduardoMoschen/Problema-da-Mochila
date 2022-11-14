#include "funcoes.h"

void alocacaoMemoria(Mochila *dados){
    dados -> peso = (int*) malloc(dados -> n*sizeof(int));
    dados -> beneficio = (int*) malloc(dados -> n*sizeof(int));

    //Verifica se a alocação ocorreu com sucesso.
    if (dados -> peso == NULL){
        printf("Malloc = NULL");
        exit(1);
    }

    //Verifica se a alocação ocorreu com sucesso.
    if (dados -> beneficio == NULL){
        printf("Malloc = NULL");
        exit(1);
    }
}

void liberacaoMemoria(Mochila *dados){
    free(dados -> peso); //Libera a memória que foi alocada para este vetor.
    free(dados -> beneficio); //Libera a memória que foi alocada para este vetor.
}

void imprimirDados(Mochila dados){
    printf("Capacidade da mochila: %d\n", dados.limiteMochila);
    printf("Total de itens: %d\n", dados.n);

    printf("Peso dos itens: ");
    for (int i = 0; i < dados.n; i++) //Laço para imprimir os pesos dos itens.
        printf("%d ", dados.peso[i]);

    printf("\nBeneficio dos itens: ");
    for (int i = 0; i < dados.n; i++) //Laço para imprimir os benefícios dos itens.
        printf("%d ", dados.beneficio[i]);

    printf("\n");

}

void abrirArquivo(char *path, Mochila *dados){
    int valor;

    FILE *arquivo;
    arquivo = fopen(path, "r");

    //Verifica se a abertura ocorreu com sucesso.
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%d", &valor);
    dados -> limiteMochila = valor; //Leitura do limite da mochila.

    fscanf(arquivo, "%d", &valor);
    dados -> n = valor; //Leitura da quantidade de itens que a mochila possui.

    alocacaoMemoria(dados);

    //Laço que faz a leitura dos dados do arquivo de forma sequencial, caso haja.
    for(int i = 0; i < dados -> n; i++){
        fscanf(arquivo, "%d", &valor);
        dados -> peso[i] = valor;
    }

    for(int i = 0; i < dados -> n; i++){
        fscanf(arquivo, "%d", &valor);
        dados -> beneficio[i] = valor;
    }

    fclose(arquivo); //Fechamento do arquivo.
}

int imprimeVetorSolucao(int n, int *solucao){
    int v;

    printf("Vetor solucao: [");

    //Laço que imprime o vetor solução.
    for (v = 0; v < n; ++v)

        //Serão impressos 0 e/ou 1, onde 0 significa que o item não foi inserido e 1 que foram.
        printf("%d", solucao[v]);

    printf("]\t");

    return v;
}

void calculaSolucaoAleatoria(int *bin, int n){
    int i;

    //Laço que gera soluções aleatória.
    for (i = 0; i < n; i++)
        bin[i] = rand() % 2; //Gera valores aleatórios que são 0 ou 1.
}

int pesoSolucao(int *solucao, Mochila dados){
    int i;
    int peso = 0;

    for (i = 0; i < dados.n; ++i)
        if (solucao[i] == 1)
            peso += dados.peso[i];
    return peso;
}

int beneficioSolucao(int *solucao, Mochila dados){
    int i;
    int capacidade = 0;

    for (i = 0; i < dados.n; ++i)
        if (solucao[i] == 1)
            capacidade += dados.beneficio[i];
    return capacidade;
}

void copiaVetor(int n, int *destino, int *origem){
    int i;

    for (i = 0; i < n; ++i)
        destino[i] = origem[i];
}

void solucaoAleatoria(Mochila *dados, int maximoIteracoes){

    clock_t tempo; //Variável para armazenar o tempo.

    int peso = 0;
    int beneficio = 0;
    int maiorBeneficio = 0;
    int i, *solucao, *melhorSolucao;

    solucao = (int*) calloc(dados -> n, sizeof(int)); //Alocação de memória para a variável.
    melhorSolucao = (int*) calloc(dados -> n, sizeof(int)); //Alocação de memória para a variável.

    tempo = clock(); //Armazena o tempo;

    //Laço que define as soluções aleatórias com base na quantidade de iterações passadas na main.
    for (i = 0; i < maximoIteracoes; ++i){
        calculaSolucaoAleatoria(solucao, dados -> n);
        peso = pesoSolucao(solucao, *dados);
        beneficio = beneficioSolucao(solucao, *dados);

        //Gera as soluções obedecendo o limite de peso da mochila.
        if (peso <= dados -> limiteMochila){
            if (beneficio > maiorBeneficio){
                maiorBeneficio = beneficio;

                //Copia o conteúdo da solução para a melhor solução existente na solução aleatória.
                copiaVetor(dados -> n, melhorSolucao, solucao);
            }
        }
    }
    tempo = clock() - tempo; //Tempo final - tempo inicial

    printf("\nMelhor Solucao Aleatoria em %d iteracoes\n", maximoIteracoes);
    imprimeVetorSolucao(dados -> n, melhorSolucao);
    printf("Peso: %d\t", pesoSolucao(melhorSolucao, *dados));
    printf("Beneficio: %d\t", beneficioSolucao(melhorSolucao, *dados));
    printf("Tempo de execucao: %lf ms\n", ((double)tempo) / ((CLOCKS_PER_SEC / 1000)));

    free(solucao); //Liberação de memória para a variável.
    free(melhorSolucao); //Liberação de memória para a variável.
}

int pesoTotal(Mochila dados){
    int i;
    int somaVetor = 0;
    for(i = 0; i < dados.n; i++)
        somaVetor += dados.peso[i];
    return somaVetor;
}

void calculaSolucaoMelhorPeso(Mochila dados, int *bin){
    int pTotal = pesoTotal(dados);
    int maior = 0;
    int *aux; // Vetor auxiliar para guardar o valor peso dos itens que não entrarão na mochila
    aux = (int*) calloc(dados.n, sizeof(int));
    while(pTotal > dados.limiteMochila){
        pTotal = 0;
        maior = 0;

        // Realiza o calculo até o peso total dos itens disponíveis ser igual ou menor ao peso limite
        // da mochila
        for(int i=0; i < dados.n; i++)
            pTotal = pesoTotal(dados); 

        if (pTotal > dados.limiteMochila){
            for(int i=0; i < dados.n; i++)
                // Verifica qual o maior valor peso e o armazena no vetor auxiliar
                if (dados.peso[i] > maior){ 
                    maior = dados.peso[i];
                    aux[i] = maior;
                }

            for(int i=0; i < dados.n; i++)
                // O maior valor é substituido por 0, o que significa que não ficará na mochila
                if (dados.peso[i] == maior){
                    dados.peso[i] = 0;
                    break;
                }
        }
    }
    for(int i=0; i < dados.n; i++){ 
        // O vetor solução é criado, qualquer elemento != 0 é trocado por 1
        if (dados.peso[i] != 0) bin[i] = 1;
        // Os valores peso retirados são retornados para o vetor peso
        if (dados.peso[i] == 0) dados.peso[i] = aux[i]; 
    }

    free(aux);
}

void relacaoPesoBeneficio(Mochila dados, float *vetor){
    float relacao;
    for (int i=0; i < dados.n; i++){
        relacao = ((float)dados.beneficio[i] / (float)dados.peso[i]);
        vetor[i] = relacao;
    }
}

void calculaCustoBeneficio(Mochila dados, int *bin){
    int pTotal = 0;
    float maior;
    float *relacao; 
    
    relacao = (float*) calloc(dados.n, sizeof(float));

    relacaoPesoBeneficio(dados, relacao);
    while (pTotal <= dados.limiteMochila){
        maior = 0;
        for (int i=0; i < dados.n; i++)
            // Armazena o maior valor da relação peso benefício na variável
            if (relacao[i] > maior) 
                maior = relacao[i]; 

        for (int i=0; i < dados.n; i++){
            // Caso o maior dado do vetor relação seja igual ao da variável, é incrementado o peso 
            // do item na variável peso total
            if (maior == relacao[i]){ 
                pTotal += dados.peso[i];
                // Caso o peso total seja menor que o peso limite da mochila, o valor 1 é acrescentado 
                // ao local referente ao peso do item, e seu custo benefício é retirado do vetor custo 
                // benefício
                if (pTotal < dados.limiteMochila){ 
                    bin[i] = 1;
                    relacao[i] = 0;
                }
            }
        } 
    }
}

void calculaMelhorBeneficio(Mochila dados, int *bin){
    int somaPeso = 0, somaBeneficio, maior;
    int *auxBeneficio, *auxPeso; // Vetores criados para fazer mudanças dentro da função sem ser necessário alterar os vetores originais

    auxBeneficio = (int*) calloc(dados.n, sizeof(int)); 
    auxPeso = (int*) calloc(dados.n, sizeof(int)); 

    // Copia o vetor referente ao beneficio dos itens para o vetor auxiliar
    copiaVetor(dados.n, auxBeneficio, dados.beneficio); 
    // Copia o vetor referente ao peso dos itens para o vetor auxiliar
    copiaVetor(dados.n, auxPeso, dados.peso); 

    while (somaPeso <= dados.limiteMochila){
        somaBeneficio = 0;
        maior = 0;

        for (int i=0; i < dados.n; i++)
            if (auxBeneficio[i] > maior)
                maior = auxBeneficio[i]; // O maior valor do vetor benefício é armazenado na variável 

        for (int i=0; i < dados.n; i++) 
            // Se o beneficio do item for igual ao maior valor armazenado e o peso do item 
            //não ultrapasse o limite da mochila, o item é colocado na mochila, o peso total da mochila 
            //é incrementado e o valor benefício é alterado para 0
            if (auxBeneficio[i] == maior && (somaPeso + auxPeso[i]) <= dados.limiteMochila){ 
                bin[i] = 1;
                somaPeso += auxPeso[i];
                auxBeneficio[i] = 0;
            // Se não, o valor do peso e do benefício é alterado para 0
            } else if ((somaPeso + auxPeso[i]) > dados.limiteMochila){
                auxPeso[i] = 0;
                auxBeneficio[i] = 0;
                break;
            }
        
        // Somatório do benefício para controlar a estrutura de loop
        for (int i=0; i < dados.n; i++)
            somaBeneficio += auxBeneficio[i];
        
        // Condição de parada do loop, quando o somatório do vetor for igual a 0, significa que
        // não há mais itens para adicionar na mochila e encerra o loop
        if (somaPeso <= dados.limiteMochila && somaBeneficio == 0)
            break;
    }

    // Libera a memória do vetor auxiliar
    free(auxBeneficio); 
    free(auxPeso);
}

void solucaoMelhorBeneficio(Mochila dados){
    clock_t tempo; //Variável para armazenar o tempo.

    int peso = 0;
    int beneficio = 0;
    int *solucao;

    solucao = (int*) calloc(dados.n, sizeof(int));

    tempo = clock(); //Armazena o tempo;
    calculaMelhorBeneficio(dados, solucao);
    peso = pesoSolucao(solucao, dados);
    beneficio = beneficioSolucao(solucao, dados);

    tempo = clock() - tempo; //Tempo final - tempo inicial
    printf("\nMelhor Solucao Baseada em Melhor Beneficio\n");
    imprimeVetorSolucao(dados.n, solucao);
    printf("Peso: %d\t", peso);
    printf("Beneficio: %d\t", beneficio);
    printf("Tempo de execucao: %lf ms", ((double)tempo) / ((CLOCKS_PER_SEC / 1000)));

    free(solucao);
}

void solucaoMelhorPeso(Mochila dados){

    clock_t tempo; //Variável para armazenar o tempo.

    int peso = 0;
    int beneficio = 0;
    int *solucao;

    solucao = (int*) calloc(dados.n, sizeof(int));

    tempo = clock(); //Armazena o tempo;
    calculaSolucaoMelhorPeso(dados, solucao); 
    peso = pesoSolucao(solucao, dados);
    beneficio = beneficioSolucao(solucao, dados);
    tempo = clock() - tempo; //Tempo final - tempo inicial

    printf("\nMelhor Solucao Baseada em Menor Peso\n");
    imprimeVetorSolucao(dados.n, solucao);
    printf("Peso: %d\t", peso);
    printf("Beneficio: %d\t", beneficio);
    printf("Tempo de execucao: %lf ms", ((double)tempo) / ((CLOCKS_PER_SEC / 1000)));

    free(solucao);
}

void solucaoCustoBeneficio(Mochila dados){

    clock_t tempo; //Variável para armazenar o tempo.

    int peso = 0;
    int beneficio = 0;
    int *solucao;

    solucao = (int*) calloc(dados.n, sizeof(int));
    tempo = clock(); //Armazena o tempo;

    calculaCustoBeneficio(dados, solucao);
    peso = pesoSolucao(solucao, dados);
    beneficio = beneficioSolucao(solucao, dados);
    tempo = clock() - tempo; //Tempo final - tempo inicial

    printf("\nMelhor Solucao Baseada em Melhor Custo Beneficio\n");
    imprimeVetorSolucao(dados.n, solucao);
    printf("Peso: %d\t", peso);
    printf("Beneficio: %d\t", beneficio);
    printf("Tempo de execucao: %lf ms", ((double)tempo) / ((CLOCKS_PER_SEC / 1000)));

    free(solucao);
}

/* ================= FORÇA BRUTA ================= */

int geraCusto (int QtdItens, int *solucao, Item *vetorItem) {  
  int Custo = 0; // Auxiliar para receber o custo

  for (int i = 0; i <  QtdItens ; i++) { // Acessando os itens do vetor de estrutura de dados e somando ao custo de acordo com a insercao da solucao;
   if (solucao[i]) {
      Custo += vetorItem[i].peso;
    }
  }

  return Custo; // Retornando o Custo
}

int geraBeneficio (int QtdItens, int *solucao, Item *vetorItem) {
  int Beneficio = 0; // Auxiliar para receber o Beneficio

  for (int i = 0; i <  QtdItens ; i++) { // Acessando os itens do vetor de estrutura de dados e somando o beneficio e armazenando dentro da variavel
    if (solucao[i]) {
      Beneficio += vetorItem[i].beneficio;
    }
  }
  return Beneficio; // Retornando o Beneficio
}

void armazenaMelhorSolucao(int QtdItens, int *vetorSolucao, int *solucao) {
  memcpy(vetorSolucao, solucao, sizeof(int) *  QtdItens ); // usando a funcao memcpy para copiar o bloco de memoria da solucao para o vetor da melhor solucao
}

void trocar(int *metade, int *outrametade) { 
  int aux = *outrametade;  // gravanda o valor binario na auxiliar
  *outrametade = *metade;  // atribuindo o valor na posicao da metade para outrametade
  *metade = aux;   // e entao jogando a outrametade para a metade
}

void conversaoParaBinario (int QtdItens, int posicao, int *vetorsolucao) {  
	int i; 
  for (i = 0; posicao > 0; posicao /= 2, i++) {  // gerando solucao binaria de forma tracejada
    vetorsolucao[i] = (posicao % 2) ? 1 : 0;
  }
   
	for (int j =  QtdItens - 1; j < (i / 2); j--) {   // ajustando a solucao para que a mesma seja uma solucao unica
    trocar(&vetorsolucao[i - j - 1], &vetorsolucao[j]);
  }
}

void solucaoForcaBruta (int QtdItens, int capacidade, int *vetorSolucao, Item *vetorItem) {
	int *solucao = calloc( QtdItens, sizeof(int));  // alocando memoria para armazenar as solucoes temporariamente para que elas sejam testadas
	int peso = 0, beneficio = 0, maiorBeneficio = 0;  // variavel peso e beneficio seram geradas apartir do vetorsolucao gerado, e maior beneficio armazera e melhor beneficio ate agora

  //laco que ira gerar todas as solucoes possiveis para que possam ser todas testadas e descoberta a melhor solucao
 	for (int i = 1; i < (pow(2, QtdItens)); i++) {  
    conversaoParaBinario( QtdItens , i, solucao); // gerando o vetorsolucao [0,0,1,...,n]

		peso = geraCusto( QtdItens, solucao, vetorItem);  // atribuindo o custo da solucao
		beneficio = geraBeneficio( QtdItens , solucao, vetorItem); // atribuindo o beneficio da solucao

		if (peso <= capacidade) { // caso a solucao gerada seja a melhor solucao até agora eles sera gravada no vetorSolucao
			if (beneficio > maiorBeneficio) {
  			maiorBeneficio = beneficio;
  			armazenaMelhorSolucao( QtdItens , vetorSolucao, solucao);  // chamando a funcao para armazenar a melhor solucao no vetorsolucao
			} 
        }
	}

	free(solucao); // liberando memoria do vetor solucao
}

void imprimeSolucao(int QtdItens,int *vetorSolucao,Item *vetorItem){ 
printf("\nMelhor Solucao Forca Bruta (otima)\nVetor solucao: ");
    //laco para imprimir o vetor com parenteses // 
    for(int i=0;i<QtdItens;i++){
      if(i==0){
      printf("[%d",vetorSolucao[i]);
      }else if(i==QtdItens-1){
        printf("%d]",vetorSolucao[i]);
      }else{
        printf("%d",vetorSolucao[i]);
      }
    }
    printf("  Peso: %d Beneficio: %d\t",geraCusto(QtdItens,vetorSolucao,vetorItem),geraBeneficio(QtdItens,vetorSolucao,vetorItem));
} 

void forcaBruta(Mochila *dados){
    clock_t tempo; //Variável para armazenar o tempo.

    int QtdItens = dados -> n;  // definindo a quantidade de itens da mochila apartir da informacao na estrura de dados
    int LimiteMochila = dados -> limiteMochila; // definindo o limite de peso da mochila apartir da informacao na estrura de dados

    int *vetorSolucao = calloc(QtdItens, sizeof(int));  // definindo vetorSolucao como ponteiro que ira armazenar a MelhorSolucao e alocando memoria para o mesmo
    Item *vetorItem = calloc(QtdItens, sizeof(Item));    // definindo vetorItem como ponteiro que iria ser o vetordeitem contendo beneficio e custo em cada posicao

    for(int i = 0; i < QtdItens; i++){     // copiando os arquivos de beneficio e peso de itens contidos na estrutura de dados, para o vetordeitem
      vetorItem[i].peso = dados -> peso[i];  
      vetorItem[i].beneficio = dados -> beneficio[i];
    }

    tempo = clock(); //Armazena o tempo;

    solucaoForcaBruta(QtdItens, LimiteMochila, vetorSolucao, vetorItem);  // chamando a funcao que vai gerar todas as solucoes possives para a instancia e achar a melhor solucao
    // tem como parametro a quantidade de itens, o limite de peso da mochila, o vetor Solucao e o vetor de itens
    tempo = clock() - tempo; //Tempo final - tempo inicial

    imprimeSolucao(QtdItens,vetorSolucao,vetorItem); // chamando a funcao para imprimir a melhor solucao achada
    // tem como parametro a quantidade de itens, o vetor Solucao e o vetor de itens
    printf("Tempo de execucao: %lf ms", ((double)tempo) / ((CLOCKS_PER_SEC / 1000)));

    free(vetorSolucao); // liberando a memoria do vetor solucao
    free(vetorItem); // liberando a memoria do Vetor de itens
  
}