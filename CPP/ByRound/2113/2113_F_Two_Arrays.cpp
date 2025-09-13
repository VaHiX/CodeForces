/*
 * Problem URL : https://codeforces.com/problemset/problem/2113/F
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for (auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for (auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx), end(Tx)
const int N = 2e5 + 5;
int n, a[N], b[N];
int h[N], e[N * 2], ne[N * 2], w[N * 2], idx;
int cnt[N], cnt1[N];
bool vis[N], vis1[N];
void add(int a, int b, int c) {
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void dfs1(int x, int color, bool f) {
  if (vis[x])
    return;
  vis[x] = 1;
  for (int i = h[x]; ~i; i = ne[i]) {
    int j = e[i];
    if (vis1[abs(w[i])])
      continue;
    vis1[abs(w[i])] = 1;
    if (color == 0 && w[i] > 0)
      swap(a[w[i]], b[w[i]]);
    if (color == 1 && w[i] < 0)
      swap(a[abs(w[i])], b[abs(w[i])]);
    dfs1(j, color, 0);
    if (f)
      color = 1 - color;
  }
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    cin >> n;
    For(i, 0, 2 * n + 2) h[i] = -1;
    For(i, 0, 2 * n + 2) vis[i] = vis1[i] = cnt[i] = 0;
    idx = 0;
    For(i, 1, n) cin >> a[i];
    For(i, 1, n) cin >> b[i];
    For(i, 1, n) cnt[a[i]]++, cnt[b[i]]++;
    For(i, 1, n) add(a[i], b[i], i);
    For(i, 1, n) add(b[i], a[i], -i);
    int ans = 0;
    For(i, 1, 2 * n) ans += (cnt[i] >= 1) + (cnt[i] >= 2);
    cout << ans << '\n';
    For(i, 1, 2 * n) if (cnt[i] == 1 && !vis[i]) dfs1(i, 1, 0);
    For(i, 1, 2 * n) if (cnt[i] >= 2 && !vis[i]) dfs1(i, 1, 1);
    For(i, 1, n) cout << a[i] << ' ';
    cout << '\n';
    For(i, 1, n) cout << b[i] << ' ';
    cout << '\n';
  }
  return 0;
}