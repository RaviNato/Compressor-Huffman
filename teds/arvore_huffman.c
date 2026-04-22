#include <stdio.h>
#include <stdlib.h>
#include "arvore_huffman.h"

Ptr_de_no_de_arvore_huffman novo_no_de_arvore_huffman (Ptr_de_no_de_arvore_huffman e, I32 f, U8 c, Ptr_de_no_de_arvore_huffman d)
{
    Ptr_de_no_de_arvore_huffman novo = (Ptr_de_no_de_arvore_huffman)malloc(sizeof(Struct_do_no_de_arvore_huffman));

    novo->esquerda=e;
    novo->frequencia=f;
    novo->caractere=c;
    novo->direita=d;

    return novo;
}

/*void nova_arvore_huffman (Arvore_huffman* a, I32 (*c) (Elemento x, Elemento y), void (*m) (Elemento x))
{
    a->raiz=NULL;
    a->comparacao=c;
    a->mostra=m;
}*/

static void aux_free_nos(Ptr_de_no_de_arvore_huffman no) {
    if (no == NULL) return;
    aux_free_nos(no->esquerda);
    aux_free_nos(no->direita);
    free(no);
}

void free_arvore_huffman(Ptr_de_no_de_arvore_huffman* raiz) {
    if (raiz == NULL || *raiz == NULL) return;
    aux_free_nos(*raiz);
    *raiz = NULL;
}