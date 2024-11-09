#include <math.h>
#include <stdio.h>

#include "calculo.h"

#define PI 3.14159265358979323846

Matrix* calcula_ut(int t) {
    Matrix* ut = cria_matriz(2, 1);

    // 1º Caso: para t < 0
    if (t < 0) {
        set_matriz(u, 0, 0, 0);
        set_matriz(u, 1, 0, 0);
        return ut;
    }

    // 2º Caso: para 0 ⩽ t < 10
    if (0 <= t && t < 10) {
        set_matriz(u, 0, 0, 1);
        set_matriz(u, 1, 0, (0.2 * PI));
        return ut;
    }

    // 3º Caso: para t ⩾ 10
    else {
        set_matriz(u, 0, 0, 1);
        set_matriz(u, 1, 0, ((-0.2) * PI));
        return ut;
    }

}

// Declarando o valor de x3 que compõe a matriz x(t)
double x3(double x) {return x;}

// -> Função que calcula o valor da matriz x(t)
Matrix* calcula_xt(Matrix *ut, int t) {

    // É preciso calcular a integral de x_derivada, obtendo assim x(t) 
    Integral* integral = cria_integral(0, get_matriz(&u, 1, 0), 1000);
    Matrix* xt = cria_matriz(3, 1);

    // Setando os valores de x(t)
    set_matriz(xt, 0, 0, (-cos(get_matriz(&u, 1, 0))) + cos(0));
    set_matriz(xt, 1, 0, (sin(get_matriz(&u, 1, 0))) - sin(0));
    set_matriz(xt, 2, 0, calcula_integral(integral, x3));

    // Liberando a integral da memória
    libera_integral(integral);

    return xt;
}

// Função que calcula o valor da matriz y(t)
Matrix* calcula_yt(Matrix *xt) {
    
    // Criando e setando a matriz identidade
    Matrix* m_id = cria_matriz_identidade(3);

    // Retornando o valor de y pelo produto entre x(t) e a matriz identidade
    Matrix* yt = produto_matrizes(m_id, &xt);
    
    // Liberando a matriz identidade da memória
    libera_matriz(m_id);

    return yt;
}

Matrix* calcula_yft(Matrix *xt, Matrix *u, double diametro) {
    // Criando a matriz x(t)
    Matrix* x = calcula_x(t, u);
    
    // Criando e setando a matriz identidade
    Matrix* m_aux = cria_matriz(3, 3);
    set_matriz(m_aux, 0, 0, 0.5 * diametro * cos(get_matriz(&x, 2, 0)));
    set_matriz(m_aux, 0, 1, 0);
    set_matriz(m_aux, 0, 2, 0);
    set_matriz(m_aux, 1, 0, 0);
    set_matriz(m_aux, 1, 1, 0.5 * diametro * sin(get_matriz(&x, 2, 0)));
    set_matriz(m_aux, 1, 2, 0);
    set_matriz(m_aux, 2, 0, 0);
    set_matriz(m_aux, 2, 1, 0);
    set_matriz(m_aux, 2, 2, 1);

    // Retornando o valor de y pelo produto entre x(t) e a matriz identidade
    Matrix* yf = soma_matrizes(produto_matrizes(m_aux, &x), &x);
    return yf;
}

