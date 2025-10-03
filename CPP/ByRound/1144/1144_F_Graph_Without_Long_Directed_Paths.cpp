/*
 * Problem URL : https://codeforces.com/contest/1144/problem/F
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
vector<int> v[200005];
int a[200005];
pair<int, int> e[200005];
bool vis[200005];
int n, m;

void dfs(int x, int f) {
  a[x] = f;
  vis[x] = 1;
  for (int i : v[x])
    if (!vis[i])
      dfs(i, 3 - f);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &e[i].first, &e[i].second);
    v[e[i].first].push_back(e[i].second);
    v[e[i].second].push_back(e[i].first);
  }
  dfs(1, 1);
  for (int i = 0; i < m; i++)
    if (a[e[i].first] == a[e[i].second])
      return puts("NO"), 0;
  puts("YES");
  for (int i = 0; i < m; i++)
    cout << a[e[i].first] - 1;
}
