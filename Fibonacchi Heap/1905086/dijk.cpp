#include "fibo.cpp"
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int N = 1e5;
vector<pair<int, int>> adj[N];
int dist[N], par[N];

void dijkstra_bin(int src,int n)
{
    vector<bool> visited(n+1);
    for (int i=0; i<=n; i++) {
        dist[i] = INT_MAX;
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,src});
    dist[src] = 0;
    par[src] = -1;
    int u;
    while(!pq.empty())
    {
        u = pq.top().second;
        pq.pop();
        visited[u] = true;
        int v,w;
        for(auto x: adj[u])
        {
            tie(v,w) = x;
            if(visited[v]==false && dist[v]>dist[u]+w)
            {
                dist[v] = dist[u]+w;
                par[v]=u;
                pq.push({dist[v],v});
            }
        }
    }
}

void dijkstra_fibo(int st, int n) {
    FibonacciHeap fh;

    for (int i=0; i<=n; i++) {
        dist[i] = INT_MAX;
    }
    dist[st] = 0;
    par[st] = -1;
    fh.insertion(0, st);

    while (!fh.isEmpty()) {
        int u = fh.getID();
        int u_wt = fh.Extract_min();
        dist[u] = u_wt;

        for (pair<int, int> v_pair: adj[u]) {
            int v = v_pair.first;
            int wt = v_pair.second;

            if (dist[u] + wt < dist[v]) {
                if (dist[v] == INT_MAX) {
                    fh.insertion(dist[u] + wt, v);
                }
                else {
                    fh.decrease_key(dist[u] + wt, v);
                }
                dist[v] = dist[u] + wt;
                par[v] = u;
            }
        }
    }
}
int short_path(int t)
{
    vector<int> path;
    for (int v = t; v != -1; v = par[v])
        path.push_back(v);
    return path.size()-1;
}
int main()
{
    fstream cingraph("in1.txt");
    int n, m;
    cingraph >> n >> m;

    for (int i=0; i<m; i++)
    {
        int u, v, wt;
        cingraph >> u >> v >> wt;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    cingraph.close();

    fstream cininput("in2.txt");
    int t;
    cininput >> t;
    fstream cout("output.txt");
    for (int i=1; i<=t; i++)
    {
        int st, dest;
        cininput >> st >> dest;

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        dijkstra_fibo(st, n);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

        cout<<short_path(dest)<<" "<<dist[dest]<<" "<<fixed<<time_span.count()<<" ";

        memset(dist, 0, sizeof(dist));
        memset(par, 0, sizeof(par));

        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        dijkstra_bin(st, n);
        high_resolution_clock::time_point t4 = high_resolution_clock::now();
        duration<double> time_span1 = duration_cast<duration<double>>(t4 - t3);

        cout<<fixed<<time_span1.count()<<endl;

        memset(dist, 0, sizeof(dist));
        memset(par, 0, sizeof(par));
    }
    cininput.close();

    return 0;
}
