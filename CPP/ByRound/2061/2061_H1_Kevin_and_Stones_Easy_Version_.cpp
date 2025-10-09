/*
 * Problem URL : https://codeforces.com/problemset/problem/2061/H1
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 4005, M = 20005;

int n, m;
char a[N], b[N];
int p[N], q[N], k;
int u[M], v[M];
int la[N], ne[M], en[M], idx;
int vis[N], match[N];
int lka[N], lkb[N], id[N];
int fa[N], cnt[N];

inline void Add(int a, int b) {
  ne[++idx] = la[a];
  la[a] = idx;
  en[idx] = b;
}
inline int Find(int u) {
  for (int i = la[u]; i; i = ne[i]) {
    int v = en[i];
    if (!vis[v]) {
      vis[v] = 1;
      if (!match[v] || Find(match[v])) {
        match[v] = u;
        return 1;
      }
    }
  }
  return 0;
}
inline int Match(int p[], int lk[]) {
  for (int i = 1; i <= n; i++)
    id[i] = match[i] = 0;
  for (int i = 1; i <= k; i++)
    id[p[i]] = i;
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= n; j++)
      vis[j] = 0;
    if (!Find(p[i]))
      return 0;
  }
  for (int i = 1; i <= n; i++)
    if (match[i])
      lk[id[match[i]]] = i;
  return 1;
}

inline int gfa(int i) { return i == fa[i] ? i : fa[i] = gfa(fa[i]); }
inline int Check(int d) {
  for (int i = 1; i <= n * 2; i++)
    cnt[i] = 0;
  for (int i = 1; i <= k; i++)
    cnt[gfa(p[i])]++;
  for (int i = 1; i <= k; i++)
    cnt[gfa(q[i] + d)]--;
  for (int i = 1; i <= n * 2; i++)
    if (cnt[i])
      return 0;
  return 1;
}

inline void Solve() {
  scanf("%d%d%s%s", &n, &m, a + 1, b + 1);
  k = 0;
  for (int i = 1; i <= n; i++)
    if (a[i] == '1')
      p[++k] = i;
  k = 0;
  for (int i = 1; i <= n; i++)
    if (b[i] == '1')
      q[++k] = i;
  for (int i = 1; i <= n; i++)
    la[i] = 0;
  idx = 0;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u[i], &v[i]);
    Add(u[i], v[i]), Add(v[i], u[i]);
  }
  int flag = 1;
  for (int i = 1; i <= n; i++)
    flag &= a[i] == b[i];
  if (flag)
    return puts("YES"), void();
  if (!Match(p, lka) || !Match(q, lkb))
    return puts("NO"), void();
  for (int i = 1; i <= n * 2; i++)
    fa[i] = i;
  for (int i = 1; i <= m; i++) {
    fa[gfa(u[i])] = gfa(v[i] + n);
    fa[gfa(v[i])] = gfa(u[i] + n);
  }
  puts(Check(0) || Check(n) ? "YES" : "NO");
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    Solve();
  return 0;
}