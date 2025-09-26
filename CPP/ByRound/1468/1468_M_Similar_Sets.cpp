/*
 * Problem URL : https://codeforces.com/contest/1468/problem/M
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
#define um unordered_map

using namespace std;

const int N = 2e5 + 10;

int T, n, K[N], tmp[N], inv[N];
bool vis[N];
int lst[N];

void print(pair<int, int> res) {
  if (res.first > res.second)
    swap(res.first, res.second);
  printf("%d %d\n", res.first, res.second);
  return;
}

vector<int> vec[N];
vector<pair<int, int>> e[N];

void solve() {
  vector<int> vec[n + 10];
  int m = 0, S = 0;
  for (int i = 1; i <= n; S += K[i], ++i) {
    scanf("%d", &K[i]);
    vec[i].clear();
    for (int j = 0; j < K[i]; ++j) {
      int x;
      scanf("%d", &x);
      vec[i].emplace_back(x);
      tmp[++m] = x;
    }
  }
  sort(tmp + 1, tmp + 1 + m);
  m = unique(tmp + 1, tmp + 1 + m) - tmp - 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < K[i]; ++j) {
      int x = lower_bound(tmp + 1, tmp + 1 + m, vec[i][j]) - tmp;
      inv[x] = vec[i][j], vec[i][j] = x;
    }
  }
  int B = sqrt(S) / 2;
  bool flag = false;
  pair<int, int> res;
  for (int i = 1; i <= n; ++i) {
    if (K[i] <= B)
      continue;
    for (int j = 0; j < K[i]; ++j) {
      vis[vec[i][j]] = true;
    }
    for (int p = 1; p <= n; ++p) {
      if (p == i)
        continue;
      int cnt = 0;
      for (int j = 0; j < K[p]; ++j) {
        if (vis[vec[p][j]])
          cnt++;
        if (cnt >= 2) {
          flag = true;
          res = {i, p};
          break;
        }
      }
      if (flag)
        break;
    }
    for (int j = 0; j < K[i]; ++j) {
      vis[vec[i][j]] = false;
    }
    if (flag) {
      print(res);
      return;
    }
  }

  for (int i = 1; i <= m; ++i) {
    e[i].clear();
  }

  for (int i = 1; i <= n; ++i) {
    if (K[i] > B)
      continue;
    for (int j = 0; j < K[i]; ++j) {
      for (int k = j + 1; k < K[i]; ++k) {
        e[min(vec[i][j], vec[i][k])].push_back({max(vec[i][j], vec[i][k]), i});
      }
    }
  }

  for (int x = 1; x <= m; ++x) {
    for (int j = 0; j < e[x].size(); ++j) {
      if (lst[e[x][j].first]) {
        flag = true;
        res = {lst[e[x][j].first], e[x][j].second};
        break;
      }
      lst[e[x][j].first] = e[x][j].second;
    }

    for (int j = 0; j < e[x].size(); ++j) {
      lst[e[x][j].first] = 0;
    }

    if (flag) {
      print(res);
      return;
    }
  }

  puts("-1");
  return;
}

int main(void) {

  scanf("%d", &T);

  while (T--) {
    scanf("%d", &n);
    solve();
  }

  return 0;
}