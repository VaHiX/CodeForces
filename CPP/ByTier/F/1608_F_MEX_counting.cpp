// Problem: CF 1608 F - MEX counting
// https://codeforces.com/contest/1608/problem/F

// Problem: F. MEX counting
// Algorithm: Dynamic Programming with range updates and prefix sums
// Time Complexity: O(n^2 * k)
// Space Complexity: O(n^2)

#include <stdio.h>
#include <string.h>
#include <algorithm>

#pragma GCC optimize("Ofast")
#pragma target("avx512f,sse2,sse3,sse4,sse4.2")
using namespace std;
const int mod = 998244353;
inline void ensureMod(int &x) { x += (x >> 31) & mod; }
int n, m, b[2001], l[2001], r[2001];
int f[2][2001][2001], g[2001][2002];
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
    l[i] = max(b[i] - m, 0);        // Minimum possible value at position i
    r[i] = min(b[i] + m, i);        // Maximum possible value at position i
  }
  for (int i = 2; i <= n; i++)
    l[i] = max(l[i], l[i - 1]);     // Propagate lower bound forward
  for (int i = n - 1; i >= 1; i--)
    r[i] = min(r[i], r[i + 1]);     // Propagate upper bound backward
  int now = 0;
  for (int i = l[n]; i <= r[n]; i++)
    f[now][i][1] = 1;               // Base case: last element
  for (int i = n - 1; i >= 1; i--) {
    now ^= 1;                       // Toggle current DP layer
    for (int j = l[i]; j <= r[i]; j++)
      memset(f[now][j], 0, sizeof(int) * (n + 1));  // Reset current DP state
    for (int j = l[i + 1]; j <= r[i + 1]; j++)
      for (int k = 1; k <= n; k++) {
        if (!f[now ^ 1][j][k]) 
          continue;
        f[now][j][k] = (f[now][j][k] + (n - k + 1ll) * f[now ^ 1][j][k]) % mod; // Transition with contribution of MEX
        if (j)
          g[j - 1][k + 1] = f[now ^ 1][j][k];   // Apply difference array update for prefix sum optimization
      }
    for (int j = r[i + 1]; j > l[i]; j--)
      for (int k = 1; k <= n; k++) {
        g[j - 1][k] += g[j][k] - mod, ensureMod(g[j - 1][k]);     // Propagate prefix sum
        g[j - 1][k + 1] -= g[j][k], ensureMod(g[j - 1][k + 1]);   // Apply difference update
      }
    for (int j = l[i]; j <= r[i]; j++)
      for (int k = 1; k <= n; k++)
        f[now][j][k] += g[j][k] - mod, ensureMod(f[now][j][k]); // Accumulate prefix sum updates
    for (int j = l[i]; j <= r[i + 1]; j++)
      memset(g[j], 0, sizeof(int) * (n + 1));   // Reset auxiliary array
  }
  long long answer = 0;
  for (int j = l[1]; j <= r[1]; j++)
    for (int k = 1; k <= n; k++)
      answer += 1ll * f[now][j][k] * (j ? 1 : n - k + 1) % mod; // Final accumulation of result
  printf("%lld\n", answer % mod);
  return 0;
}


// https://github.com/VaHiX/codeForces/