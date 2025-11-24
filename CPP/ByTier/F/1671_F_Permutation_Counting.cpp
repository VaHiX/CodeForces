// Problem: CF 1671 F - Permutation Counting
// https://codeforces.com/contest/1671/problem/F
 
/*
 * Problem: F. Permutation Counting
 * 
 * Purpose: Count the number of permutations of size n with exactly k inversions and exactly x local inversions.
 * 
 * Algorithms/Techniques:
 * - Dynamic Programming with precomputed small cases
 * - Preprocessing all valid permutations up to length 12
 * - Fast exponentiation for modular inverse
 * - Combinatorial coefficient calculation with modular arithmetic
 * 
 * Time Complexity: O(n * k * x * len^3) where len is up to 12, so effectively O(n)
 * Space Complexity: O(n + len^4) where len is up to 12, so effectively O(1)
 * 
 * The solution uses a recursive backtracking approach to generate all valid small permutations (up to 12 elements),
 * and then applies dynamic programming on the structure of the problem to compute counts for larger n.
 */
 
#include <algorithm>
#include <iostream>
#include <random>
 
using namespace std;
#define int long long
#define double long double
#define endl '\n'
mt19937 rnd(537462565);
const int mod = 998244353;
 
// Add two numbers modulo mod
void ad(int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
}
 
// Fast exponentiation (modular exponentiation)
int qpow(int a, int b, int res = 1) {
  while (b) {
    if (b & 1)
      res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}
 
// Global variables
int cas, n, X, Y, a[20], dp[20][25][20][20], inv[20], cnt[20][20][20];
 
// Recursive function to generate permutations and count inversions and increasing pairs
void dfs(int p, int msk, int len, int x, int y, int mx) {
  if (x > 11 || y > 11) // Pruning condition based on limits
    return;
  if (p > len) {
    cnt[len][x][y]++; // Store the count for this specific combination
    return;
  }
  if (p > 1 && mx == p - 1) {
    return; // Early termination if the sequence is already increasing
  }
  for (int i = 1; i <= len; i++)
    if (msk >> i & 1) { // If i-th bit is set in mask
      int s = x, t = y;
      a[p] = i;
      for (int j = 1; j < p; j++)
        if (i < a[j])
          s++; // Count inversions
      if (p > 1 && a[p] < a[p - 1])
        t++; // Count local inversions (decreasing pairs)
      dfs(p + 1, msk ^ (1 << i), len, s, t, max(mx, i)); // Continue DFS
    }
}
 
// Compute combination C(n, k) modulo mod
int C(int x, int y) {
  if (x < 0 || y < 0 || x < y)
    return 0;
  if (x == 0)
    return 1;
  int t = 1;
  for (int i = 1; i <= y; i++)
    t = t * (x - i + 1) % mod * inv[i] % mod; // Modular division
  return t;
}
 
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
 
  // Precompute modular inverses using Fermat's little theorem
  for (int i = 1; i < 20; i++)
    inv[i] = qpow(i, mod - 2);
 
  // Generate counts for all permutations of sizes 2 to 12
  for (int i = 2; i <= 12; i++)
    dfs(1, (1 << i + 1) - 1, i, 0, 0, 0);
 
  // Initialize base case
  dp[0][0][0][0] = 1;
 
  // Dynamic programming to build up solutions for larger n
  for (int i = 0; i < 11; i++)
    for (int j = i; j <= 22; j++)
      for (int x = 0; x < 11; x++)
        for (int y = 0; y < 11 && y <= j - i; y++)
          for (int len = 1; j + len <= 22 && len <= 12; len++)
            for (int s = 1; x + s <= 11; s++)
              for (int t = 1; y + t <= 11; t++)
                ad(dp[i + 1][j + len][x + s][t + y], // Update DP
                   dp[i][j][x][y] * cnt[len][s][t] % mod);
 
  // Process queries
  cin >> cas;
  while (cas--) {
    cin >> n >> X >> Y;
    int ans = 0;
    // Accumulate answer using combinatorial formula
    for (int i = 0; i <= 11; i++)
      for (int j = i; j <= 22; j++)
        ad(ans, dp[i][j][X][Y] * C(n - j + i, i) % mod);
    cout << ans << endl;
  }
  return 0;
}
 
 
// https://github.com/VaHiX/CodeForces/