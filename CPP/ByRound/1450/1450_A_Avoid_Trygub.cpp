/*
 * Problem URL : https://codeforces.com/problemset/problem/1450/A
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string a;
    std::cin >> a;
    sort(a.begin(), a.end());
    std::cout << a << std::endl;
  }
}
