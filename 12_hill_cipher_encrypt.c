#include <stdio.h>
#include <string.h>
#include <ctype.h>

void matrix_multiply(int key[2][2], int plain[2], int result[2]) {
    result[0] = (key[0][0] * plain[0] + key[0][1] * plain[1]) % 26;
    result[1] = (key[1][0] * plain[0] + key[1][1] * plain[1]) % 26;
}

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void hill_encrypt(char *plaintext, int key[2][2]) {
    int len = strlen(plaintext);
    int i;
    
    for (i = 0; i < len; i += 2) {
        if (i + 1 < len) {
            int plain[2] = {tolower(plaintext[i]) - 'a', tolower(plaintext[i+1]) - 'a'};
            int cipher[2];
            
            matrix_multiply(key, plain, cipher);
            
            plaintext[i] = cipher[0] + 'a';
            plaintext[i+1] = cipher[1] + 'a';
        }
    }
}

void hill_decrypt(char *ciphertext, int key[2][2]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0] + 26) % 26;
    int det_inv = mod_inverse(det, 26);
    
    int inv_key[2][2];
    inv_key[0][0] = (key[1][1] * det_inv) % 26;
    inv_key[0][1] = ((-key[0][1] * det_inv) % 26 + 26) % 26;
    inv_key[1][0] = ((-key[1][0] * det_inv) % 26 + 26) % 26;
    inv_key[1][1] = (key[0][0] * det_inv) % 26;
    
    int len = strlen(ciphertext);
    int i;
    
    for (i = 0; i < len; i += 2) {
        if (i + 1 < len) {
            int cipher[2] = {tolower(ciphertext[i]) - 'a', tolower(ciphertext[i+1]) - 'a'};
            int plain[2];
            
            matrix_multiply(inv_key, cipher, plain);
            
            ciphertext[i] = plain[0] + 'a';
            ciphertext[i+1] = plain[1] + 'a';
        }
    }
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight oclock";
    int key[2][2] = {{9, 4}, {5, 7}};
    
    printf("Hill Cipher Encryption/Decryption\n\n");
    printf("Key matrix:\n");
    printf("[%d %d]\n", key[0][0], key[0][1]);
    printf("[%d %d]\n\n", key[1][0], key[1][1]);
    
    printf("Original message: %s\n", message);
    
    // Encrypt
    char encrypted[1000];
    strcpy(encrypted, message);
    hill_encrypt(encrypted, key);
    printf("Encrypted message: %s\n", encrypted);
    
    // Decrypt
    char decrypted[1000];
    strcpy(decrypted, encrypted);
    hill_decrypt(decrypted, key);
    printf("Decrypted message: %s\n", decrypted);
    
    return 0;
}
