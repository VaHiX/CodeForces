/*
 * Problem URL : https://codeforces.com/contest/2025/problem/F
 * Submit Date : 2025-09-10
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int a[N], b[N], n, m, pre[N], k;
bool f[N];
struct Node {
  int x, y;
} d[N];
struct node {
  int to, nxt, id;
} e[N * 2];
void add(int u, int v, int id) {
  k++;
  e[k] = {v, pre[u], id};
  pre[u] = k;
}
void dfs(int x) {
  f[x] = true;
  for (int i = pre[x]; i; i = e[i].nxt) {
    int to = e[i].to;
    if (!f[to]) {
      dfs(to);
      if (a[to]) {
        a[to] ^= 1, a[x] ^= 1;
        b[e[i].id] ^= 1;
      }
    }
  }
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &d[i].x, &d[i].y);
    a[d[i].x] ^= 1;
    add(d[i].x, d[i].y, i);
    add(d[i].y, d[i].x, i);
  }
  for (int i = 1; i <= n; i++) {
    if (!f[i])
      dfs(i);
  }
  memset(a, 0, sizeof(a));
  for (int i = 1; i <= m; i++) {
    if (!b[i]) {
      if (!a[d[i].x])
        printf("x+\n");
      else
        printf("x-\n");
      a[d[i].x] ^= 1;
    } else {
      if (!a[d[i].y])
        printf("y+\n");
      else
        printf("y-\n");
      a[d[i].y] ^= 1;
    }
  }
  return 0;
}
