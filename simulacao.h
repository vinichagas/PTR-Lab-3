
// Criando a interface para a simulação
#ifndef SIMULACAO_H
#define SIMULACAO_H

#include <stdio.h>

#include "matrix.h"

typedef struct {
    double media;
    double var;
    double desv_pad;
    double min;
    double max;
    double q1;
    double q2;
    double q3;
} Dados;

// Função que realiza a simuacao do sistema, recebendo de paramentro 4 matrizes, o diâmetro e um intevalo de tempo
void simula(Matrix *ut, Matrix *xt, Matrix *yt, Matrix *yft, double diametro, int t);

// Função que salva o resultado da função <print_matrix_txt> no formato CSV
void salva_resultados(Matrix *ut, Matrix *xt, Matrix *yt, Matrix *yft, int t, const char *nome_arquivo);

// Função que gera o gráfico de yf(t)
void gera_grafico();

// Função que utiliza as outras funções e escreve os dados finais em uma tabela
void salva_tabela_dados(int tam, char *nome_arquivo);

#endif
