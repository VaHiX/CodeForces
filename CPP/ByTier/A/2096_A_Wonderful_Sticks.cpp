/*
 * Problem URL : https://codeforces.com/problemset/problem/2096/A
 * Submit Date : 2025-08-10
 */

#include <iostream>
#include <vector>

int main() {

  std::ios_base::sync_with_stdio(false);

  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    long mn(1), mx(n);
    std::vector<long> v(n);
    for (long p = s.size() - 1; p >= 0; p--) {
      v[p + 1] = (s[p] == '<') ? (mn++) : (mx--);
    }
    v[0] = mx;

    for (long p = 0; p < v.size(); p++) {
      std::cout << v[p] << " ";
    }
    std::cout << std::endl;
  }
}
