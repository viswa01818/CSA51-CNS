#include <stdio.h>
#include <string.h>

void affine_encrypt_block(unsigned char *block, int a, int b) {
    *block = (a * (*block) + b) % 256;
}

void affine_decrypt_block(unsigned char *block, int a, int b) {
    int a_inv = 0;
    for (int i = 1; i < 256; i++) {
        if ((a * i) % 256 == 1) { a_inv = i; break; }
    }
    *block = (a_inv * ((*block) - b + 256)) % 256;
}

void cbc_encrypt(unsigned char *data, int len, unsigned char iv, int cipher_type, void *key) {
    unsigned char prev = iv;
    for (int i = 0; i < len; i++) {
        data[i] ^= prev;
        if (cipher_type == 1) { // Affine
            int *k = (int*)key;
            affine_encrypt_block(&data[i], k[0], k[1]);
        }
        prev = data[i];
    }
}

void cbc_decrypt(unsigned char *data, int len, unsigned char iv, int cipher_type, void *key) {
    unsigned char prev = iv;
    for (int i = 0; i < len; i++) {
        unsigned char temp = data[i];
        if (cipher_type == 1) { // Affine
            int *k = (int*)key;
            affine_decrypt_block(&data[i], k[0], k[1]);
        }
        data[i] ^= prev;
        prev = temp;
    }
}

int main() {
    printf("CBC Mode Implementation with Multiple Ciphers\n\n");
    
    unsigned char plaintext[] = {0x00, 0x01, 0x02, 0x03};
    unsigned char ciphertext[4];
    unsigned char decrypted[4];
    unsigned char iv = 0xAA; // 1010 1010
    int key[2] = {3, 5}; // Affine parameters
    
    printf("Test data for S-DES:\n");
    printf("IV: 0x%02X (1010 1010)\n", iv);
    printf("Plaintext: ");
    for (int i = 0; i < 4; i++) printf("0x%02X ", plaintext[i]);
    printf("\n");
    
    // Encrypt
    memcpy(ciphertext, plaintext, 4);
    cbc_encrypt(ciphertext, 4, iv, 1, key);
    
    printf("Ciphertext: ");
    for (int i = 0; i < 4; i++) printf("0x%02X ", ciphertext[i]);
    printf("\n");
    
    // Decrypt
    memcpy(decrypted, ciphertext, 4);
    cbc_decrypt(decrypted, 4, iv, 1, key);
    
    printf("Decrypted: ");
    for (int i = 0; i < 4; i++) printf("0x%02X ", decrypted[i]);
    printf("\n");
    
    return 0;
}
