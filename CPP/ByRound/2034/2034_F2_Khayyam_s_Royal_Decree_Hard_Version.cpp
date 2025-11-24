// Problem: CF 2034 F2 - Khayyam's Royal Decree (Hard Version)
// https://codeforces.com/contest/2034/problem/F2

/*
F2. Khayyam's Royal Decree (Hard Version)
Algorithms/Techniques: Dynamic Programming, Combinatorics, Probabilities, Modular Arithmetic

Time Complexity: O(k^2 + n + m + k * log(mod)) where k is the number of scrolls,
                 and n, m are the count of red rubies and blue sapphires respectively.
Space Complexity: O(n + m + k^2) for precomputed factorials, DP arrays, and node storage.

This solution computes the expected value of gems in Khayyam's satchel at the end of the game,
accounting for special conditions which double the value when certain counts are reached.
It uses combinatorics to calculate probabilities and dynamic programming to compute
transition values efficiently.
*/

#include <algorithm>
#include <stdio.h>
using namespace std;

const int N = 5010, M = 4e5 + 10, mod = 998244353;

struct node {
  int x, y;
  // Custom comparison operator to sort by sum of coordinates
  int operator<(const node &a) const { return x + y < a.x + a.y; };
} a[N];

int fac[M], inv[M], w[N];

// Fast exponentiation: returns (a^b) % mod
int qpow(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1)
      ans = 1ll * ans * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return ans;
}

// Precompute factorials and inverse factorials up to n
void pre(int n) {
  fac[0] = 1;
  for (int i = 1; i <= n; i++)
    fac[i] = 1ll * i * fac[i - 1] % mod;
  inv[n] = qpow(fac[n], mod - 2);
  for (int i = n; i >= 1; i--)
    inv[i - 1] = 1ll * i * inv[i] % mod;
}

// Compute combination C(n, m) using precomputed factorials
int C(int n, int m) { return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod; }

void solve() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  
  // Read the special conditions: r_i, b_i (0-indexed in array a)
  for (int i = 1; i <= k; i++) {
    scanf("%d%d", &a[i].x, &a[i].y);
    // Transform coordinates to relative to end point (n,m) -> difference from start
    a[i].x = n - a[i].x;
    a[i].y = m - a[i].y;
  }

  // Initialize start and end points
  a[0].x = a[0].y = 0;
  a[k + 1].x = n;
  a[k + 1].y = m;

  // Sort by the sum of coordinates to process in order (topological sort)
  sort(a + 1, a + k + 1);

  // w[i] stores the number of paths from point i to end that satisfy the conditions
  w[k + 1] = 1;
  for (int i = k; i >= 1; i--) {
    w[i] = 0;
    for (int j = i + 1; j <= k + 1; j++) {
      // Check if point j is reachable from point i
      if (a[i].x <= a[j].x && a[i].y <= a[j].y) {
        int X = a[j].x - a[i].x, Y = a[j].y - a[i].y;
        // Add contribution of path from j to end using combinations C(X+Y, X)
        w[i] = (w[i] + 1ll * w[j] * C(X + Y, X)) % mod;
      }
    }
  }

  // Calculate expected value
  int ans = 0;
  for (int i = 1; i <= k + 1; i++) {
    // For each point we can reach, compute contribution of that point's value:
    // t = 2 * x + y because red gives 2 and blue gives 1. Then multiply with path count
    int t = 2 * a[i].x + a[i].y;
    ans = (ans + 1ll * t * C(a[i].x + a[i].y, a[i].x) % mod * w[i]) % mod;
  }

  // Normalize by total number of sequences
  ans = 1ll * ans * fac[n] % mod * fac[m] % mod * inv[n + m] % mod;
  printf("%d\n", ans);
}

int main() {
  int T;
  pre(4e5); // Precompute factorials up to max possible n+m
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/