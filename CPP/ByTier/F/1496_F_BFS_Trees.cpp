/*
 * Problem URL : https://codeforces.com/problemset/problem/1496/F
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500, MOD = 998244353;

int n, m, dis[MAXN][MAXN];
long long answer[MAXN][MAXN];
vector<int> adj[MAXN], par[MAXN][MAXN];
queue<int> q;

void dist() {
  for (int i = 1; i <= n; i++) {
    q.push(i);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto u : adj[v]) {
        if (u != i && dis[i][u] == 0) {
          q.push(u);
          dis[i][u] = dis[i][v] + 1;
        }
        if (dis[i][u] == dis[i][v] + 1)
          par[i][u].push_back(v);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dist();
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      int sp = 0; // This is not special it represents shortest path!!
      for (int k = 1; k <= n; k++) {
        if (dis[i][k] + dis[k][j] == dis[i][j] && k != i && k != j)
          sp++;
      }
      long long ans = 1;
      if (sp > dis[i][j] - 1 && i != j) // -1 is because we want the number of
                                        // verticies in the shortest path
        ans = 0; // it is not possible if there are more than one shortest path
                 // between i and j
      for (int k = 1; k <= n; k++) {
        if (ans == 0)
          break;
        if (dis[i][j] != dis[i][k] + dis[j][k]) {
          int t = 0;
          for (auto u : par[i][k]) {
            if (dis[j][k] == dis[j][u] + 1)
              t++;
          }
          ans = ans * t % MOD;
        }
      }
      answer[i][j] = answer[j][i] = ans;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      cout << answer[i][j] << ' ';
    cout << '\n';
  }

  return 0;
}