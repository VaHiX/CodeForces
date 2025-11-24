// Problem: CF 1974 E - Money Buys Happiness
// https://codeforces.com/contest/1974/problem/E

/*
 * Problem: E. Money Buys Happiness
 * Purpose: To find the maximum sum of happiness Charlie can obtain given
 * monthly income and happiness offers. Algorithm: Dynamic Programming with
 * space optimization. Time Complexity: O(m * sum_happiness) where m is number
 * of months and sum_happiness is the total happiness value. Space Complexity:
 * O(sum_happiness) due to the DP array.
 *
 * Approach:
 *   - We use a 2D DP array where dp[i][j] represents the maximum money left
 * after considering first i months with total happiness j.
 *   - For each month, we update the DP states by:
 *     1. Adding current month's salary to all previous states (money
 * accumulation).
 *     2. If we can afford an item (dp[cur][j - h[i]] >= c[i]), we consider
 * buying it and update the DP state.
 *   - We iterate from maximum happiness down to minimum, to avoid recomputation
 * issues.
 *   - Finally, we find the highest achievable happiness value (the maximum j
 * such that dp[cur][j] >= 0).
 */

#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
template <typename T> void _do(T x) { cerr << x << "\n"; }
template <typename T, typename... U> void _do(T x, U... y) {
  cerr << x << ", ";
  _do(y...);
}
const int MOD1 = 1e9 + 7;
const int MOD2 = 998244353;
const ll INF = 4e18;
ll fpow(ll a, ll b, ll m) {
  if (!b)
    return 1;
  ll tmp = 1;
  for (ll cur = a; b; b >>= 1, cur = cur * cur % m)
    if (b & 1)
      tmp = tmp * cur % m;
  return tmp;
}
ll inv(ll a, ll m) { return fpow(a, m - 2, m); }
#define MottoHayaku                                                            \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(0);
#define rep(i, n) for (int i = 0; i < n; i++)
#define rep1(i, n) for (int i = 1; i <= n; i++)
#define F first
#define S second
#define pb push_back
#define uni(c) c.resize(distance(c.begin(), unique(c.begin(), c.end())))
#define unisort(c) sort(c.begin(), c.end()), uni(c)
const int N = 1e5 + 5;
ll dp[2][N];
void solve() {
  int n;
  ll x;
  cin >> n >> x;
  int tot = 0;
  vector<int> c(n + 1), h(n + 1);
  rep1(i, n) {
    cin >> c[i] >> h[i];
    tot += h[i];
  }
  rep(_, 2) rep(i, tot + 1) dp[_][i] = -INF;
  dp[0][0] = 0;
  int cur = 0;
  rep1(i, n) {
    rep(j, tot + 1) dp[cur ^ 1][j] = (dp[cur][j] < 0 ? -INF : dp[cur][j] + x);
    for (int j = h[i]; j <= tot; j++)
      if (dp[cur][j - h[i]] >= c[i]) {
        dp[cur ^ 1][j] = max(dp[cur ^ 1][j], dp[cur][j - h[i]] - c[i] + x);
      }
    cur ^= 1;
  }
  ll mx = tot;
  while (dp[cur][mx] < 0)
    mx--;
  cout << mx << "\n";
}
signed main() {
  MottoHayaku int t;
  cin >> t;
  while (t--) {
    solve();
  }
}

// https://github.com/VaHiX/CodeForces/