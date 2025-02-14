#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define TAMANHO_DA_MEMORIA 1 << 16 // O tamanho da memória é 2 elevado a quant de bits
#define TAMANHO_DA_PILHA 16 // O tamanho da pilha é igual a quantidade de bits

uint16_t Registrador[8];
uint16_t PC = 0; // Inicializa o valor de PC, que vai armazenar o endereço da próxima instrução
uint16_t IR = 0; // Inicializa o valor do IR, que vai armazenar o endereço da instrução atual
uint16_t SP = 0x8200; // Representa o Valor inicial de SP, que vai armazenar endereço do valor que está na pilha 
uint8_t Flags = 0; // 0000, representa as flags Carry, Overflow, Zero, Signal respectivamente
uint16_t Memoria_de_dados[TAMANHO_DA_MEMORIA] = {0}; // Armazena os dados usados e manipulados durante a execução do programa.
uint16_t Memoria_de_programa[TAMANHO_DA_MEMORIA] ={0}; // Armazena as instruções
uint16_t Pilha[TAMANHO_DA_PILHA] = {0}; // Armazena os dados temporários,  como variáveis locais, endereços de retorno de funções e o contexto de execução de funções.
    //MOV
void movImediato(uint8_t registrador, uint8_t imediato){
    Registrador[registrador] = imediato;
}
void movRegistrador(uint8_t r_destino, uint8_t r_origem){
    Registrador[r_destino] = Registrador[r_origem]; // Revisar isso aqui
}
//ULA
void add(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
    Registrador[r_destino] = Registrador[r_origem] + Registrador[r_origem2]; // Revisar isso aqui 
}
void sub(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
    Registrador[r_destino] = Registrador[r_origem] - Registrador[r_origem2]; // Revisar isso aqui
}
void mul(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
    Registrador[r_destino] = Registrador[r_origem] * Registrador[r_origem2]; // Revisar isso aqui
}
void and(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
    Registrador[r_destino] = Registrador[r_origem] & Registrador[r_origem2]; // Revisar isso aqui
}
void xor(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
    Registrador[r_destino] = Registrador[r_origem] ^ Registrador[r_origem2]; // Revisar isso aqui
}
void orr(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2){
    Registrador[r_destino] = Registrador[r_origem] | Registrador[r_origem2]; // Revisar isso aqui
}
void shr(uint8_t r_destino, uint8_t r_origem, uint8_t imediato){
    Registrador[r_destino] = Registrador[r_origem] >> imediato; // Revisar isso aqui
}
void shl(uint8_t r_destino, uint8_t r_origem, uint8_t imediato){
    Registrador[r_destino] = Registrador[r_origem] << imediato; // Revisar isso aqui
}
void ror(uint8_t Rd, uint8_t Rm) {
    uint16_t valor = Registrador[Rm];
    uint16_t bitLSB = valor & 1; // Obtém o bit menos significativo (LSB)
    Registrador[Rd] = (valor >> 1) | (bitLSB << 15); // Move bits e recoloca o LSB no MSB
}
void rol(uint8_t Rd, uint8_t Rm) {
    uint16_t valor = Registrador[Rm];
    uint16_t bitMSB = (valor >> 15) & 1; // Obtém o bit mais significativo (MSB)
    Registrador[Rd] = (valor << 1) | bitMSB; // Move bits e recoloca o MSB no LSB
}
void cmp(uint8_t r1, uint8_t r2){
    uint16_t valor_r1 = registrador[r1];
    uint16_t valor_r2 = registrador[r2];
    if(valor_r1 == valor_r2){
        Flags |= (1 << 2); // Z (Zero)
    }
    if(valor_r1 < valor_r2){
        Flags |= (1 << 3); // S (Sing)
    }
}
void not(uint8_t Rd, uint8_t Rm) {
    Registrador[Rd] = ~Registrador[Rm];
}
//PILHA
void psh(uint8_t valor_registrador){
    if(SP == 0){
        printf("PILHA CHEIA!!!!!!!!!!!!, NÃO CONSIGO DAR PUSH :(\n");
        return;
    }
    Memoria_de_dados[SP] = Registrador[valor_registrador]; //Tá certo, só inverte a ordem
    SP--; //SP decrementa depois, pois a pilha que estamos trabalhando é full descend;
}
void pop(uint8_t Rd) {
    if (SP < TAMANHO_DA_PILHA) { // Verifica se a pilha não está vazia
        Registrador[Rd] = Pilha[SP]; // Rd recebe o valor no topo da pilha
        SP++; // Move o ponteiro da pilha para baixo (decresce)
    } else {
        printf("Erro: Pilha ta seca seca (vazia)\n");
    }
}
//STORE
void strImediato(uint8_t *r_destino, uint8_t imediato){
    Registrador[*r_destino] = imediato; 
}

void strRegistrador(uint8_t *r_destino, uint8_t r_origem){
    Registrador[*r_destino] = Registrador[r_origem];
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
//ver de ldr tá certo
void ldr(uint8_t r_destino, uint8_t r_origem){
    Registrador[r_destino] = Registrador[r_origem]; 
}

//DESVIO

void jmp(uint8_t Imediato){
    PC += Imediato;
}
void jeq(uint8_t imediato) {
    if (Flags & 0x4) {          // Verifica a flag Zero (bit 3: 0x4 = 0100)
        PC = imediato;     // Atualiza PC se condição satisfeita
    }
}
void jlt(uint8_t imediato) {
    if ((Flags & 0x1) && !(Flags & 0x4)) { // Signal (bit 0: 0x1) ativo e Zero inativo
        PC = imediato;
    }
}
void jgt(uint8_t imediato) {
    if (!(Flags & 0x1) && !(Flags & 0x4)) { // Signal e Zero inativos
        PC = imediato;
    }
}
void decodificarInstrucao(uint16_t instrucao) {
    uint8_t opcode = (instrucao >> 12) & 0xF; // Extrai o opcode (4 bits mais significativos)
    uint8_t modo = (instrucao >> 11) & 0x1;   // Extrai o modo (5º bit)
    uint16_t operandos = instrucao & 0x7FF;   // Extrai os operandos (11 bits restantes)

    //MOV 
    if(opcode == 0b0001) { 
        if(modo == 0) {
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
            strRegistrador( Registrador[rm], Registrador[rn]);
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
        ldr Registrador[rd],  Registrador[rm]);
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
    char nomeArquivo[100]; // Nome do arquivo
    uint16_t endereco, instrucao;

    printf("Digite o nome do arquivo: ");
    scanf("%99s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    
    // Lê o arquivo linha por linha no formato "endereço: 0xINSTRUÇÃO"
    while (fscanf(arquivo, "%hx: 0x%hx", &endereco, &instrucao) == 2) {
        Memoria_de_programa[endereco / 2] = instrucao; // Divide por 2 para alinhar ao índice correto
        printf("Endereço: 0x%04X | Instrução: 0x%04X\n", endereco, instrucao);
    }

    fclose(arquivo);

    // Simulação da execução (pode ser removido depois)
    PC = 0; // Inicia o PC no primeiro endereço
    while (PC < TAMANHO_DA_MEMORIA && Memoria_de_programa[PC / 2] != 0x0FF8) { // 0x0FF8 pode ser uma instrução de parada
        IR = Memoria_de_programa[PC / 2]; // Carrega a instrução no IR
        printf("Executando instrução em 0x%04X: 0x%04X\n", PC, IR);
        decodificarInstrucao(IR);
        PC += 2; // Avança para a próxima instrução
    }
    return 0;
}