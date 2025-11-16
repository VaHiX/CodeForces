// Problem: CF 1827 B1 - Range Sorting (Easy Version)
// https://codeforces.com/contest/1827/problem/B1

/*
 * Problem: B1. Range Sorting (Easy Version)
 *
 * Approach:
 * - For each subarray, we compute its "beauty" which is the minimum operations
 *   to sort it using range-sort operations.
 * - We use a segment tree to efficiently query for the first element greater
 * than a given value.
 * - We use stack-based preprocessing to find the nearest smaller element to the
 * left for each position.
 * - For each position, we calculate a DP value representing the contribution to
 * the total beauty.
 *
 * Time Complexity: O(n log n) per test case due to segment tree operations and
 * preprocessing. Space Complexity: O(n) for the segment tree and auxiliary
 * arrays.
 */

#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <stddef.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define piii pair<int, pii>
#define pll pair<ll, ll>
#define plll pair<ll, pll>
#define pb push_back
#define qb pop_back
#define F first
#define S second
typedef long long ll;
typedef double db;
const ll INF = 1e18;
const ll maxn = 3e5 + 10;
const ll mod = 1e9 + 7;
ll gcd(ll a, ll b) {
  if (a == 0)
    return b;
  if (b == 0)
    return a;
  if (a < b)
    swap(a, b);
  while (a % b) {
    swap(a, b);
    b %= a;
  }
  return b;
}
ll pw(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1)
      res = (res * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return res;
}
string s, t;
ll n, m, k, a[maxn], dp[maxn], cp[maxn], pos_less[maxn];
vector<pll> stk;
set<ll> se;
bool mark[maxn];
ll mx[maxn << 2];
void build(int tl = 1, int tr = n, int v = 1) {
  if (tl == tr) {
    mx[v] = a[tl];
    return;
  }
  int mid = (tl + tr) >> 1, ml = (v << 1), mr = (v << 1) | 1;
  build(tl, mid, ml);
  build(mid + 1, tr, mr);
  mx[v] = max(mx[ml], mx[mr]);
}
ll ask(ll val, int l, int r, int tl = 1, int tr = n, int v = 1) {
  if (l > r)
    return -1;
  if (tl == tr) {
    if (a[tl] > val)
      return tl;
    else
      return -1;
  }
  int mid = (tl + tr) >> 1, ml = (v << 1), mr = (v << 1) | 1;
  int res = -1;
  if (mx[mr] > val)
    res = ask(val, max(l, mid + 1), r, mid + 1, tr, mr);
  if (res != -1)
    return res;
  return ask(val, l, min(mid, r), tl, mid, ml);
}
void slv() {
  ll ans = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  build(); // Build segment tree for range max queries
  stk.clear();
  pos_less[1] = -1;
  stk.push_back({a[1], 1});
  for (int i = 2; i <= n; i++) {
    while (stk.size() > 0 && stk[stk.size() - 1].F > a[i]) {
      stk.pop_back(); // Remove elements greater than current
    }
    if (stk.size() == 0) {
      pos_less[i] = -1; // No smaller element on the left
    } else {
      pos_less[i] = stk[stk.size() - 1].S; // Index of nearest smaller element
    }
    stk.push_back({a[i], i}); // Keep the current element in the stack
  }
  stk.clear();
  for (ll i = 1; i <= n; i++) {
    ans += (i * (i + 1)) /
           2; // Total number of subarrays (used as base for counting)
  }
  dp[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (pos_less[i] == -1) {
      dp[i] = i; // If no smaller element, entire array needs sorting
    } else {
      ll pos = pos_less[i];
      dp[i] = i - pos;
      dp[i] += dp[pos];
      dp[i] += pos;
      ll ps =
          ask(a[i], 1,
              pos); // Find first element greater than a[i] in range [1, pos]
      if (ps == -1) {
        continue; // If none found, skip
      } else {
        dp[i] -= ps; // Adjust dp[i] by subtracting 'ps' to account for
                     // overlapping range
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    ans -=
        dp[i]; // Subtract contribution of dp[i] from total to get final result
  }
  cout << ans << "\n";
  return;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  cout.tie(NULL);
  int _ = 1;
  cin >> _;
  while (_--) {
    slv();
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/