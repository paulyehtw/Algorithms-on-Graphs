#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>

using std::vector;
double inf = std::numeric_limits<double>::max();

struct point{
  double cost = inf;
  int idx;
  int x;
  int y;
};

bool compare_cost(const point &a, const point &b)
{
  return a.cost < b.cost;
}

double minimum_distance(vector<point> &points) {
  double result = 0.;
  points[0].cost = 0;
  while(points.size() > 0){
    std::sort(points.begin(), points.end(), compare_cost);
    point v = points.front();
    points.erase(points.begin());
    result += v.cost;
    for(int p = 0; p < points.size(); ++p){
      double x_diff = v.x - points[p].x;
      double y_diff = v.y - points[p].y;
      double cost_temp = sqrt(pow(x_diff,2) + pow(y_diff,2));
      if(points[p].cost > cost_temp)
        points[p].cost = cost_temp;
    }
  }
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  vector<point> points(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> points[i].x >> points[i].y;
    points[i].idx = i;
  }
  std::cout << std::setprecision(10) << minimum_distance(points) << std::endl;
}
