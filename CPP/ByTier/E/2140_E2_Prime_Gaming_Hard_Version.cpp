// Problem: CF 2140 E2 - Prime Gaming (Hard Version)
// https://codeforces.com/contest/2140/problem/E2

/*
E2. Prime Gaming (Hard Version)
Algorithms/Techniques: Game Theory, Dynamic Programming with Bitmask, Fast Exponentiation
Time Complexity: O(n * 2^n + m * n)
Space Complexity: O(2^n)

This problem uses dynamic programming with bitmasks to determine the outcome of a two-player game
where players alternate turns removing piles based on "good" indices. It calculates the sum of final
pile sizes over all valid configurations.

The approach involves:
1. Using bitmask DP to simulate the game and compute winning/losing states.
2. Counting how many configurations lead to each pile size.
3. Computing contribution of each size using modular exponentiation.
*/

#include <iostream>
#include <random>

#define int long long
#define endl '\n'
#define pii pair<int, int>
#define fi first
#define se second
#define rep(x, y, z) for (int x = (y); x <= (z); ++x)
#define per(x, z, y) for (int x = (z); x >= (y); --x)
using namespace std;
constexpr int maxn = 25, inf = 1e12, mod = 1e9 + 7;
mt19937 rnd(20070407);
int n, m, k, c[maxn], cnt[maxn];
bool f[maxn][1 << 20];
constexpr int del(int s, int d) {
  if (!d)
    return s >> 1;
  return (s & ((1 << d) - 1)) | ((s >> (d + 1)) << d);
}
constexpr bool in(int s, int d) { return s >> d & 1; }
int qpow(int a, int b) {
  int res = 1;
  for (int t = a; b; t = t * t % mod, b >>= 1)
    if (b & 1)
      res = res * t % mod;
  return res;
}
void solve() {
  cin >> n >> m >> k;
  rep(i, 1, k) cin >> c[i];
  if (m == 1) {
    cout << 1 << endl;
    return;
  }
  rep(i, 1, n) cnt[i] = 0;
  f[n - 1][1] = true, f[n - 1][0] = false;
  per(i, n - 2, 0) rep(s, 0, (1 << (n - i)) - 1) {
    bool flag = false;
    rep(j, 1, k) if (c[j] <= n - i) { // Try each good index
      bool nxt = f[i + 1][del(s, c[j] - 1)]; // Recurse after deleting the pile at index c[j]
      if ((i & 1) ^ nxt) { // If next state is losing for current player
        flag = true;
        break;
      }
    }
    f[i][s] = (i & 1) ^ flag; // Determine whether player i can win from this state
  }
  int ans = 0;
  rep(s, 0, (1 << n) - 1) cnt[__builtin_popcountll(s)] += f[0][s]; // Count configurations by pile count
  rep(x, 1, m) rep(i, 1, n) {
    ans += qpow(x - 1, n - i) * qpow(m - x + 1, i) % mod * cnt[i] % mod,
        ans %= mod;
  }
  cout << ans << endl;
}
signed main() {
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/