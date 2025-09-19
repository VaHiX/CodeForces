/*
 * Problem URL : https://codeforces.com/contest/761/problem/A
 * Submit Date : 2025-09-02
 */

#include <iostream>

int main() {

  int a, b;
  std::cin >> a >> b;
  std::cout << (((a + b > 0) && (-1 <= a - b) && (a - b <= 1)) ? "YES" : "NO")
            << std::endl;
  return 0;
}
