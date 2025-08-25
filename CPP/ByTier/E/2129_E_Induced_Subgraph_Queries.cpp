/*
 * Problem URL : https://codeforces.com/problemset/problem/2129/E
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, m, k, bn, pre[150005], l, r, w[150005], cnt[262144], sum[512],
    ans[150005];
vector<int> e[150005];
struct query {
  int l, r, k, id;
} q[150005];
bool cmp(query a, query b) {
  return pre[a.l] / bn == pre[b.l] / bn
             ? pre[a.l] / bn & 1 ? a.r < b.r : a.r > b.r
             : pre[a.l] / bn < pre[b.l] / bn;
}
void add(int x) {
  w[x] = 0;
  for (int i = 0; i < e[x].size(); i++) {
    int v = e[x][i];
    if (v >= l && v <= r)
      cnt[w[v]]--, sum[w[v] >> 9]--, w[v] ^= x, cnt[w[v]]++, sum[w[v] >> 9]++,
          w[x] ^= v;
  }
  cnt[w[x]]++, sum[w[x] >> 9]++;
}
void del(int x) {
  cnt[w[x]]--, sum[w[x] >> 9]--, w[x] = 0;
  for (int i = 0; i < e[x].size(); i++) {
    int v = e[x][i];
    if (v >= l && v <= r)
      cnt[w[v]]--, sum[w[v] >> 9]--, w[v] ^= x, cnt[w[v]]++, sum[w[v] >> 9]++;
  }
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cin >> t;
  while (t--) {
    cin >> n >> m, bn = sqrt(n + m);
    for (int i = 1, u, v; i <= m; i++)
      cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
    for (int i = 1; i <= n; i++)
      pre[i] = pre[i - 1] + e[i].size() + 1;
    cin >> k;
    for (int i = 1; i <= k; i++)
      cin >> q[i].l >> q[i].r >> q[i].k, q[i].id = i;
    sort(q + 1, q + k + 1, cmp), l = 1, r = 0;
    for (int i = 1; i <= k; i++) {
      while (l > q[i].l)
        add(--l);
      while (r < q[i].r)
        add(++r);
      while (l < q[i].l)
        del(l++);
      while (r > q[i].r)
        del(r--);
      for (int j = 0;; q[i].k -= sum[j >> 9], j += 512) {
        if (q[i].k <= sum[j >> 9]) {
          while (q[i].k > cnt[j])
            q[i].k -= cnt[j++];
          ans[q[i].id] = j;
          break;
        }
      }
    }
    for (int i = 1; i <= k; i++)
      cout << ans[i] << '\n';
    for (int i = 1; i <= n; i++)
      e[i].clear(), w[i] = 0;
    for (int i = 0; i < 2 << __lg(n); i++)
      cnt[i] = 0;
    memset(sum, 0, sizeof(sum));
  }
  return 0;
}