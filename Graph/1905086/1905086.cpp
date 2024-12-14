#include <bits/stdc++.h>
#include <fstream>
using namespace std;
queue<int> q;
int destination[10016], visit[10000], dist[10000], parent[10000], faces, squares;

bool is_valid(int node)
{
    if (node < 1 || node > squares || visit[node] == 1)
        return false;
    else
        return true;
}
int BFS(int root)
{
    for (int i = 0; i <= squares; i++){
        visit[i] = 0;
        parent[i] = -1;
    }

    visit[root] = 1;
    q.push(root);
    dist[root] = 0;

    while (!q.empty())
    {
        int current_node = q.front();
        q.pop();
        for (int i = 1; i <= faces; i++)
        {
            int next_node = destination[current_node + i];
            if (is_valid(next_node))
            {
                q.push(next_node);
                visit[next_node] = 1;
                dist[next_node] = dist[current_node] + 1;
                parent[current_node + i] = current_node;
            }
            if (next_node != (current_node + i))
            {
                if (is_valid(current_node + i))
                {
                    visit[current_node + i] = 1;
                    parent[next_node] = current_node + i;
                }
            }
        }
    }
    return (visit[squares] != 0) ? dist[squares] : -1;
}
vector<int> shortest_path()
{
    vector<int> path;
    for (int i = squares; i != -1; i = parent[i])
    {
        path.push_back(i);
    }
    return path;
}

vector<int> reachable_nodes()
{
    vector<int> visited;
    for (int i = 1; i <= squares; i++)
    {
        if (visit[i] == 0)
            visited.push_back(i);
    }
    return visited;
}

void getInput(int &start, int &last, string myText)
{
    stringstream ss(myText);
    ss >> start >> last;
}

int main()
{
    int t, l, s, u, v;
    string myText;
    ifstream MyReadFile("input.txt");
    ofstream OutFile("out.txt");
    OutFile.clear();

    getline(MyReadFile, myText);
    stringstream(myText) >> t;

    while (t--)
    {
        getline(MyReadFile, myText);
        getInput(faces, squares, myText);

        for (int i = 1; i <= squares; i++)
        {
            destination[i] = i;
        }
        getline(MyReadFile, myText);
        stringstream(myText) >> l;

        for (int i = 0; i < l; i++)
        {
            getline(MyReadFile, myText);
            getInput(u, v, myText);

            destination[u] = v;
        }

        getline(MyReadFile, myText);
        stringstream(myText) >> s;

        for (int i = 0; i < s; i++)
        {
            getline(MyReadFile, myText);
            getInput(u, v, myText);

            destination[u] = v;
        }
        ///----------------------------------output----------------------------///

        int total_moves = BFS(1);

        vector<int> short_path, visited;
        short_path = shortest_path();
        visited = reachable_nodes();
        OutFile << total_moves << '\n';
        if (total_moves != -1)
        {
            reverse(short_path.begin(), short_path.end());
            for (int i = 0; i < short_path.size(); i++)
            {
                OutFile << short_path[i] << ' ';
                if (i != short_path.size() - 1)
                {
                    OutFile << "->";
                }
            }
            OutFile << '\n';
        }
        else
        {
            OutFile << "No Solution" << '\n';
        }

        if (visited.size() == 0)
        {
            OutFile << "All reachable" << '\n';
        }
        else
        {
            for (int i : visited)
            {
                OutFile << i << ' ';
            }
            OutFile << '\n';
        }
        OutFile << '\n';
    }
    MyReadFile.close();
    OutFile.close();
    return 0;
}
