/*
 * Problem URL : https://codeforces.com/contest/1196/problem/D2
 * Submit Date : 2025-08-27
 */

/*
 * Problem URL : https://codeforces.com/contest/1196/problem/D2
 * Submit Date : 2025-08-27
 */

#include <iostream>

int main() {

  const std::string templ = "RGB";

  long q;
  std::cin >> q;
  while (q--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;

    long mn(1e9);
    for (long d = 0; d < 3; d++) {
      long cnt(0), mind(1e9);
      for (long p = 0; p < n; p++) {
        if (s[p] != templ[(d + p) % 3]) {
          ++cnt;
        }
        if (p >= k && s[p - k] != templ[(d + p - k) % 3]) {
          --cnt;
        }
        if (p >= k - 1) {
          mind = (mind < cnt) ? mind : cnt;
        }
      }

      mn = (mn < mind) ? mn : mind;
    }

    std::cout << mn << std::endl;
  }

  return 0;
}
