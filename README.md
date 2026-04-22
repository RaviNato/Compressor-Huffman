# Compressor Huffman #
Este projeto consiste em um compressor e descompressor de arquivos que utiliza a Codificação de Huffman, uma técnica de compressão sem perdas baseada na frequência de ocorrência de cada símbolo no conjunto de dados.


# Como Funciona #
1. Análise de Frequência
O programa lê o arquivo de entrada byte a byte e contabiliza quantas vezes cada um dos 256 caracteres possíveis aparece. Essa contagem é a base para decidir quais caracteres serão comprimidos.

2. Construção da Árvore de Huffman
Utilizamos uma Fila de Prioridade para construir uma árvore binária:
- Cada caractere é inicialmente um nó folha.
- Os dois nós com as menores frequências são unidos em um novo nó pai, cuja frequência é a soma das frequências dos filhos.
- Esse processo se repete até que reste apenas um único nó (a raiz).

3. Geração de Códigos (Codificação de Comprimento Variável)
Ao percorrer a árvore da raiz até as folhas:
- Atribuímos o bit 0 para cada conversão à esquerda.
- Atribuímos o bit 1 para cada conversão à direita. Dessa forma, caracteres frequentes recebem códigos curtos (ex: 10), enquanto caracteres raros recebem códigos longos (ex: 110101). Isso garante que nenhum código seja prefixo de outro.

4. Compressão e Escrita de Bits
O arquivo original é lido novamente e cada caractere é substituído pelo seu novo código de bits. Como o computador trabalha com bytes (múltiplos de 8 bits), o projeto gerencia um buffer de bits para empacotar esses códigos e gravá-los corretamente no disco.


# Performance #
A eficiência da compressão depende da Entropia dos dados:
- Arquivos de Texto (.txt, .csv): Alta taxa de compressão (podendo reduzir o tamanho em até 50%).
- Arquivos Binários Já Comprimidos (.png, .mp3, .zip): Tendem a manter o mesmo tamanho, pois já possuem alta entropia e pouca redundância estatística.


# Como Compilar e Executar: #
- Certifique-se de ter um compilador C (como o GCC) instalado;
- Abra o Prompt de comando;
- Escreva "cd <diretório_da_pasta_do_programa>" (Ex: "cd C:\Users\user\Downloads\Compressor Huffman") e dê enter;
- Deixe o arquivo que quiser comprimir na própria pasta do programa;
- OPCIONAL: Se fizer alguma alteração no código, compile novamente com "gcc main.c teds/*.c -o compressor" e enter;
- Escreva "compressor.exe" e dê enter, então siga as intruções.













