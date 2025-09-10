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

void playfair_encrypt(char *plaintext, char matrix[5][5]) {
    int i, len = strlen(plaintext);
    char processed[1000];
    int j = 0;
    
    // Process plaintext: remove spaces, add X for double letters
    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char c = toupper(plaintext[i]);
            if (c == 'J') c = 'I';
            
            if (j > 0 && processed[j-1] == c) {
                processed[j++] = 'X';
            }
            processed[j++] = c;
        }
    }
    
    // Add X if odd length
    if (j % 2 == 1) {
        processed[j++] = 'X';
    }
    processed[j] = '\0';
    
    // Encrypt pairs
    for (i = 0; i < j; i += 2) {
        int row1, col1, row2, col2;
        find_position(matrix, processed[i], &row1, &col1);
        find_position(matrix, processed[i+1], &row2, &col2);
        
        if (row1 == row2) {
            processed[i] = matrix[row1][(col1 + 1) % 5];
            processed[i+1] = matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            processed[i] = matrix[(row1 + 1) % 5][col1];
            processed[i+1] = matrix[(row2 + 1) % 5][col2];
        } else {
            processed[i] = matrix[row1][col2];
            processed[i+1] = matrix[row2][col1];
        }
    }
    
    strcpy(plaintext, processed);
}

int main() {
    char keyword[] = "MFHIJKUNOPQZVWXYELARGDSTBC";
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char matrix[5][5];
    
    printf("Playfair Encryption with Given Matrix\n");
    printf("Keyword: %s\n", keyword);
    printf("Message: %s\n\n", message);
    
    create_playfair_matrix(keyword, matrix);
    
    printf("Playfair Matrix:\n");
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    
    printf("\nEncrypting...\n");
    
    char encrypted[1000];
    strcpy(encrypted, message);
    playfair_encrypt(encrypted, matrix);
    
    printf("Encrypted message: %s\n", encrypted);
    
    // Format the encrypted message for better readability
    printf("\nFormatted ciphertext:\n");
    for (i = 0; encrypted[i] != '\0'; i++) {
        printf("%c", encrypted[i]);
        if ((i + 1) % 5 == 0) printf(" ");
    }
    printf("\n");
    
    return 0;
}
