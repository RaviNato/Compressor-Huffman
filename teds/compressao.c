#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compressao.h"

static Ptr_de_no_de_arvore_huffman construir_arvore_huffman(I32* frequencias) {
    Fila fila_de_prioridade;
    nova_fila_de_prioridade(&fila_de_prioridade, 256);

    for (I32 i = 0; i < 256; i++) {
        if (frequencias[i] > 0) {
            guarde_na_fila_em_ordem(&fila_de_prioridade, novo_no_de_arvore_huffman(NULL, frequencias[i], (U8)i, NULL));
        }
    }

    while (fila_de_prioridade.qtd_atual > 1) {
        Ptr_de_no_de_arvore_huffman n1 = retire_da_fila_de_prioridade(&fila_de_prioridade);
        Ptr_de_no_de_arvore_huffman n2 = retire_da_fila_de_prioridade(&fila_de_prioridade);
        guarde_na_fila_em_ordem(&fila_de_prioridade, novo_no_de_arvore_huffman(n1, n1->frequencia + n2->frequencia, 0, n2));
    }
    return retire_da_fila_de_prioridade(&fila_de_prioridade);
}

static boolean calcular_frequencias(const char* nome_arquivo, I32* frequencias) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) return false;
    U8 byte_lido;
    while (fread(&byte_lido, sizeof(U8), 1, arquivo) == 1) frequencias[byte_lido]++;
    fclose(arquivo);
    return true;
}

static void gerar_codigos(Ptr_de_no_de_arvore_huffman raiz, Codigo* atual, Codigo* dicionario) {

    if (raiz->esquerda == NULL && raiz->direita == NULL) {
        clone(*atual, &dicionario[raiz->caractere]);
        return;
    }

    if (raiz->esquerda != NULL) {
        adiciona_bit(atual, 0);
        gerar_codigos(raiz->esquerda, atual, dicionario);
        joga_fora_bit(atual);
    }

    if (raiz->direita != NULL) {
        adiciona_bit(atual, 1);
        gerar_codigos(raiz->direita, atual, dicionario);
        joga_fora_bit(atual);
    }
}

static void salvar_arquivo_comprimido(const I8* nome_origem, I32* frequencias, Codigo* dicionario) {
    FILE *entrada = fopen(nome_origem, "rb");
    
    I8 nome_saida[510];
    sprintf(nome_saida, "%s.huff", nome_origem);
    FILE *saida = fopen(nome_saida, "wb");

    if (!entrada || !saida) {
        printf("\nNao foi possivel abrir arquivo para gravacao!\n");
        return;
    }

    fwrite(frequencias, sizeof(I32), 256, saida);

    U8 bits_validos_no_ultimo_byte = 0;
    long posicao_contador = ftell(saida);
    fwrite(&bits_validos_no_ultimo_byte, sizeof(U8), 1, saida);

    U8 byte_lido;
    U8 buffer = 0;
    I32 bits_no_buffer = 0;

    rewind(entrada); 

    while (fread(&byte_lido, sizeof(U8), 1, entrada) == 1) {
        Codigo c = dicionario[byte_lido];
        for (I32 i = 0; i < c.tamanho; i++) {
            U8 bit;
            if (pega_bit(c, i, &bit)) {
                if (bit == 1 || bit == '1') {
                    buffer = buffer | (1 << (7 - bits_no_buffer));
                }
                bits_no_buffer++;

                if (bits_no_buffer == 8) {
                    fwrite(&buffer, sizeof(U8), 1, saida);
                    buffer = 0;
                    bits_no_buffer = 0;
                }
            }
        }
    }

    if (bits_no_buffer > 0) {
        fwrite(&buffer, sizeof(U8), 1, saida);
        bits_validos_no_ultimo_byte = bits_no_buffer;
    } else {
        bits_validos_no_ultimo_byte = 8;
    }

    fseek(saida, posicao_contador, SEEK_SET);
    fwrite(&bits_validos_no_ultimo_byte, sizeof(U8), 1, saida);

    printf("Arquivo comprimido gerado: %s\n\n", nome_saida);

    fclose(entrada);
    fclose(saida);
}

