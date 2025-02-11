#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

    //MOV
    void movImediato(uint8_t registrador, uint8_t imediato){
        Registrador[registrador] = imediato;
    }

    void movRegistrador(uint8_t r_destino, uint8_t r_origem){
        Registrador[r_destino] = Registrador[r_origem]; // Revisar isso aqui
    }


    //ULA
    void add(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] + Registrador[r_origem2]; // Revisar isso aqui 
    }

    void sub(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
       Registrador[r_destino] = Registrador[r_origem] - Registrador[r_origem2]; // Revisar isso aqui
    }
    
    void mul(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] * Registrador[r_origem2]; // Revisar isso aqui
    }


    void and(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] & Registrador[r_origem2]; // Revisar isso aqui
    }

    void xor(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] ^ Registrador[r_origem2]; // Revisar isso aqui
    }

    void orr(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] | Registrador[r_origem2]; // Revisar isso aqui
    }

    void shr(uint8_t r_destino, uint8_t r_origem, uint8_t imediato){
        Registrador[r_destino] = Registrador[r_origem] >> imediato; // Revisar isso aqui
    }

    void shl(uint8_t r_destino, uint8_t r_origem, uint8_t imediato){
       Registrador[r_destino] = Registrador[r_origem] << imediato; // Revisar isso aqui
    }

    void ror(uint8_t Rd, uint8_t Rm) {
        uint16_t valor = Registrador[Rm];
        uint16_t bitLSB = valor & 1; // Obtém o bit menos significativo (LSB)
        Registrador[Rd] = (valor >> 1) | (bitLSB << 15); // Move bits e recoloca o LSB no MSB
    }

    void rol(uint8_t Rd, uint8_t Rm) {
        uint16_t valor = Registrador[Rm];
        uint16_t bitMSB = (valor >> 15) & 1; // Obtém o bit mais significativo (MSB)
        Registrador[Rd] = (valor << 1) | bitMSB; // Move bits e recoloca o MSB no LSB
    }

    void cmp(uint8_t r1, uint8_t r2){
       uint16_t valor_r1 = registrador[r1];
       uint16_t valor_r2 = registrador[r2];
        if(valor_r1 == valor_r2){
            Flags |= (1 << 2); // Z (Zero)
        }
        if(valor_r1 < valor_r2){
            Flags |= (1 << 3); // S (Sing)
    }
    
    }

    void not(uint8_t Rd, uint8_t Rm) {
        Registrador[Rd] = ~Registrador[Rm];
    }


    //PILHA
    void psh(uint8_t valor_registrador){
        if(SP == 0){
            printf("PILHA CHEIA!!!!!!!!!!!!, NÃO CONSIGO DAR PUSH :(\n");
            return;
        }
        Memoria_de_dados[SP] = Registrador[valor_registrador]; //Tá certo, só inverte a ordem
        SP--; //SP decrementa depois, pois a pilha que estamos trabalhando é full descend;
    }


    void pop(uint8_t Rd) {
        if (SP < TAMANHO_DA_PILHA) { // Verifica se a pilha não está vazia
            Registrador[Rd] = Pilha[SP]; // Rd recebe o valor no topo da pilha
            SP++; // Move o ponteiro da pilha para baixo (decresce)
        } else {
            printf("Erro: Pilha ta seca seca (vazia)\n");
        }
    }



    //STORE
    void strImediato(uint8_t *r_destino, uint8_t imediato){
        Registrador[*r_destino] = imediato; 
    }
    
    void strRegistrador(uint8_t *r_destino, uint8_t r_origem){
        Registrador[*r_destino] = Registrador[r_origem];
    }

    //NOP
    void nop(){
        printf("antes de executar o nop");
        _asm_("nop");
        printf("depois de executar o nop");
    }

    //HALT
    void halt(){
        exit(0);
    }

    //LOAD
    //ver de ldr tá certo
    void ldr(uint8_t r_destino, uint8_t r_origem){
        Registrador[r_destino] = Registrador[r_origem]; 
    }

    //DESVIO

    void jmp(uint8_t Imediato){
        PC += Imediato;
    }

    
void jeq(uint8_t imediato) {
    if (Flags & 0x4) {          // Verifica a flag Zero (bit 3: 0x4 = 0100)
        PC = imediato;     // Atualiza PC se condição satisfeita
    }
}


void jlt(uint8_t imediato) {
    if ((Flags & 0x1) && !(Flags & 0x4)) { // Signal (bit 0: 0x1) ativo e Zero inativo
        PC = imediato;
    }
}


void jgt(uint8_t imediato) {
    if (!(Flags & 0x1) && !(Flags & 0x4)) { // Signal e Zero inativos
        PC = imediato;
    }
}


    int main(){
        
    }
