// Problem: CF 2009 G3 - Yunli's Subarray Queries (extreme version)
// https://codeforces.com/contest/2009/problem/G3

/*
G3. Yunli's Subarray Queries (extreme version)
Time Complexity: O(n log n + q log q)
Space Complexity: O(n)

Algorithms/Techniques:
- Coordinate compression
- Sliding window with frequency counting
- Range minimum query (RMQ) using segment tree
- Monotonic stack for prefix/suffix computations

This code processes queries on an array to compute the sum of minimum operations 
required to make any subarray of size k consecutive. The approach involves:
1. Coordinate compression of values.
2. Calculating minimum operations needed for each window of size k.
3. Using RMQ for fast range minimum queries.
4. Preprocessing prefix and suffix sums using monotonic stacks.
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define inf 9000000000000000000
#define foR(x, l, r) for (auto x = l; x <= r; x++)
#define For(x, r, l) for (auto x = r; x >= l; x--)
#define all(a) a.begin(), a.end()
void solve() {
  int n, k, q;
  cin >> n >> k >> q;
  vector<ll> a(n), b(n), fre(n + 1), cnt(n), f(n), rf(n), lf(n), rg(n), lg(n);
  vector<array<int, 22>> st(n - k + 1);
  for (ll &i : a)
    cin >> i;
  foR(i, 0, n - 1) {
    a[i] -= i; // Transform to difference array
    b[i] = a[i];
  }
  sort(all(b));
  foR(i, 0, n - 1) a[i] = lower_bound(all(b), a[i]) - b.begin(); // Coordinate compression
  ll res = 0;
  foR(i, 0, k - 2) {
    fre[cnt[a[i]]]--;
    res = max(res, ++cnt[a[i]]);
    fre[cnt[a[i]]]++;
  }
  foR(i, 0, n - k) {
    fre[cnt[a[i + k - 1]]]--;
    res = max(res, ++cnt[a[i + k - 1]]);
    fre[cnt[a[i + k - 1]]]++;
    while (fre[res] == 0)
      res--; // Find the maximum frequency
    f[i] = k - res; // Minimum operations for window starting at i
    fre[cnt[a[i]]]--;
    cnt[a[i]]--;
    fre[cnt[a[i]]]++;
  }
  vector<int> stk;
  For(i, n - 1, 0) {
    while (!stk.empty() && f[stk.back()] > f[i])
      stk.pop_back();
    if (stk.empty()) {
      rf[i] = f[i] * (n - i);
    } else {
      rf[i] = rf[stk.back()] + f[i] * (stk.back() - i);
    }
    rg[i] = rf[i] + (i < n - 1 ? rg[i + 1] : 0);
    stk.emplace_back(i);
  }
  stk.clear();
  foR(i, 0, n - 1) {
    while (!stk.empty() && f[stk.back()] > f[i])
      stk.pop_back();
    if (stk.empty()) {
      lf[i] = f[i] * (i + 1);
    } else {
      lf[i] = lf[stk.back()] + f[i] * (i - stk.back());
    }
    lg[i] = lf[i] + (i ? lg[i - 1] : 0);
    stk.emplace_back(i);
  }
  foR(i, 0, n - k) st[i][0] = i;
  foR(j, 1, 21) for (int i = 0; i + (1 << j) - 1 <= n - k; i++) {
    int a = st[i][j - 1], b = st[i + (1 << (j - 1))][j - 1];
    st[i][j] = f[a] < f[b] ? a : b;
  }
  auto query = [&](int l, int r) {
    int len = __lg(r - l + 1);
    int a = st[l][len], b = st[r - (1 << len) + 1][len];
    return f[a] < f[b] ? a : b;
  };
  while (q--) {
    int l, r;
    cin >> l >> r;
    l--, r -= k;
    int p = query(l, r);
    cout << (ll)(p - l + 1) * (r - p + 1) * f[p] + rg[l] - rg[p] -
                rf[p] * (p - l) + lg[r] - lg[p] - lf[p] * (r - p)
         << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/