#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
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

void count_frequencies(char *text, int freq[26]) {
    int i;
    for (i = 0; i < 26; i++) freq[i] = 0;
    
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            freq[tolower(text[i]) - 'a']++;
        }
    }
}

void affine_decrypt(char *ciphertext, int a, int b) {
    int a_inv = mod_inverse(a, 26);
    int i;
    
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int c = tolower(ciphertext[i]) - 'a';
            int p = (a_inv * (c - b + 26)) % 26;
            ciphertext[i] = isupper(ciphertext[i]) ? 
                           (p + 'A') : (p + 'a');
        }
    }
}

int main() {
    char ciphertext[1000];
    int freq[26];
    int i, j, max_freq = 0, second_max = 0;
    int max_char = 0, second_char = 0;
    
    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;
    
    // Count frequencies
    count_frequencies(ciphertext, freq);
    
    // Find most frequent characters
    for (i = 0; i < 26; i++) {
        if (freq[i] > max_freq) {
            second_max = max_freq;
            second_char = max_char;
            max_freq = freq[i];
            max_char = i;
        } else if (freq[i] > second_max) {
            second_max = freq[i];
            second_char = i;
        }
    }
    
    printf("\nFrequency Analysis:\n");
    printf("Most frequent: %c (%d times)\n", max_char + 'A', max_freq);
    printf("Second most frequent: %c (%d times)\n", second_char + 'A', second_max);
    
    // Assume B maps to E and U maps to T
    int c1 = 1; // B = 1
    int p1 = 4; // E = 4
    int c2 = 20; // U = 20
    int p2 = 19; // T = 19
    
    // Solve: c1 = (a * p1 + b) mod 26
    //        c2 = (a * p2 + b) mod 26
    // This gives us: c1 - c2 = a * (p1 - p2) mod 26
    
    int diff_c = (c1 - c2 + 26) % 26;
    int diff_p = (p1 - p2 + 26) % 26;
    
    // Find 'a' such that diff_c = a * diff_p mod 26
    int a = -1;
    for (i = 1; i < 26; i++) {
        if (gcd(i, 26) == 1 && (i * diff_p) % 26 == diff_c) {
            a = i;
            break;
        }
    }
    
    if (a == -1) {
        printf("Could not find valid 'a' value\n");
        return 1;
    }
    
    int b = (c1 - a * p1 + 26) % 26;
    
    printf("\nFound parameters: a = %d, b = %d\n", a, b);
    
    // Decrypt
    char decrypted[1000];
    strcpy(decrypted, ciphertext);
    affine_decrypt(decrypted, a, b);
    printf("Decrypted message: %s\n", decrypted);
    
    return 0;
}
