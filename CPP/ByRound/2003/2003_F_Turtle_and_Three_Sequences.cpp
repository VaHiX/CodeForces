/*
 * Problem URL : https://codeforces.com/contest/2003/problem/F
 * Submit Date : 2025-09-14
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3003;
int n, m, ans, a[N], b[N], c[N], d[N];
mt19937 rd(time(0));
struct BIT {
  int tr[N];
  void Add(int x, int y) {
    for (; x <= n; x += x & -x)
      tr[x] = max(tr[x], y);
  }
  int Ask(int x) {
    int s = 0;
    for (; x; x -= x & -x)
      s = max(s, tr[x]);
    return s;
  }
  void Clear() {
    for (int i = 0; i <= n; i++)
      tr[i] = 0;
  }
} T[32];
void Solve() {
  for (int i = 0; i < 1 << m; i++)
    T[i].Clear();
  for (int i = 1; i <= n; i++)
    d[i] = rd() % m;
  for (int i = 1; i <= n; i++) {
    int x = d[b[i]], y = 0;
    T[1 << x].Add(a[i], c[i]);
    for (int S = 1; S < 1 << m; S++)
      if (!(S >> x & 1)) {
        y = T[S].Ask(a[i]);
        if (y)
          T[S | (1 << x)].Add(a[i], y + c[i]);
      }
  }
  ans = max(ans, T[(1 << m) - 1].Ask(n));
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    cin >> b[i];
  for (int i = 1; i <= n; i++)
    cin >> c[i];
  for (int t = 1; t <= 100; t++)
    Solve();
  cout << (!ans ? -1 : ans);
}