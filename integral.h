// Criando a interface "integral.h" para a ADT Integral
#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <stdlib.h>

typedef struct {
    double a; // limite inferior
    double b; // limite superior
    int nsub; // número de subintervalos
} Integral;

// -> Criando uma nova estrutura para uma integral
Integral* cria_integral(double a, double b, int nsub);

// -> Calculando a integral, utilizando a Regra do Trapézio
double calcula_integral(Integral* integral, double (*f)(double x));

// -> Liberando a memória
void libera_integral(Integral* integral);

#endif
