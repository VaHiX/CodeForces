/*
 * Problem URL : https://codeforces.com/contest/2004/problem/D
 * Submit Date : 2025-09-14
 */

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
const int _ = 2e5 + 5;
int n, m;
int z[_], l[_], r[_];
map<string, int> to;
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  to["BG"] = 1, to["RY"] = 6, to["BR"] = 2, to["GY"] = 5, to["BY"] = 3,
  to["GR"] = 4;
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      string p;
      cin >> p;
      z[i] = to[p];
    }
    z[n + 1] = 0;
    for (int i = 1; i <= n; i++)
      l[i] = z[i - 1] == z[i] || z[i - 1] + z[i] == 7 ? l[i - 1] + 1 : 1;
    for (int i = n; i >= 1; i--)
      r[i] = z[i + 1] == z[i] || z[i + 1] + z[i] == 7 ? r[i + 1] + 1 : 1;
    while (m--) {
      int x, y;
      cin >> x >> y;
      if (x > y)
        swap(x, y);
      if (z[x] + z[y] != 7 || x + r[x] < y)
        printf("%d\n", y - x);
      else {
        if (l[x] == x && y + r[y] == n + 1)
          printf("-1\n");
        else {
          if (l[x] == x)
            printf("%d\n", 2 * r[y] + y - x);
          if (y + r[y] == n + 1)
            printf("%d\n", 2 * l[x] + y - x);
          if (l[x] != x && y + r[y] != n + 1)
            printf("%d\n", 2 * min(l[x], r[y]) + y - x);
        }
      }
    }
  }
}