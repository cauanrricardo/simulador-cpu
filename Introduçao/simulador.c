#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define TAMANHO_DA_MEMORIA 1 << 16 // O tamanho da memória é 2 elevado a quant de bits
#define TAMANHO_DA_PILHA 16 // O tamanho da pilha é igual a quantidade de bits

uint16_t Registradores[8];
uint16_t PC = 0; // Inicializa o valor de PC, que vai armazenar o endereço da próxima instrução
uint16_t IR = 0; // Inicializa o valor do IR, que vai armazenar o endereço da instrução atual
uint16_t SP = 0x8200; // Representa o Valor inicial de SP
uint8_t Flags = 0; // 0000, representa as flags Carry, Overflow, Zero, Signal respectivamente
uint16_t Memoria_de_dados[TAMANHO_DA_MEMORIA] = {0};
uint16_t Memoria_de_programa[TAMANHO_DA_MEMORIA] ={0};
uint16_t Pilha[TAMANHO_DA_PILHA] = {0};


/*void imprimirBinario(uint16_t valor) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (valor >> i) & 1);
    }
} 
*/
void decodificarInstrucao(uint16_t instrucao) {
    uint8_t opcode = (instrucao >> 12) & 0xF; // Extrai o opcode (4 bits mais significativos)
    uint8_t modo = (instrucao >> 11) & 0x1;   // Extrai o modo (5º bit)
    uint16_t operandos = instrucao & 0x7FF;   // Extrai os operandos (11 bits restantes)
    printf("Opcode: 0x%02x Modo: 0x%02x Operandos: 0x%03x\n", opcode, modo, operandos);
    
    
    /*if(opcode == 0000 & modo == 0) {
        nop();
    }
    if(opcode == 1111 & modo == 1) {
        return;
    }
    if(opcode == 0001) { //MOV
        if(modo == 1) {
            movRegister(Registradores[(operandos >> 8) & 0x7], Registradores[(operandos >> 5) & 0x7]);
        }
        else {
            movImmediato(Registradores[operandos >> 8] & 0x7, (operandos & 0xFF));
        }
    }*/
    if(opcode == 0010) {
        if(modo == 1) {
            return;//storeRegister();
        }
        else {
            uint16_t parte_immediato = operandos & 0x700;
            uint16_t segunda_parte = operandos & 0x1F;
            //storeimmediato(Registradores[(operandos >> 5) & 0x7], parte_immediato | segunda_parte);
            printf("0x%03x", parte_immediato);
        }
    }
}

int main () {
    decodificarInstrucao(0x2A62);
}