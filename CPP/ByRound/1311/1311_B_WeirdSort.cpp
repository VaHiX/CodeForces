/*
 * Problem URL : https://codeforces.com/problemset/problem/1311/B
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
int i, j, k, n, m, a[100];
int main() {
  for (scanf("%*d"); ~scanf("%d%d", &n, &m); i = j = 0) {
    std::set<int> p;
    for (; i < n; i++)
      scanf("%d", a + i);
    while (m--)
      scanf("%d", &i), p.insert(i);
    for (k = 1; k <= n; k++)
      if (!p.count(k))
        std::sort(a + j, a + k), j = k;
    puts(std::is_sorted(a, a + n) ? "YES" : "NO");
  }
}