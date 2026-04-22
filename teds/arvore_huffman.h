#ifndef ARVORE_BINARIA_DE_HUFFMAN
#define ARVORE_BINARIA_DE_HUFFMAN
#include "meustipos.h"

typedef void* Elemento;

typedef struct Struct_do_no_de_arvore_huffman {
    struct Struct_do_no_de_arvore_huffman* esquerda;
    //Elemento informacao;  //info de arvore default
    I32 frequencia;
    U8 caractere;
    struct Struct_do_no_de_arvore_huffman* direita;
} Struct_do_no_de_arvore_huffman;

typedef Struct_do_no_de_arvore_huffman* Ptr_de_no_de_arvore_huffman;

typedef struct{
    Ptr_de_no_de_arvore_huffman raiz;
    I32 (*comparacao) (Elemento x, Elemento y);
    void (*mostra) (Elemento x);
} Arvore_huffman;

Ptr_de_no_de_arvore_huffman novo_no_de_arvore_huffman(Ptr_de_no_de_arvore_huffman e, I32 f, U8 c, Ptr_de_no_de_arvore_huffman d);
//void nova_arvore_huffman (Arvore_huffman* a, I32 (*c) (Elemento x, Elemento y), void (*m) (Elemento x));
void free_arvore_huffman (Ptr_de_no_de_arvore_huffman* a);

#endif // ARVORE_BINARIA_DE_HUFFMAN