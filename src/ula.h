//ULA
void add(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
    Registrador[r_destino] = Registrador[r_origem] + Registrador[r_origem2]; // Revisar isso aqui 
}

void sub(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
   Registrador[r_destino] = Registrador[r_origem] - Registrador[r_origem2]; // Revisar isso aqui
}

void mul(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
    Registrador[r_destino] = Registrador[r_origem] * Registrador[r_origem2]; // Revisar isso aqui
}


void and(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
    Registrador[r_destino] = Registrador[r_origem] & Registrador[r_origem2]; // Revisar isso aqui
}

void xor(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
    Registrador[r_destino] = Registrador[r_origem] ^ Registrador[r_origem2]; // Revisar isso aqui
}

void orr(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
    Registrador[r_destino] = Registrador[r_origem] | Registrador[r_origem2]; // Revisar isso aqui
}

void shr(uint8_t r_destino, uint8_t r_origem, uint8_t imediato) {
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

void cmp(uint8_t r1, uint8_t r2) {
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
