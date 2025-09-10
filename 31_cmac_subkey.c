#include <stdio.h>
#include <string.h>

void cmac_subkey_analysis() {
    printf("CMAC Subkey Generation Analysis\n\n");
    
    printf("CMAC subkey generation process:\n");
    printf("1. Apply block cipher to all-zero block\n");
    printf("2. First subkey K1: left shift result, conditionally XOR constant\n");
    printf("3. Second subkey K2: left shift K1, conditionally XOR constant\n\n");
    
    printf("Constants needed:\n");
    printf("a. For 64-bit blocks: 0x1B (0001 1011)\n");
    printf("b. For 128-bit blocks: 0x87 (1000 0111)\n\n");
    
    printf("How left shift and XOR accomplishes the result:\n");
    printf("1. Left shift multiplies by 2 in GF(2^n)\n");
    printf("2. If MSB was 1, we need to reduce modulo irreducible polynomial\n");
    printf("3. XOR with constant performs this reduction\n");
    printf("4. This ensures we stay within the finite field\n\n");
    
    printf("Example for 128-bit blocks:\n");
    printf("L = E(K, 0^128)\n");
    printf("If L[0] = 0: K1 = L << 1\n");
    printf("If L[0] = 1: K1 = (L << 1) ⊕ 0x87\n");
    printf("If K1[0] = 0: K2 = K1 << 1\n");
    printf("If K1[0] = 1: K2 = (K1 << 1) ⊕ 0x87\n\n");
    
    printf("This ensures proper field arithmetic in GF(2^128).\n");
}

int main() {
    cmac_subkey_analysis();
    return 0;
}
