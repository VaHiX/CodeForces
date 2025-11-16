// Problem: CF 1694 A - Creep
// https://codeforces.com/contest/1694/problem/A

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long a, b;
    std::cin >> a >> b;
    std::string s("");
    // Start with the character that has more count to minimize the maximum difference
    if (a >= b) {
      s = "0";
      --a;
    } else {
      s = "1";
      --b;
    }
    // Alternate between the two characters to keep the difference minimal
    while (a > 0 || b > 0) {
      if (s.back() == '0') {
        // If the last character is '0', append '1' if available
        if (b > 0) {
          s += '1';
          --b;
        } else if (a > 0) {
          // Otherwise, append '0' if available
          s += '0';
          --a;
        }
      } else if (s.back() == '1') {
        // If the last character is '1', append '0' if available
        if (a > 0) {
          s += '0';
          --a;
        } else if (b > 0) {
          // Otherwise, append '1' if available
          s += '1';
          --b;
        }
      }
    }
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/