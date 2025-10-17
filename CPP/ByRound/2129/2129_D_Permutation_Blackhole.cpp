// Problem: CF 2129 D - Permutation Blackhole
// https://codeforces.com/contest/2129/problem/D

/*
D. Permutation Blackhole

Algorithm: Dynamic Programming with Memoization
- The problem involves counting permutations that produce a given coloring sequence based on a specific process.
- The core idea uses recursive DFS with memoization to explore possible placements of elements and their scores.
- The state is defined by subarray boundaries [l, r], and the maximum score constraints from left and right ends (pl and pr).
- For each position k in [l,r], we try placing p_k and calculate valid combinations of left and right subtrees.
- Precomputed binomial coefficients are used for combination counting.

Time Complexity: O(n^4) per test case due to nested loops and recursive calls with memoization.
Space Complexity: O(n^2 + n^3) for dp map and binomial coefficient table.

*/

#include <stdio.h>
#include <algorithm>
#include <unordered_map>

using namespace std;
const int mod = 998244353;
int s[110], n;
int c[110][110]; // Binomial coefficients
unordered_map<int, int> dp; // Memoization

int dfs(int l, int r, int pl, int pr) {
  if (l > r)
    return pl <= 1 && pr <= 1;
  if ((pl - 1) + (pr - 1) > r - l + 1)
    return 0;
  int st = 101 * (101 * (101 * pl + pr) + r) + l;
  if (dp.find(st) != dp.end())
    return dp[st];
  int ans = 0;
  for (int k = l; k <= r; k++) {
    // Determine whether to apply left or right penalty
    int p0 = (l > 1 && (r == n || k - l <= r - k));
    int p1 = (r < n && (l == 1 || k - l > r - k));
    int pz = c[r - l][k - l]; // Combination number
    if (pl == 1 && p0)
      continue; // Skip this case to avoid violating constraint
    if (pr == 1 && p1)
      continue; // Skip this case to avoid violating constraint
    if (s[k] == -1) {
      // Free choice for s[k], we enumerate all valid values
      (ans += 1ll * pz * dfs(l, k - 1, max(0, pl - p0), 0) % mod *
              dfs(k + 1, r, 0, max(0, pr - p1)) % mod) %= mod;
    } else {
      // Fixed value s[k], try all valid values for left and right partitions
      for (int o = 0; o <= s[k]; o++)
        (ans += 1ll * pz * dfs(l, k - 1, max(0, pl - p0), o + 1) % mod *
                dfs(k + 1, r, s[k] - o + 1, max(0, pr - p1)) % mod) %= mod;
    }
  }
  return dp[st] = ans;
}

void sol() {
  scanf("%d", &n);
  c[0][0] = 1;
  for (int i = 0; i <= n; i++) {
    c[i][0] = 1;
    for (int j = 1; j <= i; j++)
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
  }
  dp.clear();
  int fu = 0;
  for (int i = 1; i <= n; i++)
    scanf("%d", &s[i]), fu += max(0, s[i]);
  if (fu >= n) {
    puts("0");
    return;
  }
  printf("%d\n", dfs(1, n, 1, 1));
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    sol();
  return 0;
}


// https://github.com/VaHiX/CodeForces/