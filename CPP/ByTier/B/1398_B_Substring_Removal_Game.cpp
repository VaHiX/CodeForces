/*
 * Problem URL : https://codeforces.com/contest/1398/problem/B
 * Submit Date : 2025-09-04
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::vector<long> v;
    long cnt(0);
    bool ones(false);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '1') {
        ones = true;
        ++cnt;
      } else {
        if (ones) {
          v.push_back(cnt);
        }
        cnt = 0;
        ones = false;
      }
    }

    if (ones) {
      v.push_back(cnt);
    }
    sort(v.rbegin(), v.rend());

    long total(0);
    for (long p = 0; p < v.size(); p += 2) {
      total += v[p];
    }
    printf("%ld\n", total);
  }

  return 0;
}
