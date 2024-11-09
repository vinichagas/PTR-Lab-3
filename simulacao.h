
// Criando a interface para a simulação
#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdio.h>

#include "matrix.h"

// Função que faz a transposição e printa uma matriz
void transpose_and_print(Matrix *m);

// Função que realiza a simuacao do sistema, recebendo de paramentro
// 3 matrizes e um intevalo de tempo
void simulate(Matrix *ut, Matrix *xt, Matrix *yt, Matrix *yft, int t);

// Função que ajuda a salvar o resultado da simulação em um arquivo .txt
void print_matrix_txt(Matrix *m, FILE *fp);

// Função que salva o resultado da função <print_matrix_txt> no formato CSV
void save_simulation_results(Matrix *ut, Matrix *xt, Matrix *yt, Matrix *yft, int t, const char *filename);

#endif
