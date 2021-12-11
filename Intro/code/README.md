1) Il file exam.c fa il calcolo seriale e viene compilato con il comando:
gcc exam.c -o exam.x -lm 
ed eseguito:
./exam.x N R input.dat
2) Il file compile.c fa il calcolo in parallelo con MPI e viene compilato con il comando:
mpicc compile.c -o density -lm
ed eseguito:
mpirun -np # ./density N R input.dat 
3) Il file compile2.c fa il calcolo in parallelo con OpenMP e viene compilato con il comando:
gcc -fopenmp omp.c -o density2 -lm
ed eseguito:
OMP_NUM_THREADS= # ./density2 N R input.dat 

