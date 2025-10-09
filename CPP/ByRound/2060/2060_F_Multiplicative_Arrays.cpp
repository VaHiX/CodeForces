// Problem: CF 2060 F - Multiplicative Arrays
// https://codeforces.com/contest/2060/problem/F

/*
F. Multiplicative Arrays

Purpose:
This code computes the number of integer arrays of length at most n,
with each element between 1 and k, such that their product equals x for each x from 1 to k.

Algorithms/Techniques:
- Preprocessing using dynamic programming to compute dp[i][j] = number of ways to represent j as a product of i factors <= k
- Combinatorial formulas to compute C[i] = binomial coefficients (n+1 choose i)
- Modular exponentiation for fast modular inverse

Time Complexity: O(k * log k + n)
Space Complexity: O(k)

*/

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 100005, M = 998244353;
int dp[22][N], C[30];

// Fast modular exponentiation
int qp(int x, int y = M - 2) {
  int r = 1;
  while (y) {
    if (y & 1)
      r = 1ll * r * x % M;
    x = 1ll * x * x % M;
    y = y / 2;
  }
  return r;
}

// Initialize dp table
void init() {
  int m = 100000;
  for (int i = 2; i <= m; i++)
    dp[1][i] = 1;
  for (int i = 1; i <= 18; i++)
    for (int j = 2; j <= m; j++)
      for (int k = 2; j * k <= m; k++)
        dp[i + 1][j * k] = (dp[i + 1][j * k] + dp[i][j]) % M;
}

// Solve for a single test case
void solve() {
  int k, n;
  cin >> k >> n;
  C[1] = n + 1;
  for (int i = 2; i <= min(22, n + 1); i++)
    C[i] = 1ll * C[i - 1] * (n + 2 - i) % M * qp(i) % M; // Compute binomial coefficients
  for (int x = 1; x <= k; x++) {
    if (x == 1)
      cout << n << ' ';
    else {
      int ans = 0;
      for (int i = 1; i <= min(n, 18); i++)
        ans = (ans + 1ll * dp[i][x] * C[i + 1]) % M;
      cout << ans << ' ';
    }
  }
  cout << '\n';
}

int main() {
  init();
  int nc;
  cin >> nc;
  while (nc--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/