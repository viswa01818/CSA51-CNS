#include <stdio.h>
#include <math.h>

int main() {
    printf("SHA-3 Block Analysis\n\n");
    
    printf("SHA-3 with 1024-bit block size:\n");
    printf("- State matrix: 5x5 lanes of 64 bits each\n");
    printf("- Total state: 5 × 5 × 64 = 1600 bits\n");
    printf("- Capacity portion: 512 bits (8 lanes)\n");
    printf("- Rate portion: 1024 bits (remaining lanes)\n\n");
    
    printf("Initial state (all zeros in capacity portion):\n");
    printf("Lanes 0-16: Rate portion (can have non-zero bits)\n");
    printf("Lanes 17-24: Capacity portion (all zeros initially)\n\n");
    
    printf("Analysis of zero lane propagation:\n");
    printf("1. First message block P0 has at least one nonzero bit in each lane\n");
    printf("2. After first permutation, some capacity lanes become nonzero\n");
    printf("3. Each subsequent block affects more capacity lanes\n");
    printf("4. Eventually all capacity lanes become nonzero\n\n");
    
    printf("Time calculation:\n");
    printf("- Each block processes 1024 bits\n");
    printf("- Capacity portion: 8 lanes (512 bits)\n");
    printf("- Worst case: need 8 blocks to affect all capacity lanes\n");
    printf("- Each block requires one permutation\n");
    printf("- Total time: 8 permutations\n\n");
    
    printf("However, due to SHA-3's design:\n");
    printf("- Theta step spreads changes across all lanes\n");
    printf("- Rho and Pi steps move bits around\n");
    printf("- Chi step creates complex interactions\n");
    printf("- Iota step adds round constants\n\n");
    
    printf("Realistic estimate: 2-3 blocks (permutations) before\n");
    printf("all capacity lanes have at least one nonzero bit\n");
    
    return 0;
}
