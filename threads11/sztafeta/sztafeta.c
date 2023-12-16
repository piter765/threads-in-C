#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <unistd.h>
#include "mpi.h"

int main( int argc, char** argv ){ 
  
  int rank, size, source, dest, tag, i; 
  char name[50];
  char namesent[50];
  int prev, x = 5;
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  if(size>1) {
    
    if(rank==0) {
      tag=0;
      dest=1;
      prev=size-1;
      printf("\nProces %d wyslal liczbe %d, do procesu: %d \n", rank, x, dest);
      MPI_Send( &x, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
    } 
    if (rank<size-1 && rank !=0) {
      prev = rank-1;
      dest = rank+1;
      MPI_Recv( &x, 1, MPI_INT, prev, MPI_ANY_TAG , MPI_COMM_WORLD, &status );
      printf("Proces %d odebral liczbe %d, od procesu: %d i wysle liczbe do procesu: %d \n",
       rank, x, status.MPI_SOURCE, dest);
      x++;
      MPI_Send(&x, 1, MPI_INT, dest, tag, MPI_COMM_WORLD ); 
      printf("Proces %d wyslal liczbe %d do procesu: %d\n", rank, x, dest);
    }
    if(rank == size-1) {
      prev = rank-1;
      dest = 0;
      MPI_Recv( &x, 1, MPI_INT, prev, MPI_ANY_TAG , MPI_COMM_WORLD, &status );
      printf("Proces %d odebral liczbe %d, od procesu: %d i wysle liczbe do procesu: %d \n",
       rank, x, status.MPI_SOURCE, dest);
    }
  
  MPI_Finalize(); 
  }
  return(0);
  
}

