/*
 * Problem URL : https://codeforces.com/contest/2134/problem/D
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;

int n, rt, ed;
int num, fst[200010], lst[400010], to[400010];
int fa[200010], dep[200010], sz[200010];

void clear() {
  num = 0;
  for (int i = 1; i <= n; i++) {
    fst[i] = 0;
    fa[i] = 0;
  }
}

void insert(int u, int v) {
  lst[++num] = fst[u];
  to[num] = v;
  fst[u] = num;
  lst[++num] = fst[v];
  to[num] = u;
  fst[v] = num;
}

int dfs(int x) {
  sz[x] = 0;
  int md = x;
  for (int i = fst[x]; i; i = lst[i])
    if (fa[x] != to[i]) {
      fa[to[i]] = x;
      dep[to[i]] = dep[x] + 1;
      sz[x]++;
      int nd = dfs(to[i]);
      if (dep[nd] > dep[md])
        md = nd;
    }
  return md;
}

int main() {
  int T, u, v;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    clear();
    for (int i = 1; i < n; i++) {
      scanf("%d%d", &u, &v);
      insert(u, v);
    }
    /*
    if(n==1) {
            puts("-1");
            continue;
    }
    */
    rt = dfs(1);
    for (int i = 1; i <= n; i++) {
      fa[i] = 0;
      dep[i] = 0;
      sz[i] = 0;
    }
    ed = dfs(rt);
    if (dep[ed] == n - 1) {
      puts("-1");
      continue;
    }
    while (sz[fa[ed]] < 2)
      ed = fa[ed];
    for (int i = fst[fa[ed]]; i; i = lst[i])
      if (fa[fa[ed]] != to[i] && ed != to[i]) {
        printf("%d %d %d\n", fa[fa[ed]], fa[ed], to[i]);
        break;
      }
  }
  return 0;
}