#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
    printf("Pilha:\n")
    for(int i = 0: i < TAMANHO_DA_PILHA; i++){
        printf("0x%04x: 0x%04X\n", 0x8200 + i, Pilha[i]);
    }

    printf("\n");
    printf("Flags:\n");
    printf("Carry = %x \n Overflow = %x \n Zero = %x \n Signed = %x", (Flags >> 3) & 0x1, (Flags >> 2) & 0x1, (Flags >> 1) & 0x1, (Flags & 0x1));
}

    //MOV
    void movImediato(uint16_t registrador, uint16_t imediato){
        Registrador[registrador] = imediato;
    }

    void movRegistrador(uint16_t r_destino, uint16_t r_origem){
        Registrador[r_destino] = Registrador[r_origem]; // Revisar isso aqui
    }


    //ULA
    void add(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] + Registrador[r_origem2]; // Revisar isso aqui 
    }

    void sub(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
       Registrador[r_destino] = Registrador[r_origem] - Registrador[r_origem2]; // Revisar isso aqui
    }
    
    void mul(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] * Registrador[r_origem2]; // Revisar isso aqui
    }


    void and(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] & Registrador[r_origem2]; // Revisar isso aqui
    }

    void xor(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] ^ Registrador[r_origem2]; // Revisar isso aqui
    }

    void orr(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] | Registrador[r_origem2]; // Revisar isso aqui
    }

    void shr(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
        Registrador[r_destino] = Registrador[r_origem] >> imediato; // Revisar isso aqui
    }

    void shl(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
       Registrador[r_destino] = Registrador[r_origem] << imediato; // Revisar isso aqui
    }

    void ror(uint16_t Rd, uint16_t Rm) {
        uint16_t valor = Registrador[Rm];
        uint16_t bitLSB = valor & 1; // Obtém o bit menos significativo (LSB)
        Registrador[Rd] = (valor >> 1) | (bitLSB << 15); // Move bits e recoloca o LSB no MSB
    }

    void rol(uint16_t Rd, uint16_t Rm) {
        uint16_t valor = Registrador[Rm];
        uint16_t bitMSB = (valor >> 15) & 1; // Obtém o bit mais significativo (MSB)
        Registrador[Rd] = (valor << 1) | bitMSB; // Move bits e recoloca o MSB no LSB
    }

    void cmp(uint16_t r1, uint16_t r2){
       uint16_t valor_r1 = registrador[r1];
       uint16_t valor_r2 = registrador[r2];
        if(valor_r1 == valor_r2){
            Flags |= (1 << 2); // Z (Zero)
        }
        if(valor_r1 < valor_r2){
            Flags |= (1 << 3); // S (Sing)
    }
    
    }

    void not(uint16_t Rd, uint16_t Rm) {
        Registrador[Rd] = ~Registrador[Rm];
    }


    //PILHA
    void psh(uint16_t valor_registrador){
        if(SP == 0){
            printf("PILHA CHEIA!!!!!!!!!!!!, NÃO CONSIGO DAR PUSH :(\n");
            return;
        }
        Memoria_de_dados[SP] = Registrador[valor_registrador]; //Tá certo, só inverte a ordem
        SP--; //SP decrementa depois, pois a pilha que estamos trabalhando é full descend;
    }


    void pop(uint16_t Rd) {
        if (SP < TAMANHO_DA_PILHA) { // Verifica se a pilha não está vazia
            Registrador[Rd] = Pilha[SP]; // Rd recebe o valor no topo da pilha
            SP++; // Move o ponteiro da pilha para baixo (decresce)
        } else {
            printf("Erro: Pilha ta seca seca (vazia)\n");
        }
    }



    //STORE
    void strImediato(uint16_t *r_destino, uint16_t imediato){
        Registrador[*r_destino] = imediato; 
    }
    
    void strRegistrador(uint16_t *r_destino, uint16_t r_origem){
        Registrador[*r_destino] = Registrador[r_origem];
    }

    //NOP
    void nop(){
        printf("antes de executar o nop");
        statusSimulador();
        printf("depois de executar o nop");
    }

    //HALT
    void halt(){
        statusSimulador();
        exit(0);
    }

    //LOAD
    
    void ldr(uint16_t r_destino, uint16_t r_origem){
        Registrador[r_destino] = Registrador[r_origem]; 
    }

    //DESVIO

    void jmp(uint16_t Imediato){
        PC += Imediato;
    }

    
void jeq(uint16_t imediato) {
    if (Flags & 0x4) {          // Verifica a flag Zero (bit 3: 0x4 = 0100)
        PC = imediato;     // Atualiza PC se condição satisfeita
    }
}


void jlt(uint16_t imediato) {
    if ((Flags & 0x1) && !(Flags & 0x4)) { // Signal (bit 0: 0x1) ativo e Zero inativo
        PC = imediato;
    }
}


void jgt(uint16_t imediato) {
    if (!(Flags & 0x1) && !(Flags & 0x4)) { // Signal e Zero inativos
        PC = imediato;
    }
}




    int main(){
        
    }
