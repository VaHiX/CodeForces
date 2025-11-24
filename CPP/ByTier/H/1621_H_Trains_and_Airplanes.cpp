// Problem: CF 1621 H - Trains and Airplanes
// https://codeforces.com/contest/1621/problem/H

#include <stdio.h>
#include <algorithm>
#include <vector>

#define int long long
const int maxn = 2e5 + 5;
const int inf = 1e18;
struct node {
  int to, nxt, val;
} e[maxn << 1];
int n, m, k, q, tot, fa[maxn], col[maxn], h[maxn], w[maxn], f[maxn];
int dis[30], g[maxn][30], min[maxn][30];
char s[maxn], c;
std::vector<int> v[maxn];

// Find function for Union-Find (with path compression)
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

// Add edge to adjacency list
inline void add(int x, int y, int z) { e[++tot] = {y, h[x], z}, h[x] = tot; }

// Calculate fine cost for current path from root to node "now"
void calc(int now) {
  int res = 0, val = 0;
  for (int i = k; i >= 1; i--) {
    if (dis[i]) {
      int tmp = dis[i] + val;
      val = 0;
      int num = tmp / m;
      g[now][i] = num + res;
      res = 0;
      if (tmp % m == 0)
        g[now][i]--, res = 1;
      val = tmp % m;
    }
  }
}

// DFS traversal to compute fine cost for each node for all zones
void dfs(int now, int ff) {
  calc(now);
  for (int i = 1; i <= k; i++)
    min[now][i] = g[now][i];
  for (int i = h[now]; i; i = e[i].nxt) {
    int to = e[i].to;
    if (to != ff) {
      dis[col[to]] += e[i].val;
      dfs(to, now);
      if (col[to] == col[now]) {
        fa[find(to)] = find(now);
        for (int j = 1; j <= k; j++)
          min[find(now)][j] = std::min(min[find(now)][j], min[to][j]);
      }
      dis[col[to]] -= e[i].val;
    }
  }
}

// Post DFS traversal to gather information about zone sets for each node
void get(int now, int ff) {
  int res = 0;
  for (int i = 1; i <= k; i++)
    if (g[now][i] != min[find(now)][i])
      res |= (1 << i);
  v[now].push_back(res);
  for (int i = h[now]; i; i = e[i].nxt) {
    int to = e[i].to;
    if (to != ff) {
      get(to, now);
      if (col[to] == col[now]) {
        for (auto j : v[to])
          v[now].push_back(j);
        std::sort(v[now].begin(), v[now].end());
        v[now].erase(std::unique(v[now].begin(), v[now].end()), v[now].end());
      }
    }
  }
}

// Solve function to calculate minimal cost for a given station
int solve(int now) {
  int res = inf;
  for (auto i : v[now]) {
    int tmp = 0;
    for (int j = 1; j < col[now]; j++) {
      if (j == col[now])
        continue;
      int num = min[find(now)][j] + ((i >> j) & 1);
      tmp += (int)std::min((double)f[j] * num, (double)w[j]);
    }
    res = std::min(res, tmp);
  }
  return res;
}

// Main function to handle input, process queries, and output results
signed main() {
  scanf("%lld", &n);
  for (int i = 1, x, y, z; i < n; i++) {
    scanf("%lld%lld%lld", &x, &y, &z);
    add(x, y, z);
    add(y, x, z);
  }
  scanf("%lld", &k);
  scanf("%s", s + 1);
  for (int i = 1; i <= n; i++)
    col[i] = s[i] - 'A' + 1, fa[i] = i;
  for (int i = 1; i <= k; i++)
    scanf("%lld", &w[i]);
  for (int i = 1; i <= k; i++)
    scanf("%lld", &f[i]);
  scanf("%lld", &m);
  dfs(1, 0);
  get(1, 0);
  scanf("%lld", &q);
  while (q--) {
    int op, x;
    scanf("%lld", &op);
    if (op == 1) {
      scanf(" %c%lld", &c, &x);
      w[c - 'A' + 1] = x;
    } else if (op == 2) {
      scanf(" %c%lld", &c, &x);
      f[c - 'A' + 1] = x;
    } else {
      scanf("%lld", &x);
      printf("%lld\n", solve(x));
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/