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
    //printf("Opcode: 0x%02x Modo: 0x%02x Operandos: 0x%03x\n", opcode, modo, operandos);
    //uint8_t Rm = (operandos >> 5) & 0x7;
    // Extrai Rn dos bits 4, 3 e 2
    //uint8_t Rn = (operandos >> 2) & 0x7;

    //printf("Rm: 0x%03x Rn: 0x%03x\n", &Registradores[Rm], Registradores[Rn]); // Pega o endereço de Registradores[Rm] e o conteúdo de Registradores[Rn]; 
    //printf("Rm: 0x%03x Rn: 0x%03x\n", Registradores[(operandos >> 2) & 0x7], Registradores[(operandos >> 5) & 0x7]);

    //if(opcode == 1111 & modo == 1) {
      //  return;
    //}
    //MOV 
    if(opcode == 0b0001) { 
        if(modo == 1) {
            uint8_t rd = (operandos >> 8) & 0x7;
            uint8_t rm = (operandos >> 5) & 0x7;
            movRegistrador(Registradores[rd], Registradores[rm]);
        }
        else {
            uint8_t rd = (operandos >> 8) & 0x7;
            uint8_t imediato = (operandos & 0xFF);
            movImediato(Registradores[rd], imediato);
        }
    }
    //STORE (STR)
    if(opcode == 0b0010) {
        if(modo == 0) {
            uint8_t rm = (operandos >> 2) & 0x7;
            uint8_t rn = (operandos >> 5) & 0x7;
            storeRegistrador(&Registradores[rm], Registradores[rn]);
        }
        else {
            uint16_t parte_immediato = operandos & 0x700;
            uint16_t segunda_parte = operandos & 0x1F;
            strImediato(&Registradores[(operandos >> 5)] & 0x7, (parte_immediato | segunda_parte));
        }
    } 
    //LOAD (LDR) 
    if(opcode == 0b0011) {
        uint8_t rd = (operandos >> 8) & 0x7;
        uint8_t rm = (operandos >> 8) & 0x7;
        ldr(Registradores[rd], &Registradores[rm]);
        //Rd = endereço(Rm);
    }
    //Instruções da ULA
    uint8_t rd = (operandos >> 8) & 0x7;
    uint8_t rm = (operandos >> 5) & 0x7;
    uint8_t rn = (operandos >> 2) & 0x7;
    //ADD
    if(opcode == 0b0100) {
        add(Registradores[rd], Registradores[rm], Registradores[rn]);
    }
    //SUB
    if(opcode == 0b0101) {
        sub(Registradores[rd], Registradores[rm], Registradores[rn]);
    }
    //MUL
    if(opcode == 0b0110) {
        mul(Registradores[rd], Registradores[rm], Registradores[rn]);
    }
    //AND
    if(opcode == 0b0111) {
        and(Registradores[rd], Registradores[rm], Registradores[rn]);
    }
    //ORR
    if(opcode == 0b1000) {
        orr(Registradores[rd], Registradores[rm], Registradores[rn]);
    }
    //NOT
    if(opcode == 0b1001) {
        not(Registradores[rd], Registradores[rm]);
    }
    //XOR
    if(opcode == 0b1010) {
        xor(Registradores[rd], Registradores[rm], Registradores[rn]);
    }
    // CMP & PILHA
    uint8_t zero = operandos & 0x3;
    if(opcode == 0b0000 && modo == 0) {
        if(zero == 0b11) {
            orr(Registradores[rm], Registradores[rn]);
        }
        if(zero == 0b01) {
            push(Registradores[rn]);
        }
        if(zero = 0b10) {
            pop(Registradores[rd]);
        }
        else {
            nop();
        }
    }
    //Shift Right (SHR)
    uint8_t imediato = operandos & 0x1F;
    if(opcode == 0b1011) {
        shr(Registradores[rd], Registradores[rm], imediato);
    }
    //Shift Left (SHL)
    if(opcode == 0b1100) {
        shl(Registradores[rd], Registradores[rm], imediato);
    }
    //Rotate Right (ROR)
    if(opcode == 0b1101) {
        ror(Registradores[rd], Registradores[rm]);
    }
    //Rotate Left (ROL) 
    if(opcode == 0b1110) {
        rol(Registradores[rd], Registradores[rm]);
    }
    //DESVIOS 
    if(opcode == 0b0000 && modo == 1) {
        uint8_t imediato = (operandos >> 2) & 0x1FF;
        if(zero == 0b00) {
            jmp(imediato);
        }
        if(zero == 0b01) {
            jeq(imediato);
        }
        if(opcode == 0b10) {
            jlt(imediato);
        }
        if(opcode == 0b11) {
            jgt(imediato);
        }
    }
}

int main () {
    decodificarInstrucao(0x2762);
}