// Problem: CF 2112 F - Variables and Operations
// https://codeforces.com/contest/2112/problem/F

/*
F. Variables and Operations
time limit per test5 seconds
memory limit per test512 megabytes

Task:
There are n variables; let's denote the value of the i-th variable as a_i.
There are also m operations which will be applied to these variables; the i-th operation is described by three integers x_i, y_i, z_i. When the i-th operation is applied, the variable x_i gets assigned the following value:
min(a_x_i, a_y_i + z_i).
Every operation will be applied exactly once, but their order is not fixed; they can be applied in any order.
Let's call a sequence of initial variable values a_1, a_2, ..., a_n stable, if no matter in which order we apply operations, the resulting values will be the same. If the resulting value of the i-th variable depends on the order of operations, then the sequence of initial variable values is called i-unstable.
You have to process q queries. In each query, you will be given initial values a_1, a_2, ..., a_n and an integer k; before applying the operations, you can at most k times choose a variable and decrease it by 1. For every variable i, you have to independently determine if it is possible to transform the given values into an i-unstable sequence.

Algorithms/Techniques:
- Floyd-Warshall for computing shortest paths
- Greedy approach with binary search on answer

Time Complexity: O(n^3 + q * n^2)
Space Complexity: O(n^2)

*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int N = 505;
const int INF = 1e9 + 5;
int n, m;
int x, y, z;
int dp[N][N];
int q;
int k;
int a[N];

void solve() {
  cin >> n >> m;
  vector<vector<int>> f(n, vector<int>(n, INF));
  for (int i = 0; i < n; i++)
    f[i][i] = 0;
  for (int i = 0; i < m; i++) {
    cin >> x >> y >> z;
    x--, y--;
    f[x][y] = min(f[x][y], z);  // Store weight of edge from x to y
  }
  vector<vector<int>> g = f;
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]); // Floyd-Warshall DP
      }
    }
  }
  cin >> q;
  while (q--) {
    cin >> k;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    string ans(n, '0');
    for (int i = 0; i < n; i++) {
      int z = a[i];
      // Find minimum value through paths involving all other nodes
      for (int j = 0; j < n; j++) {
        z = min(z, f[i][j] + a[j]);
      }
      // Check if making node i unstable is possible with at most k decreases
      for (int j = 0; j < n; j++) {
        if (g[i][j] + a[j] - k < min(z, f[i][j] + a[j] - k)) {
          ans[i] = '1';
          break;
        }
      }
    }
    cout << ans << endl;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int yt = 1;
  while (yt--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/