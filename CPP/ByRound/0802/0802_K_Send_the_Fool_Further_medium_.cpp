/*
 * Problem URL : https://codeforces.com/contest/802/problem/K
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
struct node {
  int to, next, dis;
} a[250001];
struct nood {
  int w, bh;
} s[200001];
int n, k, cnt, g[200001], f[200001][2], size[200001], sum[200001];
void build(int from, int to, int dis) {
  a[++cnt].to = to;
  a[cnt].next = g[from];
  a[cnt].dis = dis;
  g[from] = cnt;
}
bool cmp(nood x, nood y) { return x.w > y.w; }
void dfs(int u, int fa) {
  for (int i = g[u]; i; i = a[i].next) {
    int v = a[i].to;
    if (v != fa) {
      dfs(v, u);
    }
  }
  int t = 0;
  for (int i = g[u]; i; i = a[i].next) {
    int v = a[i].to;
    if (v != fa) {
      f[v][1] += a[i].dis;
      f[v][0] += a[i].dis;
      t++;
      s[t].w = f[v][0];
      s[t].bh = v;
    }
  }
  sort(s + 1, s + t + 1, cmp);
  for (int i = 1; i <= t; i++)
    sum[i] = sum[i - 1] + s[i].w;
  f[u][0] = sum[min(k - 1, t)];
  if (t == 0) {
    return;
  }
  for (int i = 1; i <= k; i++) {
    f[u][1] = max(f[u][1], sum[min(k, t)] - s[i].w + f[s[i].bh][1]);
    if (i >= t) {
      break;
    }
  }
  for (int i = k + 1; i <= t; i++) {
    f[u][1] = max(f[u][1], sum[k - 1] + f[s[i].bh][1]);
  }
}
int main() {
  int x, y, z;
  scanf("%d%d", &n, &k);
  for (int i = 1; i < n; i++) {
    scanf("%d%d%d", &x, &y, &z);
    x++;
    y++;
    build(x, y, z);
    build(y, x, z);
  }
  dfs(1, 0);
  printf("%d", f[1][1]);
  return 0;
}
