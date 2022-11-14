<h1 align="center"> Problema da Mochila </h1>

# 📖 Sobre

O **Problema da Mochila**, também conhecido como **Mochila Binária** ou **Knapsack Problem**,  pode ser informalmente declarado como o problema de empacotar itens em uma mochila dentro dos limites de diferentes dimensões. Eles podem ser, por exemplo, o peso máximo que pode ser transportado,  volume máximo disponpivel e/ou a quantidade máxima que pode ser paga pelos itens. Cada item tem um nível de lucro atribuído a ele e peso em cada dimensão. Além disso, a mochila tem capacidade limitada em cada dimensão. O objetivo é selecionar um subconjunto de itens que maximize a soma de seus lucros e mantenha o peso total em cada dimensão não mais do que a capacidade correspondente.

Neste código, é apresentado duas mochilas e cinco tipos de abordagens diferentes para a tomada de decisão dos itens a serem inseridos dentro da mochila. Especificaremos as mochilas em arquivos de texto e será divido da seguinte forma: na primeira estará o limite de peso da mochila. Na segunda estará a quantidade de itens disponíveis para serem adicionados. Na terceira o peso de cada item e na quarta o benefício de cada item. Analisando as quatro linhas de cada arquivo de texto, fica claro que cada valor será um número inteiro.

Abaixo contém quais são os cinco tipos diferentes de abordagens usadas:

    • Escolha aleatória com várias partidas;
    • Heurística de maior benefício, começando pelo maior benefício;
    • Heurística de menor peso, começando pelo menos peso;
    • Heurística de melhor relação peso benefício, começando pela melhor relação peso benefício;
    • Força bruta.

# 📓 Instruções de uso

Primeiramente, temos a divisão de pastas onde foi dividida entre as funções desenvolvidas para o problema, os casos de teste e as instâncias de teste.

Após deixar isso claro, começaremos por pasta. As pastas **Casos de Teste** e **Instâncias** são usadas para pegar os dados de entrada e usar eles para rodar o programa. Já a **Funções** são onde estão as funções desenvolvidas.

**OBSERVAÇÃO**: Dentro da main.c há uma função que abre o arquivo .txt usado para pegar os dados. Para usar esse arquivo, deve-se colocar o diretório dele como parâmetro da função. Para ficar mais fácil, você pode pôr o arquivo dentro da pasta funções e colocar apenas o nome do arquivo dentro do parâmetro da função.

Há duas maneiras de rodar o código: a primeira, que é no Linux, é através do makefile que está neste repositório. E a segunda, no Windows que é através do gcc; para isso, precisa estar conseguindo compilar arquivos .c.

Para usar o makefile, basta abrir o terminal e digitar **make all** e **./main** para executar. No Windows, **gcc -c funcoes.c main.c** , **gcc -o <nome_do_executável> funcoes.o main.o** e **./<nome_do_executável>** para executar.

**OBSERVAÇÃO**: Se o compilador estiver funcionando no Windows, é possível fazer a compilação dos arquivos dentro do terminal do Visual Studio Code.