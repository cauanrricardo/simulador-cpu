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
ex: ADD R2, R1, R0 - onde o R1, R0 sao as origens(valoes q vao ser somados) e o resultado sera armazenado em R2(destino
operando1: Pode ser o primeiro número (registrador ou valor imediato) em uma operação aritmética.
-------
operando2: Pode ser o segundo número (registrador ou valor imediato) na mesma operação.
--------
Por exemplo, na operação de adição (ADD), os operandos seriam os dois números que estão sendo somados.
*/
void atualizar_flags(int resultado, int operando1, int operando2, char tipo_operacao){
    Flags = 0;
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
    if(tipo_operacao == 'A'){
        if(resultado < operando1 || resultado < operando2){
            Flags = Flags | (1 << 0);
        } else{
            Flags = Flags & ~(1 << 0);
        }
        else if(tipo_operacao == 'S'){
            if(resultado > operando1 || resultado > operando2){
                Flags = Flags | (1 << 0); //c = 1;
            } else{
                Flags = Flags & ~(1 << 0); //c = 0;
            }
        }
    }
    //Flag overflow (OV)
    if ((resultado < 0 && (operando1 > 0 && operando2 > 0)) || 
    (resultado > 0 && (operando1 < 0 && operando2 < 0))) {
         Flags = Flags | (1 << 1); // OV = 1
    } else {
        Flags = Flags & ~(1 << 1); // OV = 0
         }
}

void manipular_pilha(uint8_t opcode, uint16_t valor){
    if(opcode == ob01){
        //empurra para a pilha (sp), entao diminiu o ponteiro da pilha
        Memoria_de_dados[SP] = valor;
        SP = SP - 2;
    } else if(opcode == POP){
        //retirar da pilha, ou sej,a, aumenta o ponteiro de pilha
        SP = SP + 2;
        valor = Memoria_de_dados[SP];
    }
}

int main(){

}