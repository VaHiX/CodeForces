// Problem: CF 1594 C - Make Them Equal
// https://codeforces.com/contest/1594/problem/C

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    char c;
    std::cin >> n >> c;
    std::string s;
    std::cin >> s;
    long res(0), last(-1);
    bool same(true);
    for (long p = s.size() - 1; p >= 0; p--) {
      // If current character is not equal to target character `c`
      if (s[p] != c) {
        same = false;
      } else if (last < 0) {
        // Record the position of the last occurrence of `c`
        last = p + 1;
      }
    }
    // If all characters are already `c`
    if (same) {
      std::cout << "0" << std::endl;
    } else if (2 * last > n) {
      // If the last `c` is in a position that allows making all characters `c` in one operation
      std::cout << "1\n" << last << std::endl;
    } else {
      // Otherwise, two operations are needed
      std::cout << "2\n" << (n - 1) << " " << n << std::endl;
    }
  }
}

// https://github.com/VaHiX/CodeForces/