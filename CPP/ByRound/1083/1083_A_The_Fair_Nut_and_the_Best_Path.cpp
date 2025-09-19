/*
 * Problem URL : https://codeforces.com/contest/1083/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10;
int T, n, tot, h[N];
ll w[N], dp[N], ans = 0;
struct Edge {
  int v, nxt;
  ll w;
} e[N << 1];
void add(int a, int b, ll c) {
  e[++tot].v = b, e[tot].w = c, e[tot].nxt = h[a], h[a] = tot;
}
void dfs(int x, int fx) {
  dp[x] = w[x];
  ans = max(ans, w[x]);
  for (int i = h[x], v; i; i = e[i].nxt)
    if ((v = e[i].v) != fx) {
      dfs(v, x);
      ans = max(ans, dp[x] + dp[v] - e[i].w);
      dp[x] = max(dp[x], dp[v] + w[x] - e[i].w);
    }
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%lld", w + i);
  for (int i = 1; i < n; i++) {
    int a, b;
    ll c;
    scanf("%d%d%lld", &a, &b, &c);
    add(a, b, c), add(b, a, c);
  }
  dfs(1, 0);
  printf("%lld\n", ans);
}