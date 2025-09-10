#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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

void mono_decrypt(char *ciphertext, char *key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char target = tolower(ciphertext[i]);
            for (int j = 0; j < 26; j++) {
                if (tolower(key[j]) == target) {
                    ciphertext[i] = isupper(ciphertext[i]) ? (j + 'A') : (j + 'a');
                    break;
                }
            }
        }
    }
}

int main() {
    char ciphertext[] = "QEB NRFZH YOLTK CLU GRJMP LSBO QEB IXWV ALD";
    int top_n = 3;
    
    printf("Monoalphabetic Frequency Attack (Third Implementation)\n\n");
    printf("Ciphertext: %s\n", ciphertext);
    printf("Finding top %d possible plaintexts...\n\n", top_n);
    
    struct result { double score; char key[27]; char plaintext[1000]; } results[200];
    int count = 0;
    
    for (int i = 0; i < 200; i++) {
        char key[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int j = 0; j < 26; j++) {
            int k = rand() % 26;
            char temp = key[j]; key[j] = key[k]; key[k] = temp;
        }
        
        char test[1000]; strcpy(test, ciphertext);
        mono_decrypt(test, key);
        
        results[count].score = calculate_score(test);
        strcpy(results[count].key, key);
        strcpy(results[count].plaintext, test);
        count++;
    }
    
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (results[i].score > results[j].score) {
                struct result temp = results[i]; results[i] = results[j]; results[j] = temp;
            }
        }
    }
    
    printf("Top %d results:\n", top_n);
    for (int i = 0; i < top_n && i < count; i++) {
        printf("%d. Score: %.2f\nText: %s\n\n", i+1, results[i].score, results[i].plaintext);
    }
    
    return 0;
}
