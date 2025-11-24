// Problem: CF 2089 E - Black Cat Collapse
// https://codeforces.com/contest/2089/problem/E

/*
E. Black Cat Collapse
Algorithm: Dynamic Programming on Trees with Combination Math
Time Complexity: O(n^4)
Space Complexity: O(n^3)

Task Description:
The world is a rooted tree with root at node 1. Each day, we can explore a node u that has not yet collapsed. After this exploration,
the black cat causes u and all nodes in its subtree to collapse. Additionally, at the end of the i-th day, if it exists, the number n-i+1 node will also collapse.
For each i from 1 to n, determine how many exploration schemes there are where exactly i operations happen, and the last operation is at node 1.
*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using i64 = long long;
constexpr int maxn = 90, mo = 998244353;
int T;
int n, sz[maxn], tmp[maxn], C[maxn][maxn], h[maxn][maxn], g[maxn][maxn],
    f[maxn][maxn][maxn];
vector<int> e[maxn];

inline int add(int x, int y) {
  x += y;
  return x < mo ? x : x - mo;
}
inline void upd(int &x, int y) {
  x = add(x, y);
  return;
}

void clean() {
  for (int i = 1; i <= n; ++i)
    vector<int>().swap(e[i]);
  memset(sz, 0, sizeof(sz));
  memset(h, 0, sizeof(h));
  memset(g, 0, sizeof(g));
  memset(f, 0, sizeof(f));
}

void solve() {
  clean();
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    if (u > v)
      swap(u, v);
    e[u].emplace_back(v); // Build the adjacency list for the tree
  }
  C[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = C[i][0] = 1; j <= i; ++j)
      C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]); // Precompute combinations using Pascal's triangle
  }
  f[n + 1][0][0] = 1; // Base case: when we're beyond the tree, no more operations left
  for (int i = n; i; --i) {
    h[i][0] = 1; // Initialize h[i][0] = 1 for leaf nodes or empty subtrees
    for (int x : e[i]) { // Process each child of node i
      fill(tmp, tmp + sz[i] + sz[x] + 1, 0); // Reset temp array
      for (int j = 0; j <= sz[i]; ++j) {
        for (int k = 0; k <= sz[x]; ++k)
          upd(tmp[j + k], (i64)h[i][j] * h[x][k] % mo * C[j + k][j] % mo); // Combine subtree results
      }
      sz[i] += sz[x]; // Update size of node i in terms of total nodes in this subtree
      for (int j = 0; j <= sz[i]; ++j)
        h[i][j] = tmp[j]; // Copy combined result back to h[i]
    }
    for (int j = 0; j <= sz[i]; ++j)
      g[i][j + 1] = h[i][j]; // Shift values for use in future calculations
    sz[i]++;
    for (int j = sz[i]; j; --j)
      upd(h[i][j], h[i][j - 1]); // Accumulate prefix sums of h[i]
    for (int j = 0; j <= n - i; ++j) { // Update transition states f based on the current node
      for (int k = j; k <= n; ++k) {
        if (!f[i + 1][j][k])
          continue;
        if (i > 1)
          upd(f[i][j][k], f[i + 1][j][k]); // Propagate valid transitions without exploring node i yet
        for (int l = k + 1; l <= n - i + 1; ++l)
          upd(f[i][j + 1][l], f[i + 1][j][k]); // Explore node i and update the state accordingly
      }
    }
    int v = i + sz[i];
    for (int j = 0; j <= n - v + 1; ++j) { // Calculate transitions considering collapse effect of node v
      for (int k = j; k <= n; ++k) {
        if (!f[v][j][k])
          continue;
        for (int l = 1; l <= min(k - j, sz[i]); ++l)
          upd(f[i][j + l][k], (i64)f[v][j][k] * C[k - j][l] % mo * g[i][l] % mo); // Combine current and substate properly
      }
    }
  }
  for (int i = 1; i <= n; ++i)
    cout << f[1][i][i] << " \n"[i == n]; // Print the answer for each day count
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/