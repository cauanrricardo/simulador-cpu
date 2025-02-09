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
uint16_t SP = 0x8200; // Representa o Valor inicial de SP, que vai armazenar endereço do valor que está na pilha 
uint8_t Flags = 0; // 0000, representa as flags Carry, Overflow, Zero, Signal respectivamente
uint16_t Memoria_de_dados[TAMANHO_DA_MEMORIA] = {0}; // Armazena os dados usados e manipulados durante a execução do programa.
uint16_t Memoria_de_programa[TAMANHO_DA_MEMORIA] ={0}; // Armazena as instruções
uint16_t Pilha[TAMANHO_DA_PILHA] = {0}; // Armazena os dados temporários,  como variáveis locais, endereços de retorno de funções e o contexto de execução de funções.


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

    //MOV 
    if(opcode == 0b0001) { 
        if(modo == 1) {
            uint8_t rd = (operandos >> 8) & 0x7;
            uint8_t rm = (operandos >> 5) & 0x7;
            movRegistrador(rd, rm);
        }
        else {
            uint8_t rd = (operandos >> 8) & 0x7;
            uint8_t imediato = (operandos & 0xFF);
            movImediato(rd, imediato);
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
            uint8_t parte_immediato = operandos & 0x700;
            uint8_t segunda_parte = operandos & 0x1F;
            uint16_t rm = (operandos >> 5) & 0x7;
            strImediato(rm, (parte_immediato | segunda_parte));
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
        add(rd, rm, rn);
    }
    //SUB
    if(opcode == 0b0101) {
        sub(rd, rm, rn);
    }
    //MUL
    if(opcode == 0b0110) {
        mul(rd, rm, rn);
    }
    //AND
    if(opcode == 0b0111) {
        and(rd, rm, rn);
    }
    //ORR
    if(opcode == 0b1000) {
        orr(rd, rm, rn);
    }
    //NOT
    if(opcode == 0b1001) {
        not(rd, rm);
    }
    //XOR
    if(opcode == 0b1010) {
        xor(rd, rm, rn);
    }
    // CMP & PILHA
    uint8_t zero = operandos & 0x3;
    if(opcode == 0b0000 && modo == 0) {
        if(zero == 0b11) {
            orr(rm, rn);
        }
        else if(zero == 0b01) {
            push(rn);
        }
        else if(zero == 0b10) {
            pop(rd);
        }
        else {
            nop();
        }
    }
    //Shift Right (SHR)
    uint8_t imediato = operandos & 0x1F;
    if(opcode == 0b1011) {
        shr(rd, rm, imediato);
    }
    //Shift Left (SHL)
    if(opcode == 0b1100) {
        shl(rd, rm, imediato);
    }
    //Rotate Right (ROR)
    if(opcode == 0b1101) {
        ror(rd, rm);
    }
    //Rotate Left (ROL) 
    if(opcode == 0b1110) {
        rol(rd, rm);
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
        if(zero == 0b10) {
            jlt(imediato);
        }
        if(zero == 0b11) {
            jgt(imediato);
        }
    }
}

int main () {
    FILE *arquivo;
    char nomeArquivo[TAMANHO_DA_MEMORIA];
    char endereco[10];
    uint16_t instrucao;
    printf("Digite o nome do arquivo: ");

    scanf("%99[^\n]", nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    while(fscanf(arquivo, ""))












    decodificarInstrucao(0x1803);
}