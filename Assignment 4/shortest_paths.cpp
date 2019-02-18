#include <iostream>
#include <limits>
#include <vector>
#include <queue>

long long inf = std::numeric_limits<long long>::max()/2;

using std::vector;
using std::queue;

void bfs(const vector<vector<int> > &adj, vector<int> &visited, queue<int> Q) {
  while (!Q.empty()) {
    int x = Q.front();
    Q.pop();
    for (int i = 0; i < adj[x].size(); i++) {
      if (!visited[adj[x][i]]) {
        Q.push(adj[x][i]);
        visited[adj[x][i]] = 1;
      }
    }
  }
}

void bellman_ford(const vector<vector<int> > &adj, const vector<vector<int> > &cost, vector<long long> &distance, 
                    vector<int> &reachable, vector<int> &shortest, queue<int> &Q_shortest){
  bool updated = true;
  for (int i = 0; i < adj.size() && updated; i++) {
    updated = false;
    for (int j = 0; j < adj.size(); j++) {
      for (int k = 0; k < adj[j].size(); k++) {
        if (reachable[adj[j][k]] && distance[adj[j][k]] > distance[j] + cost[j][k]) {
          distance[adj[j][k]] = distance[j] + cost[j][k];
          updated = true;
          if (i == adj.size() - 1) {
            Q_shortest.push(adj[j][k]);
            shortest[adj[j][k]] = 1;
          }
        }
      }
    }
  }
}

void shortest_paths(const vector<vector<int> > &adj, const vector<vector<int> > &cost, const int s, vector<long long> &distance, 
                    vector<int> &reachable, vector<int> &shortest) {
  queue<int> Q_reachable;
  queue<int> Q_shortest;
  Q_reachable.push(s);
  distance[s] = 0;
  reachable[s] = 1;
  bfs(adj, reachable, Q_reachable);
  bellman_ford(adj, cost, distance, reachable, shortest, Q_shortest);
  if(!Q_shortest.empty())
    bfs(adj, shortest, Q_shortest);
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, inf);
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 0);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}