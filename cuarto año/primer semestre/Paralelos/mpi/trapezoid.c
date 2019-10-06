/*
 * Peter S. Pacheco, An Introduction to Parallel Programming,
 * Morgan Kaufmann Publishers, 2011
 * IPP:   Section 3.4.2 (pp. 104 and ff.)
 * Timing and command line argument added by Hannah Sonsalla,
 * Macalester College, 2017
 *
 * mpi_trap.c
 *
 * ... Use MPI to implement a parallel version of the trapezoidal
 *     rule.  Uses collective communications to distribute the
 *     input data and compute the global sum.
 *
 * Input:    Number of trapezoids
 * Output:   Estimate of the integral from a to b of f(x)
 *           using the trapezoidal rule and n trapezoids.
 *
 * Usage:    mpirun -np <number of processes> ./mpi_trap < number of trapezoids>
 *
 * Algorithm:
 *    1.  Each process calculates "its" interval of
 *        integration.
 *    2.  Each process estimates the integral of f(x)
 *        over its interval using the trapezoidal rule.
 *    3a. Each process != 0 sends its integral to 0.
 *    3b. Process 0 sums the calculations received from
 *        the individual processes and prints the result.
 *
 * Note:  f(x) is all hardwired to x*x.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

const double a = 0;
const double b = 2000000000;

/* Function declarations */
void Get_input(int argc, char* argv[], int my_rank, double* n_p);
double Trap(double left_endpt, double right_endpt, int trap_count,
   double base_len);
double f(double x);

int main(int argc, char** argv) {

   int my_rank, comm_sz, local_n;
   double n, h, local_a, local_b;
   double local_int, total_int;
   double start, finish, loc_elapsed, elapsed;

   MPI_Init(NULL, NULL);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   Get_input(argc, argv, my_rank, &n); /*Read user input */

   /*Note: h and local_n are the same for all processes*/
   h = (b-a)/n;          /* length of each trapezoid */
   local_n = n/comm_sz;  /* number of trapezoids per process */

   /* Length of each process' interval of integration = local_n*h. */
   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*h;

   MPI_Barrier(MPI_COMM_WORLD);
   start = MPI_Wtime();
   /* Calculate each process' local integral using local endpoints*/
   local_int = Trap(local_a, local_b, local_n, h);
   finish = MPI_Wtime();
   loc_elapsed = finish-start;
   MPI_Reduce(&loc_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

   /* Add up the integrals calculated by each process */
   MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0,
         MPI_COMM_WORLD);

   if (my_rank == 0) {
      printf("%i\n",my_rank );
      printf("Integral=  %.0f\n ",total_int);
      printf("Tiempo = %f miliseg \n", elapsed * 1000);
   }
   MPI_Finalize();
   /* Shut down MPI */
   

   return 0;
} /*  main  */


void Get_input(int argc, char* argv[], int my_rank, double* n_p){
	if (my_rank == 0) {
		if (argc!= 2){
		    fprintf(stderr, "usage: mpirun -np <N> %s <number of trapezoids> \n", argv[0]);
            fflush(stderr);
            *n_p = -1;
		} else {
			*n_p = atoi(argv[1]);
		}
	}
	// Broadcasts value of n to each process
	MPI_Bcast(n_p, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	// negative n ends the program
    if (*n_p <= 0) {
        MPI_Finalize();
        exit(-1);
    }
}  
 
double Trap(double left_endpt, double right_endpt, int trap_count, double base_len) {
   double estimate, x;
   int i;

   estimate = (f(left_endpt) + f(right_endpt))/2.0;
   for (i = 1; i <= trap_count-1; i++) {
      x = left_endpt + i*base_len;
      estimate += f(x);
   }
   estimate = estimate*base_len;

   return estimate;
} /*  Trap  */


double f(double x) {
   return x*x;
} /* f */
