#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc,char *argv[])
{   
    int num_processes;
    int rank;
    int length;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0)
    {
        MPI_Get_processor_name(hostname,&length);
        cout<<"Process with rank "<<rank<<" is on processor "<<hostname<<endl;
    }
    else
    {
        MPI_Get_processor_name(hostname,&length);
        cout<<"Process with rank "<<rank<<" is on processor "<<hostname<<endl;
    }
    fflush(stdout);
    MPI_Finalize();
    return 0;
}