/*
 * Problem URL : https://codeforces.com/problemset/problem/2107/D
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
inline int read() {
  int x = 0, f = 1;
  char c = 0;
  while (!isdigit(c)) {
    if (c == '-')
      f = -1;
    c = getchar();
  }
  while (isdigit(c)) {
    x = (x << 3) + (x << 1) + (c - '0');
    c = getchar();
  }
  return x * f;
}
const int N = 3e5 + 10;
int n;
int ne[N], e[N], h[N], idx;
int to[N];
bool st[N];
vector<array<int, 3>> ans;
inline void add(int a, int b) {
  ne[idx] = h[a];
  e[idx] = b;
  h[a] = idx++;
}
PII dfs(int u, int pre) {
  PII res = {0, u};
  to[u] = 0;
  for (int i = h[u]; ~i; i = ne[i]) {
    int v = e[i];
    if (v != pre && !st[v]) {
      PII w = dfs(v, u);
      if (w > res)
        res = w, to[u] = v;
    }
  }
  return {res.first + 1, res.second};
}
void work(int u) {
  auto t = dfs(u, u);
  int S = t.second;
  t = dfs(S, S);
  int dia = t.first, T = t.second;
  ans.push_back({dia, max(S, T), min(S, T)});
  for (int now = S; now; now = to[now])
    st[now] = true;
  for (int now = S; now; now = to[now]) {
    for (int i = h[now]; ~i; i = ne[i]) {
      int v = e[i];
      if (!st[v])
        work(v);
    }
  }
}
inline void solve() {
  ans.clear();
  n = read();
  for (int i = 1; i <= n; i++)
    h[i] = -1, st[i] = false;
  idx = 0;
  for (int i = 1; i < n; i++) {
    int a = read(), b = read();
    add(a, b);
    add(b, a);
  }
  work(1);
  sort(ans.begin(), ans.end(), greater<>());
  for (auto [a, b, c] : ans)
    printf("%d %d %d ", a, b, c);
  puts("");
}
int main() {
  int t = read();
  while (t--)
    solve();
  return 0;
}