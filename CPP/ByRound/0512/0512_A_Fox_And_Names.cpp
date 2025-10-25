/*
 * Problem URL : https://codeforces.com/contest/512/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;

int n, vi[26];
string s, t;
stack<int> topo;
vector<int> g[26];

void dfs(int u) {
  vi[u] = 1;
  for (auto v : g[u]) {
    if (vi[v] == 1) {
      cout << "Impossible";
      exit(0);
    }
    if (!vi[v])
      dfs(v);
  }
  topo.push(u);
  vi[u] = 2;
}

void addEdge(string u, string v) {
  for (int i = 0; i < min(u.size(), v.size()); i++)
    if (u[i] != v[i]) {
      g[u[i] - 'a'].push_back(v[i] - 'a');
      return;
    }
  if (u.size() > v.size()) {
    cout << "Impossible";
    exit(0);
  }
}

signed main() {
  cin >> n >> s;
  while (n-- - 1) {
    cin >> t;
    addEdge(s, t);
    s = t;
  }
  for (int i = 0; i < 26; i++)
    if (!vi[i])
      dfs(i);
  while (!topo.empty()) {
    cout << char(topo.top() + 'a');
    topo.pop();
  }
  return 0;
}