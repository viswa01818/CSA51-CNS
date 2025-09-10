#include <stdio.h>
#include <string.h>

void analyze_des_subkeys() {
    printf("DES Subkey Bit Analysis\n\n");
    
    printf("DES uses 56-bit key (64-bit with parity bits)\n");
    printf("Key is split into two 28-bit halves: C0 and D0\n\n");
    
    printf("Subkey generation process:\n");
    printf("1. PC-1 permutation selects 56 bits from 64-bit key\n");
    printf("2. Split into C0 (28 bits) and D0 (28 bits)\n");
    printf("3. For each round i:\n");
    printf("   - Left shift Ci-1 and Di-1 by shift amount\n");
    printf("   - PC-2 permutation selects 48 bits from 56-bit result\n\n");
    
    printf("Bit analysis:\n");
    printf("- First 24 bits of each subkey come from C half (28 bits)\n");
    printf("- Last 24 bits of each subkey come from D half (28 bits)\n");
    printf("- PC-2 selects 24 bits from each 28-bit half\n");
    printf("- This creates disjoint subsets as required\n\n");
    
    printf("Shift schedule:\n");
    int shifts[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    for (int i = 0; i < 16; i++) {
        printf("Round %2d: %d bit shift\n", i+1, shifts[i]);
    }
    
    printf("\nThis ensures that:\n");
    printf("- Each subkey uses different bit combinations\n");
    printf("- No single bit from original key appears in all subkeys\n");
    printf("- Provides good key diffusion\n");
}

int main() {
    analyze_des_subkeys();
    return 0;
}
