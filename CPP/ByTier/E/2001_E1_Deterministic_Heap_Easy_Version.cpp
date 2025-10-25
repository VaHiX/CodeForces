// Problem: CF 2001 E1 - Deterministic Heap (Easy Version)
// https://codeforces.com/contest/2001/problem/E1

/*
 * Problem: E1. Deterministic Heap (Easy Version)
 * Purpose: Count the number of different deterministic max-heaps that can be formed by applying 'add' operation exactly k times on a perfect binary tree of size 2^n - 1.
 * Algorithms/Techniques:
 *   - Dynamic Programming with memoization
 *   - Tree traversal logic and heap property constraints
 * Time Complexity: O(n * k^2) per test case
 * Space Complexity: O(n * k) for DP tables
 */

#include <stdint.h>
#include <string.h>
#include <iostream>

using namespace std;
const int MAX = 505;
int dp_f[MAX][MAX], dp_g[MAX][MAX];
int MOD;

// Function g(n, k): Computes number of ways to distribute k operations among n nodes such that heap properties hold
int g(int n, int k) {
  if (k < 0)
    return 0;
  if (n == 1)
    return 1;
  int &ret = dp_g[n][k];
  if (~ret)
    return ret;
  ret = g(n, k - 1); // Base case: do not use any operation
  for (int a = 0; a <= k; a++) {
    int b = k - a;
    ret = (ret + 1LL * g(n - 1, a) * g(n - 1, b)) % MOD;
  }
  return ret;
}

// Function f(n, k): Computes number of deterministic max-heaps with n nodes and k operations
int f(int n, int k) {
  if (k < 0)
    return 0;
  if (n == 1)
    return 1;
  int &ret = dp_f[n][k];
  if (~ret)
    return ret;
  ret = f(n, k - 1); // Base case: do not use any operation
  for (int a = 0; 2 * a < k; a++) {
    int b = k - a;
    ret = (ret + 2LL * g(n - 1, a) * f(n - 1, b)) % MOD;
  }
  return ret;
}

void solve() {
  int n, k;
  cin >> n >> k >> MOD;
  memset(dp_f, -1, sizeof dp_f);
  memset(dp_g, -1, sizeof dp_g);
  cout << f(n, k) << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/