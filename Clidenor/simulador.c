#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define memory_size 65536;
int main(){
    //mov
    void mov_imediato(uint16_t *registrador, uint16_t imediato){
        *registrador = valor_imediato;
    }
    void mov_registrador(uint16_t r_destino, uint16_t r_origem){
        r_destino = r_origem;
    }
    //operações
    void add(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        r_destino = r_origem + r_origem2;
    }

    void sub(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        r_destino = r_origem - r_origem2;
    }
    
    void mul(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        r_destino = r_origem * r_origem2;
    }

    void div(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        r_destino = r_origem / r_origem2;
    }

    void and(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        r_destino = r_origem & r_origem2;
    }

    void xor(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        r_destino = r_origem ^ r_origem2;
    }

    void orr(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        r_destino = r_origem | r_origem2;
    }

    void shr(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
        r_destino = r_origem >> r_origem2;
    }

    void shl(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
        r_destino = r_origem << imediato;
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

    


    //pilha

    //rever PILHA ESTÁ ERRADO
    void psh(uint16_t valor_registrador){
        *SP = valor;
        SP = SP - 1;
    }
    void pop(){
        SP++;
        valor = *SP;
    }



    //Store
    void str_imediato(uint16_t *r_destino, uint16_t imediato){
        *r_destino = imediato;
    }
    
    void str_registrador(uint16_t *r_destino, uint16_t r_origem){
        *r_destino = r_origem;
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
        _asm_("hlt");
    }






}