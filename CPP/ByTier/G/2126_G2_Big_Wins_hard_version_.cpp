/*
 * Problem URL : https://codeforces.com/problemset/problem/2126/G2
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
int a[200001], dsu[2][200001], q[200001], m, n, r, s, t;
bool v[2][200001];
bool cmp(int i, int j) { return a[i] == a[j] ? i < j : a[i] < a[j]; }
int find(int w, int x) {
  return dsu[w][x] == x ? dsu[w][x] : dsu[w][x] = find(w, dsu[w][x]);
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  for (cin >> t; t; t--) {
    cin >> n;
    r = 0;
    m = 1000000000;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      q[i] = i;
      dsu[0][i] = i;
      dsu[1][i] = i;
      v[0][i] = 0;
      v[1][i] = 0;
    }
    sort(q + 1, q + n + 1, cmp);
    for (int i = n; i >= 1; i--) {
      s = 2;
      if (!v[0][q[i]]) {
        v[0][q[i]] = 1;
        m = min(a[q[i]], m);
        s--;
      }
      for (int j = find(0, q[i]); j >= 2 && s >= 1; j = find(0, j - 1)) {
        if (!v[0][j - 1]) {
          v[0][j - 1] = 1;
          m = min(a[j - 1], m);
          s--;
        }
        dsu[0][j] = find(0, j - 1);
      }
      s = 2;
      if (!v[1][q[i]]) {
        v[1][q[i]] = 1;
        m = min(a[q[i]], m);
        s--;
      }
      for (int j = find(1, q[i]); j <= n - 1 && s >= 1; j = find(1, j + 1)) {
        if (!v[1][j + 1]) {
          v[1][j + 1] = 1;
          m = min(a[j + 1], m);
          s--;
        }
        dsu[1][j] = find(1, j + 1);
      }
      r = max(a[q[i]] - m, r);
    }
    cout << r << '\n';
  }
  return 0;
}