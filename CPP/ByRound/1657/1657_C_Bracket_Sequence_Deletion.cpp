/*
 * Problem URL : https://codeforces.com/contest/1657/problem/C
 * Submit Date : 2025-08-27
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1657/C
 * Submit Date : 2025-08-27
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

    long cnt(0), rem(n);
    std::string cur("");
    for (long p = 0; p < n; p++) {
      cur += s[p];
      if (cur == "()" || (cur.size() > 1 && cur.back() == cur[0])) {
        ++cnt;
        rem -= cur.size();
        cur = "";
      }
    }

    std::cout << cnt << " " << rem << std::endl;
  }
}
