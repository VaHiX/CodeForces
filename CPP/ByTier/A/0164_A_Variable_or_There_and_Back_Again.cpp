/*
 * Problem URL : https://codeforces.com/contest/164/problem/A
 * Submit Date : 2025-09-07
 */

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

I f_arr[N];
vector<I> adjs1[N], adjs2[N];
B viss1[N], viss2[N];

void dfs1(I a) {
  if (viss1[a])
    return;
  viss1[a] = 1;
  for (auto b : adjs1[a])
    dfs1(b);
}

void dfs2(I a) {
  if (viss2[a])
    return;
  viss2[a] = 1;
  if (f_arr[a] != 1)
    for (auto b : adjs2[a])
      dfs2(b);
}

I main() {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    cin >> f_arr[i];
  for (I i = 0; i < m; i++) {
    I a, b;
    cin >> a >> b, a--, b--;
    adjs1[a].push_back(b);
    adjs2[b].push_back(a);
  }
  for (I i = 0; i < n; i++) {
    if (f_arr[i] == 1)
      dfs1(i);
    if (f_arr[i] == 2)
      dfs2(i);
  }
  for (I i = 0; i < n; i++)
    printf("%i\n", viss1[i] && viss2[i]);
  return 0;
}