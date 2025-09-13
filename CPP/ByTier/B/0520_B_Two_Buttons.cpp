/*
 * Problem URL : https://codeforces.com/problemset/problem/520/B
 * Submit Date : 2025-08-18
 */

#include <iostream>
int n, m, a;
main() {
  std::cin >> n >> m;
  while (n < m)
    m % 2 ? m++ : m /= 2, a++;
  std::cout << a + n - m;
}