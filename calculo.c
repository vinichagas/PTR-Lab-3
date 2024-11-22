#include <math.h>
#include <stdio.h>

#include "calculo.h"

#define PI 3.14159265358979323846

double f(double x) { return x; }

double integrar(double valor, int a, double b, int n) {
  for (int i = 0; i < n; i++) {
    double t = a + i * (b - a) / n;
    valor += f(t) * (b - a) / n;
  }
  return valor;
}

Matrix* calcula_ut(int t) {
    Matrix* ut = cria_matriz(2, 1);

    // 1º Caso: para t < 0
    if (t < 0) {
        ut->dados[0][0] = 0;
        ut->dados[1][0] = 0;
    }
    // 2º Caso: para 0 ⩽ t < 10
    else if (0 <= t && t < 10) {
        ut->dados[0][0] = 1;
        ut->dados[1][0] = (0.2 * PI);
    }
    // 3º Caso: para t ⩾ 10
    else {
        ut->dados[0][0] = 1;
        ut->dados[0][0] = ((-0.2) * PI);
    }

    return ut;
}

// -> Função que calcula o valor da matriz x(t)
Matrix* calcula_xt(Matrix *ut, int t) {

    Matrix* xt = cria_matriz(3, 1);

    double x3 = ut->dados[1][0];

    // Setando os valores de x(t)
    if (t < 0) {
        xt->dados[0][0] = 0;
        xt->dados[1][0] = 0;
        xt->dados[2][0] = 0;

    } else if (t >= 0 && t < 10) {
        xt->dados[0][0] = -cos(x3); // sin(x3)
        xt->dados[1][0] = sin(x3);  // cos(x3)
        xt->dados[2][0] = 0.2 * PI; // falta integrar
        
        // integrando
        xt->dados[2][0] = integrar(xt->dados[2][0], 0, ut->dados[1][0], 100);
        
    } else if (t >= 10) {
        xt->dados[0][0] = -cos(x3);  // sin(x3)
        xt->dados[1][0] = sin(x3);   // cos(x3)
        xt->dados[2][0] = -0.2 * PI; // falta integrar
        
        // integrando
        xt->dados[2][0] = integrar(xt->dados[2][0], 0, ut->dados[1][0], 100);

    }

    return xt;
}

Matrix* calcula_yt(Matrix *xt) {

  // Criar matriz y(t)
  Matrix *yt = cria_matriz_identidade(3);

  yt = produto_matrizes(yt, xt);

  return yt;
}

Matrix* calcula_yft(Matrix *xt, Matrix *ut, double diametro) {

    // Criando e setando a matriz identidade
    Matrix* m_aux = cria_matriz_identidade(3);
    m_aux->dados[0][0] =  0.5 * diametro * cos(ut->dados[1][0]);
    m_aux->dados[1][1] =  0.5 * diametro * sin(ut->dados[1][0]);

    print_matriz(m_aux);

    // Retornando o valor de y pelo produto entre x(t) e a matriz identidade
    Matrix* yft = soma_matrizes(produto_matrizes(m_aux, xt), xt);
    libera_matriz(m_aux);

    return yft;
}

