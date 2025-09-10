#include <stdio.h>
#include <string.h>
#include <ctype.h>

void create_playfair_matrix(char *keyword, char matrix[5][5]) {
    int i, j, k = 0;
    int used[26] = {0};
    
    // Add keyword letters
    for (i = 0; keyword[i] != '\0' && k < 25; i++) {
        char c = toupper(keyword[i]);
        if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
            if (c == 'J') c = 'I'; // Replace J with I
            matrix[k/5][k%5] = c;
            used[c - 'A'] = 1;
            k++;
        }
    }
    
    // Add remaining letters
    for (i = 0; i < 26 && k < 25; i++) {
        if (!used[i] && i != 9) { // Skip J
            matrix[k/5][k%5] = 'A' + i;
            k++;
        }
    }
}

void find_position(char matrix[5][5], char c, int *row, int *col) {
    int i, j;
    if (c == 'J') c = 'I';
    
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void playfair_decrypt(char *ciphertext, char matrix[5][5]) {
    int i, len = strlen(ciphertext);
    
    // Decrypt pairs
    for (i = 0; i < len; i += 2) {
        if (i + 1 < len) {
            int row1, col1, row2, col2;
            find_position(matrix, ciphertext[i], &row1, &col1);
            find_position(matrix, ciphertext[i+1], &row2, &col2);
            
            if (row1 == row2) {
                ciphertext[i] = matrix[row1][(col1 - 1 + 5) % 5];
                ciphertext[i+1] = matrix[row2][(col2 - 1 + 5) % 5];
            } else if (col1 == col2) {
                ciphertext[i] = matrix[(row1 - 1 + 5) % 5][col1];
                ciphertext[i+1] = matrix[(row2 - 1 + 5) % 5][col2];
            } else {
                ciphertext[i] = matrix[row1][col2];
                ciphertext[i+1] = matrix[row2][col1];
            }
        }
    }
}

int main() {
    char keyword[] = "PT109"; // From the problem context
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOYUWRHEBAAHYUSEDQ";
    char matrix[5][5];
    
    printf("PT-109 Playfair Decryption\n");
    printf("Keyword: %s\n", keyword);
    printf("Ciphertext: %s\n\n", ciphertext);
    
    create_playfair_matrix(keyword, matrix);
    
    printf("Playfair Matrix:\n");
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    
    printf("\nDecrypting...\n");
    
    char decrypted[1000];
    strcpy(decrypted, ciphertext);
    playfair_decrypt(decrypted, matrix);
    
    printf("Decrypted message: %s\n", decrypted);
    
    // Format the decrypted message for better readability
    printf("\nFormatted message:\n");
    for (i = 0; decrypted[i] != '\0'; i++) {
        printf("%c", decrypted[i]);
        if ((i + 1) % 5 == 0) printf(" ");
    }
    printf("\n");
    
    return 0;
}
