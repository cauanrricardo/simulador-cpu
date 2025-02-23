#include "../src/globais.h"

//STORE
void strImediato(uint8_t r_destino, uint8_t imediato){
    Memoria_de_dados[Registrador[r_destino]] = imediato;
    printf("Memoria_de_dados[Registrador[rm]] = %02x\n", Memoria_de_dados[0]);
}

void strRegistrador(uint8_t r_destino, uint8_t r_origem){
    Memoria_de_dados[Registrador[r_destino]] = Registrador[r_origem];
}

//LOAD
void ldr(uint8_t r_destino, uint8_t r_origem){ // Usar memoria de dados
    Registrador[r_destino] = Memoria_de_dados[Registrador[r_origem]];
    printf("Registrador[%1x] = %02x\n", r_destino, Registrador[r_destino]);
}