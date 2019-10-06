/* File:     
 *     pth_mat_vect.c 
 *
 * Purpose:  
 *     Computes a parallel matrix-vector product.  Matrix
 *     is distributed by block rows.  Vectors are distributed by 
 *     blocks.
 *
 * Input:
 *     m, n: order of matrix
 *     A, x: the matrix and the vector to be multiplied
 *
 * Output:
 *     y: the product vector
 *
 * Compile:  gcc -g -Wall -o pth_mat_vect pth_mat_vect.c -lpthread
 * Usage:
 *     pth_mat_vect <thread_count>
 *
 * Notes:  
 *     1.  Local storage for A, x, y is dynamically allocated.
 *     2.  Number of threads (thread_count) should evenly divide both 
 *         m and n.  The program doesn't check for this.
 *     3.  We use a 1-dimensional array for A and compute subscripts
 *         using the formula A[i][j] = A[i*n + j]
 *     4.  Distribution of A, x, and y is logical:  all three are 
 *         globally shared.
 *
 * IPP:    Section 4.3 (pp. 159 and ff.).  Also Section 4.10 (pp. 191 and 
 *         ff.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "timer.h"

/* Global variables */
int     thread_count;
int     m, n;
double* A;
double* x;
double* y;
int semilla = 0;

/* Serial functions */
void Usage(char* prog_name);
void llenar_matrix(char* prompt, double A[], int m, int n);
void llenar_vector(char* prompt, double x[], int n);
void Print_matrix(double A[], int m, int n);
void Print_vector(double y[], double m);

/* Parallel function */
void *Pth_mat_vect(void* rank);

/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;
    double start, finish, elapsed;

   pthread_t* thread_handles;

   if (argc != 2) Usage(argv[0]);
   thread_count = atoi(argv[1]);
   thread_handles = malloc(thread_count*sizeof(pthread_t));

   printf("Enter m and n\n");
   scanf("%d%d", &m, &n);

   A = malloc(m*n*sizeof(double));
   x = malloc(n*sizeof(double));
   y = malloc(m*sizeof(double));
   
   llenar_matrix("Llenando Matriz", A, m, n);
   //Print_matrix(A, m, n);

   llenar_vector("Llenando vector", x, n);
   //Print_vector(x, n);

   GET_TIME(start);
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
         Pth_mat_vect, (void*) thread);

   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);

   GET_TIME(finish);
   //Print_vector(y, m);

   elapsed = finish - start;

   printf("   Elapsed time = %f seconds\n", elapsed);

   free(A);
   free(x);
   free(y);

   return 0;
}  /* main */


/*------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   print a message showing what the command line should
 *            be, and terminate
 * In arg :   prog_name
 */
void Usage (char* prog_name) {
   fprintf(stderr, "usage: %s <thread_count>\n", prog_name);
   exit(0);
}  /* Usage */

/*------------------------------------------------------------------
 * Function:    Read_matrix
 * Purpose:     Read in the matrix
 * In args:     prompt, m, n
 * Out arg:     A
 */
void llenar_matrix(char* prompt, double A[], int m, int n) {
   int             i, j;

   srand(time(NULL));
   printf("%s\n", prompt);
   for (i = 0; i < m; i++) 
      for (j = 0; j < n; j++)
            A[i*n+j] = rand() % 20;
}  /* Read_matrix */


/*------------------------------------------------------------------
 * Function:        Read_vector
 * Purpose:         Read in the vector x
 * In arg:          prompt, n
 * Out arg:         x
 */
void llenar_vector(char* prompt, double x[], int n) {
   int   i;
   semilla += 17;
   srand(time(NULL) + semilla);
   printf("%s\n", prompt);
   for (i = 0; i < n; i++) 
      x[i] = rand() % 20;
}  /* Read_vector */


/*------------------------------------------------------------------
 * Function:       Pth_mat_vect
 * Purpose:        Multiply an mxn matrix by an nx1 column vector
 * In arg:         rank
 * Global in vars: A, x, m, n, thread_count
 * Global out var: y
 */
void *Pth_mat_vect(void* rank) {
   long my_rank = (long) rank;
   int i, j;
   int local_m = m/thread_count; 
   int my_first_row = my_rank*local_m;
   int my_last_row = (my_rank+1)*local_m - 1;

   for (i = my_first_row; i <= my_last_row; i++) {
      y[i] = 0.0;
      for (j = 0; j < n; j++)
          y[i] += A[i*n+j]*x[j];
   }

   return NULL;
}  /* Pth_mat_vect */


/*------------------------------------------------------------------
 * Function:    Print_matrix
 * Purpose:     Print the matrix
 * In args:     title, A, m, n
 */
void Print_matrix(double A[], int m, int n) {
   int   i, j;
   for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++)
         printf("%4.1f ", A[i*n + j]);
      printf("\n");
   }
}  /* Print_matrix */


/*------------------------------------------------------------------
 * Function:    Print_vector
 * Purpose:     Print a vector
 * In args:     title, y, m
 */
void Print_vector(double y[], double m) {
   int   i;
   for (i = 0; i < m; i++)
      printf("%4.1f ", y[i]);
   printf("\n");
}  /* Print_vector */
