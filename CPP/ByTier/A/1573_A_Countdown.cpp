// Problem: CF 1573 A - Countdown
// https://codeforces.com/contest/1573/problem/A

/*
Problem: Minimum operations to reduce a number to 0 on a digital clock.

Algorithm/Techniques: Greedy approach with digit manipulation.
Time Complexity: O(n) where n is the number of digits in the string.
Space Complexity: O(1) - only using a few variables for computation.

Approach:
- For each digit, we count its contribution to the total operations.
- If a digit is non-zero, we add 1 operation for swapping it with a preceding zero,
  and also add the digit's value as a decrement operation needed to make it 0.
- The key insight is that we can swap digits to move zeros to earlier positions,
  minimizing the number of decrements needed.

*/

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
    long res(0);
    for (long p = 0; p < s.size(); p++) {
      res += (s[p] - '0'); // Add the numeric value of current digit for decrements needed
      if ((p < s.size() - 1) && (s[p] > '0')) {
        ++res; // Increment for a possible swap operation with a zero ahead
      }
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/