// Problem: CF 1704 E - Count Seconds
// https://codeforces.com/contest/1704/problem/E

/*
 * Problem: Count Seconds
 * 
 * Purpose: 
 *   Given a directed acyclic graph (DAG) with node values, simulate a process
 *   where each second, all nodes with positive values decrement by 1, and
 *   their outgoing edges propagate 1 to the next nodes. Return the time when
 *   all values become 0.
 * 
 * Algorithm:
 *   - Simulation with topological sorting
 *   - For small steps, simulate the process directly
 *   - For large steps, compute the final contribution using topological order
 * 
 * Time Complexity:
 *   O(n^2) per test case in worst case due to simulation, but optimized via
 *   early termination when all nodes reach 0.
 * 
 * Space Complexity:
 *   O(n + m) for adjacency list and auxiliary arrays.
 * 
 * Techniques:
 *   - Simulation with topological sorting
 *   - Modular arithmetic for large results
 * 
 * Note:
 *   The first part simulates step-by-step until all values are 0.
 *   The second part calculates remaining time with topological order.
 * 
 */

#include <algorithm>
#include <iostream>
#include <vector>

#define ll long long
#define mod 998244353
using namespace std;

ll a[1010], na[1010], rd[1010], vis[1010];
vector<int> e[1010];

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, m, i, j, flg = 0;
    cin >> n >> m;
    for (i = 1; i <= n; i++) {
      cin >> a[i];
      e[i].clear();
      rd[i] = 0;
      vis[i] = 0;
    }
    for (i = 1; i <= m; i++) {
      int u, v;
      cin >> u >> v;
      e[u].push_back(v);
      rd[v]++;
    }
    ll ans = 0;
    for (i = 1; i <= n + 2; i++) {
      int f = 0;
      for (j = 1; j <= n; j++) {
        na[j] = a[j];
        if (a[j])
          f = 1;
      }
      if (!f) {
        flg = 1;
        break;
      }
      for (j = 1; j <= n; j++)
        if (a[j]) {
          na[j]--;
          f = 1;
          for (auto p : e[j])
            na[p]++;
        }
      for (j = 1; j <= n; j++)
        a[j] = na[j];
      ans++;
    }
    if (flg) {
      cout << ans % mod << endl;
      continue;
    }
    ll res = 0, s = 0;
    for (i = 1; i <= n; i++) {
      int p = 0;
      for (j = 1; j <= n; j++)
        if (!vis[j] && rd[j] == 0) {
          p = j;
          break;
        }
      vis[p] = 1;
      if (i == n) {
        res = a[p];
        break;
      }
      for (auto q : e[p])
        (a[q] += a[p]) %= mod, rd[q]--;
    }
    cout << (ans + res) % mod << endl;
  }
}


// https://github.com/VaHiX/CodeForces/