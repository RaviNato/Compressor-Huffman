#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "teds/compressao.h"
#include "teds/meustipos.h"

I32 main () {
    I8 opcao_menu[10];
    I8 nome_arquivo[500];

    while (1) {
        printf("###### Compressor Huffman ######\n\n");

        printf("[1] Comprimir arquivo\n");
        printf("[2] Descomprimir arquivo\n");
        printf("[0] Sair\n");

        printf("\n################################\n\n");

        fgets(opcao_menu, sizeof(opcao_menu), stdin);

        if (opcao_menu[1] == '\n') {
            if (opcao_menu[0] == '1') {

                printf("Digite o nome do arquivo e sua extensao, a ser comprimido: ");
                scanf("%s", nome_arquivo);
                comprimir_arquivo(nome_arquivo);
                getchar();

            } else if (opcao_menu[0] == '2') {

                printf("Digite o nome do arquivo e sua extensao, a ser descomprimido: ");
                scanf("%s", nome_arquivo);
                descomprimir_arquivo(nome_arquivo);
                getchar();

            } else if (opcao_menu[0] == '0') {

                printf("Saindo do programa...\n");
                break;

            } else { // caso o usuário tenha digitado um caractere inválido
                printf("Opcao invalida. Por favor, selecione uma opcao valida.\n\n");
            }
        } else { // caso o usuário tenha digitado mais de um caractere
            printf("Entrada invalida. Por favor, selecione uma opcao valida.\n\n");
            if (strchr(opcao_menu, '\n') == NULL) {
                while(getchar() != '\n');
            }
            continue;
        }
    }

    return 0;
}