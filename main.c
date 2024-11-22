//-----------------------------------------------------------------------------------
//
//              PTR - Laboratório 3 - Simulação de Sistemas com Threads
//
// Discente : Vinícius Fernandes das Chagas (22050485)
// Docente  : Prof. André Luis Cavalcante
//
//-----------------------------------------------------------------------------------

// Declarando as bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

#include "calculo.h"
#include "matrix.h"
#include "simulacao.h"

// Definição da estrutura para os argumentos a serem passados para a thread
typedef struct ThreadArgs {
  Matrix *ut;
  Matrix *xt;
  Matrix *yt;
  Matrix *yft;
  double diametro;
  int t;
  char *nome_arquivo;
} ThreadArgs;

// Função utilizada para simular o sistema em uma thread separada
void* thread_simula(void* arg) {

  // O ponteiro arg é convertido para um ponteiro ThreadArgs
  ThreadArgs *args = (ThreadArgs*)arg;

  // Parâmetros sendo extraídos da estrutura arg
  Matrix *ut = args->ut;
  Matrix *xt = args->xt;
  Matrix *yt = args->yt;
  Matrix *yft = args->yft;
  int t = args->t;
  double diametro = args->diametro;

  // A função simula é chamada para realizar a simulação
  simula(ut, xt, yt, yft, diametro, t);
  printf("\n");

  // Realizando a chamada para terminar a execução da thread
  pthread_exit(NULL);
}

// Função utilizada para calcular as matrizes do sistema em uma thread separada
void* thread_calcula(void* arg) {

  // O ponteiro arg é convertido para um ponteiro ThreadArgs
  ThreadArgs *args = (ThreadArgs*)arg;
  
  // Parâmetros sendo extraídos da estrutura arg
  Matrix *ut = args->ut;
  Matrix *xt = args->xt;
  Matrix *yt = args->yt;
  Matrix *yft = args->yft;
  int t = args->t;
  double diametro = args->diametro;

  // Calculando os valores das matrizes
  for (int i = 0; i < t+1; i++) {
    ut = calcula_ut(i);
    xt = calcula_xt(ut, i);
    yt = calcula_yt(xt);
    yft = calcula_yft(xt, ut, diametro);

    usleep(30000);

    // Salvando os resultados das matrizes e passando o nome do arquivo 
    // onde ficarão os resultados
    salva_resultados(ut, xt, yt, yft, i, args->nome_arquivo);
  }

  //salva_tabela_dados(t+1, args->nome_arquivo);

  // Realizando a chamada para terminar a execução da thread
  pthread_exit(NULL);
}

// Função principal do programa
int main() {
  
  int t = 20;             // variável que armazena o tempo decorrido
  char nome_arquivo[50];  // nome do arquivo (tamanho limite: 50)
  double diametro;

  // Criação do menu inicial
  printf("\n----------------------------------------- Sistema de Robô Móvel -----------------------------------------\n\n");

  printf("Informe o diâmetro do robô (em cm): ");
  scanf("%lf", &diametro); // escaneando o tamanho do diâmetro do robô
  printf("\n");

  printf("Digite o nome do arquivo, seguido de .txt (Se o arquivo já existir, os dados irão para o final do arquivo):");
  printf("\n(Arquivo padrão: 'saida.txt')");
  printf("\n\n=> ");
  scanf("%s", nome_arquivo); // escaneando o nome do arquivo
  printf("\n");

  // Criando as matrizes
  Matrix *ut = cria_matriz(2, 1);
  Matrix *xt = cria_matriz(3, 2);
  Matrix *yt = cria_matriz(3, 1);
  Matrix *yft = cria_matriz(3, 3);

  // Criando as threads
  ThreadArgs thread_args = { ut, xt, yt, yft, diametro, t, nome_arquivo};

  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, thread_simula, (void*)&thread_args);
  printf("\n\n");
  pthread_create(&thread2, NULL, thread_calcula, (void*)&thread_args);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  // Mensagens de verificação que aparecem no final do programa
  printf("\nOBS: As funções u(t) e yft(t) foram impressas transpostas (uT e yftT)\n\n");

  printf("Operações feitas com sucesso!!\n\n");

  // Gera o gráfico de yf(t)
  gera_grafico(nome_arquivo);

  libera_matriz(ut);
  libera_matriz(xt);
  libera_matriz(yt);
  libera_matriz(yft);

  return 0;
}
