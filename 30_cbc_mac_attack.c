#include <stdio.h>
#include <string.h>

void cbc_mac_attack_demo() {
    printf("CBC MAC Attack Demonstration\n\n");
    
    printf("Given: T = MAC(K, X) for one-block message X\n");
    printf("Adversary can compute MAC for two-block message X || (X ⊕ T)\n\n");
    
    printf("Attack process:\n");
    printf("1. Adversary obtains T = MAC(K, X)\n");
    printf("2. Constructs message: X || (X ⊕ T)\n");
    printf("3. Computes MAC(K, X || (X ⊕ T))\n\n");
    
    printf("Why this works:\n");
    printf("CBC-MAC computation:\n");
    printf("Block 1: C1 = E(K, X)\n");
    printf("Block 2: C2 = E(K, (X ⊕ T) ⊕ C1)\n");
    printf("MAC = C2\n\n");
    
    printf("Since C1 = T (from original MAC):\n");
    printf("C2 = E(K, (X ⊕ T) ⊕ T)\n");
    printf("C2 = E(K, X ⊕ T ⊕ T)\n");
    printf("C2 = E(K, X)\n");
    printf("C2 = T\n\n");
    
    printf("Therefore: MAC(K, X || (X ⊕ T)) = T\n");
    printf("Adversary successfully forged a MAC without knowing the key!\n\n");
    
    printf("This demonstrates that CBC-MAC is not secure for variable-length messages.\n");
    printf("Solution: Use CMAC or HMAC for secure MAC generation.\n");
}

int main() {
    cbc_mac_attack_demo();
    return 0;
}
