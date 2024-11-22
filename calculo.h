// Criando a interface "calculo.h" para o cálculo do sistema de controle a ser feito
#ifndef CALCULO_H
#define CALCULO_H

#include "matrix.h"

// Função que calcula o valor da matriz u(t)
Matrix* calcula_ut(int t);

// Função que calcula o valor da matriz x(t)
Matrix* calcula_xt(Matrix *ut, int t);

// Função que calcula o valor da matriz y(t)
Matrix* calcula_yt(Matrix *xt);

// Função que calcula o valor da matriz yf(t)
Matrix* calcula_yft(Matrix *xt, Matrix *ut, double diametro);

#endif
