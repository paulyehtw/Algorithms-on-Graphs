#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
  vector<int> dist(adj.size(), -1);
  queue<int> Q;
  dist[0] = 0;
  Q.push(0);
  while(Q.size() > 0){
    int u = Q.front();
    Q.pop();
    for(size_t i = 0; i < adj[u].size(); ++i){
      if(dist[adj[u][i]] == dist[u] && dist[adj[u][i]] != -1)
          return 0;
      else if(dist[adj[u][i]] == -1){
        Q.push(adj[u][i]);
        dist[adj[u][i]] = dist[u] + 1;
      }
    }
  }
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
