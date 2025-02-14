//MOV
void movImediato(uint8_t registrador, uint8_t imediato) {
    Registrador[registrador] = imediato;
}

void movRegistrador(uint8_t r_destino, uint8_t r_origem) {
    Registrador[r_destino] = Registrador[r_origem]; // Revisar isso aqui
}
