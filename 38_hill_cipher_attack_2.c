#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

void matrix_inverse(int matrix[2][2], int inv[2][2]) {
    int det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0] + 26) % 26;
    int det_inv = mod_inverse(det, 26);
    inv[0][0] = (matrix[1][1] * det_inv) % 26;
    inv[0][1] = ((-matrix[0][1] * det_inv) % 26 + 26) % 26;
    inv[1][0] = ((-matrix[1][0] * det_inv) % 26 + 26) % 26;
    inv[1][1] = (matrix[0][0] * det_inv) % 26;
}

void matrix_multiply(int a[2][2], int b[2][2], int result[2][2]) {
    result[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % 26;
    result[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % 26;
    result[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % 26;
    result[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % 26;
}

int main() {
    printf("Hill Cipher Attack (Second Implementation)\n\n");
    
    char plain1[] = "ab";
    char cipher1[] = "cd";
    char plain2[] = "ef";
    char cipher2[] = "gh";
    
    printf("Known plaintext-ciphertext pairs:\n");
    printf("Plain: %s -> Cipher: %s\n", plain1, cipher1);
    printf("Plain: %s -> Cipher: %s\n\n", plain2, cipher2);
    
    int p1[2] = {plain1[0] - 'a', plain1[1] - 'a'};
    int c1[2] = {cipher1[0] - 'a', cipher1[1] - 'a'};
    int p2[2] = {plain2[0] - 'a', plain2[1] - 'a'};
    int c2[2] = {cipher2[0] - 'a', cipher2[1] - 'a'};
    
    int P[2][2] = {{p1[0], p2[0]}, {p1[1], p2[1]}};
    int C[2][2] = {{c1[0], c2[0]}, {c1[1], c2[1]}};
    
    int P_inv[2][2];
    matrix_inverse(P, P_inv);
    
    int key[2][2];
    matrix_multiply(C, P_inv, key);
    
    printf("Recovered key matrix:\n");
    printf("[%d %d]\n", key[0][0], key[0][1]);
    printf("[%d %d]\n\n", key[1][0], key[1][1]);
    
    printf("Hill cipher is vulnerable to known plaintext attacks!\n");
    
    return 0;
}
