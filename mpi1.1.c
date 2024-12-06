#include <stdio.h>
#include <string.h>  
#include <mpi.h>     

int main(void) {
   int        comm_size;               /* Número de processos    */
   int        my_rank;               /* Rank   do processo     */
   
   int a = 9;
   int b = 3;
   int res = 0;
   int valor;

   /* Inicia MPI */
   MPI_Init(NULL, NULL); 

   /* Obter número de processos */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_size); 

   /* Obter rank (id) do processo */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   //printf("Número de processos: %d Rank do processos corrente: %d \n", comm_sz, my_rank);
   
   if (my_rank == 1 ){
      printf("res p1: %d \n", a - b);
      int result = a - b;
      MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
   }
   else if (my_rank == 2 ){
      printf("res p2: %d \n", a * b);
      int result = a * b;
      MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
   }
   else if (my_rank == 3){
      printf("res p3: %d \n", a + b);
      int result = a + b;
      
      MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
   }
   else if (my_rank == 0){ 
      printf("Processo centralizador em execução: %d of %d!\n", my_rank, comm_size);
      
      for (int q = 1; q < comm_size; q++) {
         /* Recepção da mensagem do processo q */
         MPI_Recv(&valor, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      
         res = res + valor;
      }
      printf("res final: %d \n", res);
   }
   else{
      int result = 0;
      MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
   }
   

   
   /* Encerra MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
