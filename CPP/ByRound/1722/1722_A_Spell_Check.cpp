/*
 * Problem URL : https://codeforces.com/problemset/problem/1722/A
 * Submit Date : 2025-08-21
 */

#include <algorithm>
#include <iostream>

int main() {

  std::string target = "Timur";
  sort(target.begin(), target.end());

  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    sort(s.begin(), s.end());
    std::cout << ((s == target) ? "YES" : "NO") << std::endl;
  }
}
