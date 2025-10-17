/*
 * Problem URL : https://codeforces.com/contest/1361/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
#define mst(a) memset(a, 0, sizeof a)
int num[N], n, m;
vector<int> e[N], ans, col[N];
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    int c;
    scanf("%d", &c);
    col[c].push_back(i);
    num[i] = 1;
  }
  for (int i = 1; i <= n; i++) {
    for (auto u : col[i]) {
      if (num[u] != i)
        puts("-1"), exit(0);
      for (auto v : e[u])
        if (num[v] == i)
          num[v]++;
      ans.push_back(u);
    }
  }
  for (auto i : ans)
    printf("%d ", i);
  return 0;
}
