#include <stdio.h>
#include <string.h>
#include <ctype.h>

void count_frequencies(char *text, int freq[26]) {
    for (int i = 0; i < 26; i++) freq[i] = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) freq[tolower(text[i]) - 'a']++;
    }
}

double calculate_score(char *text) {
    double english_freq[] = {8.2,1.5,2.8,4.3,12.7,2.2,2.0,6.1,7.0,0.1,0.8,4.0,2.4,6.7,7.5,1.9,0.1,6.0,6.3,9.1,2.8,1.0,2.4,0.1,2.0,0.1};
    int freq[26]; count_frequencies(text, freq);
    int total = 0; for (int i = 0; i < 26; i++) total += freq[i];
    double score = 0; for (int i = 0; i < 26; i++) {
        double observed = (double)freq[i] / total * 100;
        score += (observed - english_freq[i]) * (observed - english_freq[i]);
    } return score;
}

void caesar_decrypt(char *ciphertext, int key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            ciphertext[i] = ((ciphertext[i] - base - key + 26) % 26) + base;
        }
    }
}

int main() {
    char ciphertext[] = "WKLV LV D WHVW PHVVDJH";
    int top_n = 5;
    
    printf("Additive Cipher Frequency Attack (Second Implementation)\n\n");
    printf("Ciphertext: %s\n", ciphertext);
    printf("Finding top %d possible plaintexts...\n\n", top_n);
    
    struct result { int key; double score; char plaintext[1000]; } results[26];
    
    for (int key = 0; key < 26; key++) {
        char test[1000]; strcpy(test, ciphertext);
        caesar_decrypt(test, key);
        
        results[key].key = key;
        results[key].score = calculate_score(test);
        strcpy(results[key].plaintext, test);
    }
    
    for (int i = 0; i < 26; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (results[i].score > results[j].score) {
                struct result temp = results[i]; results[i] = results[j]; results[j] = temp;
            }
        }
    }
    
    printf("Top %d results:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        printf("%d. Key: %d, Score: %.2f\n", i+1, results[i].key, results[i].score);
        printf("   Plaintext: %s\n\n", results[i].plaintext);
    }
    
    return 0;
}
