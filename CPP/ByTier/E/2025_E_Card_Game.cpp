// Problem: CF 2025 E - Card Game
// https://codeforces.com/contest/2025/problem/E

/*
E. Card Game
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n * m^2)
Space Complexity: O(n * m)

This problem counts valid card distributions where the first player can win a card game.
The key idea is to model the matching game using dynamic programming, involving combinations and recursion
to determine how many subsets of cards can beat other subsets.

The core DP state g[i][j] represents number of ways to assign j cards among i suits such that
the assignment allows the first player to win. The recurrence involves convolution of combinations
and a helper function f which computes certain combinatorial values based on suit/rank dominance.
*/

#include <iostream>

#define mod 998244353
using namespace std;
const int N = 510;
int n, m, fc[N], f[N], g[N][N]; // fc: factorial array, f: helper function values, g: DP table

// Fast exponentiation
int ksm(int a, int b) {
  int tmp = 1;
  while (b) {
    if (b & 1)
      tmp = 1ll * tmp * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return tmp;
}

// Compute combination C(n, m) using precomputed factorials
int c(int n, int m) {
  return 1ll * fc[n] * ksm(fc[m], mod - 2) % mod * ksm(fc[n - m], mod - 2) % mod;
}

int main() {
  cin >> n >> m;
  fc[0] = 1;
  for (int i = 1; i <= m; i++)
    fc[i] = 1ll * fc[i - 1] * i % mod;

  // Precompute f[i] for even values of i
  for (int i = 0; i <= m; i += 2)
    f[i] = (c(m, (m + i) / 2) - c(m, (m + i) / 2 + 1) + mod) % mod;

  // Initialize g[1][0] = 1 as base case
  g[1][0] = 1;
  for (int i = 2; i <= n; i++) // For each number of suits from 2 to n
    for (int j = 0; j <= m; j += 2) // For even numbers of cards
      for (int k = 0; k <= j; k += 2) // Convolution step over all valid k
        g[i][j] = (g[i][j] + 1ll * g[i - 1][j - k] * f[k] % mod) % mod;

  int ans = 0;
  for (int i = 0; i <= m; i += 2) {
    // Sum up contributions to final answer using convolution again
    ans = (1ll * g[n][i] * f[i] % mod + ans) % mod;
  }
  cout << ans;
  return 0;
}


// https://github.com/VaHiX/codeForces/