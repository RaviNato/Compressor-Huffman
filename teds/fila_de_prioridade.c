#include <stdlib.h>
#include "fila_de_prioridade.h"

boolean nova_fila_de_prioridade (Fila* f, U32 capacidade){
    if (capacidade<=0) return false;

    (*f).capacidade_inicial=capacidade;
    (*f).capacidade=capacidade;

    (*f).vetor=(ElementoDeFila*)malloc(capacidade*sizeof(ElementoDeFila));

    (*f).qtd_atual=0;
    
    (*f).inicio=0;
    
    (*f).final=0;

    return true;
}

boolean guarde_na_fila_em_ordem(Fila* f, Ptr_de_no_de_arvore_huffman novo_no) {
    if (f->qtd_atual == f->capacidade) {
        U32 nova_capacidade = f->capacidade * 2;
        ElementoDeFila* novo_vetor = (ElementoDeFila*) malloc(nova_capacidade * sizeof(ElementoDeFila));

        if (novo_vetor == NULL) return false;

        for (U32 i = 0; i < f->qtd_atual; i++) {
            novo_vetor[i] = f->vetor[(f->inicio + i) % f->capacidade];
        }

        free(f->vetor);
        f->vetor = novo_vetor;
        f->capacidade = nova_capacidade;
        f->inicio = 0;
        f->final = f->qtd_atual; 
    }

    I32 contador = f->qtd_atual;
    I32 pos_vazia = f->final;
    I32 atual_idx = (f->final - 1 + f->capacidade) % f->capacidade;

    while (contador > 0) {
        Ptr_de_no_de_arvore_huffman no_atual = (Ptr_de_no_de_arvore_huffman)f->vetor[atual_idx];
        
        if (no_atual->frequencia > novo_no->frequencia) {
            f->vetor[pos_vazia] = f->vetor[atual_idx];
            pos_vazia = atual_idx;
            atual_idx = (atual_idx - 1 + f->capacidade) % f->capacidade;
            contador--;
        } else {
            break;
        }
    }

    f->vetor[pos_vazia] = (ElementoDeFila)novo_no;
    f->final = (f->final + 1) % f->capacidade;
    f->qtd_atual++;

    return true;
}

Ptr_de_no_de_arvore_huffman retire_da_fila_de_prioridade(Fila* f) {
    if (f->qtd_atual == 0) return NULL;

    Ptr_de_no_de_arvore_huffman extraido = (Ptr_de_no_de_arvore_huffman)f->vetor[f->inicio];

    f->vetor[f->inicio] = NULL;
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->qtd_atual--;

    // 3. Lógica de redução de memória (opcional no Huffman, mas boa prática)
    if (f->qtd_atual > 0 && f->qtd_atual <= f->capacidade / 4 && f->capacidade > f->capacidade_inicial) {
        U32 metade = f->capacidade / 2;
        ElementoDeFila* novo = (ElementoDeFila*)malloc(metade * sizeof(ElementoDeFila));
        if (novo != NULL) {
            for (I32 i = 0; i < f->qtd_atual; i++) {
                novo[i] = f->vetor[(f->inicio + i) % f->capacidade];
            }
            free(f->vetor);
            f->vetor = novo;
            f->inicio = 0;
            f->final = f->qtd_atual;
            f->capacidade = metade;
        }
    }

    return extraido;
}

boolean fila_de_prioridade_vazia (Fila f)
{
    /*
    if (f.qtd_atual==0)
        return true;
    else
        return false;
    */
    return f.qtd_atual==0;
}

boolean fila_de_prioridade_cheia (Fila f){
    /*
    if (f.qtd_atual==f.capacidade)
        return true;
    else
        return false;
    */
    return f.qtd_atual==f.capacidade;
}

boolean free_fila_de_prioridade (Fila* f) {
    if (f->vetor == NULL) return false;

    free(f->vetor); 
    f->vetor = NULL;
    f->qtd_atual = 0;
    f->capacidade = 0;

    return true;
}