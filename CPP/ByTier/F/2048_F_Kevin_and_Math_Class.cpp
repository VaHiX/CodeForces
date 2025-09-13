/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int kMaxN = 2e5 + 1, kL = 64;

struct V {
  LL f[kL], a, b, l, r;
} v[kMaxN];
int s[kMaxN], t, n, m, ans;

void T(int x) {
  if (x) {
    T(v[x].l), T(v[x].r);
    for (int l = 0, r = 0; l + r < kL;
         (v[v[x].l].f[l] > v[v[x].r].f[r] ? l++ : r++)) {
      v[x].f[l + r] = max({v[v[x].l].f[l], v[v[x].r].f[r], v[x].a});
      (l + r) &&
          (v[x].f[l + r] =
               min(v[x].f[l + r], (v[x].f[l + r - 1] + v[x].b - 1) / v[x].b));
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> t; t--;) {
    cin >> n;
    fill(v + 1, v + 1 + n, v[m = 0]);
    for (int i = 1; i <= n; i++) {
      cin >> v[i].a;
    }
    for (int i = 1; i <= n; i++) {
      cin >> v[i].b;
      for (; m && v[i].b < v[s[m]].b; m--) {
        v[i].l = s[m];
      }
      m && (v[s[m]].r = i), s[++m] = i;
    }
    T(s[1]);
    for (ans = 0; v[s[1]].f[ans] > 1; ans++) {
    }
    cout << ans << '\n';
  }
  return 0;
}