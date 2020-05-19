#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
    int n,e;
    cin>>n>>e;
    int graph[n][n];
    int answer[n]={-1};
    int visited[n]={0};
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            graph[i][j]=0;
        }
    }
    while(e--)
    {
        int u,v;
        cin>>u>>v;
        graph[u][v]=1;
        graph[v][u]=1;
    }
    int index=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(graph[i][j]==1)
            {
                if(visited[j]==0)
                {
                    visited[j]=1;
                    answer[index++]=j;
                }
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        cout<<answer[i]<<" ";
    }
    return 0;
}
