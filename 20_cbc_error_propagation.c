#include <stdio.h>
#include <string.h>

void analyze_cbc_error_propagation() {
    printf("CBC Error Propagation Analysis\n\n");
    
    printf("CBC Mode Error Propagation:\n");
    printf("P1 = D(C1) ⊕ IV\n");
    printf("P2 = D(C2) ⊕ C1\n");
    printf("P3 = D(C3) ⊕ C2\n");
    printf("...\n\n");
    
    printf("If there's an error in transmitted C1:\n");
    printf("- P1 will be corrupted (directly affected)\n");
    printf("- P2 will be corrupted (because P2 = D(C2) ⊕ C1)\n");
    printf("- P3, P4, ... will NOT be affected\n\n");
    
    printf("Answers:\n");
    printf("a. Are any blocks beyond P2 affected? NO\n");
    printf("   Only P1 and P2 are affected by an error in C1.\n\n");
    
    printf("b. If there's a bit error in source P1:\n");
    printf("   - This error propagates through ALL subsequent ciphertext blocks\n");
    printf("   - C1 = E(P1 ⊕ IV) - error in P1 affects C1\n");
    printf("   - C2 = E(P2 ⊕ C1) - error propagates to C2\n");
    printf("   - C3 = E(P3 ⊕ C2) - error continues to propagate\n");
    printf("   - Effect: ALL ciphertext blocks after the error are affected\n");
    printf("   - At receiver: ALL plaintext blocks will be corrupted\n");
}

int main() {
    analyze_cbc_error_propagation();
    return 0;
}
