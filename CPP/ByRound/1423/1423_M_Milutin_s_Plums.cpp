/*
 * Problem URL : https://codeforces.com/contest/1423/problem/M
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
int Tim = 1;
const int N = 1e6 + 5;
const int inf = 1e9;
int n, m;
unordered_map<int, int> a[N];
int f[N], p[N];
int ask(int x, int y) {
  if (a[x].count(y)) {
    return a[x][y];
  }
  cout << "? " << x << ' ' << y << endl;
  cin >> a[x][y];
  return a[x][y];
}
void calc(int i, int j) {
  if (f[i] > ask(i, j)) {
    p[i] = j;
    f[i] = ask(i, j);
  }
}
void SMAWK(vector<int> r, vector<int> c) {
  vector<int> C;
  int k = -1;
  for (int i : c) {
    while (!C.empty() && ask(r[k], C[k]) >= ask(r[k], i)) {
      C.pop_back();
      k--;
    }
    if (k + 1 < r.size()) {
      C.push_back(i);
      k++;
    }
  }
  if (r.size() == 1) {
    calc(r[0], C[0]);
    return;
  }
  vector<int> R;
  for (int i = 1; i < r.size(); i += 2) {
    R.push_back(r[i]);
  }
  c = C;
  SMAWK(R, c);
  int u = 0;
  for (int i = 0; i < r.size(); i += 2) {
    while (u < c.size() && c[u] < (i + 1 == r.size() ? inf : p[r[i + 1]])) {
      calc(r[i], c[u]);
      u++;
    }
    if (u < c.size()) {
      calc(r[i], c[u]);
    }
  }
}
vector<int> r, c;
void Solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    r.push_back(i);
  }
  for (int i = 1; i <= m; i++) {
    c.push_back(i);
  }
  memset(f, 0x3f, sizeof f);
  SMAWK(r, c);
  int ans = inf;
  for (int i = 1; i <= n; i++) {
    ans = min(ans, f[i]);
  }
  cout << "! " << ans << endl;
}
signed main() {
  while (Tim--) {
    Solve();
  }
  return 0;
}