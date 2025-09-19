/*
 * Problem URL : https://codeforces.com/problemset/problem/1060/A
 * Submit Date : 2025-08-19
 */

#include <iostream>

int main() {
  std::ios_base::sync_with_stdio(false);
  const long N = 11;
  long len;
  std::string s;
  std::cin >> len >> s;
  long eights(0);
  for (long p = 0; p < s.size(); p++) {
    eights += (s[p] == '8');
  }
  long ans = (s.size() / N);
  ans = (ans < eights) ? ans : eights;
  std::cout << ans << std::endl;

  return 0;
}
