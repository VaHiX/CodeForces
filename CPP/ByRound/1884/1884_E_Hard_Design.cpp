// Problem: CF 1884 E - Hard Design
// https://codeforces.com/contest/1884/problem/E

/*
Algorithm: Hard Design
Purpose: To compute for each cyclic shift of the array, the minimum number of operations (cnt) and the maximum possible coins (cost) that can be obtained.

Approach:
- For each cyclic shift, convert the problem into a difference array of (max_val - a[i]).
- Then use a monotonic stack to simulate the process of making the array non-decreasing.
- For each element in the array, we calculate cost for operations needed to make the array equal.
- The solution uses a two-pass technique (left to right and right to left) with a stack to efficiently compute the cost contribution.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing arrays and stack

*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>

#define se second
#define fi first
#define pil pair<int, ll>
using namespace std;
using ll = long long;
const int N = 4e6 + 3, P = 1e9 + 7;
template <class T> void add(T &x, T y) {
  if ((x += y) >= P)
    x -= P;
}
template <class T> void dlt(T &x, T y) {
  if ((x -= y) < 0)
    x += P;
}
int a[N];
int n, top;
ll s[N], l[N], r[N];
pil st[N];
void solve() {
  cin >> n;
  ll ans = 0, sum = 0;
  int cnt = 0;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  int id = max_element(a + 1, a + 1 + n) - a, mx = a[id];
  for (int i = 1; i <= n; ++i)
    a[i] = mx - a[i];
  for (int i = n + 1; i <= 3 * n; ++i)
    a[i] = a[i - n];
  for (int i = 1; i <= 2 * n; ++i)
    s[i] = s[i - 1] + max(0, a[i] - a[i - 1]);
  top = 0;
  id += n;
  for (int i = id + 1; i <= id + n; ++i) {
    ll v = 1;
    while (top && st[top].fi >= a[i]) {
      auto [h, w] = st[top--];
      dlt(sum, w * (h - a[i]) % P);
      v += w;
    }
    r[i - id] = (a[i] + sum * 2 + r[i - id - 1]) % P;
    sum += a[i];
    st[++top] = {a[i], v};
  }
  top = 0;
  for (int i = id - 1; i >= id - n; --i) {
    ll v = 1;
    while (top && st[top].fi >= a[i]) {
      auto [h, w] = st[top--];
      dlt(sum, w * (h - a[i]) % P);
      v += w;
    }
    l[id - i] = (a[i] + sum * 2 + l[id - i - 1]) % P;
    sum += a[i];
    st[++top] = {a[i], v};
  }
  id -= n;
  for (int i = 1; i <= n; ++i) {
    ll ans = 0;
    if (i <= id)
      ans = (l[id - i] + r[n - 1 - (id - i)]) % P;
    else
      ans = (l[id + n - i] + r[n - 1 - (id + n - i)]) % P;
    printf("%lld %lld\n", s[i + n - 1] - s[i] + a[i], ans);
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  for (cin >> T; T--;)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/