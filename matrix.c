#include "matrix.h"

Matrix* cria_matriz(int linhas, int colunas) {
    // Para criar uma matriz, é preciso alocar memória
    Matrix* matriz = malloc(sizeof(Matrix));
    matriz->linhas = linhas;
    matriz->colunas = colunas;

    for (int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            matriz->dados[i][j] = 0;
        }
    }
    
    // Retornando a matriz
    return matriz; 
}

Matrix* cria_matriz_identidade(int n) {
    Matrix* matriz = malloc(sizeof(Matrix));
    matriz->linhas = n;
    matriz->colunas = n;

    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i == j) {
                matriz->dados[i][j] = 1;
            }
            else {
                matriz->dados[i][j] = 0;
            }
        }
    }
    
    // Retornando a matriz
    return matriz; 
}

void libera_matriz(Matrix* matriz) {
    // Liberando a memória da matriz em si
    free(matriz);
}

double get_matriz(Matrix* matriz, int linha, int coluna) {
    return matriz->dados[linha][coluna];
}

void set_matriz(Matrix* matriz, int linha, int coluna, double valor) {
    matriz->dados[linha][coluna] = valor;
}

Matrix* soma_matrizes(Matrix* matriz1, Matrix* matriz2) {
    
    // Caso a ordem das matrizes seja diferente...
    if (matriz1->linhas != matriz2->linhas || matriz1->colunas != matriz2->colunas) {
        printf("Matrizes de ordem diferente não podem ser somadas!\n\n");
        return NULL;
    }   

    // Criando uma nova matriz resultante da soma
    Matrix* soma = cria_matriz(matriz1->linhas, matriz1->colunas);

    // Realizando a operação
    for (unsigned i=0; i < matriz1->linhas; i++) {
        for (unsigned j=0; j < matriz1->colunas; j++) {
            soma->dados[i][j] = matriz1->dados[i][j] + matriz2->dados[i][j];
        }
    }

    // Retornando a matriz resultante da soma
    return soma;
}

Matrix* subtracao_matrizes(Matrix* matriz1, Matrix* matriz2) {

    // Caso a ordem das matrizes seja diferente...
    if (matriz1->linhas != matriz2->linhas || matriz1->colunas != matriz2->colunas) {
        printf("Matrizes de ordem diferente não podem ser subtraidas!\n\n");
        return NULL;
    } 

    // Criando uma nova matriz resultante da subtração
    Matrix* sub = cria_matriz(matriz1->linhas, matriz1->colunas);

    // Realizando a operação
    for (unsigned i=0; i < matriz1->linhas; i++) {
        for (unsigned j=0; j < matriz1->colunas; j++) {
            sub->dados[i][j] = matriz1->dados[i][j] - matriz2->dados[i][j];
        }
    }

    // Retornando a matriz resultante da subtração
    return sub;
}

Matrix* produto_matrizes(Matrix* matriz1, Matrix* matriz2) {
    
    // Se o número de colunas de uma matriz for diferente do número de linhas da outra...
    if (matriz1->colunas != matriz2->linhas) {
        printf("O produto entre as matrizes não pode ser realizado!\n\n");
        return NULL;
    }
    
    // Criando uma nova matriz resultante do produto
    Matrix* produto = cria_matriz(matriz1->linhas, matriz2->colunas);

    // Realizando a operação
    for (unsigned i=0; i < matriz1->linhas; i++) {
        for (unsigned j=0; j < matriz2->colunas; j++) {
            produto->dados[i][j] = 0;
            for (unsigned k=0; k < matriz1->colunas; k++) {
                produto->dados[i][j] += matriz1->dados[i][k] * matriz2->dados[k][j];
            }      
        }
    }

    // Retornando a matriz resultante do produto
    return produto;
}

Matrix* soma_matriz_escalar(Matrix* matriz, double escalar) {
    // Criando uma nova matriz resultante da soma
    Matrix* soma = cria_matriz(matriz->linhas, matriz->colunas);

    // Realizando a operação
    for (unsigned i=0; i < matriz->linhas; i++) {
        for (unsigned j=0; j < matriz->colunas; j++) {
            soma->dados[i][j] = matriz->dados[i][j] + escalar;
        }
    }

    // Retornando a matriz resultante da soma
    return soma;
}

Matrix* subtracao_matriz_escalar(Matrix* matriz, double escalar) {
    // Criando uma nova matriz resultante da subtração
    Matrix* sub = cria_matriz(matriz->linhas, matriz->colunas);

    // Realizando a operação
    for (unsigned i=0; i < matriz->linhas; i++) {
        for (unsigned j=0; j < matriz->colunas; j++) {
            sub->dados[i][j] = matriz->dados[i][j] - escalar;
        }
    }

    // Retornando a matriz resultante da subtração
    return sub;
}

Matrix* produto_matriz_escalar(Matrix* matriz, double escalar) {
    // Criando uma nova matriz resultante do produto
    Matrix* produto = cria_matriz(matriz->linhas, matriz->colunas);

    // Realizando a operação
    for (unsigned i=0; i < matriz->linhas; i++) {
        for (unsigned j=0; j < matriz->colunas; j++) {
            produto->dados[i][j] = matriz->dados[i][j] * escalar;      
        }
    }

    // Retornando a matriz resultante do produto
    return produto;
}

