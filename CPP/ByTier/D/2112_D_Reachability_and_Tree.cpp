/*
 * Problem URL : https://codeforces.com/problemset/problem/2112/D
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> gr;

void f(int x, int p, int c) {
  for (auto y : gr[x]) {
    if (c)
      cout << x + 1 << ' ' << y + 1 << '\n';
    if (y != p)
      f(y, x, c ^ 1);
  }
}

void solve() {
  int n;
  cin >> n;
  gr.clear();
  gr.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    gr[u].push_back(v);
    gr[v].push_back(u);
  }
  for (int i = 0; i < n; ++i) {
    if (gr[i].size() == 2) {
      cout << "YES\n";
      f(gr[i][0], i, 1);
      f(gr[i][1], i, 0);
      cout << i + 1 << ' ' << gr[i][1] + 1 << '\n';
      return;
    }
  }
  cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}