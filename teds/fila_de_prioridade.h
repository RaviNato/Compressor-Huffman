#ifndef FILA
#define FILA

#include "meustipos.h"
#include "arvore_huffman.h"

typedef void* ElementoDeFila;

typedef struct { 
    ElementoDeFila* vetor; // Elemento vetor [];
    U32 capacidade_inicial, capacidade, qtd_atual, inicio, final;
} Fila;

boolean nova_fila_de_prioridade (Fila* f, U32 capacidade);
boolean guarde_na_fila_em_ordem (Fila* f, Ptr_de_no_de_arvore_huffman novo_no);
Ptr_de_no_de_arvore_huffman retire_da_fila_de_prioridade (Fila* f);
boolean fila_de_prioridade_cheia (Fila f);
boolean fila_de_prioridade_vazia (Fila f);
boolean free_fila_de_prioridade (Fila* f);
/*
boolean guarde_na_fila (Fila* f, ElementoDeFila e);
boolean recupere_da_fila (Fila f, ElementoDeFila* e);
boolean remova_elemento_da_fila (Fila* f);
*/
#endif // FILA