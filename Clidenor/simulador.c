#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

    //MOV
    void movImediato(uint16_t registrador, uint16_t imediato){
        Resgistradores[registrador] = imediato;
    }

    void movRegistrador(uint16_t r_destino, uint16_t r_origem){
        Registradores[r_destino] = Registradores[r_origem]; // Revisar isso aqui
    }


    //ULA
    void add(uint16_t r_destino, uint16_t Registradores[r_origem], uint16_t Registradores[r_origem2]){
        Registradores[r_destino] = Registradores[r_origem] + Registradores[r_origem2]; // Revisar isso aqui 
    }

    void sub(uint16_t r_destino, uint16_t Registradores[r_origem], uint16_t Registradores[r_origem2]){
       Registradores[r_destino] = Registradores[r_origem] - Registradores[r_origem2]; // Revisar isso aqui
    }
    
    void mul(uint16_t r_destino, uint16_t Registradores[r_origem], uint16_t Registradores[r_origem2]){
        Registradores[r_destino] = Registradores[r_origem] * Registradores[r_origem2]; // Revisar isso aqui
    }


    void and(uint16_t r_destino, uint16_t Registradores[r_origem], uint16_t Registradores[r_origem2]){
        Registradores[r_destino] = Registradores[r_origem] & Registradores[r_origem2]; // Revisar isso aqui
    }

    void xor(uint16_t r_destino, uint16_t Registradores[r_origem], uint16_t Registradores[r_origem2]){
        Registradores[r_destino] = Registradores[r_origem] ^ Registradores[r_origem2]; // Revisar isso aqui
    }

    void orr(uint16_t r_destino, uint16_t Registradores[r_origem], uint16_t Registradores[r_origem2]){
        Registradores[r_destino] = Registradores[r_origem] | Registradores[r_origem2]; // Revisar isso aqui
    }

    void shr(uint16_t r_destino, uint16_t Registradores[r_origem], uint16_t imediato){
        Registradores[r_destino] = Registradores[r_origem] >> Registradores[r_origem2]; // Revisar isso aqui
    }

    void shl(uint16_t r_destino, uint16_t Registradores[r_origem], uint16_t imediato){
       Registradores[r_destino] = Registradores[r_origem] << imediato; // Revisar isso aqui
    }

    void ROR(uint8_t Rd, uint8_t Rm) {
        uint16_t valor = Registradores[Rm];
        uint16_t bitLSB = valor & 1; // Obtém o bit menos significativo (LSB)
        Registradores[Rd] = (valor >> 1) | (bitLSB << 15); // Move bits e recoloca o LSB no MSB
    }

    void ROL(uint8_t Rd, uint8_t Rm) {
        uint16_t valor = Registradores[Rm];
        uint16_t bitMSB = (valor >> 15) & 1; // Obtém o bit mais significativo (MSB)
        Registradores[Rd] = (valor << 1) | bitMSB; // Move bits e recoloca o MSB no LSB
    }

    void cmp(uint16_t r1, uint16_t r2){
       uint16_t valor_r1 = registradores[r1];
       uint16_t valor_r2 = registradores[r2];
        if(valor_r1 == valor_r2){
            Flags |= (1 << 2); // Z (Zero)
        }
        if(valor_r1 < valor_r2){
            Flags |= (1 << 3); // S (Sing)
    }
    
    }


    //PILHA
    void psh(uint16_t valor_registrador){
        if(SP == 0){
            printf("PILHA CHEIA!!!!!!!!!!!!, NÃO CONSIGO DAR PUSH :(\n");
            return;
        }
        Memoria_de_dados[SP] = Registradores[valor_registrador]; //Tá certo, só inverte a ordem
        SP--; //SP decrementa depois, pois a pilha que estamos trabalhando é full descend;
    }


    void pop(uint8_t Rd) {
        if (SP < TAMANHO_DA_PILHA) { // Verifica se a pilha não está vazia
            Registradores[Rd] = Pilha[SP]; // Rd recebe o valor no topo da pilha
            SP++; // Move o ponteiro da pilha para baixo (decresce)
        } else {
            printf("Erro: Pilha ta seca seca (vazia)\n");
        }
    }



    //STORE
    void str_imediato(uint16_t *r_destino, uint16_t imediato){
        Registradores[*r_destino] = imediato; 
    }
    
    void str_registrador(uint16_t *r_destino, uint16_t Registradores[r_origem]){
        Registradores[*r_destino] = Registradores[r_origem];
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
    void ldr(uint16_t r_destino, uint16_t *Registradores[r_origem]){
        Registradores[r_destino] = *Registradores[r_origem]; 
    }

    //DESVIO

    void jmp(uint16_t Imediato){
        PC += Imediato;
    }

    void jeq(uint16_t Imediato){ // A gente está usando as flags em apenas uma variável, dê uma olhada no meu código (Victor)
        if(zero && !sign){
            PC += Imediato;
        }
    }
    
    void jlt(uint16_t Imediato){
        if(sign && !zero){
            PC += Imediato;
            }
    }

    void jgt(uint16_t Imediato){
        if(!sign && !zero){
            PC += Imediato;
            }
    }


    int main(){
        
    }
