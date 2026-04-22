#ifndef COMPRESSAO
#define COMPRESSAO

#include "codigo.h"
#include "fila_de_prioridade.h"
#include "arvore_huffman.h"
#include "meustipos.h"

boolean comprimir_arquivo(const I8* nome_arquivo);
boolean descomprimir_arquivo(const I8* nome_arquivo_huff);

#endif // COMPRESSAO