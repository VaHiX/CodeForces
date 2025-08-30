/*
 * Problem URL : https://codeforces.com/problemset/problem/548/B
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;
bitset<501> bb[501];
int ans[501];
int n, m, q;

int update(int x) {
  int s = 0;
  int curr = 0;
  for (int i = 1; i <= m; i++) {
    if (!bb[x][i])
      curr = 0;
    else
      curr++;
    s = max(s, curr);
  }
  ans[x] = s;
  return *max_element(ans + 1, ans + n + 1);
}

int main() {
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      int x;
      cin >> x;
      bb[i][j] = x;
      update(i);
    }
  while (q--) {
    int a, b;
    cin >> a >> b;
    bb[a][b] = !bb[a][b];
    cout << update(a) << endl;
  }
}
