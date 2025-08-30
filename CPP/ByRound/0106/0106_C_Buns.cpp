/*
 * Problem URL : https://codeforces.com/problemset/problem/106/C
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
int n, m, a, b, c, d, p[1001], s, t, i = 1;
main() {
  for (std::cin >> n >> m >> c >> d; i <= n / c; i++)
    p[i * c] = i * d;
  while (m--)
    for (std::cin >> a >> b >> c >> d, t = 1; t <= a / b; t++)
      for (i = n; i >= c; i--)
        p[i] = std::max(p[i], p[i - c] + d);
  for (i = 1; i <= n; i++)
    s = std::max(s, p[i]);
  std::cout << s;
}