#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define TAMANHO_DA_MEMORIA 1 << 16 // O tamanho da memória é 2 elevado a quant de bits
#define TAMANHO_DA_PILHA 16 // O tamanho da pilha é igual a quantidade de bits

///////////////////////////////////////////////
uint8_t ram64kx8[TAM_RAM]; // memoria de dados
uint8_t rom64kx8[TAM_ROM]; // memoria de program

uint16_t ler_memoria(uint8_t Memoria_de_programa[], uint16_t address)
{
    uint16_t addr = address & 0xFFFE; //forca endereco par

    uint8_t byte0 = Memoria_de_programa[addr];
    uint8_t byte1 = Memoria_de_programa[addr + 1];

    return ((uint16)byte1<<8) & ((uint16)byte0);
}

void escrever_byte_memoria(uint8_t Memoria_de_programa[], uint16_t address, uint8_t data)
{
    mem[addr] = data;
}

void escrever_half_memoria(uint8_t Memoria_de_dados[], uint16_t address, uint16_t data)
{
    uint8_t byte0 = (uint8_t)(data & 0x00ff);
    uint8_t byte1 = (uint8_t)((data & 0xff00) >> 8);

    escrever_byte_memoria(mem,address, byte0);
    escrever_byte_memoria(mem,(address + 1), byte1);
}


uint16_t ler_ram(uint16_t address)
{
    return ler_memoria(ram64kx8, address);
}

uint16_t ler_rom(uint16_t address)
{
    return ler_memoria(rom64kx8,address);
}

void busca()
{
    IR = ler_memoria(rom64kx8, PC);
    PC = PC + 2; 
}

void push(uint16_t data)
{
    escrever_half_memoria(ram64kx8,SP,data);
    SP = SP - 2;
}
void pop()
{
    SP = SP + 2;
    return ler_memoria(ram64kx8,SP);
}

/////////////////////////////////////////////////////

