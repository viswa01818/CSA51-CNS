#include <stdio.h>
#include <string.h>

void affine_encrypt_block(unsigned char *block, int a, int b) {
    *block = (a * (*block) + b) % 256;
}

void counter_mode_encrypt(unsigned char *data, int len, unsigned char counter, int cipher_type, void *key) {
    for (int i = 0; i < len; i++) {
        unsigned char keystream = counter + i;
        if (cipher_type == 1) { // Affine
            int *k = (int*)key;
            affine_encrypt_block(&keystream, k[0], k[1]);
        }
        data[i] ^= keystream;
    }
}

void counter_mode_decrypt(unsigned char *data, int len, unsigned char counter, int cipher_type, void *key) {
    counter_mode_encrypt(data, len, counter, cipher_type, key); // Same as encrypt
}

int main() {
    printf("Counter Mode Implementation\n\n");
    
    unsigned char plaintext[] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x04};
    unsigned char ciphertext[6];
    unsigned char decrypted[6];
    unsigned char counter = 0x00;
    int key[2] = {3, 5};
    
    printf("Test data for S-DES:\n");
    printf("Counter starts at: 0x%02X (0000 0000)\n", counter);
    printf("Plaintext: ");
    for (int i = 0; i < 6; i++) printf("0x%02X ", plaintext[i]);
    printf("\n");
    
    // Encrypt
    memcpy(ciphertext, plaintext, 6);
    counter_mode_encrypt(ciphertext, 6, counter, 1, key);
    
    printf("Ciphertext: ");
    for (int i = 0; i < 6; i++) printf("0x%02X ", ciphertext[i]);
    printf("\n");
    
    // Decrypt
    memcpy(decrypted, ciphertext, 6);
    counter_mode_decrypt(decrypted, 6, counter, 1, key);
    
    printf("Decrypted: ");
    for (int i = 0; i < 6; i++) printf("0x%02X ", decrypted[i]);
    printf("\n");
    
    return 0;
}
