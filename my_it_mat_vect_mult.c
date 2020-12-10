/**
 *   \file my_it_mat_vect_mult.c
 *   \brief Multiplica iterativamente un matriz nxn 
 *          por un vector de n posiciones
 *
 *   \author Danny Múnera
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>


/* función para generar <size> cantidad de datos aleatorios */
void gen_data(double * array, int size);
/* función para multiplicar iterativamente un matriz 
 * <m x n> por un vector de tam <n> */
void mat_vect_mult(double* A, double* x, double* y, int n, int it);
/* función para imprimir un vector llamado <name> de tamaño <m>*/
void print_vector(char* name, double*  z, int m);

int main()
{
  double* A = NULL;
  double* x = NULL;
  double* y = NULL;
  int n, iters;
  long seed;
  struct timeval start_time, stop_time, elapsed_time;


  // Obtener las dimensiones
  printf("Ingrese la dimensión n:\n");
  scanf("%d", &n);
  printf("Ingrese el número de iteraciones:\n");
  scanf("%d", &iters);
  printf("Ingrese semilla para el generador de números aleatorios:\n");
  scanf("%ld", &seed);
  srand(seed);

  // la matriz A tendrá una representación unidimensional
  A = malloc(sizeof(double) * n * n);
  x = malloc(sizeof(double) * n);
  y = malloc(sizeof(double) * n);


  gettimeofday(&start_time,NULL);

  //generar valores para las matrices
  gen_data(A, n*n);
  gen_data(x, n);

  mat_vect_mult(A, x, y, n, iters);

  print_vector("y", y, n);

  gettimeofday(&stop_time,NULL);
  timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine

  printf("Total time was %f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);


  free(A);
  free(x);
  free(y);
  
  return 0;
}

void gen_data(double * array, int size){
  int i;
  for (i = 0; i < size; i++)
    array[i] = (double) rand() / (double) RAND_MAX;
}

void mat_vect_mult(double* A, double* x, double* y, int n, int it){
  int h, i, j;
  for(h = 0; h < it; h++){
    for(i = 0; i < n; i++){
      y[i] = 0.0;
      for(j = 0; j < n; j++)
	y[i] += A[i*n+j] * x[j];
    }
    // x <= y
    for(i = 0; i < n; i++)
      x[i] = y[i]/(n/2.0);
  }
}

void print_vector(char* name, double*  z, int m) {
   int i;
   printf("\nVector %s\n", name);
   for (i = 0; i < m; i++)
      printf("%f ", z[i]);
   printf("\n");
}
