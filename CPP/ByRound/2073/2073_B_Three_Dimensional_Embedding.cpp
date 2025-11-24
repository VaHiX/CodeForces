// Problem: CF 2073 B - Three-Dimensional Embedding
// https://codeforces.com/contest/2073/problem/B

#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <utility>
#include <vector>

using namespace std;
int n, m, i, j, k, a, b, x, y, d, deg[1610], X[1610], Y[1610], col[4010];
vector<pair<int, int>> edge;
vector<pair<int, int>> adj[1610];
struct pnt {
  int x, y, z;
};
// Function to create a polyline for an edge starting from vertex i
// h is the height (z-coordinate) of the polyline
// YY is a parameter used to compute offset for connecting polylines
vector<pnt> f(int i, int h, int YY) {
  vector<pnt> ans;
  int x = X[i], y = Y[i];
  deg[i]++;
  ans.push_back({x, y, 0});
  int Y = 0;
  if (deg[i] == 1) {
    ans.push_back({x - 1, y, 0});
    ans.push_back({x - 1, y - 2, 0});
    ans.push_back({x, y - 2, 0});
    Y = y - 2;
  } else if (deg[i] == 2) {
    ans.push_back({x, y - 1, 0});
    Y = y - 1;
  } else if (deg[i] == 3)
    Y = y;
  else if (deg[i] == 4) {
    ans.push_back({x, y + 1, 0});
    Y = y + 1;
  } else if (deg[i] == 5) {
    ans.push_back({x + 1, y, 0});
    ans.push_back({x + 1, y + 2, 0});
    ans.push_back({x, y + 2, 0});
    Y = y + 2;
  }
  ans.push_back({x, Y, h});
  ans.push_back({x - 1, Y, h});
  ans.push_back({x - 1, 400 - YY, h});
  ans.push_back({x - 1, 400 - YY, h + 1});
  return ans;
}
// Function to create another polyline for an edge starting from vertex i
// Similar to f but with a slightly different configuration for Y-coordinate
vector<pnt> g(int i, int h) {
  vector<pnt> ans;
  int x = X[i], y = Y[i];
  deg[i]++;
  ans.push_back({x, y, 0});
  int Y = 0;
  if (deg[i] == 1) {
    ans.push_back({x - 1, y, 0});
    ans.push_back({x - 1, y - 2, 0});
    ans.push_back({x, y - 2, 0});
    Y = y - 2;
  } else if (deg[i] == 2) {
    ans.push_back({x, y - 1, 0});
    Y = y - 1;
  } else if (deg[i] == 3)
    Y = y;
  else if (deg[i] == 4) {
    ans.push_back({x, y + 1, 0});
    Y = y + 1;
  } else if (deg[i] == 5) {
    ans.push_back({x + 1, y, 0});
    ans.push_back({x + 1, y + 2, 0});
    ans.push_back({x, y + 2, 0});
    Y = y + 2;
  }
  ans.push_back({x, Y, h});
  ans.push_back({x + 1, Y, h});
  return ans;
}
vector<pnt> ans[4010];
int main() {
  // Read input: number of vertices and edges
  scanf("%d %d", &n, &m);
  for (i = 0; i < m; i++) {
    scanf("%d %d", &a, &b);
    edge.push_back({a, b});
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
  }
  // Grid-based initialization of vertex coordinates
  d = (sqrt(n) / 3);
  d = max(d, 1);
  for (i = 1; i <= n; i++) {
    a = (i - 1) / d, b = (i - 1) % d;
    X[i] = 3 * a + 1;
    Y[i] = 5 * b + 2;
  }
  int mx = 0;
  for (j = 0; j < edge.size(); j++) {
    a = edge[j].first, b = edge[j].second;
    if (X[a] == X[b])
      continue;
    int c = (a - 1) / d, dd = (b - 1) / d;
    vector<int> A(10 * d);
    for (i = c * d + 1; i <= c * d + d; i++) {
      for (auto q : adj[i])
        A[col[q.second]] = 1;
    }
    for (i = dd * d + 1; i <= dd * d + d; i++) {
      for (auto q : adj[i])
        A[col[q.second]] = 1;
    }
    for (i = 1; i < A.size(); i++)
      if (A[i] == 0)
        break;
    col[j] = i;
    mx = max(mx, i);
  }
  for (i = 1; i <= mx; i++) {
    int cnt = 0;
    for (j = 0; j < edge.size(); j++) {
      a = edge[j].first, b = edge[j].second;
      if (col[j] != i)
        continue;
      cnt++;
      vector<pnt> V1 = f(a, 2 * i - 1, cnt), V2 = f(b, 2 * i - 1, cnt);
      while (V2.size()) {
        V1.push_back(V2.back());
        V2.pop_back();
      }
      ans[j] = V1;
    }
  }
  int h = 2 * mx;
  for (j = 0; j < edge.size(); j++) {
    a = edge[j].first, b = edge[j].second;
    if (X[a] != X[b])
      continue;
    h++;
    vector<pnt> V1 = g(a, h), V2 = g(b, h);
    while (V2.size()) {
      V1.push_back(V2.back());
      V2.pop_back();
    }
    ans[j] = V1;
  }
  for (i = 1; i <= n; i++)
    printf("%d %d\n", X[i], Y[i]);
  for (j = 0; j < edge.size(); j++) {
    printf("%d ", ans[j].size());
    for (auto p : ans[j]) {
      printf("%d %d %d ", p.x, p.y, p.z);
    }
    puts("");
  }
}

// https://github.com/VaHiX/CodeForces/