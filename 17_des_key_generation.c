#include <stdio.h>
#include <string.h>

void des_key_schedule(unsigned long long key, unsigned long long subkeys[16]) {
    int pc1[] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
    int pc2[] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
    int shifts[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    
    unsigned long long permuted = 0;
    for (int i = 0; i < 56; i++) {
        if (key & (1ULL << (64 - pc1[i]))) permuted |= (1ULL << (55 - i));
    }
    
    unsigned int left = (permuted >> 28) & 0xFFFFFFF;
    unsigned int right = permuted & 0xFFFFFFF;
    
    for (int round = 0; round < 16; round++) {
        left = ((left << shifts[round]) | (left >> (28 - shifts[round]))) & 0xFFFFFFF;
        right = ((right << shifts[round]) | (right >> (28 - shifts[round]))) & 0xFFFFFFF;
        
        unsigned long long combined = ((unsigned long long)left << 28) | right;
        subkeys[round] = 0;
        
        for (int i = 0; i < 48; i++) {
            if (combined & (1ULL << (56 - pc2[i]))) subkeys[round] |= (1ULL << (47 - i));
        }
    }
}

void des_decrypt_key_schedule(unsigned long long key, unsigned long long subkeys[16]) {
    des_key_schedule(key, subkeys);
    // Reverse order for decryption
    for (int i = 0; i < 8; i++) {
        unsigned long long temp = subkeys[i];
        subkeys[i] = subkeys[15-i];
        subkeys[15-i] = temp;
    }
}

int main() {
    unsigned long long key = 0x133457799BBCDFF1;
    unsigned long long encrypt_keys[16], decrypt_keys[16];
    
    printf("DES Key Generation Analysis\n\n");
    printf("Original key: 0x%016llX\n\n", key);
    
    des_key_schedule(key, encrypt_keys);
    des_decrypt_key_schedule(key, decrypt_keys);
    
    printf("Encryption subkeys (K1-K16):\n");
    for (int i = 0; i < 16; i++) {
        printf("K%2d: 0x%012llX\n", i+1, encrypt_keys[i]);
    }
    
    printf("\nDecryption subkeys (K16-K1):\n");
    for (int i = 0; i < 16; i++) {
        printf("K%2d: 0x%012llX\n", 16-i, decrypt_keys[i]);
    }
    
    printf("\nKey generation for decryption uses reverse order of encryption keys.\n");
    return 0;
}
