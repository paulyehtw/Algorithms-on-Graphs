#include <iostream>
#include <vector>

using std::vector;

int cycle = 0;

void explore(vector<vector<int> > &adj,vector<int> &visited, int vertex, int start){
  if(cycle == 1){return;}
  for(int i = 0; i < adj[vertex].size(); ++i){
    if(adj[vertex][i] == start){
      cycle = 1;
      return;
    }
    if(visited[adj[vertex][i]] != 1){
      visited[adj[vertex][i]] = 1;
      explore(adj, visited, adj[vertex][i], start);
    }
  }
}

int acyclic(vector<vector<int> > &adj) {
  for(int i = 0; i < adj.size(); ++i){
    if(adj[i].size() > 0){
      vector<int> visited(adj.size(), 0);
      if(visited[i] == 0){
        explore(adj, visited, i, i);
      }
    }
  }
  return cycle;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
