#include "../src/globais.h"

// DESVIOS
void jmp(uint16_t imediato) {
    PC = imediato; // Desvio absoluto
}

void jeq(uint16_t imediato) {
    if (Flags & 0x2) { // Verifica a flag Zero (bit 1: 0x2 = 0010)
        PC = imediato; // Desvio absoluto
    }
}

void jlt(uint16_t imediato) {
    if ((Flags & 0x1) && !(Flags & 0x2)) { // Signal (bit 0: 0x1) ativo e Zero (bit 1: 0x2) inativo
        PC = imediato; // Desvio absoluto
    }
}

void jgt(uint16_t imediato) {
    if (!(Flags & 0x1) && !(Flags & 0x2)) { // Signal (bit 0: 0x1) e Zero (bit 1: 0x2) inativos
        PC = imediato; // Desvio absoluto
    }
}