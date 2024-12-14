#include<bits/stdc++.h>
#define N 100000
using namespace std;
vector<vector<pair<int,int>>> adj(N);
//vector<vector<int>>edgelist;
int n,m;
vector<int>path_dijk;

long long dijkstra(int src,int dest)
{
    vector<int> par(N,-1);
    vector<bool> visited(n);
    vector<long long>dist(N,LONG_MAX);
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
    pq.push({0,src});
    dist[src] = 0;
    int u;
    while(!pq.empty()) //O(E)
    {
        u = pq.top().second;
        pq.pop();
        visited[u] = true;
        if(u==dest&&dist[u]!=LONG_MAX)
        {
            break;
        }
        int v,w;
        for(auto x: adj[u])
        {
            tie(v,w) = x;
            if(visited[v]==false && dist[v]>dist[u]+w)
            {
                dist[v] = dist[u]+w;
                par[v]=u;
                pq.push({dist[v],v});//O(logV)
            }
        }
    }
    ///O(ElogV)
    for(int k = dest; k!=src; k=par[k])
        path_dijk.push_back(k);
    path_dijk.push_back(src);
    reverse(path_dijk.begin(),path_dijk.end());

    return dist[dest];
}
int main()
{
    fstream cin("text1.txt");
    cin>>n>>m;
    int u,v,w;
    for(int i = 0; i<m; i++)
    {
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        //edgelist.push_back({u,v,w});
    }
    int src,dest;
    cin>>src>>dest;
    cout<<"Shortest path cost: "<<dijkstra(src,dest)<<endl;
    int j;
    for(j = 0; j < path_dijk.size()-1; j++)
    {
        cout<<path_dijk[j]<<" -> ";
    }
    cout<<path_dijk[j]<<endl;
    return 0;
}

