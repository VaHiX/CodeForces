/*
 * Problem URL : https://codeforces.com/problemset/problem/844/C
 * Submit Date : 2025-08-14
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
#include <stack>
#include <string>
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n");
#define nl printf("\n");
#define N 100010
#define pp pair<int, int>

using namespace std;

int n, idx;
pp *a, *sa;
bool vis[N];
vector<int> v[N];

void dfs(pp s) {
  vis[s.second] = 1;
  if (sa[s.second].first == s.first) {
    v[idx].push_back(s.second + 1);
    idx++;
    return;
  }

  v[idx].push_back(s.second + 1);

  pp x = sa[s.second];
  if (!vis[x.second])
    dfs(x);
  else
    idx++;
}

int main() {

  int i, j, k;
  int m;

  cin >> n;

  a = new pp[n];
  sa = new pp[n];

  for (i = 0; i < n; i++) {
    cin >> k;
    a[i] = {k, i};
    sa[i] = a[i];
  }

  sort(sa, sa + n);

  idx = 0;
  memset(vis, 0, sizeof(vis));
  for (i = 0; i < n; i++) {
    if (!vis[i])
      dfs(a[i]);
  }

  cout << idx << endl;
  for (i = 0; i < idx; i++) {
    if (v[i].size()) {
      m = v[i].size();
      cout << m << " ";

      for (j = 0; j < m; j++)
        cout << v[i][j] << " ";

      cout << endl;
    }
  }

  return 0;
}
