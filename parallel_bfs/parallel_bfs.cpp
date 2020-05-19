#include <iostream>
#include <mpi.h>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
int main(int argc,char *argv[])
{   
    int id,size,n,e,u,v,s;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    if(id==0)
    {   
        fstream fin;
        fin.open("data.txt");
        fin>>n;
        int graph[n][n];
        int visited[n]={0};
        int bfs_result[n]={-1};
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                graph[i][j]=0;
            }
        }
        fin>>e;
        int i=0;
        while(i<e)
        {   
            fin>>u>>v;
            graph[u][v]=1;
            graph[v][u]=1;
            i++;
        }
        fin>>s;
        fin.close();
        i=0;
        for(int j=0;j<n;j++)
        {
            if(graph[id][j]==1)
            {
                if(visited[j]==0)
                {
                    visited[j]=1;
                    bfs_result[i++]=j;
                }
            }
        }
        cout<<endl;
        MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Bcast(graph,n*n,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Send(&i,1,MPI_INT,id+1,1,MPI_COMM_WORLD);
        MPI_Send(visited,n,MPI_INT,id+1,1,MPI_COMM_WORLD);
        MPI_Send(bfs_result,n,MPI_INT,id+1,1,MPI_COMM_WORLD);
    }
    else if(id==size-1)
    {   
        int n,i;
        MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
        int graph[n][n];
        int visited[n]={0};
        int bfs_result[n];
        MPI_Bcast(graph,n*n,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Recv(&i,1,MPI_INT,id-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(visited,n,MPI_INT,id-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(bfs_result,n,MPI_INT,id-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        for(int j=0;j<n;j++)
        {
            if(graph[id][j]==1)
            {   
                if(visited[j]==0)
                {
                    visited[j]=1;
                    bfs_result[i++]=j;
                }
            }
        }
        for(int i=0;i<n;i++)
        {
            cout<<bfs_result[i]<<" ";
        }
    }
    else
    {   
        int n,i;
        MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
        int graph[n][n];
        int visited[n]={0};
        int bfs_result[n];
        MPI_Bcast(graph,n*n,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Recv(&i,1,MPI_INT,id-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(visited,n,MPI_INT,id-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(bfs_result,n,MPI_INT,id-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        for(int j=0;j<n;j++)
        {
            if(graph[id][j]==1)
            {   
                if(visited[j]==0)
                {
                    visited[j]=1;
                    bfs_result[i++]=j;
                }
            }
        }
        MPI_Send(&i,1,MPI_INT,id+1,1,MPI_COMM_WORLD);
        MPI_Send(visited,n,MPI_INT,id+1,1,MPI_COMM_WORLD);
        MPI_Send(bfs_result,n,MPI_INT,id+1,1,MPI_COMM_WORLD);
    }
    fflush(stdout);
    MPI_Finalize();
    return 0;
}