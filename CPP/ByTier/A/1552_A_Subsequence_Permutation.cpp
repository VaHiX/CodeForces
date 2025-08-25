/*
 * Problem URL : https://codeforces.com/problemset/problem/1552/A
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
    std::string s;
    std::cin >> s;
    std::string t = s;
    sort(t.begin(), t.end());
    long cnt(0);
    for (long p = 0; p < t.size(); p++) {
      cnt += (s[p] != t[p]);
    }
    std::cout << cnt << std::endl;
  }
}
