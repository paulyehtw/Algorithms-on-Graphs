#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > get_reverse_graph(const vector<vector<int> > &adj){
	vector<vector<int> > r_adj(adj.size());
	for (size_t i = 0; i < adj.size(); ++i) 
		for (size_t j = 0; j < adj[i].size(); ++j) 
			r_adj[adj[i][j]].push_back(i);
	return r_adj;
}

void dfs_rev(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
	used[x] = 1;
	for (size_t i = 0; i < adj[x].size(); i++)
		if (!used[adj[x][i]])
			dfs_rev(adj, used, order, adj[x][i]);
	order.push_back(x);
} 

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  for(int i = 0; i < used.size(); ++i)
    if(used[i] != 1)
      dfs_rev(adj, used, order, i);
  reverse(order.begin(),order.end()); 
  return order;
}

void dfs(int x, const vector<vector<int> > &adj, vector<int> &used)
{
	used[x] = 1;
	for (size_t i = 0; i < adj[x].size(); i++) 
		if (!used[adj[x][i]]) 
			dfs(adj[x][i], adj, used);
}

int number_of_strongly_connected_components(const vector<vector<int> > &adj)
{
	vector<vector<int> > r_adj = get_reverse_graph(adj);
	vector<int> order = toposort(r_adj);
	vector<int> visited(adj.size(), 0);
	int	cnt = 0;
	for (size_t i = 0; i < order.size(); i++) {
		int	v = order[i];
		if (!visited[v]) {
			dfs(v, adj, visited);
			cnt++;
		}
	}
	return cnt;
}

int main()
{
	size_t n, m;
	cin >> n >> m;
	vector<vector<int> > adj(n);
	for (size_t i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		adj[x - 1].push_back(y - 1);
	}
	cout << number_of_strongly_connected_components(adj) << endl;
	return 0;
}