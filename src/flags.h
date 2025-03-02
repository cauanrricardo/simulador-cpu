#include "../src/globais.h"

void atualizar_flags(uint16_t resultado) {
    // flag zero (z)
    if (resultado == 0) {
        Flags = Flags | (1 << 4); // z == 1
    }
    else {
        Flags = Flags & ~(1 << 4); // z = 0;
    }
    // flag sinal (s) - para saber se o resltado é negativo
    // Flag Sinal (S): Se o bit 15 do resultado for 1, o número é negativo (em complemento de 2).
    // Isso indica que a operação gerou um número negativo, portanto, a flag S é setada (S = 1).
    // Caso contrário, se o bit 15 for 0, o número é positivo ou zero, e a flag S é dessetada (S = 0).
    if (resultado & 0x8000) {  // pega o bit mais significativo (0x8000 = 1000 0000 0000 0000 )                             // se o bit for mais significativo for 1, (indica que e negativo)
        Flags = Flags | 1; // s = 1;
    }
    else {
        Flags = Flags & ~(1); // s = 0
    }
    printf("flags: %04x\n", Flags);
}