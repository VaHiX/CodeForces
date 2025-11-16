// Problem: CF 1949 A - Grove
// https://codeforces.com/contest/1949/problem/A

// # Maximum Trees in Lawn
// ## Problem Description
// We are given a square lawn of size n×n with integer coordinates and need to plant the maximum number of trees such that:
// - Each tree is planted at an integer coordinate point
// - Each tree's roots form a disk of radius r centered at that point
// - All disks must fit entirely within the lawn (can touch boundary)
// - Disks can only intersect on their boundaries
// - We want to maximize the number of trees

// ## Algorithm Approach
// This problem is solved using a maximum clique algorithm in a graph where vertices are valid planting positions and edges represent conflicting placements (disks that overlap).

// ## Complexity
// **Time Complexity**: O(3^(n/3)) in worst case for maximum clique, where n is the number of valid positions.
// **Space Complexity**: O(n^2) for storing the graph and auxiliary arrays.

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

using namespace std;
using ll = long long;
#define all(a) (a).begin(), (a).end()
#ifdef DEBUG
template <class T> ostream &operator<<(ostream &out, vector<T> a) {
  out << '[';
  for (T x : a)
    out << x << ',';
  return out << ']';
}
template <class T> vector<T> ary(T *a, int l, int r) {
  return vector<T>{a + l, a + 1 + r};
}
template <class T> void debug(T x) { cerr << x << endl; }
template <class T, class... S> void debug(T x, S... y) {
  cerr << x << ' ', debug(y...);
}
#else
#define debug(...) void()
#endif
const int N = 405;
struct MaxClique {
  bool g[N][N];  // Graph adjacency matrix
  int n, dp[N], st[N][N], ans, res[N];  // dp[i] stores max clique size starting from vertex i
  void init(int n) {
    this->n = n;
    memset(g, false, sizeof(g));
  }
  void addedge(int u, int v, int w) { g[u][v] = w; }  // Add edge to graph
  int stk[N];
  bool dfs(int sz, int num) {
    if (sz == 0) {
      if (num > ans) {
        ans = num;
        copy(stk + 1, stk + 1 + num, res + 1);
        return true;
      }
      return false;
    }
    for (int i = 0; i < sz; i++) {
      if (sz - i + num <= ans)
        return false;  // Pruning: early termination if impossible to improve
      int u = st[num][i];
      if (dp[u] + num <= ans)
        return false;  // Pruning: can't improve current best
      int cnt = 0;
      for (int j = i + 1; j < sz; j++) {
        if (g[u][st[num][j]])
          st[num + 1][cnt++] = st[num][j];  // Build subgraph for next recursive call
      }
      stk[num + 1] = u;
      if (dfs(cnt, num + 1))
        return true;
    }
    return false;
  }
  int solver() {
    ans = 0;
    memset(dp, 0, sizeof(dp));
    for (int i = n; i >= 1; i--) {
      int cnt = 0;
      for (int j = i + 1; j <= n; j++) {
        if (g[i][j])
          st[1][cnt++] = j;
      }
      stk[1] = i;
      dfs(cnt, 1);
      dp[i] = ans;  // Store max clique size from this node
    }
    return ans;
  }
} S;
const double eps = 1e-9;
int n, k, id[N][N];
pair<int, int> p[N * N];
double r;
int main() {
  scanf("%d%lf", &n, &r);
  // Precompute valid positions where tree can be planted
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      if (min({i, j, n - i, n - j}) > r - eps) {
        id[i][j] = ++k, p[k] = {i, j};  // Valid position only if at least r distance from boundary
      }
    }
  }
  S.init(k);  // Initialize graph with k nodes
  // Add edges between positions that are too close to each other
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      if (!id[i][j])
        continue;
      for (int x = 0; x <= n; x++) {
        for (int y = 0; y <= n; y++) {
          if (!id[x][y])
            continue;
          int dx = i - x, dy = j - y;
          double dis = sqrt(dx * dx + dy * dy);
          // If distance is greater than 2*r, disks don't overlap
          if (dis + eps > r + r)
            S.addedge(id[i][j], id[x][y], 1);
        }
      }
    }
  }
  int ans = S.solver();
  cout << ans << endl;
  for (int i = 1; i <= ans; i++) {
    auto [x, y] = p[S.res[i]];
    printf("%d %d\n", x, y);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/