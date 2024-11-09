// Criando a interface "matrix.h" para a ADT Matrix (Matriz)
#ifndef MATRIX_H
#define MATRIX_H
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    double dados[4][4];
    int linhas;
    int colunas;
} Matrix;

// -> Cria uma nova matriz com o número de linhas e de colunas como parâmetros
Matrix* cria_matriz(int linhas, int colunas);

//-> Cria uma nova matriz identidade de tamanho n
Matrix* cria_matriz_identidade(int n);

// -> Libera da memória a matriz 
void libera_matriz(Matrix* matriz);

// -> Retorna o valor na posição especificada (linha e coluna) de uma matriz
double get_matriz(Matrix* matriz, int linha, int coluna);

// -> Define o valor na posição especificada (linha e coluna) de uma matriz
void set_matriz(Matrix* matriz, int linha, int coluna, double dado);

// -> Retorna a matriz resultante da soma de duas matrizes
Matrix* soma_matrizes(Matrix* matriz1, Matrix* matriz2);

// -> Retorna a matriz resultante da subtração de duas matrizes
Matrix* subtracao_matrizes(Matrix* matriz1, Matrix* matriz2);

// -> Retorna a matriz resultante do produto de duas matrizes
Matrix* produto_matrizes(Matrix* matriz1, Matrix* matriz2);

// -> Retorna a matriz resultante da soma de uma matriz por um escalar
Matrix* soma_matriz_escalar(Matrix* matriz, double escalar);

// -> Retorna a matriz resultante da subtração de uma matriz por um escalar
Matrix* subtracao_matriz_escalar(Matrix* matriz, double escalar);

// -> Retorna a matriz resultante do produto de uma matriz por um escalar
Matrix* produto_matriz_escalar(Matrix* matriz, double escalar);

// -> Retorna a transposta de uma matriz
Matrix* matriz_transposta(Matrix* matriz);

// -> Calcula e retorna o determinante de uma matriz
double determinante_matriz(Matrix* matriz);

// -> Retorna a inversa de uma matriz, se for possível
Matrix* matriz_inversa(Matrix* matriz);

// -> Imprime a matriz
void print_matriz(Matrix* matriz);

#endif