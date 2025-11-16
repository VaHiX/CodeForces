// Problem: CF 2161 F - SubMST
// https://codeforces.com/contest/2161/problem/F

/*
Algorithm: 
- This code computes the sum of MST weights over all possible subsets of vertices in a tree.
- It uses a technique based on edge counting in the metric graph induced by the tree.
- For each edge in the tree, we compute how many times it contributes to MSTs of various subsets.
- The key idea involves:
  1. Converting the tree into a metric graph where edge weights are distances.
  2. For each edge, we determine how many subsets of vertices will have this edge in their MST.
  3. To count this, we do a DFS traversal and use prefix/suffix sums of depths to compute the contribution.
- This approach relies on tree decomposition and careful counting of vertex subsets.
Time Complexity: O(n^3), due to nested loops and processing per edge
Space Complexity: O(n^2), to store adjacency list and auxiliary arrays
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;
#define rp(i, x, y) for (int i = (x); i <= (y); ++i)
#define pr(i, x, y) for (int i = (x); i >= (y); --i)
#define pi pair<int, int>
typedef long long ll;
#define eb emplace_back
#define all(x) x.begin(), x.end()
#define vi vector<int>
#define vvi vector<vi>
const int MOD = 1e9 + 7;
const int N = 5005;
int n, pw[N];
int qp(int a, int k) {
  int ans = 1;
  for (; k; k >>= 1) {
    if (k & 1)
      ans = 1ll * ans * a % MOD;
    a = 1ll * a * a % MOD;
  }
  return ans;
}
void slv() {
  cin >> n;
  vector<vi> to(2 * n + 1);
  rp(i, 1, n - 1) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    to[u].eb(n - 1 + i);
    to[v].eb(n - 1 + i);
    to[n - 1 + i].eb(u);
    to[n - 1 + i].eb(v);
  }
  int ans = 0, nn = 2 * n - 1;
  vi dep(nn), in(nn), out(nn), id(nn);
  int tim = 0;
  function<void(int, int)> dfs = [&](int u, int fa) {
    in[u] = ++tim;
    id[tim] = u;
    for (auto v : to[u])
      if (v != fa) {
        dep[v] = dep[u] + 1;
        dfs(v, u);
      }
    out[u] = tim;
  };
  vi a(nn), b(nn);
  rp(u, 0, nn - 1) {
    tim = dep[u] = 0;
    dfs(u, -1);
    for (auto v : to[u])
      if (u < v) {
        fill(all(a), 0);
        fill(all(b), 0);
        rp(i, 1, nn) {
          int x = id[i];
          if (x >= n)
            continue;
          if (i >= in[v] && i <= out[v])
            ++a[dep[x] - 1];
          else
            ++b[dep[x]];
        }
        pr(i, nn - 2, 0) a[i] += a[i + 1], b[i] += b[i + 1];
        rp(i, 0, nn - 1) if (a[i] && b[i]) ans =
            (ans + 1ll * (pw[a[i]] - 1) * (pw[b[i]] - 1)) % MOD;
        else break;
      }
    fill(all(a), 0);
    fill(all(b), 0);
    for (auto v : to[u]) {
      int d = 0;
      rp(i, in[v], out[v]) {
        int x = id[i];
        if (x < n)
          ++b[dep[x] - 1], d = max(d, dep[x] - 1);
      }
      pr(i, d - 1, 0) b[i] += b[i + 1];
      rp(i, 0, d) {
        ans = (ans + pw[b[i]] - 1) % MOD;
        a[i] += b[i];
        b[i] = 0;
      }
    }
    rp(i, 0, nn - 1) ans = (ans + MOD - (pw[a[i]] - 1)) % MOD;
  }
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  pw[0] = 1;
  rp(i, 1, N - 2) pw[i] = 2ll * pw[i - 1] % MOD;
  int T = 1;
  cin >> T;
  while (T--)
    slv();
  return 0;
}


// https://github.com/VaHiX/CodeForces/