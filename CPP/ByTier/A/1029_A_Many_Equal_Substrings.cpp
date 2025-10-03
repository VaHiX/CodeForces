/*
 * Problem URL : https://codeforces.com/contest/1029/problem/A
 * Submit Date : 2025-08-30
 */

#include <iostream>

int main() {

  long n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;

  long start(0);
  for (long dist = 1; dist < s.size(); dist++) {
    long g(dist);
    while (g < s.size()) {
      if (s[g - dist] != s[g]) {
        break;
      }
      ++g;
    }
    if (g == s.size()) {
      start = s.size() - dist;
      break;
    }
  }

  std::cout << s;
  for (long p = 1; p < k; p++) {
    std::cout << s.substr(start);
  }
  std::cout << std::endl;

  return 0;
}
