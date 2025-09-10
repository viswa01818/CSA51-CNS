#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void des_encrypt_block(unsigned long long block, unsigned long long key, unsigned long long *result) {
    // Simplified DES encryption (actual implementation would be much more complex)
    *result = block ^ key; // Placeholder
}

void des_decrypt_block(unsigned long long block, unsigned long long key, unsigned long long *result) {
    // Simplified DES decryption
    *result = block ^ key; // Placeholder
}

void cbc_encrypt_3des(unsigned long long *blocks, int num_blocks, unsigned long long key1, unsigned long long key2, unsigned long long key3, unsigned long long iv) {
    unsigned long long prev = iv;
    
    for (int i = 0; i < num_blocks; i++) {
        blocks[i] ^= prev;
        des_encrypt_block(blocks[i], key1, &blocks[i]);
        des_decrypt_block(blocks[i], key2, &blocks[i]);
        des_encrypt_block(blocks[i], key3, &blocks[i]);
        prev = blocks[i];
    }
}

void cbc_decrypt_3des(unsigned long long *blocks, int num_blocks, unsigned long long key1, unsigned long long key2, unsigned long long key3, unsigned long long iv) {
    unsigned long long prev = iv;
    
    for (int i = 0; i < num_blocks; i++) {
        unsigned long long temp = blocks[i];
        des_decrypt_block(blocks[i], key3, &blocks[i]);
        des_encrypt_block(blocks[i], key2, &blocks[i]);
        des_decrypt_block(blocks[i], key1, &blocks[i]);
        blocks[i] ^= prev;
        prev = temp;
    }
}

int main() {
    printf("CBC Mode with 3DES\n\n");
    
    unsigned long long plaintext[] = {0x0123456789ABCDEF, 0xFEDCBA9876543210};
    unsigned long long ciphertext[2];
    unsigned long long decrypted[2];
    unsigned long long key1 = 0x133457799BBCDFF1;
    unsigned long long key2 = 0x0E329232EA6D0D73;
    unsigned long long key3 = 0x133457799BBCDFF1;
    unsigned long long iv = 0x123456789ABCDEF0;
    
    printf("Plaintext blocks:\n");
    for (int i = 0; i < 2; i++) {
        printf("Block %d: 0x%016llX\n", i+1, plaintext[i]);
    }
    
    // Encrypt
    memcpy(ciphertext, plaintext, sizeof(plaintext));
    cbc_encrypt_3des(ciphertext, 2, key1, key2, key3, iv);
    
    printf("\nCiphertext blocks:\n");
    for (int i = 0; i < 2; i++) {
        printf("Block %d: 0x%016llX\n", i+1, ciphertext[i]);
    }
    
    // Decrypt
    memcpy(decrypted, ciphertext, sizeof(ciphertext));
    cbc_decrypt_3des(decrypted, 2, key1, key2, key3, iv);
    
    printf("\nDecrypted blocks:\n");
    for (int i = 0; i < 2; i++) {
        printf("Block %d: 0x%016llX\n", i+1, decrypted[i]);
    }
    
    printf("\nComparison:\n");
    printf("a. For security: 3DES is more secure than DES\n");
    printf("b. For performance: DES is faster than 3DES\n");
    
    return 0;
}
