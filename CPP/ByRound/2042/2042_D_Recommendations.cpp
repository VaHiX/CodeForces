/*
 * Problem URL : https://codeforces.com/contest/2042/problem/D
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
#define fo(i, x, y) for (int i = x; i < y; ++i) //[x,y)
int T, n, tp, l[N], r[N], o[N], q[N], al[N], ar[N];
main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n, iota(o, o + n, 0);
    fo(i, 0, n) cin >> l[i] >> r[i];
    sort(o, o + n,
         [](int i, int j) { return l[i] ^ l[j] ? l[i] < l[j] : r[i] > r[j]; }),
        tp = -1;
    fo(i, 0, n) {
      while (~tp && r[q[tp]] < r[o[i]])
        --tp;
      al[o[i]] = ~tp ? l[q[tp]] : -1;
      q[++tp] = o[i];
    }
    sort(o, o + n,
         [](int i, int j) { return r[i] ^ r[j] ? r[i] > r[j] : l[i] < l[j]; }),
        tp = -1;
    fo(i, 0, n) {
      while (~tp && l[q[tp]] > l[o[i]])
        --tp;
      ar[o[i]] = ~tp ? r[q[tp]] : -1;
      q[++tp] = o[i];
    }
    fo(i, 1, n) if (l[o[i]] == l[o[i - 1]] && r[o[i]] == r[o[i - 1]]) al[o[i]] =
        al[o[i - 1]] = -1;
    fo(i, 0, n) cout << (~al[i] && ~ar[i] ? ar[i] - al[i] + l[i] - r[i] : 0)
                     << '\n';
  }
}
