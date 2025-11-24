// Problem: CF 2046 C - Adventurers
// https://codeforces.com/contest/2046/problem/C

/*
Algorithm: Coordinate Compression + Binary Indexed Tree (BIT) + Two Pointers
Time Complexity: O(n log^2 n)
Space Complexity: O(n)

The problem is about dividing cities among four merchants such that the minimum number of cities any merchant gets is maximized. 
This is a classic optimization problem which can be solved using coordinate compression and binary indexed tree (BIT).

Approach:
1. First, we compress the coordinates to handle large coordinate values efficiently.
2. We then use BIT to maintain counts of cities in different quadrants.
3. We iterate through sorted x-coordinates and adjust the BITs accordingly to find the optimal dividing point.
4. For each valid x0, we determine the optimal y0 to maximize the minimum number of cities any merchant receives.

*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define dbg(x) cout << #x << " = " << x << '\n'
#define dbgv(x)                                                                \
  for (int i = 0; i < x.size(); i++)                                           \
    cout << x[i] << ' ';                                                       \
  cout << '\n'
#define inf 1000000005
#define mod 1000000007
template <class T> struct BIT {
  int n;
  vector<T> data;
  BIT(int n) : n(n) { data.resize(n); }
  void add(int p, T x) {
    for (++p; p <= n; p += p & -p)
      data[p - 1] += x;
  }
  T sum(int l, int r) { return sum(r + 1) - sum(l); }
  T sum(int r) {
    T s = 0;
    for (; r; r -= r & -r)
      s += data[r - 1];
    return s;
  }
  int lower_bound(T sum) {
    if (sum < 0)
      return -1;
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      int npos = pos + pw;
      if (npos <= n && data[npos - 1] <= sum)
        pos = npos, sum -= data[pos - 1];
    }
    return pos + 1;
  }
};
void solve() {
  int n;
  cin >> n;
  vector<int> x(n), y(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  vector<int> xs = x, ys = y;
  sort(xs.begin(), xs.end());
  sort(ys.begin(), ys.end());
  xs.resize(unique(xs.begin(), xs.end()) - xs.begin());
  ys.resize(unique(ys.begin(), ys.end()) - ys.begin());
  for (int i = 0; i < n; i++) {
    y[i] = lower_bound(ys.begin(), ys.end(), y[i]) - ys.begin();
    x[i] = lower_bound(xs.begin(), xs.end(), x[i]) - xs.begin();
  }
  vector<int> pos(n);
  iota(pos.begin(), pos.end(), 0);
  sort(pos.begin(), pos.end(),
       [&x](const int i, const int j) { return x[i] < x[j]; });
  int s = ys.size(), k = 0;
  int X0 = 0, Y0 = 0;
  BIT<int> fl(s), fr(s);
  for (int i = 0; i < n; i++) {
    fr.add(y[i], 1);
  }
  for (int j = 0; j < n; j++) {
    int i = pos[j];
    fr.add(y[i], -1);
    fl.add(y[i], 1);
    if (j + 1 < n && x[pos[j + 1]] == x[i]) {
      continue;
    }
    while (true) {
      if (j + 1 < 2 * (k + 1)) {
        break;
      }
      if (n - j - 1 < 2 * (k + 1)) {
        break;
      }
      int yl = max(fl.lower_bound(k) - 1, fr.lower_bound(k) - 1);
      int yr =
          min(fl.lower_bound(j - k) - 1, fr.lower_bound(n - 1 - j - 1 - k) - 1);
      if (yl >= yr) {
        break;
      }
      k++;
      X0 = xs[x[i]] + 1;
      Y0 = ys[yr];
    }
  }
  cout << k << "\n";
  cout << X0 << " " << Y0 << "\n";
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ll t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/