uint16_t Registrador[8];
uint16_t PC = 0; // Inicializa o valor de PC, que vai armazenar o endereço da próxima instrução
uint16_t IR = 0; // Inicializa o valor do IR, que vai armazenar o endereço da instrução atual
uint16_t SP = 0x8200; // Representa o Valor inicial de SP, que vai armazenar endereço do valor que está na pilha 
uint8_t Flags = 0; // 0000, representa as flags Carry, Overflow, Zero, Signal respectivamente
uint16_t Memoria_de_dados[TAMANHO_DA_MEMORIA] = {0}; // Armazena os dados usados e manipulados durante a execução do programa.
uint16_t Memoria_de_programa[TAMANHO_DA_MEMORIA] ={0}; // Armazena as instruções
uint16_t Pilha[TAMANHO_DA_PILHA] = {0}; // Armazena os dados temporários,  como variáveis locais, endereços de retorno de funções e o contexto de execução de funções.

    //MOV
    void movImediato(uint16_t registrador, uint16_t imediato){
        Registrador[registrador] = imediato;
        printf("MOV R[%02x], #%04x\n", registrador, Registrador[registrador]);
    }

    void movRegistrador(uint16_t r_destino, uint16_t r_origem){
        Registrador[r_destino] = Registrador[r_origem]; // Revisar isso aqui
    }


    //ULA
    void add(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
        Registrador[r_destino] = Registrador[r_origem] + Registrador[r_origem2]; // Revisar isso aqui 
    }

    void sub(uint16_t r_destino, uint16_t r_origem, uint16_t r_origem2){
       Registrador[r_destino] = Registrador[r_origem] - Registrador[r_origem2]; // Revisar isso aqui
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

    void orr(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
        Registrador[r_destino] = Registrador[r_origem] | Registrador[r_origem2]; // Revisar isso aqui
    }

    void shr(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
        Registrador[r_destino] = Registrador[r_origem] >> imediato; // Revisar isso aqui
    }

    void shl(uint16_t r_destino, uint16_t r_origem, uint16_t imediato){
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

    void cmp(uint16_t r1, uint16_t r2){
       uint16_t valor_r1 = Registrador[r1];
       uint16_t valor_r2 = Registrador[r2];
        if(valor_r1 == valor_r2){
            Flags |= (1 << 2); // Z (Zero)
        }
        if(valor_r1 < valor_r2){
            Flags |= (1 << 3); // S (Sing)
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
    
    void not(uint8_t Rd, uint8_t Rm) {
        Registrador[Rd] = ~Registrador[Rm];
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
    void strImediato(uint16_t r_destino, uint16_t imediato){
        Registrador[r_destino] = imediato; 
    }
    
    void strRegistrador(uint16_t *r_destino, uint16_t r_origem){
        Registrador[*r_destino] = Registrador[r_origem];
    }

    //NOP
    void nop(){
        printf("antes de executar o nop");
        asm("nop");
        printf("depois de executar o nop");
    }

    //HALT
    void halt(){
        exit(0);
    }

    //LOAD
    //ver de ldr tá certo
    void ldr(uint16_t r_destino, uint16_t r_origem){
        Registrador[r_destino] = Registrador[r_origem]; 
    }

    //DESVIO

    void jmp(uint16_t Imediato){
        PC += Imediato;
    }

    
void jeq(uint16_t novo_endereco) {
    if (Flags & 0x4) {          // Verifica a flag Zero (bit 3: 0x4 = 0100)
        PC = novo_endereco;     // Atualiza PC se condição satisfeita
    }
}


void jlt(uint16_t novo_endereco) {
    if ((Flags & 0x1) && !(Flags & 0x4)) { // Signal (bit 0: 0x1) ativo e Zero inativo
        PC = novo_endereco;
    }
}


void jgt(uint16_t novo_endereco) {
    if (!(Flags & 0x1) && !(Flags & 0x4)) { // Signal e Zero inativos
        PC = novo_endereco;
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
            movRegistrador(Registrador[rm], Registrador[rn]);
        }
        else {
            uint16_t parte_immediato = operandos & 0x700;
            uint8_t segunda_parte = operandos & 0x1F;
            uint16_t rm = (operandos >> 5) & 0x7;
            strImediato(rm, (parte_immediato | segunda_parte));
        }
    } 
    //LOAD (LDR) 
    if(opcode == 0b0011) {
        uint8_t rd = (operandos >> 8) & 0x7;
        uint8_t rm = (operandos >> 8) & 0x7;
        ldr(rd,  rm);
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
            cmp(rm, rn);
        }
        else if(zero == 0b01) {
            psh(rn);
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

    printf("Digite o path do arquivo: ");
    scanf("%99s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    
    // Lê o arquivo linha por linha no formato "endereço: 0xINSTRUÇÃO"
    while (fscanf(arquivo, "%hx: 0x%hx", &endereco, &instrucao) == 2) {
        /*uint8_t primeira_parte_endereco = (endereco >> 8) & 0x15;
        uint8_t segunda_parte_endereco = endereco & 0x15;
        uint8_t primeira_parte_instrucao = instrucao >> 8 & 0x15;
        uint8_t segunda_parte_instrucao = instrucao & 0x15;
        Memoria_de_programa[primeira_parte_endereco] = primeira_parte_instrucao;
        Memoria_de_programa[segunda_parte_endereco] = segunda_parte_instrucao; // Divide por 2 para alinhar ao índice correto*/
        printf("Primeira parte Endereco: 0x%04X, Segunda parte Endereco: 0x%04X | Primeira parte da Instrucao: 0x%04X, Segunda parte da Instrucao: 0x%04x\n", primeira_parte_endereco, segunda_parte_endereco, primeira_parte_instrucao, segunda_parte_instrucao);
    }
    
    fclose(arquivo);

    // Simulação da execução (pode ser removido depois)
    PC = 0; // Inicia o PC no primeiro endereço
    while (PC < TAMANHO_DA_MEMORIA && Memoria_de_programa[PC / 2] != 0x0FF8) { // 0x0FF8 pode ser uma instrução de parada
        PC += 2; // Avança para a próxima instrução
        IR = Memoria_de_programa[PC]; // Carrega a instrução no IR
        printf("Executando instrucao em 0x%04X: 0x%04X\n", PC, IR);
        decodificarInstrucao(IR);
    }
    /*printf("%hu", sizeof(uint16_t)  1* + &Registrador); */
    /*uint16_t *ponteir = 0;
    ponteir = &Registrador[1];
    printf("%x", ponteir); */
    return 0;
}