// Problem: CF 1799 G - Count Voting
// https://codeforces.com/contest/1799/problem/G

/*
 * Problem: Count Voting
 * Algorithm: Dynamic Programming with Combinatorics
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 *
 * This solution uses dynamic programming to count the number of valid voting
 * configurations. Each person votes for someone from a different team. We process
 * teams one by one and track how many votes each person in the team can receive.
 * For each team, we compute combinations of how votes can be distributed among
 * its members based on their desired vote counts.
 *
 * The dynamic programming state f[i] represents the number of ways to assign
 * votes such that a total of i people got some votes.
 * We use combinatorial mathematics to count valid vote distributions for each team.
 * Finally, we multiply with factorial to account for arrangement.
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;
const int maxn = 205, mod = 998244353;
int n, m, T, ans;
int a[maxn], c[maxn], f[maxn], g[maxn], h[maxn], nfac[maxn], fac[maxn],
    inv[maxn], fu[2] = {1, mod - 1};
vector<int> v[maxn];

// Inline function to add value with modulo
inline void inc(int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
}

// Compute combination C(a, b) using precomputed factorials
inline int C(int a, int b) {
  return a < b ? 0 : 1ll * fac[a] * nfac[b] % mod * nfac[a - b] % mod;
}

int main() {
  scanf("%d", &n);
  inv[1] = nfac[0] = nfac[1] = fac[0] = fac[1] = 1;
  // Precompute factorials and inverse factorials
  for (int i = 2; i <= n; i++)
    fac[i] = 1ll * fac[i - 1] * i % mod,
    inv[i] = mod - 1ll * (mod / i) * inv[mod % i] % mod,
    nfac[i] = 1ll * nfac[i - 1] * inv[i] % mod;

  // Read desired vote counts
  for (int i = 1; i <= n; i++)
    scanf("%d", &c[i]);

  // Read team assignments and group people by team
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), v[a[i]].emplace_back(i);

  // Initialize DP array
  f[0] = 1;

  // Process each team
  for (int t = 1; t <= n; t++)
    if (v[t].size()) {
      int s = v[t].size();  // Number of people in this team
      memset(g, 0, sizeof(g));
      memset(h, 0, sizeof(h));
      g[0] = 1;
      int nows = 0;

      // For each person in the team, update the DP state
      for (int p = 0; p < v[t].size(); p++) {
        int x = v[t][p];
        for (int i = 0; i <= nows; i++)
          if (g[i])
            for (int j = 0; j <= c[x]; j++)
              // Compute ways to assign j votes to person x
              h[i + j] = (h[i + j] + 1ll * fu[j & 1] * nfac[c[x] - j] % mod *
                                         g[i] % mod * C(s - i, j)) %
                         mod;
        nows += c[x];
        for (int i = 0; i <= nows; i++)
          g[i] = h[i], h[i] = 0;
      }

      // Merge current team's results with overall DP state
      for (int i = 0; i <= n; i++)
        if (f[i])
          for (int j = 0; j <= s && i + j <= n; j++)
            h[i + j] = (h[i + j] + 1ll * f[i] * g[j]) % mod;
      for (int i = 0; i <= n; i++)
        f[i] = h[i], h[i] = 0;
    }

  // Compute final answer using the factorial of remaining votes
  for (int i = 0; i <= n; i++)
    ans = (ans + 1ll * fac[i] * f[n - i]) % mod;

  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/