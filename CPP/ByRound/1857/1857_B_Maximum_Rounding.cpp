// Problem: CF 1857 B - Maximum Rounding
// https://codeforces.com/contest/1857/problem/B

/*
B. Maximum Rounding
Algorithm: Greedy approach to find the best rounding position that maximizes the value.
Time Complexity: O(n) where n is the length of the string representation of x.
Space Complexity: O(1) excluding input storage.

The problem asks us to maximize a number by performing rounds (from right to left).
A round at position k means:
- If the digit at position (k-1) >= 5, increment digit at position k
- Handle carry propagation when a digit becomes 9 and needs to be incremented
- Set all digits to the left of k as 0

We iterate from right to left and find the best rounding position that gives max value.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long idx(s.size()); // index of the rounding position, initially set to end
    bool carry(false);  // flag for carrying over 1s
    for (long p = s.size() - 1; p >= 0; p--) {
      // If current digit is >= '5', or if we have a carry from previous and this digit is '4'
      if (s[p] >= '5' || (s[p] == '4' && carry)) {
        idx = p;
        carry = true;
      } else {
        carry = false;
      }
    }
    // If no rounding was determined, output original number
    if (idx == s.size()) {
      std::cout << s << std::endl;
      continue;
    }
    // If we're rounding at first digit, prefix a "1"
    if (idx == 0) {
      std::cout << "1";
    } else {
      // Otherwise, print digits before rounding point and increment the digit at idx-1
      for (long p = 0; p + 1 < idx; p++) {
        std::cout << s[p];
      }
      std::cout << (char)(++s[idx - 1]);
    }
    // Print zeros for all positions after the rounding point
    for (long p = idx; p < s.size(); p++) {
      std::cout << "0";
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/