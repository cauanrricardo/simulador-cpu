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
        Registradores[r_destino] = r_origem + r_origem2;
    }

    void sub(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
       Registradores[r_destino] = r_origem - r_origem2;
    }
    
    void mul(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registradores[r_destino] = r_origem * r_origem2;
    }

    void div(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registradores[r_destino] = r_origem / r_origem2;
    }

    void and(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registradores[r_destino] = r_origem & r_origem2;
    }

    void xor(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registradores[r_destino] = r_origem ^ r_origem2;
    }

    void orr(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registradores[r_destino] = r_origem | r_origem2;
    }

    void shr(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
        Registradores[r_destino] = r_origem >> r_origem2;
    }

    void shl(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
       Registradores[r_destino] = r_origem << imediato;
    }

    uint16_t ror(uint16_t num, uint16_t n_bits){
        uint16_t num_bits = 16;
        n_bits = n_bits % num_bits;
        return (num >> n_bits) | (num << (num_bits - n_bits));
    }

    uint16_t rol (uint16_t num, uint16_t n_bits){
        uint16_t num_bits = 16;
        n_bits = n_bits % num_bits;
        return (num << n_bits) | (num >> (num_bits - n_bits));
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
        SP--;
        Memoria_de_dados[SP] = Registradores[valor_registrador];
    }

    //n sei se pop ta certo :/****
    uint16_t pop(uint16_t valor_registrador){
        if(SP == TAMANHO_DA_MEMORIA){
            printf("PILHA VAZIA!!!!!!!!!, NÃO CONSIGO DAR POP :( \n)");
            return;
        }
        uint16_t valor = Memoria_de_dados[SP];
        SP++;
        return valor;
    }



    //STORE
    void str_imediato(uint16_t *r_destino, uint16_t imediato){
        Registradores[*r_destino] = imediato;
    }
    
    void str_registrador(uint16_t *r_destino, uint16_t r_origem){
        Registradores[*r_destino] = r_origem;
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
        return 0;
    }

    //LOAD
    void ldr(uint16_t r_destino, uint16_t *r_origem){
        Registradores[r_destino] = *r_origem;
    }

    //DESVIO

    void jmp(uint16_t Imediato){
        PC += Imediato;
    }

    void jeq(uint16_t Imediato){
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
