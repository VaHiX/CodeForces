// Problem: CF 1817 F - Entangled Substrings
// https://codeforces.com/contest/1817/problem/F

/*
 * Problem: F. Entangled Substrings
 * Algorithm: Suffix Automaton + Tree DFS
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * The solution uses suffix automaton to efficiently compute all entangled substring pairs.
 * An entangled pair (a,b) means that a and b can only appear as parts of the substring "acb"
 * for some link string c. 
 * The suffix automaton identifies all unique substrings and their occurrences.
 * Then DFS on the automaton tree helps count valid entangled pairs by tracking
 * how often substrings appear and how they interact in the structure.
 */

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int maxn = 100005;
int son[maxn * 2][26], pa[maxn * 2], len[maxn * 2], vis[maxn * 2], tot;
int extend(int p, int o) {
  int now = ++tot;
  len[now] = len[p] + 1;
  while (~p && !son[p][o])
    son[p][o] = now, p = pa[p];
  if (!~p)
    pa[now] = 0;
  else {
    int d = son[p][o];
    if (len[d] == len[p] + 1)
      pa[now] = d;
    else {
      int _d = ++tot;
      len[_d] = len[p] + 1;
      for (int i = 0; i < 26; ++i)
        son[_d][i] = son[d][i];
      while (~p && son[p][o] == d)
        son[p][o] = _d, p = pa[p];
      pa[_d] = pa[d];
      pa[d] = pa[now] = _d;
    }
  }
  return now;
}
char s[maxn];
int SON[maxn * 2], BRO[maxn * 2], FA[maxn * 2];
void Addson(int u, int v) {
  BRO[v] = SON[u], SON[u] = v;
  FA[v] = u;
}
void update(int u) {
  for (int v = SON[u]; v; v = BRO[v]) {
    update(v);
    vis[u] += vis[v];
  }
}
int st[maxn], tp;
long long ans = 0;
long long CNT[maxn * 2], SUM[maxn * 2];
void dfs(int u, int depth, long long tc, long long ts) {
  ++CNT[depth + len[pa[u]]];
  SUM[depth + len[pa[u]]] -= depth + len[pa[u]];
  tc += CNT[depth];
  ts += SUM[depth];
  ans += 1ll * (len[u] - len[pa[u]]) * (tc * depth + ts);
  for (int v = SON[u]; v; v = BRO[v]) {
    dfs(v, depth + 1, tc, ts);
  }
  tc -= CNT[depth];
  ts -= SUM[depth];
  --CNT[depth + len[pa[u]]];
  SUM[depth + len[pa[u]]] += depth + len[pa[u]];
}
int main() {
  pa[0] = -1;
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  ++vis[0];
  for (int i = 1, p = 0; i <= n; ++i)
    ++vis[p = extend(p, s[i] - 'a')];
  for (int i = 1; i <= tot; ++i)
    Addson(pa[i], i);
  update(0);
  for (int i = 0; i <= tot; ++i)
    SON[i] = BRO[i] = FA[i] = 0;
  for (int i = 0; i <= tot; ++i)
    for (int j = 0; j < 26; ++j)
      if (son[i][j] && vis[son[i][j]] == vis[i])
        Addson(son[i][j], i);
  for (int i = 0; i <= tot; ++i)
    if (!FA[i])
      dfs(i, 0, 0, 0);
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/