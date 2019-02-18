#include <iostream>
#include <vector>

using std::vector;

int res = 0;

void explore(vector<vector<int> > &adj,vector<int> &visited, int vertex){
  for(int i = 0; i < adj[vertex].size(); ++i){
    if(visited[adj[vertex][i]] != 1){
      visited[adj[vertex][i]] = 1;
      explore(adj, visited, adj[vertex][i]);
    }
  }
}

int number_of_components(vector<vector<int> > &adj) {
  vector<int> visited(adj.size(),0);
  for(int i = 0; i < adj.size(); ++i){
    if(visited[i] == 0){
      res++;
      explore(adj, visited, i);
    }
  }
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
