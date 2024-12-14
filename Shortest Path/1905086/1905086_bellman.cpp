#include<bits/stdc++.h>
#define N 100000
using namespace std;
//vector<vector<pair<int,int>>> adj(N);
vector<vector<int>>edgelist;
vector<int>path_bell;
int n,m;
long long bellman_ford(int src, int dest)
{
    vector<long long>dist(N,LONG_MAX);
    vector<int> par(N,-1);
    dist[src] = 0;
    for(int i = 1; i<=n-1; i++)
    {
        for(int j = 0; j < m; j++)
        {
            int u = edgelist[j][0];
            int v = edgelist[j][1];
            int w = edgelist[j][2];
            if(dist[u]!=LONG_MAX && dist[u]+w<dist[v])
            {
                dist[v] = dist[u]+w;
                par[v] = u;
            }
        }
    }
    for(int i = 0; i < m; i++)
    {
        int u = edgelist[i][0];
        int v = edgelist[i][1];
        int w = edgelist[i][2];
        if(dist[u]!=LONG_MAX && dist[u]+w<dist[v])
        {
            return -1;
        }
    }
    ///O(EV)
    for(int k = dest; k!=src; k=par[k])
        path_bell.push_back(k);
    path_bell.push_back(src);
    reverse(path_bell.begin(),path_bell.end());
    return dist[dest];
}
int main()
{
    fstream cin("text2.txt");
    cin>>n>>m;
    int u,v,w;
    for(int i = 0; i<m; i++)
    {
        cin>>u>>v>>w;
        //adj[u].push_back({v,w});
        edgelist.push_back({u,v,w});
    }
    int src,dest;
    cin>>src>>dest;
    //cout<<dijkstra(src,dest)<<endl;
    long long cost;
    cost = bellman_ford(src,dest);
    if(cost != -1)
    {
        cout<<"The graph does not contain a negative cycle"<<endl;
        cout<<"Shortest path cost: "<<cost<<endl;
        int j;
        for(j = 0; j < path_bell.size()-1; j++)
        {
            cout<<path_bell[j]<<" -> ";
        }
        cout<<path_bell[j]<<endl;
    }
    else
    {
        cout<<"The Graph contains a negative weight cycle"<<endl;
    }
    return 0;
}


