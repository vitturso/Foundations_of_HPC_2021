#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


#define seed 68111 // seed for number generator

int main (int argc, char ** argv) 
{

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
 
 
 N=node;
 grid=malloc(sizeof(float)*3*N*N*N);
 printf("the number of grid node points is %f \n",N*N*N);
 if (radius > 1/(2*N))
   printf("the radius R must be R<=1/(2*N) \n");
 else
   printf("il raggio R di ogni sfera è %f \n", R=radius);
 V=(4*3.14*R*R*R)/3;
 printf("il volume di ogni sfera è %f \n",V);

 int index=0;
 
 
 for(i=0; i<=N-1; i++)
 {
   for(j=0; j<=N-1;j++)
   {
     for(k=0; k<=N-1; k++)
     {
        x_i=x_0/(2*N)+(2*R)*i;
        y_j=y_0/(2*N)+(2*R)*j;
        z_k=z_0/(2*N)+(2*R)*k;
        grid[index+0]=x_i;
        grid[index+1]=y_j;
        grid[index+2]=z_k;
        index+=3;
        printf("le coordinate dei punti della grid sono x_0= %f y_0= %f z_0= %f \n", x_i, y_j, z_k);
     } 
   }
 }

 
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
 
    for(t=0; t < 3*n; t++)
    {
      fscanf(fd, "%f ", &vett[t]);
      printf("%f   ", vett[t]);
      if (t>0 && (t+1)%3==0)
      { 
        printf("\n");
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
    }
/* chiude il file */
  fclose(fd);  
  
  for(d=1; d <= N*N*N; d++) 
  printf("the density of the node %d is %f \n", d, rho[d-1]/V);
 
 
  free(grid);
 
  free(vett);
 
  free(rho);
  
  
return 0;
 
}
