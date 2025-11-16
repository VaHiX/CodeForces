// Problem: CF 1811 G1 - Vlad and the Nice Paths (easy version)
// https://codeforces.com/contest/1811/problem/G1

/*
 * Problem: Vlad and the Nice Paths (easy version)
 * Algorithm: Dynamic Programming with State Compression
 * Time Complexity: O(n * k), where n is the number of tiles and k is the block size
 * Space Complexity: O(n * k), for the DP table and auxiliary arrays
 *
 * Approach:
 * - This solution uses a dynamic programming approach where we maintain for each color,
 *   the number of paths ending at that color with a certain length and their maximum length.
 * - We compress the colors to reduce the state space.
 * - For each new tile, we update the DP states based on previous states to build longer paths.
 * - The key idea is to only keep track of the maximum length paths.
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, b, a) for (int i = b; i >= a; i--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<long long> VLL;
template <typename... T> void debug(T... args) {
  cerr << "this -> ";
  ((cerr << args << " "), ...);
  cerr << '\n';
}
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define mp make_pair
#define bit(x) (1ll << (x))
#define SZ(x) ((int)x.size())
#define all(x) x.begin(), x.end()
mt19937_64 rng(random_device{}());
ll fpow(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1)
      res = res * a;
    b >>= 1;
    a = a * a;
  }
  return res;
}
ll powmod(ll a, ll b, const ll p) {
  ll res = 1;
  while (b) {
    if (b & 1)
      res = res * a % p;
    b >>= 1;
    a = a * a % p;
  }
  return res;
}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
const int mod = 1e9 + 7;
const int inf = 1ll << 29;
const double pi = acos(-1);
const double eps = 1e-12;
const int maxn = 5e5 + 15;
const int N = 505;
ll n, m, k;
ll dp[N][N], len[N][N];
int a[N];
void solve() {
  cin >> n >> k;
  vector<ll> vx;
  rep(i, 1, n) {
    cin >> a[i];
    vx.pb(a[i]);
  }
  rep(i, 1, n) rep(j, 1, k) dp[i][j] = 0, len[i][j] = -1;
  sort(all(vx));
  vx.erase(unique(all(vx)), vx.end());
  auto pos = [&](ll x) { return lower_bound(all(vx), x) - vx.begin() + 1; };
  ll ans = 1, mxlen = 0;
  rep(i, 1, n) {
    int p = pos(a[i]);
    dp[p][0] = ans;
    len[p][0] = mxlen;
    if (len[p][k - 1] + 1 > mxlen) {
      mxlen = len[p][k - 1] + 1;
      ans = dp[p][k - 1];
    } else if (len[p][k - 1] + 1 == mxlen) {
      ans = (ans + dp[p][k - 1]) % mod;
    }
    per(j, k - 1, 1) {
      if (len[p][j - 1] == len[p][j])
        dp[p][j] = (dp[p][j] + dp[p][j - 1]) % mod;
      else if (len[p][j - 1] > len[p][j])
        dp[p][j] = dp[p][j - 1], len[p][j] = len[p][j - 1];
    }
  }
  cout << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/