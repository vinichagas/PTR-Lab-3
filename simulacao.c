#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "simulacao.h"
#include "matrix.h"
#include "calculo.h"

#define PI 3.14159265358979323846

// Função que faz a transposição e printa uma matriz
void printa_transposta(Matrix *m) {
  Matrix *transposta = matriz_transposta(m);
  printf("[ ");
  for (int i = 0; i < transposta->linhas; i++) {
    for (int j = 0; j < transposta->colunas; j++) {
      printf("%.3f ", transposta->dados[i][j]);
    }
    //printf("");
  }
  printf("]");
  libera_matriz(transposta); // Libera a matriz transposta
}

// Função auxiliar para ordenar tipo double
int qsort_double(const void *a, const void *b) {
    return (*(double*)a - *(double*)b > 0) - (*(double*)a - *(double*)b < 0);
}

// Função que simula o sistema do robô móvel
void simula(Matrix *ut, Matrix *xt, Matrix *yt, Matrix *yft, double diametro, int t) {

  printf("-------------------------------------"
         " SIMULAÇÃO para Diametro = %d "
         "--------------------------------------\n\n"
         "formato -> func(t): [matriz]\n\n",
         (int)diametro);

  // double D = scanf("Determine o diametro: %lf", &D);

  for (int i = 0; i <= t; i++) {

    ut = calcula_ut(i);
    xt = calcula_xt(ut, i);
    yt = calcula_yt(xt);
    yft = calcula_yft(xt, ut, diametro);

    printf("ut(%d):  ", i);
    printa_transposta(ut);
    printf("\n");

    printf("yf(%d): ", i);
    printa_transposta(yft);
    printf("\n");
    for (int i = 0; i < 70; i++) {
      printf("-");
    }
    printf("\n");
    usleep(50000);

  }
}

void gera_grafico(const char *nome_arquivo) {
  char dados[60];
  char saida[60];
  char comando[60];

  snprintf(dados, sizeof(dados), "outputs/%s/dados.txt", nome_arquivo);
  snprintf(saida, sizeof(saida), "outputs/%s/grafico_yf_2d.png", nome_arquivo);

  const char *simulacao = (strstr(nome_arquivo, "OnLoad") != NULL) ? "Simulação com Carga" : "Simulação sem Carga";

  FILE *pipe = popen("gnuplot -persistent", "w");
  if (pipe == NULL) {
    fprintf(stderr, "Erro ao abrir o gnuplot.\n");
    exit(1);
  }

  // Configuração e geração do gráfico 2D
  fprintf(pipe, "set terminal pngcairo size 800,600\n");
  fprintf(pipe, "set output '%s'\n", saida);
  fprintf(pipe, "set title '{/:Bold=12 %s - Projeção da Trajetória de Yf(t) no Plano (Yf1, Yf2)}'\n", simulacao);
  fprintf(pipe, "set xlabel 'Yf1(t)'\n");
  fprintf(pipe, "set ylabel 'Yf2(t)'\n");
  fprintf(pipe, "unset zlabel\n");
  fprintf(pipe, "set xtics 2\n"); // Ajuste do espaçamento no eixo Yf1 para o gráfico 2D
  fprintf(pipe, "set ytics 2\n"); // Ajuste do espaçamento no eixo Yf2 para o gráfico 2D
  fprintf(pipe, "set grid\n");
  fprintf(pipe, "set style line 2 pt 7 ps 0.05 lc rgb 'blue'\n");
  fprintf(pipe, "plot '%s' using 2:3 with points linestyle 2 title 'Trajetória no Plano - Pontos'\n", dados);
  fprintf(pipe, "unset output\n");

  pclose(pipe);

  // Comandos para abrir cada gráfico gerado usando feh de forma assíncrona
  if (snprintf(comando, sizeof(comando), "feh '%s' &", saida) < sizeof(comando)) {
    system(comando);
  } else {
    fprintf(stderr, "Erro: Comando feh para gráfico 2D foi truncado.\n");
  }

}

// Função que salva os resultados da simlação em um .txt no formato CSV
void salva_resultados(Matrix *ut, Matrix *xt, Matrix *yt, Matrix *yft, int t, const char *nome_arquivo) {
  FILE* arquivo;

  // Se o arquivo for aberto com sucesso, escreve o estado atual da matriz
  if ((arquivo = fopen(nome_arquivo, "a")) != NULL) {
    // Header para o passo (opcional)

    // Imprime o tempo atual
    fprintf(arquivo, "t = %d\t", t);

    // Imprime ut no tempo atual
    fprintf(arquivo, "uT = [%.2lf, %.2lf]\t", ut->dados[0][0], ut->dados[1][0]);

    // Imprime xt no tempo atual
    /*fprintf(arquivo, "xT = [%.2lf, %.2lf, %.2lf]\t", xt->dados[0][0], xt->dados[1][0], xt->dados[2][0]);

    // Imprime yt no tempo atual
    fprintf(arquivo, "yT = [%.2lf, %.2lf, %.2lf][%.2lf, %.2lf, %.2lf][%.2lf, %.2lf, %.2lf]\t",
                      yt->dados[0][0], yt->dados[1][0], yt->dados[2][0],
                      yt->dados[0][1], yt->dados[1][1], yt->dados[2][1],
                      yt->dados[0][2], yt->dados[1][2], yt->dados[2][2]);
    */
    // Imprime yft no tempo atual    
    fprintf(arquivo, "yfT = [%.2lf, %.2lf, %.2lf]\n", yft->dados[0][0], yft->dados[1][0], yft->dados[2][0]); 
  }

  fclose(arquivo);
}

// Função que realiza a leitura dos dados obtidos na simulação
void leitura_dados(char *nome_arquivo, double *uT_00, double *uT_01, double *yfT_00, double *yfT_01, double *yfT_02, int tam){
  FILE *arquivo;

  if((arquivo = fopen(nome_arquivo, "r")) != NULL) {
    
    int time, i = 0;
    char buffer[60];

    while (fgets(buffer, sizeof(buffer), arquivo)) {
      sscanf(buffer, "t = %d	uT = [%lf, %lf]	yfT = [%lf, %lf, %lf]", &time, &uT_00[i], &uT_01[i], &yfT_00[i], &yfT_01[i], &yfT_02[i]);
      i++;
    }
  }

  fclose(arquivo);
}

// Função que processa os dados, retornando os valores de média, variância, desvio padrão e valores máximos e mínimos
Dados processa_dados(double *dados, size_t tam){
  Dados data = {0};

  qsort(dados, tam, sizeof(double), qsort_double);

  for(int i = 0; i < tam; i++){
    data.media += dados[i];
  }

  data.media /= tam;

  for(int i = 0; i < tam; i++){
    data.var += (dados[i] - data.media) * (dados[i] - data.media);
  }

  data.var /= tam;
  data.min = dados[0];
  data.max = dados[tam-1];
  data.desv_pad = sqrt(data.var);
  data.q1 = dados[(int)(tam * 0.25)];
  data.q2 = dados[(int)(tam * 0.5)];
  data.q3 = dados[(int)(tam * 0.75)];

  return data;
}

// Função que utiliza as outras funções e escreve os dados finais em uma tabela
void salva_tabela_dados(int tam, char *nome_arquivo){
  //double uT_00[tam], uT_01[tam],  yfT_00[tam],  yfT_01[tam],  yfT_02[tam];

  //leitura_dados(nome_arquivo, uT_00, uT_01, yfT_00, yfT_01, yfT_02, tam);

  //COMPLETAR 
}
