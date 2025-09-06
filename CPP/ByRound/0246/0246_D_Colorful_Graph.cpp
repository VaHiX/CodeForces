/*
 * Problem URL : https://codeforces.com/problemset/problem/246/D
 * Submit Date : 2025-08-20
 */

#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <time.h>
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n");
#define nl printf("\n");
#define N 100010
#define inf 1000000

using namespace std;

int color[N];
bool vis[N];
set<int> neighbour[N];
vector<int> adj[N];

void dfs(int s) {
  vis[s] = 1;

  for (int e : adj[s]) {
    if (color[e] != color[s]) {

      neighbour[color[s]].insert(color[e]);
      neighbour[color[e]].insert(color[s]);
    }

    if (!vis[e])
      dfs(e);
  }
}

int main() {

  int i, j, k;
  int n, m, p;
  map<int, bool> mp;

  scanf("%d%d", &n, &m);

  for (i = 1; i <= n; i++)
    scanf("%d", &color[i]), mp[color[i]] = 1;

  for (i = 0; i < m; i++) {
    scanf("%d%d", &j, &k);

    adj[j].push_back(k);
    adj[k].push_back(j);
  }

  memset(vis, 0, sizeof(vis));
  for (i = 1; i <= n; i++) {
    if (!vis[i])
      dfs(i);
  }

  p = -1;
  int ans = 0;
  for (i = 0; i < N; i++) {
    k = neighbour[i].size();
    if (p < k && mp[i]) {
      p = neighbour[i].size();
      ans = i;
    }
  }

  printf("%d\n", ans);

  return 0;
}
