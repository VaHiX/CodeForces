/*
 * Problem URL : https://codeforces.com/problemset/problem/1986/C
 * Submit Date : 2025-08-12
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int main() {

  std::ios_base::sync_with_stdio(false);

  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;
    std::set<long> t;
    for (long p = 0; p < m; p++) {
      long x;
      std::cin >> x;
      t.insert(--x);
    }
    std::string r;
    std::cin >> r;
    sort(r.begin(), r.end());

    long idx(0);
    for (std::set<long>::iterator it = t.begin(); it != t.end(); it++) {
      long pos = *it;
      s[pos] = r[idx++];
    }

    std::cout << s << std::endl;
  }
}
