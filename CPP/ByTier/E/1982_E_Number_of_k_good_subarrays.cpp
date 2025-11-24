// Problem: CF 1982 E - Number of k-good subarrays
// https://codeforces.com/contest/1982/problem/E

/*
Algorithm: Dynamic Programming with Bitmask and Recursion
Time Complexity: O(k^2 + t * log n) where t is number of test cases and n can be up to 10^18
Space Complexity: O(k^2) for the DP table

This code calculates the number of k-good subarrays in an array where each element a[i] = i.
A k-good subarray contains only numbers whose binary representation has at most k ones.
The solution uses dynamic programming and recursion based on bit representation analysis.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>

#define fi first
#define se second
#define all(v) v.begin(), v.end()
#define sz(v) int(v.size())
#define unq(v)                                                                 \
  sort(all(v));                                                                \
  v.resize(unique(all(v)) - v.begin());
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<long long, int> lli;
const int LOG = 61;
const int mod = int(1e9) + 7;
int add(int x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
  return x;
}
int mul(int x, int y) { return (1ll * x * y) % mod; }
int cost(ll x) {
  if (x % 2 == 0) {
    return mul((x / 2) % mod, (x + 1ll) % mod);
  } else {
    return mul(x % mod, ((x + 1ll) / 2) % mod);
  }
}
int DP[LOG][LOG];
void prepare() {
  for (int i = 0; i < LOG; i++) {
    DP[i][0] = 1;
    DP[i][i] = cost((1ll << (i + 1)) - 1ll);
    for (int j = 1; j < i; j++) {
      // DP[i][j] represents the number of valid subarrays of length up to i with at most j ones
      DP[i][j] = add(DP[i - 1][j], DP[i - 1][j - 1]);
    }
  }
}
int calc(ll n, int k) {
  if (n < 0)
    return 0;
  if (n == 0 || k == 0)
    return 1;
  if (n < (1ll << (k + 1)) - 1ll)
    return cost(n + 1ll);
  int t = __lg(n + 1ll);
  // Recursive structure based on binary decomposition
  return add(DP[t - 1][k], calc(n - (1ll << t), k - 1));
}
void solve() {
  ll n;
  int k;
  cin >> n >> k;
  cout << calc(n - 1, k) << "\n";
}
#define name "A"
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  if (fopen(name ".INP", "r")) {
    freopen(name ".INP", "r", stdin);
    freopen(name ".OUT", "w", stdout);
  }
  prepare();
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/