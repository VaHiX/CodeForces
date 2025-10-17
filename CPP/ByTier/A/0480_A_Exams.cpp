/*
 * Problem URL : https://codeforces.com/contest/480/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
main() {
  pair<int, int> a[5005];
  int n, i, s, x, y;
  for (scanf("%d", &n), i = 0; i < n; i++)
    scanf("%d%d", &x, &y), a[i] = make_pair(x, y);
  sort(a, a + n);
  for (i = 0, s = 0; i < n; i++)
    s = a[i].second < s ? a[i].first : a[i].second;
  printf("%d\n", s);
} /*1698474545.8304822*/