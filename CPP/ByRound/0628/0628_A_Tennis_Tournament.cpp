/*
 * Problem URL : https://codeforces.com/problemset/problem/628/A
 * Submit Date : 2025-08-16
 */

#include <iostream>

long getLargestPower(long x) {

  if (x <= 0) {
    return 0;
  }
  long a = 1;
  while (2 * a <= x) {
    a *= 2;
  }
  return a;
}

int main() {

  long n, b, p;
  std::cin >> n >> b >> p;
  long bottles(0), towels(p * n);
  while (n > 1) {
    long m = getLargestPower(n);
    bottles += b * m + (m / 2);
    n -= m / 2;
  }

  std::cout << bottles << " " << towels << std::endl;

  return 0;
}
