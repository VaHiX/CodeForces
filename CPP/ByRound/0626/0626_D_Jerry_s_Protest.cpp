/*
 * Problem URL : https://codeforces.com/contest/626/problem/D
 * Submit Date : 2025-09-04
 */

#include <algorithm>
#include <iostream>

int a[2000];
double d[5000], c[5000];

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  double ans = 0.0, b = n * (n - 1) / 2;
  for (int i = 0; i < n; i++)
    std::cin >> a[i];
  std::sort(a, a + n);
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      d[a[j] - a[i]]++;
  for (int i = 1; i < 5000; i++)
    d[i] /= b, c[i] = c[i - 1] + d[i];
  for (int i = 1; i < 5000; i++)
    for (int j = 1; j < i; j++)
      ans += d[i] * d[j] * c[i - j - 1];
  std::cout << ans << "\n";
  return 0;
}
