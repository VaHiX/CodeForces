/*
 * Problem URL : https://codeforces.com/problemset/problem/1141/A
 * Submit Date : 2025-08-13
 */

#import <iostream>
int m, n, s;
main() {
  std::cin >> n >> m;
  if (m % n)
    return std::cout << -1, 0;
  for (m /= n; ~m % 2 || m % 3 < 1; s++)
    m % 2 ? m % 3 ?: m /= 3 : m /= 2;
  std::cout << (m > 1 ? -1 : s);
}