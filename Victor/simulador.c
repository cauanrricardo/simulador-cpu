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
    void movImediato(uint16_t registrador, uint16_t imediato) {
     Registrador[registrador] = imediato;
        printf(Registrador[%02x] = %x", registrador, imediato);
    }

    void movRegistrador(uint16_t r_destino, uint16_t r_origem){
     Registrador[r_destino] = Registrador[r_origem]; // Revisar isso aqui
    }
    //ULA
    void add(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] + Registrador[r_origem2]; // Revisar isso aqui 
    }

    void sub(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] - Regitrador[r_origem2]; // Revisar isso aqui
    }
    
    void mul(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] * Registrador[r_origem2]; // Revisar isso aqui
    }

    void and(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] & Registrador[r_origem2]; // Revisar isso aqui
    }

    void xor(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] ^ Registrador[r_origem2]; // Revisar isso aqui
    }

    void orr(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] | Registrador[r_origem2]; // Revisar isso aqui
    }

    void shr(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
        Registrador[r_destino] = Registrador[r_origem] >> imediato; // Revisar isso aqui
    }

    void shl(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
        Registrador[r_destino] = Registrador[r_origem] << imediato; // Revisar isso aqui
    }

    uint16_t num_bits = 16;
    n_bits = n_bits % num_bits; // Isso tá me retornando rm; 

    uint16_t ror(uint16_t num, uint16_t n_bits){ // Encurtar o código, declarando apenas uma vez 
        return (num >> n_bits) | (num << (num_bits - n_bits)); // Não entendi a lógica
    }

    uint16_t rol (uint16_t num, uint16_t n_bits) {
        return (num << n_bits) | (num >> (num_bits - n_bits)); //Não entendi a lógica
    }

    void cmp(uint16_t r1, uint16_t r2){
       uint16_t valor_r1 = Registrador[r1];
       uint16_t valor_r2 = Registrador[r2];
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
        Memoria_de_dados[SP] = Registrador[valor_registrador]; //Tá certo, só inverte a ordem
        SP--; //SP decrementa depois, pois a pilha que estamos trabalhando é full descend;
    }
    //n sei se pop ta certo :/****
    void pop(uint16_t valor_registrador){ // Essa função é void
        if(SP == TAMANHO_DA_MEMORIA){
            printf("PILHA VAZIA!!!!!!!!!, NÃO CONSIGO DAR POP :( \n)"); // Faz sentido
            return;
        }
        SP++; //SP incrementa antes
     Registrador[valor_registrador] = Memoria_de_dados[SP]; // O que é esse valor? Não é assim que se pega o endereço de SP;
    }
    //STORE
    void strImediato(uint16_t *r_destino, uint16_t imediato){
     Registrador[r_destino] = imediato; 
    }
    
    void Registrador(uint16_t *r_destino, uint16_t r_origem){
     Registrador[r_destino] = Registrador[r_origem]; 
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
        return;  // A função é void, não retorna nada;
    }
    //LOAD
    void ldr(uint16_t r_destino, uint16_t *r_origem){
     Registrador[r_destino] = *r_origem; 
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