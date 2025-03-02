#include "../src/globais.h"

//MOV
void movImediato(uint8_t registrador, uint16_t imediato) {
    Registrador[registrador] = imediato;
    for(int i = 0; i < 8; i++) {
        printf("Registrador[%d] = %02x\n", i, Registrador[i]);
    }
}

void movRegistrador(uint8_t r_destino, uint8_t r_origem) {
    Registrador[r_destino] = Registrador[r_origem];
    for(int i = 0; i < 8; i++) {
        printf("Registrador[%d] = %02x\n", i, Registrador[i]);
    }
}
