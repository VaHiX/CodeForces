/*
 * Problem URL : https://codeforces.com/contest/1949/problem/I
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
typedef long long ll;
const ll _ = 1005;
inline ll sq(ll x) { return x * x; }
ll n, t, f[_], i, j;
vector<ll> E[_];
struct o {
  ll x, y, r;
} a[_];
inline bool p1(o x, o y) {
  return sq(x.x - y.x) + sq(x.y - y.y) == sq(x.r + y.r);
}
inline void p2(ll x) {
  t += (f[x] == 2 ? 1 : -1);
  for (auto y : E[x]) {
    if (!f[y])
      f[y] = f[x] ^ 1, p2(y);
    else if (f[x] ^ f[y] ^ 1)
      t = 1e9;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (i = 1; i <= n; i++)
    cin >> a[i].x >> a[i].y >> a[i].r;
  for (i = 1; i < n; i++)
    for (j = i + 1; j <= n; j++)
      if (p1(a[i], a[j]))
        E[i].eb(j), E[j].eb(i);
  for (i = 1; i <= n; i++)
    if (!f[i]) {
      t = 0;
      f[i] = 2;
      p2(i);
      if (t != 0 && t <= n)
        return cout << "YES\n", 0;
    }
  cout << "NO\n";
}