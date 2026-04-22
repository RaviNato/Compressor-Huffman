#ifndef MEUSTIPOS
#define MEUSTIPOS

// --- TIPOS INTEIROS ---

typedef char I8;                     // 1 byte: -128 a 127
typedef unsigned char U8;            // 1 byte: 0 a 255
typedef short int I16;               // 2 bytes: -32.768 a 32.767
typedef unsigned short int U16;      // 2 bytes: 0 a 65.535
typedef int I32;                     // 4 bytes: -2.147.483.648 a 2.147.483.647
typedef unsigned int U32;            // 4 bytes: 0 a 4.294.967.295
typedef long long int I64;           // 8 bytes: -9.223.372.036.854.775.808 a 9.223.372.036.854.775.807
typedef unsigned long long int U64;  // 8 bytes: 0 a 18.446.744.073.709.551.615

// --- TIPOS REAIS ---

typedef float R32;                   // 4 bytes: Precisão de ~7 dígitos decimais
typedef double R64;                  // 8 bytes: Precisão de ~15 dígitos decimais
typedef long double R128;            // 12 ou 16 bytes: Alta precisão (depende da arquitetura/compilador)

// --- TIPO BOOLEANO ---

typedef enum {
    false,                           // 0
    true                             // 1
} boolean;

#endif