/*
 * Problem URL : https://codeforces.com/contest/1575/problem/L
 * Submit Date : 2025-09-08
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int a[200002], c[200002], i, n, d, x, y;
pair<int, int> b[200002];
int main() {
  scanf("%d", &n);
  for (i = 1; i <= n; i = i + 1) {
    scanf("%d", &a[i]);
    b[i] = pair<int, int>(a[i], -i);
  }
  sort(b + 1, b + n + 1);
  for (i = 1; i <= n; i = i + 1)
    if (-b[i].second >= b[i].first) {
      x = -b[i].second - b[i].first;
      d = upper_bound(c + 1, c + y + 1, x) - c;
      c[d] = x;
      y = max(y, d);
    }
  printf("%d", y);
  return 0;
}