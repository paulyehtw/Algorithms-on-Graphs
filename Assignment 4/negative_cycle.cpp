#include <iostream>
#include <vector>
#include <limits>

using std::vector;
int inf = std::numeric_limits<int>::max()/2;

int negative_cycle(const vector<vector<int> > &adj, const vector<vector<int> > &cost) {
  vector<int> dist(adj.size(), inf);
  dist[0] = 0;
  bool updated = true;
  int i;
  for (i = 0; i < adj.size() && updated; ++i) {
    updated = false;
    for (int j = 0; j < adj.size(); j++) {
      for (int k = 0; k < adj[j].size(); k++) {
        if (dist[adj[j][k]] > dist[j] + cost[j][k]) {
          dist[adj[j][k]] = dist[j] + cost[j][k];
          updated = true;
        }
      }
    }
  }
  return (i == adj.size());
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost) << std::endl;
}