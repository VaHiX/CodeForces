/*
 * Problem URL : https://codeforces.com/problemset/problem/2120/F
 * Submit Date : 2025-08-14
 */

#include <cstdio>
#include <vector>
using namespace std;

int a[301][301];
vector<int> g[601];
int dfn[601], low[601], st[601], ins[601];
void dfs(int u) {
  low[u] = dfn[u] = ++dfn[0];
  st[++st[0]] = u;
  ins[u] = 1;
  for (int i = 0; i < g[u].size(); i++) {
    if (!dfn[g[u][i]])
      dfs(g[u][i]);
    if (ins[g[u][i]])
      low[u] = min(low[u], low[g[u][i]]);
  }
  if (low[u] == dfn[u])
    while (st[st[0] + 1] != u) {
      ins[st[st[0]]] = 0;
      low[st[st[0]]] = u;
      st[0]--;
    }
}
int main() {
  int t;
  scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++) {
    int n, k;
    scanf("%d%d", &n, &k);
    dfn[0] = 0;
    for (int i = 1; i <= 2 * n; i++) {
      g[i].clear();
      st[i] = 0;
      dfn[i] = 0;
    }
    for (int i = 1; i <= k; i++) {
      int m;
      scanf("%d", &m);
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          a[i][j] = 0;
      for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        a[u][v] = a[v][u] = 1;
      }
      for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
          for (int k = 1; k <= n; k++)
            if (k != i && k != j && a[i][k] != a[j][k])
              goto ed;
          if (a[i][j]) {
            g[i + n].push_back(j);
            g[j + n].push_back(i);
          } else {
            g[i].push_back(j + n);
            g[j].push_back(i + n);
          }
        ed:;
        }
    }
    // for(int i=1;i<=2*n;i++)
    //	for(int j=0;j<g[i].size();j++)
    //		printf("%d->%d\n",i,g[i][j]);
    for (int i = 1; i <= 2 * n; i++)
      if (!dfn[i])
        dfs(i);
    int ok = 1;
    for (int i = 1; i <= n; i++)
      if (low[i] == low[i + n])
        ok = 0;
    // for(int i=1;i<=2*n;i++){
    //	printf("%d%c",low[i],i==2*n?'\n':' ');
    // }
    printf(ok ? "Yes\n" : "No\n");
  }
}