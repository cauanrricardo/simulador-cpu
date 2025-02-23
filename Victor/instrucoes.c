#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "../src/ula.h"
#include "../src/pilha.h"
#include "../src/desvio.h"
#include "../src/mov.h"
#include "../src/nop_halt.h"
#include "../src/store_load.h"
#include "../src/decodificacao.h"
#include "../src/globais.c"
#include "../src/globais.h"

/*#define TAMANHO_DA_MEMORIA 1 << 16 // O tamanho da memória é 2 elevado a quant de bits
#define TAMANHO_DA_PILHA 16 // O tamanho da pilha é igual a quantidade de bits
uint16_t Registrador[8];
uint16_t PC = 0; // Inicializa o valor de PC, que vai armazenar o endereço da próxima instrução
uint16_t IR = 0; // Inicializa o valor do IR, que vai armazenar o endereço da instrução atual
uint16_t SP = 0x8200; // Representa o Valor inicial de SP, que vai armazenar endereço do valor que está na pilha 
uint8_t Flags = 0; // 0000, representa as flags Carry, Overflow, Zero, Signal respectivamente
uint16_t Memoria_de_dados[TAMANHO_DA_MEMORIA] = {0}; // Armazena os dados usados e manipulados durante a execução do programa.
uint16_t Memoria_de_programa[TAMANHO_DA_MEMORIA] ={0}; // Armazena as instruções
uint16_t Pilha[TAMANHO_DA_PILHA] = {0}; // Armazena os dados temporários,  como variáveis locais, endereços de retorno de funções e o contexto de execução de funções.
*/
///////////////////////////////////////////////
//uint8_t ram64kx8[TAM_RAM]; // memoria de dados
//uint8_t rom64kx8[TAM_ROM]; // memoria de program

uint16_t ler_memoria(uint8_t Memoria_de_programa[], uint16_t address)
{
    uint16_t addr = address & 0xFFFE; //forca endereco par

    uint8_t byte0 = Memoria_de_programa[addr];
    uint8_t byte1 = Memoria_de_programa[addr + 1];
    //printf("IR: %02x %02x\n", byte0, byte1);
    return (byte0 << 8) | (byte1);
}

void escrever_byte_memoria(uint8_t Memoria_de_programa[], uint16_t address, uint8_t data)
{
    Memoria_de_programa[address] = data; /////dados -> programa
}

void escrever_half_memoria(uint8_t Memoria_de_programa[], uint16_t address, uint16_t data) //////- dados -> programa
{
    uint8_t byte0 = (uint8_t)(data & 0x00ff);
    uint8_t byte1 = (uint8_t)((data & 0xff00) >> 8);

    escrever_byte_memoria(Memoria_de_programa,address, byte1);
    escrever_byte_memoria(Memoria_de_programa,(address + 1), byte0);
}


uint16_t ler_memoria_de_dados(uint16_t address)
{
    return ler_memoria(Memoria_de_dados /*memoria de dados[]*/, address);
}

uint16_t ler_memoria_de_program(uint16_t address)
{
    return ler_memoria(Memoria_de_programa /*memoria de programa[]*/,address);
}

void busca()
{
    IR = ler_memoria(Memoria_de_programa/*memoria de programa[]*/, PC);
    PC = PC + 2; 
    printf("IR: %04x, PC: %04x\n", IR, PC);
}
/*
void push(uint16_t data)
{
    escrever_half_memoria(Memoria_de_dados,SP,data);
    SP = SP - 2;
}
void pop()
{
    SP = SP + 2;
    return ler_memoria(Memoria_de_dados,SP);
}
*/
/////////////////////////////////////////////////////

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
        escrever_half_memoria(Memoria_de_programa, endereco, instrucao);
        //Memoria_de_programa[endereco] = instrucao; // Divide por 2 para alinhar ao índice correto
        printf("Endereco: 0x%04X, Instrucao: 0x%04x\n", endereco, instrucao);
        printf("Executando instrucao em 0x%04X: 0x%04X\n", endereco, instrucao);
        busca(); // Avança para a próxima instrução
        escrever_half_memoria(Memoria_de_programa, endereco, instrucao);
        decodificarInstrucao(IR);
        //IR = Memoria_de_programa[PC]; // Carrega a instrução no IR
    }
    
    fclose(arquivo);
    /*
    // Simulação da execução (pode ser removido depois)
    PC = 0; // Inicia o PC no primeiro endereço
    while (IR != 0xFFFF || ) { // HALT é a instrução de parada
    } */
    /*printf("%hu", sizeof(uint16_t)  1* + &Registrador); */
    /*uint16_t *ponteir = 0;
    ponteir = &Registrador[1];
    printf("%x", ponteir); */
    return 0;
}