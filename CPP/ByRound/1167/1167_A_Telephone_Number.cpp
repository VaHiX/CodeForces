// Problem: CF 1167 A - Telephone Number
// https://codeforces.com/contest/1167/problem/A

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    bool start(false); // Flag to indicate if we've found the first '8'
    long cnt(0);       // Counter for the length of the sequence starting with '8'
    for (long p = 0; p < n; p++) {
      if (!start && s[p] == '8') { // If we haven't started and current char is '8'
        start = true;
        cnt = 1;
      } else if (start) {          // If we have started counting
        ++cnt;
      }
    }
    std::cout << ((cnt >= 11) ? "YES" : "NO") << std::endl; // Check if we have at least 11 digits after the first '8'
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/