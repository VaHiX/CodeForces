// Problem: CF 1980 G - Yasya and the Mysterious Tree
// https://codeforces.com/contest/1980/problem/G

/*
Purpose: This code solves a problem involving queries on a tree where edges can be updated with XOR operations and for each query an optimal cycle is computed.

Algorithms/Techniques:
- DFS traversal to build a tree with path weights from root
- Trie-based data structure to efficiently compute maximum XOR values
- XOR properties for cycle detection in graph (path from u to v XORed with new edge)
- Lazy propagation for XOR updates

Time Complexity: O(n * log(max_val) + m * log(max_val))
Space Complexity: O(n * log(max_val))

*/

#include <algorithm>
#include <iostream>
#include <vector>

#define pb push_back
#define fi first
#define se second
#define N 200005
using namespace std;
int n, m, cnt;
int head[N], tot;
struct node {
  int nxt, to, val;
} e[N * 2];
struct que {
  int x, y, id;
};
vector<que> vec[N];
int a[N], dep[N];
int f[N];
void add(int u, int v, int w) {
  e[++tot].to = v;
  e[tot].val = w;
  e[tot].nxt = head[u];
  head[u] = tot;
}
namespace Trie {
int trie[2][N * 32][2];
int tot[2];
int cnt[2][N * 32];
void clr() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j <= tot[i]; j++) {
      cnt[i][j] = 0;
      trie[i][j][0] = trie[i][j][1] = 0;
    }
    tot[i] = 0;
  }
}
void ins(int x, int id) {
  int u = 0;
  for (int i = 30; i >= 0; i--) {
    int v = (x >> i) & 1;
    if (!trie[id][u][v])
      trie[id][u][v] = ++tot[id];
    u = trie[id][u][v];
    ++cnt[id][u];
  }
}
void del(int x, int id) {
  int u = 0;
  for (int i = 30; i >= 0; i--) {
    int v = (x >> i) & 1;
    if (!trie[id][u][v])
      trie[id][u][v] = ++tot[id];
    u = trie[id][u][v];
    --cnt[id][u];
  }
}
int qry(int x, int id) {
  int res = 0;
  int u = 0;
  for (int i = 30; i >= 0; i--) {
    int v = (x >> i) & 1;
    if (!cnt[id][trie[id][u][v ^ 1]])
      u = trie[id][u][v];
    else
      u = trie[id][u][v ^ 1], res += (1 << i);
  }
  return res;
}
} // namespace Trie
void dfs(int u, int fa) {
  dep[u] = dep[fa] ^ 1;
  Trie::ins(a[u], dep[u]);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].to, w = e[i].val;
    if (v == fa)
      continue;
    a[v] = a[u] ^ w;
    dfs(v, u);
  }
}
void sol() {
  cin >> n >> m;
  tot = 0;
  cnt = 0;
  for (int i = 1; i <= n; i++) {
    head[i] = 0;
    vec[i].clear();
  }
  for (int i = 1; i <= m; i++)
    f[i] = -1;
  for (int i = 1, u, v, w; i < n; i++) {
    cin >> u >> v >> w;
    add(u, v, w);
    add(v, u, w);
  }
  Trie::clr();
  dfs(1, 0);
  int sum = 0;
  char opt;
  int x, y;
  while (m--) {
    cin >> opt;
    if (opt == '^') {
      cin >> x;
      sum ^= x;
    } else {
      cin >> x >> y;
      Trie::del(a[x], dep[x]);
      cout << max(Trie::qry(y ^ a[x], dep[x]),
                  Trie::qry(y ^ a[x] ^ sum, dep[x] ^ 1))
           << ' ';
      Trie::ins(a[x], dep[x]);
    }
  }
  cout << endl;
}
signed main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--)
    sol();
  return 0;
}


// https://github.com/VaHiX/CodeForces/