Matrix* matriz_transposta(Matrix* matriz) {
    // Criando uma nova matriz que será a matriz transposta da atual
    Matrix* transposta = cria_matriz(matriz->colunas, matriz->linhas);

    // Realizando a operação
    for (unsigned i=0; i < matriz->linhas; i++) {
        for (unsigned j=0; j < matriz->colunas; j++) {
            transposta->dados[j][i] = matriz->dados[i][j];
        }
    }

    // Retornando a matriz já transposta
    return transposta;
}

double determinante_matriz(Matrix* matriz) {
    double determinante = 0;
    
    // Se a matriz não possui o número de linhas e colunas iguais...
    if (matriz->linhas != matriz->colunas) {
        // A matriz não é quadrada, e por isso não possui determinante
        printf("A matriz em questão não possui determinante, retornando valor 0\n");
        return 0;
    }

    // Se a matriz for de 1ª ordem (possui um único dado)...
    if (matriz->linhas == 1 && matriz->colunas == 1) {
        // Retorna o único elemento da matriz em questão
        return matriz->dados[0][0];
    }
    
    // Para matrizes de ordem superior...
    for (unsigned i=0; i < matriz->colunas; i++) {

        // Utilizando o método de Laplace, será preciso criar uma sub-matriz
        Matrix* submatriz = cria_matriz(matriz->linhas-1, matriz->colunas-1);

        // Preenchendo os dados na sub-matriz, eliminando uma linha e uma coluna da matriz original
        for (unsigned j=1; j < matriz->linhas; j++) {
            for (unsigned k = 0; k < i; k++) {
                submatriz->dados[j - 1][k] = matriz->dados[j][k];
            }
            for (unsigned k=i+1; k < matriz->colunas; k++) {
                submatriz->dados[j - 1][k - 1] = matriz->dados[j][k];
            }
        }

        // Calculando o determinante pela soma dos produtos dos dados da 1ª linha com os 
        // determinantes das sub-matrizes correspondentes, com os sinais trocados
        determinante += pow(-1, i) * matriz->dados[0][i] * determinante_matriz(submatriz);
        libera_matriz(submatriz);
    }

    // Retornando o valor (double) do determinante da matriz
    return determinante;
}

Matrix* matriz_inversa(Matrix* matriz) {

    // Calculando o determinante da matriz dada
    double determinante = determinante_matriz(matriz);

    // Se o determinante for igual a 0...
    if (determinante == 0) {
        printf("A matriz em questão não pode ser invertida, pois seu determinante é igual a 0!\n\n");
        return NULL;
    }

    // Para outros casos, uma matriz cofator será criada com o mesmo número de linhas e colunas da original
    Matrix* matriz_cofator = cria_matriz(matriz->linhas, matriz->colunas);

    // Percorrendo cada elemento da matriz original...
    for (unsigned i1=0; i1 < matriz->linhas; i1++) {
        for (unsigned j1=0; j1 < matriz->colunas; j1++) {

            // Uma submatriz será criada, semelhante àquela vista na função "determinante_matriz()"
            Matrix* submatriz = cria_matriz(matriz->linhas-1, matriz->colunas-1);

            // Percorrendo cada elemento da matriz original novamente...
            for (unsigned i2=0; i2 < matriz->linhas; i2++) {
                for (unsigned j2=0; j2 < matriz->colunas; j2++) {

                    // Se os índices do dado na matriz não forem iguais aos índices do elemento da sub-matriz...
                    if (i2 != i1 && j2 != j1) {
                        int sub_i, sub_j;
                        
                        // Determinando a linha em que o elemento será copiado para a sub-matriz
                        if (i2 < i1) {sub_i = i2;} 
                        else {sub_i = i2-1;}

                        // Determinando a coluna em que o elemento será copiado para a sub-matriz
                        if (j2 < j1) {sub_j = j2;} 
                        else {sub_j = j2-1;}
                        
                        // O elemento em questão é copiado para a sub-matriz
                        submatriz->dados[sub_i][sub_j] = matriz->dados[i2][j2];
                    }
                }
            }

            // O determinante da sub-matriz é multiplicado pelo sinal do cofator 
            // e o resultado é armazenado no elemento correspondente da matriz do cofator
            matriz_cofator->dados[i1][j1] = pow(-1, i1+j1) * determinante_matriz(submatriz);
            libera_matriz(submatriz);
        }
    }

    // Transpõe o cofator para obter a matriz adjunta
    Matrix* matriz_adjunta = matriz_transposta(matriz_cofator);
    libera_matriz(matriz_cofator);

    // Faz-se a multiplicação escalar da matriz adjunta pelo inverso do determinante, obtendo assim a inversa
    Matrix* matriz_inversa = produto_matriz_escalar(matriz_adjunta, 1 / determinante);
    libera_matriz(matriz_adjunta);
    
    // Retornando a matriz inversa
    return matriz_inversa;
}

void print_matriz(Matrix* matriz) {

    // Se a matriz não existir, não imprimirá nada
    if (!matriz) {return;}

    // Percorrendo a matriz
    for (unsigned i = 0; i < matriz->linhas; i++) {
        for (unsigned j = 0; j < matriz->colunas; j++) {
            printf("%lf ", get_matriz(matriz, i, j)); // Imprimindo cada elemento
        }
        printf("\n");
    }
    printf("\n");
}
