#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

    //MOV
    void movImediato(uint16_t registrador, uint16_t imediato){
        Resgistradores[registrador] = imediato;
    }

    void movRegistrador(uint16_t r_destino, uint16_t r_origem){
        Registradores[r_destino] = r_origem;
    }


    //ULA
    void add(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registradores[r_destino] = r_origem + r_origem2; // Revisar isso aqui 
    }

    void sub(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
       Registradores[r_destino] = r_origem - r_origem2; // Revisar isso aqui
    }
    
    void mul(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registradores[r_destino] = r_origem * r_origem2; // Revisar isso aqui
    }

    void div(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registradores[r_destino] = r_origem / r_origem2; // Essa instrução não existe
    }

    void and(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registradores[r_destino] = r_origem & r_origem2; // Revisar isso aqui
    }

    void xor(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registradores[r_destino] = r_origem ^ r_origem2; // Revisar isso aqui
    }

    void orr(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registradores[r_destino] = r_origem | r_origem2; // Revisar isso aqui
    }

    void shr(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
        Registradores[r_destino] = r_origem >> r_origem2; // Revisar isso aqui
    }

    void shl(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
       Registradores[r_destino] = r_origem << imediato; // Revisar isso aqui
    }

    uint16_t ror(uint16_t num, uint16_t n_bits){ // Encurtar o código, declarando apenas uma vez 
        uint16_t num_bits = 16;
        n_bits = n_bits % num_bits; // Isso tá me retornando rm; 
        return (num >> n_bits) | (num << (num_bits - n_bits)); // Não entendi a lógica
    }

    uint16_t rol (uint16_t num, uint16_t n_bits) {
        uint16_t num_bits = 16;
        n_bits = n_bits % num_bits;
        return (num << n_bits) | (num >> (num_bits - n_bits)); //Não entendi a lógica
    }

    void cmp(uint16_t r1, uint16_t r2){
       uint16_t valor_r1 = registradores[r1];
       uint16_t valor_r2 = registradores[r2];
        if(valor_r1 == valor_r2){
            Flags |= (1 << 0); // Z (Zero)
        }
        if(valor_r1 < valor_r2){
            Flags |= (1 << 1); // S (Sing)
    }
    
    }


    //PILHA
    void psh(uint16_t valor_registrador){
        if(SP == 0){
            printf("PILHA CHEIA!!!!!!!!!!!!, NÃO CONSIGO DAR PUSH :(\n");
            return;
        }
        SP--; //SP decrementa depois;
        Memoria_de_dados[SP] = Registradores[valor_registrador]; //Tá certo, só inverte a ordem
    }

    //n sei se pop ta certo :/****
    uint16_t pop(uint16_t valor_registrador){ // Essa função é void
        if(SP == TAMANHO_DA_MEMORIA){
            printf("PILHA VAZIA!!!!!!!!!, NÃO CONSIGO DAR POP :( \n)"); // Faz sentido
            return;
        }
        uint16_t valor = Memoria_de_dados[SP]; // O que é esse valor? Não é assim que se pega o endereço de SP;
        SP++; //SP incrementa antes
        return valor;
    }



    //STORE
    void str_imediato(uint16_t *r_destino, uint16_t imediato){
        Registradores[*r_destino] = imediato; // Não é assim que se pega endereços
    }
    
    void str_registrador(uint16_t *r_destino, uint16_t r_origem){
        Registradores[*r_destino] = r_origem; // Não é assim que se pega endereços
    }

    //NOP
    void nop(){
        printf("antes de executar o nop");
        _asm_("nop");
        printf("depois de executar o nop");
    }

    //HALT
    void halt(){
        printf("parando programa");
        return 0;  // A função é void, não retorna nada;
    }

    //LOAD
    void ldr(uint16_t r_destino, uint16_t *r_origem){
        Registradores[r_destino] = *r_origem; // Não é assim que se pega endereços;
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
