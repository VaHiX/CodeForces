// Problem: CF 2043 F - Nim
// https://codeforces.com/contest/2043/problem/F

/*
Code purpose:
This code solves the Nim game problem where Ruslan wants to maximize the number of piles he can remove such that Artem (the first player) loses. The solution uses the concept of XOR (Nim-sum) and dynamic programming to calculate the optimal removal strategy.

Algorithms:
1. Preprocessing: Build prefix sums for each pile size to quickly calculate how many piles of each size exist in any segment.
2. For each query:
   - Calculate how many piles of each size are in the segment
   - Special case handling for piles of size 0
   - If there are 2 or more piles of same size, calculate combinations
   - Use dynamic programming to find minimum moves needed to make the game lose for the first player
   - Compute the maximum number of piles that can be removed and number of ways to do so

Time Complexity: O(n * 50 + q * 50 * 64) 
Space Complexity: O(n * 50 + 64)
*/

#include <string.h>
#include <iostream>
#include <utility>

using namespace std;
const int N = 1e5 + 10, Mod = 998244353;
inline int add(int a, int b) { return a + b >= Mod ? a + b - Mod : a + b; }
int n, q, a[N], sum[55][N], cnt[55], f[65], g[65], tf[65], tg[65];
pair<int, int> solve() {
  memset(f, 0x3f, sizeof(f));
  memset(g, 0, sizeof(g));
  for (int i = 1; i <= 50; ++i) {
    if (!cnt[i])
      continue;
    tf[i] = 1, tg[i] = 1;
    for (int j = 1; j <= 63; ++j) {
      if (f[j ^ i] > f[j] + 1)
        tf[j ^ i] = f[j] + 1, tg[j ^ i] = g[j];
      else if (f[j ^ i] == f[j] + 1)
        tf[j ^ i] = f[j ^ i], tg[j ^ i] = add(g[j ^ i], g[j]);
      else
        tf[j ^ i] = f[j ^ i], tg[j ^ i] = g[j ^ i];
    }
    memcpy(f, tf, sizeof(f)), memcpy(g, tg, sizeof(tg));
  }
  return make_pair(f[0], g[0]);
}
int main() {
  ios::sync_with_stdio(0);
  cin >> n >> q;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], sum[a[i]][i] = 1;
  for (int i = 0; i <= 50; ++i)
    for (int j = 1; j <= n; ++j)
      sum[i][j] += sum[i][j - 1];
  while (q--) {
    int l, r;
    cin >> l >> r;
    for (int i = 0; i <= 50; ++i)
      cnt[i] = sum[i][r] - sum[i][l - 1];
    if (cnt[0]) {
      cout << r - l << " " << cnt[0] << endl;
      continue;
    }
    int num = 0, flg = 0;
    for (int i = 1; i <= 50; ++i)
      if (cnt[i] >= 2)
        num = add(num, 1ll * cnt[i] * (cnt[i] - 1) / 2 % Mod), flg = 1;
    if (flg)
      cout << r - l - 1 << " " << num << endl;
    else {
      auto ans = solve();
      if (ans.first > 1e9)
        cout << -1 << endl;
      else
        cout << r - l + 1 - ans.first << " " << ans.second << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/