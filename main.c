//--------------------------------------------------------------------------------------------
//                      PTR - Laboratório 2 - Simulação de Sistemas com Threads
//
// Discente : Vinícius Fernandes das Chagas (22050485)
// Docente  : Prof. André Luis Cavalcante
//
//--------------------------------------------------------------------------------------------

// Declarando as bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

#include "calculo.h"
#include "matrix.h"
#include "simulacao.h"


// Declaração de variáveis globais para as threads
double t;        // tempo decorrido do programa
Matrix* u, yft;  // variáveis u e yft
double diametro; // tamanho do diâmetro do robô



// --------------------------------------------------------------------


void* simulate_thread(void* arg) {
  // Cast the argument to the appropriate type
  ThreadArgs *args = (ThreadArgs*)arg;

  // Extract matrices from arguments
  Matrix *u = args->u;
  Matrix *xt = args->xt;
  Matrix *yt = args->yt;
  Matrix *yft = args->yft;
  
  int t = args->t;

  simulate(u, xt, yt, yft, t);
  printf("\n");

  pthread_exit(NULL);
}

void* calculate_thread(void* arg) {
  ThreadArgs *args = (ThreadArgs*)arg;
  
  Matrix *u = args->u;
  Matrix *xt = args->xt;
  Matrix *yft = args->yft;

  int t = args->t;

  for (int i = 0; i <= t; i++) {
    u  = calcula_ut(i);
    yft = calcula_yft(xt, u, 5);  // Calculate yft here

    usleep(30000);
  }

  args->save_results(u, xt, NULL, yft, t, "thread_results.csv"); // Pass matrices and filename
  
  //usleep(30000);
  pthread_exit(NULL);
}

// --------------------------------------------------------------------




// Função que será executada pela thread 1 quando ela for iniciada no main
void *tarefa_1(void *arg) {
    // Mensagem para sinalizar que a tarefa começou
    printf("Tarefa 1 começou!\n");

    // Função para calcular u(t)
    u = calcula_ut(t);

    // Aguarda 30 ms
    usleep(30000); 

    // Mensagem para sinalizar que a tarefa terminou
    printf("Tarefa 1 terminou!\n");
}


// Função que será executada pela thread 2 quando ela for iniciada no main
void *tarefa_2(void *arg) {
    // Mensagem para sinalizar que a tarefa começou
    printf("Tarefa 2 começou!\n");

    // Função para calcular u(t)
    u = calcula_ut(t);

    // Função para calcular x(t)

    // Função para calcular yft(t)
    yft = calcula_yft(xt, u, diametro);

    // Aguarda 50 ms
    usleep(50000); 

    // Mensagem para sinalizar que a tarefa terminou
    printf("Tarefa 2 terminou!\n");
}


// Função que imprime a saída para a simulação
void escrever_linha(char* nome_arquivo, int t, Matrix u, Matrix yft) {
    FILE* arquivo;
    
    // Se o arquivo for aberto com sucesso, escrever a string em uma linha
    if ((arquivo = fopen(nome_arquivo, "a")) != NULL) {
        fprintf(arquivo, "t = %d\tuT = [%.2lf, %.2lf]\tyftT = [%.2lf, %.2lf, %.2lf]\n",  
                          t, 
                          get_matriz(&u, 0, 0), get_matriz(&u, 1, 0), 
                          get_matriz(&yft, 0, 0), get_matriz(&yft, 1, 0), get_matriz(&yft, 2, 0));
    }

    fclose(arquivo);
} 


// Função principal do programa
int main() {
    
    t = 0;                                  // variável que armazena o tempo decorrido
    char nome_arquivo[50];                  // nome do arquivo (tamanho limite: 50)
    pthread_t thread_1, thread_2;           // declaração das duas threads


    // Criação do menu inicial
    printf("\n----------------------------------------- Sistema de Robô Móvel -----------------------------------------\n\n");

    printf("Informe o diâmetro do robô (em cm): ");
    scanf("%lf", &diametro); // escaneando o tamanho do diâmetro do robô
    printf("\n");

    printf("Digite o nome do arquivo, seguido de .txt (Se o arquivo já existir, os dados irão para o final do arquivo):");
    printf("\n\n=> ");
    scanf("%s", nome_arquivo); // escaneando o nome do arquivo
    printf("\n");


    // Enquanto o tempo limite (20s) não for atingido...
    while (t <= 20.0) {

        // 2º) Cria as duas threads
        pthread_create(&thread_1, NULL, tarefa_1, NULL);
        pthread_create(&thread_2, NULL, tarefa_2, NULL);

        // 3º) Espera pelo término das duas threads
        pthread_join(thread_1, NULL);
        pthread_join(thread_2, NULL);

        // 4º) Escreve no arquivo o resultado das operações
        escrever_linha(nome_arquivo, t, u, yft);

        // 5º) Incrementa a variável responsável pelo tempo decorrido do programa
        t++;

        // 8º) Começa um loop de espera até completar 1 segundo
        sleep(1);
    }


    // Mensagens de verificação que aparecem no final do programa
    printf("\nOBS: As funções u(t) e yft(t) foram impressas transpostas (uT e yftT)\n\n");

    printf("Operações feitas com sucesso!!\n\n");

    return 0;
}
