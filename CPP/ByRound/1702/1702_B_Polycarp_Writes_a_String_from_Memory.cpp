/*
 * Problem URL : https://codeforces.com/problemset/problem/1702/B
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1702/B
 * Submit Date : 2025-08-21
 */

#include <iostream>
#include <set>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long cnt(0);
    std::set<long> w;
    for (long p = 0; p < s.size(); p++) {
      w.insert(s[p]);
      if (w.size() > 3) {
        ++cnt;
        w.clear();
        w.insert(s[p]);
      }
    }

    cnt += (w.size() > 0);
    std::cout << cnt << std::endl;
  }
}
