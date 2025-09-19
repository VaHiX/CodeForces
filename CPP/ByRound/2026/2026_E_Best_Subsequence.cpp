/*
 * Problem URL : https://codeforces.com/contest/2026/problem/E
 * Submit Date : 2025-09-10
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int kN = 105;

bool vis[kN];
vector<int> e[kN];
int T, n, ans;
int m[kN];

bool DFS(int x) {
  for (int i : e[x]) {
    if (!vis[i]) {
      vis[i] = 1;
      if (!m[i] || DFS(m[i])) {
        m[i] = x;
        return 1;
      }
    }
  }
  return 0;
}

void Clear() {
  for (int i = 1; i <= n; i++) {
    e[i].clear();
  }
  memset(m, 0, sizeof(m));
  ans = 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (cin >> T; T--; Clear()) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      ll x;
      cin >> x;
      for (int j = 1; j <= 61; j++) {
        if (x >> (j - 1) & 1) {
          e[i].push_back(j);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      memset(vis, 0, sizeof(vis));
      ans += DFS(i);
    }
    cout << n - ans << '\n';
  }
  return 0;
}