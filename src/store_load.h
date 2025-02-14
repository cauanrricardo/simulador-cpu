//STORE
void strImediato(uint8_t *r_destino, uint8_t imediato){
    Registrador[*r_destino] = imediato; 
}

void strRegistrador(uint8_t *r_destino, uint8_t r_origem){
    Registrador[*r_destino] = Registrador[r_origem];
}

//LOAD
//ver de ldr tá certo
void ldr(uint8_t r_destino, uint8_t r_origem){
    Registrador[r_destino] = Registrador[r_origem]; 
}