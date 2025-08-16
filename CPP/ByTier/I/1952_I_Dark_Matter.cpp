/*
 * Problem URL : https://codeforces.com/problemset/problem/1952/I
 * Submit Date : 2025-08-12
 */

#include <iostream>

int main() {

  long long a, b;
  char x;
  std::cin >> a >> x >> b;
  std::cout << (a + b +
                ((a * a + b * b) + (a - b) + abs(a) * 2 * b - (a * b + 2)))
            << std::endl;
}
