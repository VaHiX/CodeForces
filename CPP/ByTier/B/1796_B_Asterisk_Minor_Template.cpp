// Problem: CF 1796 B - Asterisk-Minor Template
// https://codeforces.com/contest/1796/problem/B

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string a, b;
    std::cin >> a >> b;
    if (a[0] == b[0]) {
      // If first characters match, we can use a template like "x*" where x is the common first character
      std::cout << "YES\n" << a[0] << "*" << std::endl;
    } else if (a.back() == b.back()) {
      // If last characters match, we can use a template like "*x" where x is the common last character
      std::cout << "YES\n*" << a.back() << std::endl;
    } else {
      // Try to find a pair of adjacent characters in a and b that can serve as a separator
      long idx(0);
      for (long p = 1; !idx && p < a.size(); p++) {
        for (long q = 1; !idx && q < b.size(); q++) {
          // Check if a[p-1] == b[q-1] and a[p] == b[q]
          // This finds a matching pair of adjacent characters
          if ((a[p - 1] == b[q - 1]) && (a[p] == b[q])) {
            idx = p;
          }
        }
      }
      if (idx) {
        // If found, use a template like "*xy*" where x and y are the matched adjacent characters
        std::cout << "YES\n*" << a[idx - 1] << a[idx] << "*" << std::endl;
      } else {
        // If no such pair exists, it's impossible to form an asterisk-minor template
        std::cout << "NO" << std::endl;
      }
    }
  }
}

// https://github.com/VaHiX/CodeForces/