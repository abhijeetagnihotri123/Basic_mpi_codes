#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <mpi.h>
#define N 16
int A[N][N],B[N][N],C[N][N];
using namespace std;
void assign_matrix(void);
int main(int argc,char *argv[])
{   
    int id,size,from,to,ratio;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    assign_matrix();
    ratio=N/size;
    if(id==0)
    {               
        from=id*ratio;
        to=(id+1)*ratio;
        for(int i=from;i<to;i++)
        {
            for(int j=0;j<N;j++)
            {
                for(int k=0;k<N;k++)
                {
                    C[i][j]+=A[i][k]*B[k][j];
                }
            }
        }
        for(int i=1;i<size;i++)
        {
            from=i*ratio;
            to=(i+1)*ratio;
            for(int j=from;j<to;j++)
            {
                MPI_Send(A[j],N,MPI_INT,i,0,MPI_COMM_WORLD);
                MPI_Send(B[j],N,MPI_INT,i,0,MPI_COMM_WORLD);
                MPI_Send(C[j],N,MPI_INT,i,0,MPI_COMM_WORLD);
            }
        }
        for(int i=1;i<size;i++)
        {
            from=i*ratio;
            to=(i+1)*ratio;
            for(int j=from;j<to;j++)
            {
                MPI_Recv(C[j],N,MPI_INT,i,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            }
        }
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                cout<<C[i][j]<<" ";
            }

        cout<<endl;
        }
    }
    else
    {
        from=id * ratio;
        to=(id+1)*ratio;
        for(int j=from;j<to;j++)
        {
            MPI_Recv(A[j],N,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(B[j],N,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(C[j],N,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }
        for(int i=from;i<to;i++)
        {
            for(int j=0;j<N;j++)
            {
                for(int k=0;k<N;k++)
                {
                    C[i][j]+=A[i][k]*B[j][k];
                }
            }
        }
        for(int i=from;i<to;i++)
        {
            MPI_Send(C[i],N,MPI_INT,0,1,MPI_COMM_WORLD);
        }
    }
    assign_matrix();
    fflush(stdout);
    MPI_Finalize();
    return 0;
}
void assign_matrix()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            A[i][j]=(i+j);
            B[i][j]=(2*i+j);
            C[i][j]=0;
        }
    }
}