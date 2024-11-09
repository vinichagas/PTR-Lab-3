// Criando a interface "calculo.h" para o cálculo do sistema de controle a ser feito
#ifndef CALCULO_H
#define CALCULO_H
#include "matrix.h"
#include "integral.h"

// Definição da estrutura para os argumentos a serem passados para a thread
typedef struct ThreadArgs {
  Matrix *u;
  Matrix *xt;
  Matrix *yt;
  Matrix *yft;
  int t;
  void (*save_results)(Matrix*, Matrix*, Matrix*, Matrix*, int, const char*);
} ThreadArgs;

// Função que calcula o valor da matriz u(t)
Matrix* calcula_ut(int t);

// Função que calcula o valor da matriz x(t)
Matrix* calcula_xt(Matrix *ut, int t);

// Função que calcula o valor da matriz y(t)
Matrix* calcula_yt(Matrix *xt);

// Função que calcula o valor da matriz yf(t)
Matrix* calcula_yft(Matrix *xt, Matrix *u, double diametro);

#endif
