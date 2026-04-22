#include <stdlib.h>
#include "codigo.h"

boolean novo_codigo (Codigo* c /* por referência */)
{
    c->byte=(U8*)calloc(1, sizeof(U8));
    if (c->byte==NULL) return false;

    c->capacidade=8;
    c->tamanho=0;
    return true;
}

void free_codigo (Codigo* c /* por referência */)
{
    if (c->byte!=NULL) free(c->byte);
    c->byte=NULL;
}

boolean adiciona_bit (Codigo* c /* por referência */,
                      U8 valor /* 0 ou 1 */)
{
    if (c->tamanho == c->capacidade) {
        // Aumenta a capacidade e limpa a nova memória com calloc
        U32 nova_cap_bytes = (c->capacidade / 8) + 1;
        U8* novo = (U8*)calloc(nova_cap_bytes, sizeof(U8));
        if (novo == NULL) return false;

        for (I32 i = 0; i < c->capacidade / 8; i++)
            novo[i] = c->byte[i];

        free(c->byte);
        c->byte = novo;
        c->capacidade += 8;
    }

    // Calcula em qual bit do byte atual devemos escrever (0 a 7)
    U8 pos_no_byte = c->tamanho % 8;
    U8 indice_byte = c->tamanho / 8;

    if (valor == 1) {
        // Define o bit na posição correta (da esquerda para a direita)
        c->byte[indice_byte] |= (1 << (7 - pos_no_byte));
    }

    c->tamanho++;
    return true;
}


boolean joga_fora_bit (Codigo* c /* por referência */)
{
    if (c->tamanho == 0) return false;

    U8 pos_no_byte = (c->tamanho - 1) % 8;
    U8 indice_byte = (c->tamanho - 1) / 8;
    c->byte[indice_byte] &= ~(1 << (7 - pos_no_byte));

    c->tamanho--;
    return true;
}

boolean pega_byte (Codigo c /* por valor "*/,
                   U8 qual /* por valor */,
                   U8* b /*por referencia */)
{
	if (qual>c.capacidade/8) return false;
	
	*b = c.byte[qual];
	return true;
}

boolean pega_bit(Codigo c, U32 qual_bit, U8* bit) {
    if (qual_bit >= c.tamanho) return false;

    U32 indice_byte = qual_bit / 8;

    U32 posicao_no_byte = qual_bit % 8;

    U8 byte_alvo = c.byte[indice_byte];

    *bit = (byte_alvo >> (7 - posicao_no_byte)) & 1;

    return true;
}

boolean clone (Codigo original, /* por valor */
               Codigo* copia    /* por referencia */)
{
    copia->byte=(U8*)malloc(original.capacidade/8*sizeof(U8));
    if (copia->byte==NULL) return false;


    for(I32 i=0;i<original.capacidade/8;i++)
        copia->byte[i]=original.byte[i];

    copia->capacidade=original.capacidade;
    copia->tamanho=original.tamanho;
    return true;
}

I8* toString (Codigo c)
{
    I8* retorno = (I8*)malloc((c.tamanho + 1) * sizeof(I8));
    if (retorno == NULL) return NULL;

    for (U32 i = 0; i < c.tamanho; i++) {
        U8 bit;
        pega_bit(c, i, &bit);
        retorno[i] = (bit == 1) ? '1' : '0';
    }
    retorno[c.tamanho] = '\0';
    return retorno;
}

