#include <iostream>
#include <mpi.h>
#define N 10000000
using namespace std;
double p;
int main(int argc,char *argv[])
{   
    int id,num_processes;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&num_processes);
    double *pi;
    pi=new double[num_processes];
    if(id==0)
    {
        pi[id]=0;
        double x;
        double step=(1.0)/N;
        int from=id*N/num_processes;
        int till=(id+1)*N/num_processes;
        for(int i=from;i<till;i++)
        {   
            x=(i+0.5)*step;
            pi[id]+=4.0/(1+x*x)*step;
        }
        MPI_Reduce(&pi[id],&p,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        cout<<p;
    }
    else
    {
        pi[id]=0;
        double x;
        double step=1.0/N;
        int from=id*N/num_processes;
        int till=(id+1)*N/num_processes;
        for(int i=from;i<till;i++)
        {
            x=(i+0.5)*step;
            pi[id]+=4.0/(1+x*x)*step;
        }
        MPI_Reduce(&pi[id],&p,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    }
    
    delete(pi);
    fflush(stdout);
    MPI_Finalize();
    return 0;
}