/*
 * Problem URL : https://codeforces.com/problemset/problem/2119/F
 * Submit Date : 2025-08-14
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
const int N = 5e5 + 5, INF = 1e9;
int n, st, w[N];
int dist[N], tim[N];
int h[N], e[N * 2], ne[N * 2], idx;
void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }
void get_dist(int x, int fa) {
  for (int i = h[x]; ~i; i = ne[i]) {
    int j = e[i];
    if (j == fa)
      continue;
    dist[j] = dist[x] + 1;
    get_dist(j, x);
  }
}
int ans = 0;
void dfs(int x, int fa, int height, int k, int Tim, int dst, bool f) {
  if (height < 0)
    Tim = max(Tim, (-height + 1) / 2 * 2 + k * 2 + dst);
  if (Tim <= dist[x])
    ans = max(ans, dist[x]);
  else
    return;
  for (int i = h[x]; ~i; i = ne[i]) {
    int j = e[i];
    if (j == fa)
      continue;
    if (f && w[j] != w[x])
      dfs(j, x, height + w[j], min(k, tim[j]), Tim + 1, dst + 1, 1);
    else
      dfs(j, x, height + w[j], k, Tim + 1, dst + 1, 0);
  }
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    cin >> n >> st;
    idx = 0;
    For(i, 1, n) h[i] = -1, tim[i] = 1e9;
    For(i, 1, n) cin >> w[i];
    For(i, 1, n - 1) {
      int a, b;
      cin >> a >> b;
      add(a, b), add(b, a);
    }
    get_dist(1, 0);
    queue<int> q;
    For(x, 1, n) {
      if (w[x] != 1)
        continue;
      for (int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if (w[j] == 1) {
          q.push(x);
          tim[x] = 0;
          break;
        }
      }
    }
    while (q.size()) {
      int t = q.front();
      q.pop();
      for (int i = h[t]; ~i; i = ne[i]) {
        int j = e[i];
        if (tim[j] == INF && w[j] != w[t]) {
          tim[j] = tim[t] + 1;
          q.push(j);
        }
      }
    }
    ans = 0;
    dfs(st, 0, w[st], tim[st], 1, 1, 1);
    cout << ans + (dist[st] & 1) - 1 << '\n';
  }
  return 0;
}