/*
 * Problem URL : https://codeforces.com/problemset/problem/1995/D
 * Submit Date : 2025-08-13
 */

#include <algorithm>
#include <iostream>
bool m[300001];
char s[300001];
int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  int t;
  std::cin >> t;
  while (t--) {
    int n, c, k;
    std::cin >> n >> c >> k >> s;
    for (int i = 1; i < 1 << c; i++)
      m[i] = 1;
    int u[18]{}, v = 0;
    for (int i = 0; i < k; i++)
      u[s[i] - 'A']++, v |= 1 << s[i] - 'A';
    for (int i = 0; i < n; i++) {
      m[(1 << c) - 1 ^ v] = 0, v ^= (!--u[s[i] - 'A']) << s[i] - 'A';
      if (i + k < n)
        u[s[i + k] - 'A']++, v |= 1 << s[i + k] - 'A';
    }
    for (int i = 0; i < c; i++)
      for (int j = 0; j < 1 << c; j++)
        if (j & 1 << i)
          m[j ^ 1 << i] &= m[j];
    int ans = c;
    for (int i = 0; i < 1 << c; i++)
      if (m[i])
        ans = std::min(ans, __builtin_popcount(i));
    std::cout << ans << '\n';
  }
  return 0;
}