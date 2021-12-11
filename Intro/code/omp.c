 
/*
 * Copyright (C) 2016 Master in High Performance Computing
 *
 * Adapted from the net by Alberto Sartori. 
 */

// pi.c: Montecarlo integration to determine pi

// We have a circle inscribed inside a square of unit lenght. The
// ratio between the area of the square (1) and the circle (pi/4) is
// pi/4. Therefore, if we randomly choose N points inside the square,
// on average, only M=N*pi/4 points will belong to the circle. From
// the last relation we can estimate pi.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <omp.h>

// if you don ' t have drand48 uncomment the following two lines 10
// #define drand48 1.0/RANDMAXrand
// #define srand48 srand
#define seed 68111 // seed for number generator

int main (int argc, char ** argv) {

  if (argc == 4)
    {
      printf(" We calculate the density of the points of  %s on the grid of %s points and radius %s   \n",argv[3], argv[1], argv[2]);
 //    return 1;
    }
  else if (argc > 4){
  printf("too many arguments.\n");
  exit(1);
}
  else{
  printf("one argument expected.\n");
  exit(1);
}

 // faccio la grid
   int           nthreads=0;
  
   #pragma omp parallel  
   #pragma omp master
    nthreads = omp_get_num_threads();
 int node;
 float radius; 
 node=atoi(argv[1]);
 radius=atof(argv[2]);

 float x_0=1, y_0=1, z_0=1;
 float x, y, z;
 float *rho;
 float N;
 float R;
 int i, j, k;
 float x_i, y_j, z_k;
 float V;
 float *grid;
 
 //for(N=1; N<=2;N++)
// {
 N=node;
  printf("omp calculation with %d threads\nN=%f\n",nthreads ,N);
 grid=malloc(sizeof(float)*3*N*N*N);
 printf("the number of grid node points is %f \n",N*N*N);
 //R=1/(2*N);
 //printf("il raggio R di ogni sfera è %f \n", R=1/(2*N));
 if (radius > 1/(2*N))
 printf("the radius R must be R<=1/(2*N) \n");
 else
 printf("il raggio R di ogni sfera è %f \n", R=radius);
 V=(4*3.14*R*R*R)/3;
 printf("il volume di ogni sfera è %f \n",V);
 // calcoliamo la posizione dei punti della grid 
 //if(N==1)
// printf("le coordinate dei punti della grid sono %f %f %f \n", x_0/2, y_0/2,z_0/2);
 //else
// { 
 int index=0;
 
 
 for(i=0; i<=N-1; i++){
 for(j=0; j<=N-1;j++){
 for(k=0; k<=N-1; k++){
 x_i=x_0/(2*N)+(2*R)*i;

 y_j=y_0/(2*N)+(2*R)*j;

 z_k=z_0/(2*N)+(2*R)*k;
 grid[index+0]=x_i;
 grid[index+1]=y_j;
 grid[index+2]=z_k;
 index+=3;
  printf("le coordinate dei punti della grid sono x_0= %f y_0= %f z_0= %f \n", x_i, y_j, z_k);
  
 
// }
 
} 
 }
 }
// }
 
  int n;
  float *vett;
  FILE *fd;
  int t,q;
  int d=0;
  float r;
  
		
  fd=fopen("input.dat", "r"); 

		
  if( fd==NULL ) {
    perror("Errore in apertura del file");
    exit(1);
  }

		
  fscanf(fd, "%d", &n);
  vett=malloc (sizeof(float)*n*3);
 // rho=malloc (sizeof(float)*N*N*N);
  rho=calloc(sizeof(float),N*N*N); 
 
 

//reduction(+:rho[d-1])
    for(t=0; t < 3*n; t++)
   {
     fscanf(fd, "%f ", &vett[t]);
     printf("%f   ", vett[t]);
     printf("\n");
     
   }  
  
   float *rhot;
 #pragma omp parallel
 {
    int myid = omp_get_thread_num();
  // float *rvett;
  // rvett=malloc(sizeof(float)*3*n/nthreads);
     rhot=calloc(sizeof(float),N*N*N); 
    #pragma omp for 
    for(t=0; t<(3*n); t++)
//{    
      printf("[%d]received value = %f \n", myid, vett[t]);
   #pragma omp for 
   for(t=0; t < (3*n); t++)
  {   
    if (t>0 && (t+1)%3==0)
      { 
      //   printf("\n");
         float * p= &vett[t-2];

         for (q=0; q< 3*N*N*N; q=q+3)
         {
           r=(pow(grid[q+0]-p[0],2))+(pow(grid[q+1]-p[1],2))+(pow(grid[q+2]-p[2],2));
           printf("%f \n", r);
           if (r< R*R)
           {
           printf(" in \n ");
           d=(q+3)/3;
           rho[d-1]=rho[d-1]+1;
           printf("the density of the node %d is %f \n", d, 1/V);
           }  
         }
       }
   //}
   }
  }
 //  rhot[d-1]=rho[d-1]-rhot[d-1];
 
/* chiude il file */
  fclose(fd);  
 
 for(d=1; d <= N*N*N; d++) 
 printf("the total density of the node %d is %f \n", d, rho[d-1]/V);
 
 
 free(grid);
 
 free(vett);
 
 free(rho);
  
  
return 0;
 
}