boolean comprimir_arquivo(const I8* nome_arquivo) {
    Codigo dicionario[256];
    I32 frequencias[256] = {0};

    if (!calcular_frequencias(nome_arquivo, frequencias)) {
        printf("Arquivo invalido. Por favor, digite um nome de arquivo valido.\n\n");
        return false;
    }

    Ptr_de_no_de_arvore_huffman raiz_huffman = construir_arvore_huffman(frequencias);

    for(int i=0; i<256; i++) dicionario[i].byte = NULL;
    
    // caractere único
    if (raiz_huffman->esquerda == NULL && raiz_huffman->direita == NULL) {
        Codigo unico;
        novo_codigo(&unico);
        adiciona_bit(&unico, 0);
        clone(unico, &dicionario[raiz_huffman->caractere]);
        free_codigo(&unico);
    } else {
        Codigo temp;
        novo_codigo(&temp);
        gerar_codigos(raiz_huffman, &temp, dicionario);
        free_codigo(&temp);
    }

    salvar_arquivo_comprimido(nome_arquivo, frequencias, dicionario);
    
    for(int i = 0; i < 256; i++) {
        if (dicionario[i].byte != NULL) free_codigo(&dicionario[i]);
    }
    free_arvore_huffman(&raiz_huffman);

    return true;
}

boolean descomprimir_arquivo(const char* nome_arquivo_huff) {
    FILE *entrada = fopen(nome_arquivo_huff, "rb");
    if (!entrada) {
        printf("Arquivo invalido. Por favor, digite um nome de arquivo valido.\n\n");
        return false;
    }

    I32 frequencias[256];
    fread(frequencias, sizeof(I32), 256, entrada);
    
    U8 bits_validos;
    fread(&bits_validos, sizeof(U8), 1, entrada);

    Ptr_de_no_de_arvore_huffman raiz_huffman = construir_arvore_huffman(frequencias);

    I8 nome_saida[510];
    size_t len = strlen(nome_arquivo_huff);
    if (len > 5) {
        strncpy(nome_saida, nome_arquivo_huff, len - 5);
        nome_saida[len - 5] = '\0';
    } else {
        sprintf(nome_saida, "descomprimido_saida");
    }

    FILE *saida = fopen(nome_saida, "wb");
    if (!saida) {
        printf("Erro ao criar arquivo de saida\n");
        fclose(entrada);
        return false;
    }

    U8 buffer;
    Ptr_de_no_de_arvore_huffman atual = raiz_huffman;
    
    long pos_inicio_dados = ftell(entrada);
    fseek(entrada, 0, SEEK_END);
    long tam_total = ftell(entrada);
    fseek(entrada, pos_inicio_dados, SEEK_SET);

    while (fread(&buffer, sizeof(U8), 1, entrada) == 1) {
        I32 limite = (ftell(entrada) == tam_total) ? bits_validos : 8;

        for (I32 i = 0; i < limite; i++) {
            if (raiz_huffman->esquerda == NULL && raiz_huffman->direita == NULL) {
                fwrite(&(raiz_huffman->caractere), sizeof(U8), 1, saida);
            } 
            else {
                U8 bit = (buffer >> (7 - i)) & 1;
                
                if (bit == 1) atual = atual->direita;
                else          atual = atual->esquerda;

                if (atual->esquerda == NULL && atual->direita == NULL) {
                    fwrite(&(atual->caractere), sizeof(U8), 1, saida);
                    atual = raiz_huffman;
                }
            }
        }
    }

    printf("Arquivo descomprimido gerado: %s\n\n", nome_saida);
    
    fclose(entrada);
    fclose(saida);

    free_arvore_huffman(&raiz_huffman);

    return true;
}