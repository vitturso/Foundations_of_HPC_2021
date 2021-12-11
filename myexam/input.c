#include <stdio.h>
#include<stdlib.h>

//new scrivere un input 
int main (int argc, char ** argv[])
 {
  int D=3; 
  float a[D];
  int j, i, n=12;
  srand(time(0));
  
   printf("%d \n", n);
   for (i=0; i< n; i++){
    for (j = 0; j < D; j++)
    {
    a[j]=(float)rand()/(float)RAND_MAX;
    printf("%f ", a[j]); 
    }
   printf("\n");
 }
 return 0;
 }
