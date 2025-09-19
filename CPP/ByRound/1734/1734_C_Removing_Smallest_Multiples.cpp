/*
 * Problem URL : https://codeforces.com/problemset/problem/1734/C
 * Submit Date : 2025-08-21
 */

#include <iostream>

int main() {

  std::ios_base::sync_with_stdio(false);

  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    s = "a" + s;

    long long cnt(0);
    for (long p = 1; p < s.size(); p++) {
      if (s[p] == '1') {
        continue;
      }
      for (long q = p; q < s.size() && s[q] != '1'; q += p) {
        cnt += p * (s[q] == '0');
        s[q] = 'x';
      }
    }

    std::cout << cnt << std::endl;
  }
}
