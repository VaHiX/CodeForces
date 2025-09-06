/*
 * Problem URL : https://codeforces.com/problemset/problem/2038/G
 * Submit Date : 2025-08-10
 */

#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::cout << "1 1" << std::endl << std::flush;
    long x;
    std::cin >> x;
    std::cout << "1 01" << std::endl << std::flush;
    long y;
    std::cin >> y;
    std::cout << "1 11" << std::endl << std::flush;
    long z;
    std::cin >> z;
    std::cout << "0 1 " << (x == y + z + 1 ? "1" : "0") << std::endl
              << std::flush;
    long res;
    std::cin >> res;
  }

  return 0;
}
