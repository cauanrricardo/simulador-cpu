#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
// legenda do cauan
/*
imediato = é um valor constante q pode ser diretamente usado em uma operação
------
operando1: Pode ser o primeiro número (registrador ou valor imediato) em uma operação aritmética.
-------
operando2: Pode ser o segundo número (registrador ou valor imediato) na mesma operação.
--------
Por exemplo, na operação de adição (ADD), os operandos seriam os dois números que estão sendo somados.
*/
void atualizar_flags(int resultado, int operando1, int operando2, char tipo_operacao)
{
    Flags = 0;
    // flag zero (z)
    if (resultado == 0)
    {
        Flags = Flags | (1 << 2); // z == 1
    }
    else
    {
        Flags = Flags & ~(1 << 2); // z = 0;
    }

    // flag sinal (s) - para saber se o resltado é negativo
    if (resultado & 0x8000)
    {                             // se o bit for mais significativo for 1, (indica que e negativo)
        Flags = Flags | (1 << 3); // s = 1;
    }
    else
    {
        Flags = Flags & ~(1 << 3); // s = 0
    }

    // Flag carry (C)
    if (tipo_operacao == 'A') { // Soma
        if ((uint32_t)operando1 + (uint32_t)operando2 > 0xFFFF) { // Faz soma com 32 bits para detectar overflow
            Flags |= (1 << 0); // c = 1
        } else {
            Flags &= ~(1 << 0); // c = 0
        }
    } 
    else if (tipo_operacao == 'S') { // sub
        if (operando1 < operando2) { // se operando1 é menor, houve "carry" (em subtração, carry significa borrow)
            Flags |= (1 << 0); // c = 1
        } else {
            Flags &= ~(1 << 0); // c = 0
        }
    }
    // Flag overflow (OV)
    if (tipo_operacao == 'A') { // Soma
        if (((operando1 & 0x8000) == (operando2 & 0x8000)) && ((resultado & 0x8000) != (operando1 & 0x8000))) {
            Flags |= (1 << 1); // OV = 1
        } else {
            Flags &= ~(1 << 1); // OV = 0
        }
    } 
    else if (tipo_operacao == 'S') { // Subtração
        if (((operando1 & 0x8000) != (operando2 & 0x8000)) && ((resultado & 0x8000) != (operando1 & 0x8000))) {
            Flags |= (1 << 1); // OV = 1
        } else {
            Flags &= ~(1 << 1); // OV = 0
        }
    }
}

void manipular_pilha(uint8_t opcode, uint16_t valor)
{
    if (opcode == ob01) {
        if (SP == 0) {
            printf("pilha cheia, nao da pra dar push.\n");
            return;
        }
        // empurra para a pilha (sp), entao diminiu o ponteiro da pilha
        SP--;
        Memoria_de_dados[SP] = Registradores[registrador];
       // printf("PUSH: Registrador R%d -> Memória[0x%X] = 0x%X\n", registrador, SP, Registradores[registrador]);
    }
    else if (opcode == 0b10){
        if (SP == TAMANHO_DA_MEMORIA){
            printf("pilha vazia, nao é possivel dar o POP\n");
            return;
        }
        Registradores[registrador] = Memoria_de_dados[SP];
        SP++;
        // retirar da pilha, ou seja, aumenta o ponteiro de pilha
        valor = Memoria_de_dados[SP];
       // printf("POP: Memória[0x%X] -> Registrador R%d = 0x%X\n", SP, registrador, Registradores[registrador]);
    }
}

int main()
{
}