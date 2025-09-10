#include <stdio.h>
#include <string.h>
#include <ctype.h>

void count_frequencies(char *text, int freq[26]) {
    int i;
    for (i = 0; i < 26; i++) freq[i] = 0;
    
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            freq[tolower(text[i]) - 'a']++;
        }
    }
}

void find_most_frequent(int freq[26], int *max1, int *max2, int *max3) {
    int i;
    *max1 = *max2 = *max3 = 0;
    
    for (i = 0; i < 26; i++) {
        if (freq[i] > freq[*max1]) {
            *max3 = *max2;
            *max2 = *max1;
            *max1 = i;
        } else if (freq[i] > freq[*max2]) {
            *max3 = *max2;
            *max2 = i;
        } else if (freq[i] > freq[*max3]) {
            *max3 = i;
        }
    }
}

void substitution_decrypt(char *ciphertext, char *key) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char target = tolower(ciphertext[i]);
            
            // Find position in key
            for (int j = 0; j < 26; j++) {
                if (tolower(key[j]) == target) {
                    ciphertext[i] = isupper(ciphertext[i]) ? 
                                   (j + 'A') : (j + 'a');
                    break;
                }
            }
        }
    }
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡8†83(88)5†;46(;88*96*?;8)‡(;485);5†2:‡(;4956*2(5—4)8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    int freq[26];
    int max1, max2, max3;
    
    printf("Ciphertext: %s\n\n", ciphertext);
    
    // Count frequencies
    count_frequencies(ciphertext, freq);
    
    // Find most frequent characters
    find_most_frequent(freq, &max1, &max2, &max3);
    
    printf("Frequency Analysis:\n");
    printf("Most frequent: %c (%d times)\n", max1 + 'A', freq[max1]);
    printf("Second most frequent: %c (%d times)\n", max2 + 'A', freq[max2]);
    printf("Third most frequent: %c (%d times)\n", max3 + 'A', freq[max3]);
    
    // English letter frequencies: E, T, A, O, I, N, S, H, R, D, L, C, U, M, W, F, G, Y, P, B, V, K, J, X, Q, Z
    char english_freq[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    
    // Create initial key mapping
    char key[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Map most frequent ciphertext characters to most frequent English letters
    key[max1] = english_freq[0]; // E
    key[max2] = english_freq[1]; // T
    key[max3] = english_freq[2]; // A
    
    printf("\nInitial key mapping:\n");
    printf("Ciphertext: %c -> Plaintext: %c\n", max1 + 'A', english_freq[0]);
    printf("Ciphertext: %c -> Plaintext: %c\n", max2 + 'A', english_freq[1]);
    printf("Ciphertext: %c -> Plaintext: %c\n", max3 + 'A', english_freq[2]);
    
    // Try to decrypt with initial mapping
    char decrypted[1000];
    strcpy(decrypted, ciphertext);
    substitution_decrypt(decrypted, key);
    
    printf("\nInitial decryption attempt:\n%s\n", decrypted);
    
    // Look for common patterns
    printf("\nLooking for common English patterns...\n");
    printf("Note: This is a simplified approach. Full decryption would require\n");
    printf("more sophisticated pattern recognition and statistical analysis.\n");
    
    return 0;
}
