// Problem: CF 1284 A - New Year and Naming
// https://codeforces.com/contest/1284/problem/A

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<std::string> s(n);
  for (long p = 0; p < n; p++) {
    std::cin >> s[p]; // Read n strings into vector s
  }
  std::vector<std::string> t(m);
  for (long p = 0; p < m; p++) {
    std::cin >> t[p]; // Read m strings into vector t
  }
  long q;
  std::cin >> q;
  while (q--) {
    long y;
    std::cin >> y;
    --y; // Convert 1-based index to 0-based
    std::cout << s[y % n] << t[y % m] << std::endl; // Concatenate s and t at cyclic positions
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/