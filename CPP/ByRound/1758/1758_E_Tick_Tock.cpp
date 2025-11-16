// Problem: CF 1758 E - Tick, Tock
// https://codeforces.com/contest/1758/problem/E

/*
 * Problem: E. Tick, Tock
 * Purpose: Determine the number of ways to assign hours to empty cells in a grid
 *          such that all clocks can be made to show the same time through row/column shifts.
 *
 * Algorithm:
 * - Model the problem as a system of modular equations.
 * - Each row/column shift operation creates a constraint: (hour_in_row + shift) % h == target_hour
 * - Build a graph of constraints and use DFS to detect inconsistencies and count free variables.
 * - The answer is h^(number_of_free_variables - 1) (since one variable is determined by others).
 *
 * Time Complexity: O(n * m) per test case, due to graph traversal and union-find like operations.
 * Space Complexity: O(n * m) for storing the adjacency list and auxiliary arrays.
 */

#include <string.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
#define M 1000000007
ll i, j, k, n, m, t, f[500500], res, li;
ll ksm(ll a, ll p) {
  ll res = 1;
  while (p) {
    if (p & 1) {
      res = res * a % M;
    }
    a = a * a % M;
    p >>= 1;
  }
  return res;
}
vector<pair<ll, ll>> v[500500];
void dfs(ll x) {
  for (auto [i, j] : v[x]) {
    if (f[i] != -1) {
      // Check if current assignment satisfies the constraint
      if (((f[x] + f[i]) % li) != j) {
        res = -1;
        return;
      }
      continue;
    }
    if (res == -1)
      return;
    // Assign value such that constraint is satisfied
    f[i] = (j + (li - f[x])) % li;
    dfs(i);
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> li;
    memset(f, -1, (n + m) * 8 + 50);
    for (i = 1; i <= n; i++)
      for (j = 1; j <= m; j++) {
        cin >> k;
        if (k == -1)
          continue;
        // Add constraints between row and column
        v[i].push_back({j + n, k});
        v[j + n].push_back({i, k});
      }
    res = 0;
    for (i = 1; i <= n + m; i++) {
      if (f[i] != -1)
        continue;
      res++; // Increment free variable count
      f[i] = 0;
      dfs(i);
      if (res == -1) {
        cout << 0 << '\n';
        goto aaa;
      }
    }
    // Output result using modular exponentiation
    cout << ksm(li, res - 1) << '\n';
  aaa:;
    for (i = 1; i <= n + m; i++)
      v[i].clear();
  }
}


// https://github.com/VaHiX/CodeForces/