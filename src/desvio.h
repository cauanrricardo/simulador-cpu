//DESVIOS

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
