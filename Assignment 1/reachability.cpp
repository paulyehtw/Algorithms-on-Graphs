#include <iostream>
#include <vector>

using std::vector;

int reachability = 0;

void reach(vector<vector<int> > &adj,vector<int> &visited, int start, int destination){
  if(reachability == 1){return;}
  for(int i = 0; i < adj[start].size(); ++i){
    if(adj[start][i] == destination)
      reachability = 1;
    if(visited[adj[start][i]] != 1){
      visited[adj[start][i]] = 1;
      reach(adj, visited, adj[start][i], destination);
    }
  }
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<int> visited(n,0);
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  reach(adj, visited, x - 1, y - 1);
  std::cout << reachability;
}
