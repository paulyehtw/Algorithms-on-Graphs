#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>

using std::vector;
double inf = std::numeric_limits<double>::max();

struct edge{
  double dist = inf;
  int point_a;
  int point_b;
};

struct node {
  int x;
  int y;
  int parent;
  int rank = 0;
};

void make_set(vector<node> &nodes, vector<int> &x, vector<int> &y) {
  node n;
  for(int i = 0; i < x.size(); i++){
    n.x = x[i];
    n.y = y[i];
    n.parent = i;
    n.rank = 0;
    nodes.push_back(n);
  }
}

void make_edges(vector<edge> &edges, vector<int> &x, vector<int> &y){
  edge edge_temp;
  for(int i = 0; i < x.size(); ++i){
    for(int j = i + 1; j < x.size(); ++j){
      edge_temp.dist = sqrt(pow(x[i] - x[j],2) + pow(y[i] - y[j],2));
      edge_temp.point_a = i;
      edge_temp.point_b = j;
      edges.push_back(edge_temp);
    }
  }
}

bool compare_dist(const edge &a, const edge &b)
{
  return a.dist < b.dist;
}

int find(int i, vector<node> &nodes) {
  if (i != nodes[i].parent)
    nodes[i].parent = find(nodes[i].parent, nodes);
  return nodes[i].parent;
}

void unite(int u, int v, vector<node> &nodes) {
  int r1 = find(u, nodes);
  int r2 = find(v, nodes);
  if (r1 != r2) {
    if (nodes[r1].rank > nodes[r2].rank) {
      nodes[r2].parent = r1;
    } else {
      nodes[r1].parent = r2;
      if (nodes[r1].rank == nodes[r2].rank)
        nodes[r2].rank++;
    }
  }
}

double clustering(vector<int> x, vector<int> y, int k) {
  int cluster_num = 0;
  vector<node> nodes;
  vector<edge> edges;
	make_set(nodes, x, y);
  make_edges(edges, x, y);
  std::sort(edges.begin(), edges.end(), compare_dist);
  for (int i = 0; i < edges.size(); i++) {
    int point_a = edges[i].point_a;
    int point_b = edges[i].point_b;
    if (find(point_a, nodes) != find(point_b, nodes)) {
	    cluster_num++;
      unite(point_a, point_b, nodes);
    }
    if(cluster_num > x.size() - k) 
      return edges[i].dist;
  }
  return -1.;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
