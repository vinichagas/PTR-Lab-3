#include <math.h>
#include <stdio.h>
#include <unistd.h>

#include "matrix.h"
#include "calculate.h"

#define PI 3.14159265358979323846

// Função que faz a transposição e printa uma matriz
void transpose_and_print(Matrix *m) {
  Matrix *transposed = transpose(m);
  printf("[ ");
  for (int i = 0; i < transposed->rows; i++) {
    for (int j = 0; j < transposed->cols; j++) {
      printf("%.3f ", transposed->data[i][j]);
    }
    //printf("");
  }
  printf("]");
  free_matrix(transposed); // Free the transposed matrix
}

// simular o sistema
void simulate(Matrix *ut, Matrix *xt, Matrix *yt, Matrix *yft, int t) {
  t = 20;
  double D = 5;
  printf("formato\nfunc(t): [matriz]\n\n============================= "
         "SIMULACAO para Diametro = %d =============================\nobs: as "
         "matrizes foram transpostas\n\n",
         (int)D);

  // double D = scanf("Determine o diametro: %lf", &D);

  for (int i = 0; i <= t; i++) {

    u = calculateUt(i);
    xt = calculateXt(ut, t);
    yt = calculateYt(xt);
    yf = calculateYf(xt, ut, D);

    printf("ut(%d):  ", i);
    transpose_and_print(ut);
    printf("\n");

    printf("yf(%d): ", i);
    transpose_and_print(yft);
    printf("\n");
    for (int i = 0; i < 70; i++) {
      printf("-");
    }
    printf("\n");
    usleep(50000);

    free_matrix(ut);
    free_matrix(xt);
    free_matrix(yt);
    free_matrix(yft);
  }
}

// Ajuda a salvar o resultado da simulacao em um .txt
void print_matrix_csv(Matrix *m, FILE *fp) {
  for (int i = 0; i < m->rows; i++) {
    // Check if this is the last row (avoid adding comma at the end)
    int is_last_row = (i == m->rows - 1);

    for (int j = 0; j < m->cols; j++) {
      // Format each element with a specific precision (adjust as needed)
      fprintf(fp, "%0.4lf", m->data[i][j]);

      // Add comma after each element except the last one in the row
      if (!is_last_row && j < m->cols - 1) {
        fprintf(fp, ",");
      }
    }

    // Add a newline after each row
    fprintf(fp, "\n");
  }
}

// Salvar os resultados da simlação em um .txt no formato CSV
void save_simulation_results(Matrix *ut, Matrix *xt, Matrix *yt, Matrix *yft,
                             int t, const char *filename) {
  FILE *fp = fopen(filename, "w");
  if (!fp) {
    printf("Error opening file for writing.\n");
    return;
  }

  for (int i = 0; i <= t; i++) {
    // Write header for this time step (optional)
    fprintf(fp, "Time step %d:\n", i);
    // fprintf(fp, "--------------\n");
    //  Write ut matrix
    fprintf(fp, "ut(%d):\n", i);
    print_matrix_csv(ut, fp);

    // fprintf(fp, "..............\n");

    // Write yf matrix
    fprintf(fp, "yft(%d):", i);
    print_matrix_csv(yft, fp);

    /*
    // Write xt matrix
    fprintf(fp, "xt(%d):", i);
    print_matrix_csv(xt, fp);

    // Write yt matrix
    fprintf(fp, "yt(%d):", i);
    print_matrix_csv(yt, fp);

    */

    // Add a newline after each set of matrices
    fprintf(fp, "\n");
  }

  fclose(fp);
}
