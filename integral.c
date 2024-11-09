#include "integral.h"

Integral* cria_integral(double a, double b, int nsub) {
    // Criando e alocando memória para a nova integral
    Integral* integral = (Integral*)malloc(sizeof(Integral));

    integral->a    = a;    // Definindo o limite superior
    integral->b    = b;    // Definindo o limite inferior
    integral->nsub = nsub; // Definindo o subintervalo de integração

    return integral; // Retornando a integral
}

double calcula_integral(Integral* integral, double (*f)(double x)) {
    // Calculando o tamanho de cada subintervalo (h)
    double h = (integral->b - integral->a) / integral->nsub;

    // Calculando a média dos valores da função nos pontos inicial e final
    double sum = 0.5 * (f(integral->a) + f(integral->b));

    // Somando os valores da função nos pontos intermediários
    for (int i = 1; i < integral->nsub; i++) {
        sum += f(integral->a + i * h);
    }

    // Retorna a integral, que é obtida pelo produto da soma pelo tamanho do subintervalo
    return h * sum;
}

void libera_integral(Integral* integral) {
    free(integral); // liberando memória
}
