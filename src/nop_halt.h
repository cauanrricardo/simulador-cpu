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