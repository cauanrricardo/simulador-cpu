#include "../src/globais.h"

void statusSimulador(){
    //Imprimir os registradores
    printf("Registradores:\n");
    for(int i = 0; i < 8; i++){
        printf("R%d: 0x%04X\n", i, Registrador[i]);
    }

    //Imprimir SP e PC
    printf("\n");
    printf("SP: 0x%04X\n", SP);
    printf("PC: 0x%04X\n", PC);
    printf("\n");

    //imprimir a memoria agora, mas lembrar de imprimir apenas a memoria que foi acessada
    printf("\n");
    printf("Memoria de Dados:\n");
    for(int i = 0; i < TAMANHO_DA_MEMORIA; i++){
        if(Memoria_de_dados[i] != 0){
            printf("0x%04X: 0x%04X\n", i, Memoria_de_dados[i]);
        }
    }

    printf("\n");
    printf("Pilha:\n");
    for(int i = 0; i < TAMANHO_DA_PILHA; i++){
        printf("0x%04x: 0x%04X\n", 0x8200 + i, Pilha[i]);
    }

    printf("\n");
    printf("Flags:\n");
    printf("Carry = %x\nOverflow = %x\nZero = %x\nSigned = %x\n", (Flags >> 12) & 0x1, (Flags >> 8) & 0x1, (Flags >> 4) & 0x1, (Flags & 0x1));
}

//NOP
void nop(){
    printf("antes de executar o nop\n");
    statusSimulador();
    printf("depois de executar o nop\n");
}

//HALT
void halt(){
    statusSimulador();
    exit(0);
}