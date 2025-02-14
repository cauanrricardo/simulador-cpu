//PILHA
void psh(uint8_t valor_registrador) {
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

