#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
//legenda do cauan
/*
imediato = é um valor constante q pode ser diretamente usado em uma operação
ex: MOV R0, #3 = onde esse 3 o imediato
---
destino = o parametro destino, refere - se ao registrador ou memoria q será modificado pela operação
ex: MOV R0, #3 - onde R0 e o destino, q vai armazenar o valor 3
---
origem1 = é o registrador q contem o valor q vai ser utilizado na operacao
ex: ADD R2, R1, R0 - onde o R1, R0 sao as origens(valoes q vao ser somados) e o resultado sera armazenado em R2(destino)

*/

void atualizarRegistrador(uint8_t opccode, uint16_t destino, uint8_t origem1, uint_8 origem2, uint16_t imediato) {

    switch(opcode){ //opcode é na teoria, o tipo de operação

        case MOV: //mover o end
        Registradores[destino] = imediato;
        break;

        case ADD: //soma
        Registradores[destino] = Registradores[origem1] + Registradores[origem2];
        break;

        case SUB: //subtracao
        Registradores[destino] = Registradores[origem1] - Registradores[origem2];
        break;

        case MUL: //mutiplicacao
        Registradores[destino] = Registradores[origem1] * Registradores[origem2];

        case PSH:
       //esperar o vitin decodificar
        break;

        case POP:
       //esperar o vitin decodificar
        break;

        case CMP:
       //esperar o vitin decodificar
        break;

        case JEQ:
       //esperar o vitin decodificar
        break;

        case JMP:
       //esperar o vitin decodificar
        break;

        case HALT:
       //esperar o vitin decodificar
        break;

        default:

          break;


    }

}
void atualizar_flags(int resultado){
    //flag zero (z)
    if(resultado == 0){
        Flags = Flags | (1 << 2); //z == 1
    }else {
        Flags = Flags & ~(1 << 2); // z = 0;
    }

    //flag sinal (s) - para saber se o resltado é negativo
    if(resultado & 0x8000){ //se o bit for mais significativo for 1, (indica que e negativo)
        Flags = Flags | (1 << 3); //s = 1;
    } else {
        Flags = Flags & ~(1 << 3); //s = 0 
    }

    //Flag carry (C) 
    if(resultado < 0){
        Flags = Flags | (1 << 0); //c = 1 - oq na teoria indica carry
    } else {
        Flags = Flags & ~(1 << 0); //c = 0;
    }

    //Flag overflow (OV)
   if ((resultado < 0 && (resultado & 0x8000) == 0) || (resultado > 0 && (resultado & 0x8000))) { //caso o resulto ultrapasse 16 bits, F = 15
        Flags = Flags | (1 << 1); //OV = 1;
    } else{
        Flags = Flags & ~(1 << 1); //OV = 0;
    }

}

void manipular_pilha(uint8_t opcode, uint16_t valor){
    if(opcode == PSH){
        //empurra para a pilha (sp), entao diminiu o ponteiro da pilha
        Memoria[SP] = valor;
        SP = SP - 2;
    } else if(opcode == POP){
        //retirar da pilha, ou sej,a, aumenta o ponteiro de pilha
        SP = SP + 2;
        valor = Memoria[SP];
    }
}

int main(){

}