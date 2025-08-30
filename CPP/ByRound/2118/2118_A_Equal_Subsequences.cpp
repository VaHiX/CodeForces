/*
 * Problem URL : https://codeforces.com/problemset/problem/2118/A
 * Submit Date : 2025-08-10
 */

#include <iostream>

int main() {

  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::cout << std::string(n - k, '0') << std::string(k, '1') << std::endl;
  }
}
