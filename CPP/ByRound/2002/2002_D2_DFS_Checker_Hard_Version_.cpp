/*
 * Problem URL : https://codeforces.com/contest/2002/problem/D2
 * Submit Date : 2025-09-14
 */

#include <bits/stdc++.h>
using namespace std;
constexpr int _n = 3e5 + 7;
basic_string<int> v[_n];
bitset<_n> B;
int t, n, q, cnt, a[_n], l[_n], r[_n], fa[_n], tot;
void dfs(int x) {
  l[x] = ++cnt;
  for (int i : v[x])
    dfs(i);
  r[x] = cnt;
}
void upd(int x) {
  if (l[fa[a[x + 1]]] <= l[a[x]] && l[a[x]] <= r[fa[a[x + 1]]])
    tot += B[x] ^ 1, B[x] = 1;
  else
    tot -= B[x] ^ 0, B[x] = 0;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    B.reset(), tot = 0;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
      v[i].clear();
    for (int i = 2; i <= n; ++i)
      cin >> fa[i], v[fa[i]] += i;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    dfs(1);
    for (int i = 1; i < n; ++i)
      upd(i);
    for (int x, y; q--;) {
      cin >> x >> y, swap(a[x], a[y]);
      if (x > 1)
        upd(x - 1);
      if (x < n)
        upd(x);
      if (y > 1)
        upd(y - 1);
      if (y < n)
        upd(y);
      cout << (tot == n - 1 ? "yes\n" : "no\n");
    }
  }
}