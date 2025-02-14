#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
// legenda do cauan
/*
imediato = é um valor constante q pode ser diretamente usado em uma operação
------
operando1: Pode ser o primeiro número (registrador ou valor imediato) em uma operação aritmética.
-------
operando2: Pode ser o segundo número (registrador ou valor imediato) na mesma operação.
--------
Por exemplo, na operação de adição (ADD), os operandos seriam os dois números que estão sendo somados.
*/
void atualizar_flags(int resultado, int operando1, int operando2, char tipo_operacao)
{
    Flags = 0;
    
    // flag zero (z)
    if (resultado == 0) // resultado = operando1 + operando 2
    {
        Flags = Flags | (1 << 2); // z == 1
    }
    else
    {
        Flags = Flags & ~(1 << 2); // z = 0;
    }

    // flag sinal (s) - para saber se o resltado é negativo
    // Flag Sinal (S): Se o bit 15 do resultado for 1, o número é negativo (em complemento de 2).
    // Isso indica que a operação gerou um número negativo, portanto, a flag S é setada (S = 1).
    // Caso contrário, se o bit 15 for 0, o número é positivo ou zero, e a flag S é dessetada (S = 0).
    if (resultado & 0x8000)       // pega o bit mais significativo (0x8000 = 1000 0000 0000 0000 )
    {                             // se o bit for mais significativo for 1, (indica que e negativo)
        Flags = Flags | (1 << 3); // s = 1;
    }
    else
    {
        Flags = Flags & ~(1 << 3); // s = 0
    }

    /*// Flag Carry (C): Durante a soma, verificamos se houve transbordo.
    // Se a soma de `operando1` e `operando2` exceder 0xFFFF (limite de 16 bits), a flag Carry é setada.
    // Durante a subtração, se `operando1` for menor que `operando2`, ou seja, se houver empréstimo (borrow), a flag Carry também é setada.*/
    if (tipo_operacao == 'A')
    { // Soma
        if ((uint32_t)operando1 + (uint32_t)operando2 > 0xFFFF)
        {                      // Faz soma com 32 bits para detectar overflow
            Flags |= (1 << 0); // c = 1
        }
        else
        {
            Flags &= ~(1 << 0); // c = 0
        }
    }
    else if (tipo_operacao == 'S') // se for menor houve um borrow
    { 
        if (operando1 < operando2)
        {                      // se operando1 é menor, houve "carry" (em subtração, carry significa borrow)
            Flags |= (1 << 0); // c = 1
        }
        else
        {
            Flags &= ~(1 << 0); // c = 0
        }
    }
   
    /*// Flag Overflow (OV): O Overflow ocorre quando a operação aritmética gera um valor que
    // não pode ser representado corretamente com o número de bits disponíveis (16 bits), causando um transbordo de sinal.
    // Para soma, verificamos se `operando1` e `operando2` têm o mesmo sinal, mas o resultado tem sinal oposto.
    // Para subtração, verificamos se os operandos têm sinais diferentes, mas o resultado tem o sinal de `operando2`.*/
    if (tipo_operacao == 'A')
    { // Soma
        if (((operando1 & 0x8000) == (operando2 & 0x8000)) && ((resultado & 0x8000) != (operando1 & 0x8000)))
        {
            Flags |= (1 << 1); // OV = 1
        }
        else
        {
            Flags &= ~(1 << 1); // OV = 0
        }
    }
    else if (tipo_operacao == 'S') //sub
    { /
        if (((operando1 & 0x8000) != (operando2 & 0x8000)) && ((resultado & 0x8000) != (operando1 & 0x8000)))
        {
            Flags |= (1 << 1); // OV = 1
        }
        else
        {
            Flags &= ~(1 << 1); // OV = 0
        }
    }
}
/* flag overflow
(operando1 & 0x8000) == (operando2 & 0x8000): Aqui
estamos verificando se os dois operandos têm sinais iguais
&&
(resultado & 0x8000) != (operando1 & 0x8000) Estamos verificando se o resultado tem sinal oposto ao dos operandos. Ou seja, se os operandos eram positivos,
 mas o resultado se tornou negativo (ou o contrário).
--
Se a condição for verdadeira, houve overflow, e a flag Overflow (OV)
 é setada (colocando o bit 1 da variável Flags como 1).



*/

int main()
{
}