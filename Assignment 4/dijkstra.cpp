#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

int inf = std::numeric_limits<int>::max();

int extract_min(vector<int> &H, const vector<int> &dist, vector<int> &in_H){
  int remove_idx = 0;
  int min_vertex = H[remove_idx];
  int min_dis = dist[H[remove_idx]];
  for(int i = 0; i < H.size(); ++i){
    if(dist[H[i]] < min_dis){
      min_dis = dist[H[i]];
      min_vertex = H[i];
      remove_idx = i;
    }
  }
  H.erase(H.begin() + remove_idx);
  in_H[remove_idx] = 0;
  return min_vertex;
}

int distance(const vector<vector<int> > &adj, const vector<vector<int> > &cost, const int s, const int t) {
  vector<int> dist(adj.size(), inf);
  vector<int> H;
  vector<int> in_H(adj.size(), 0);
  dist[s] = 0;
  H.push_back(s);
  while(H.size() > 0){
    int u = extract_min(H, dist, in_H);
    for(size_t i = 0; i < adj[u].size(); ++i){
      int dist_temp = dist[u] + cost[u][i];
      if(dist[adj[u][i]] > dist_temp){
        dist[adj[u][i]] = dist_temp;
        if(in_H[adj[u][i]] == 0){
          H.push_back(adj[u][i]);
          in_H[adj[u][i]] = 1;
        }
      }
    }
  }
  if(dist[t] == inf)
    return -1;
  return dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
