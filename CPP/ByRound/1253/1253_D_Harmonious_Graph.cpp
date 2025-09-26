/*
 * Problem URL : https://codeforces.com/contest/1253/problem/D
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m, res, f[N], j = 1;
int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
void merge(int x, int y) {
  x = find(x);
  y = find(y);
  f[min(x, y)] = max(x, y);
}
signed main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    f[i] = i;
  for (int i = 1, a, b; i <= m; i++)
    scanf("%d %d", &a, &b), merge(a, b);
  for (int i = 1; i < n; i++) {
    int r = find(i);
    for (; j <= r; j++) {
      if (find(j) != find(i))
        merge(j, r), res++;
    }
    if (j < r + 1)
      j = r + 1;
  }
  cout << res << endl;
  return 0;
}
