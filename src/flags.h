#include "../src/globais.h"

void atualizar_flags(uint16_t op1, uint16_t op2, uint16_t resultado) {
    if (((op1 & 0x8000) == (op2 & 0x8000)) && ((op1 & 0x8000) != (resultado & 0x8000))) {
        // Se os bits de sinal dos operandos forem iguais e o bit de sinal do resultado for diferente
        // então houve um overflow
        Flags = Flags | (1 << 8); // Setando a flag de overflow (O) para 1
    } else {
        Flags = Flags & ~(1 << 8); // Caso contrário, resetando a flag de overflow (O)
    }

    if(resultado > TAMANHO_DA_MEMORIA){
        Flags = Flags | (1 << 12); // Setando a flag de carry (C) para 1
    }
    else{
       Flags = Flags & ~(1 << 12); //Caso contrário, resetando a flag de Carry (C)
    }
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