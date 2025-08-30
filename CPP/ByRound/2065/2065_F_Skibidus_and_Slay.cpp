/*
 * Problem URL : https://codeforces.com/problemset/problem/2065/F
 * Submit Date : 2025-08-23
 */

#include <stdio.h>
#include <vector>
using namespace std;

int n, a[500005], b[500005], ans[500005];
vector<int> edge[500005];

void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    edge[i].clear(), ans[i] = 0;
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    if (a[u] == a[v])
      ans[a[u]] = 1;
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    for (auto j : edge[i]) {
      if (b[a[j]])
        ans[a[j]] = 1;
      b[a[j]]++;
    }
    for (auto j : edge[i])
      b[a[j]]--;
  }
  for (int i = 1; i <= n; i++)
    printf("%d", ans[i]);
  putchar('\n');
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}