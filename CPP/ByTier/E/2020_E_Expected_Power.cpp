// Problem: CF 2020 E - Expected Power
// https://codeforces.com/contest/2020/problem/E

/*
 * Problem: E. Expected Power
 * Algorithm: Dynamic Programming with Bitmasking
 * Purpose: Compute expected value of (XOR of elements in random multiset)^2
 *
 * Time Complexity: O(n * log(max_a) * 2^k), where k=10 (bits considered)
 * Space Complexity: O(log(max_a) * 2^k) = O(10 * 2^10) = O(1024) per test case
 *
 * Approach:
 * - Use dynamic programming over bits, where we track probabilities of XOR values
 *   when building a multiset using probabilities p[i].
 * - For each bit position, maintain state for two possible XOR values (0 or 1).
 * - Transition uses prefix probabilities and updates states based on current element.
 */

#include <stdio.h>
#include <string.h>
#include <iosfwd>

#define int long long
using namespace std;
const int N = 2e5 + 5, inv = 285700002, mod = 1e9 + 7;
int t, a[N], p[N], f[2][10][10][2][2], ans, n, now;

signed main() {
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld", &n);
    ans = 0;
    for (int i = 1; i <= n; i++)
      scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++)
      scanf("%lld", &p[i]), p[i] = p[i] * inv % mod; // Normalize probabilities
    memset(f[0], 0, sizeof f[0]); // Initialize DP array for first prefix
    for (int i = 0; i < 10; i++)  // Set base case for all bit positions
      for (int j = 0; j < 10; j++)
        f[0][i][j][0][0] = 1;

    for (int i = 1; i <= n; i++) {
      now = i & 1; // Toggle between two DP states
      memset(f[now], 0, sizeof f[now]); // Clear current state

      // For each bit position, transition all possible states using probability p[i]
      for (int j = 0; j < 10; j++)
        for (int k = 0; k < 10; k++)
          for (int u = 0; u < 2; u++)
            for (int v = 0; v < 2; v++)
              f[now][j][k][u][v] =
                  (p[i] * f[now ^ 1][j][k][u ^ ((a[i] >> j) & 1)]
                           [v ^ ((a[i] >> k) & 1)] +
                   (1 - p[i] + mod) * f[now ^ 1][j][k][u][v]) %
                  mod;
    }

    // Final answer computation: sum of all possible (xor^2) contributions
    for (int i = 0; i < 10; i++)
      for (int j = 0; j < 10; j++)
        ans += f[n & 1][i][j][1][1] * (1 << i + j);
    printf("%lld\n", ans % mod);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/