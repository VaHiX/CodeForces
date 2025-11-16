// Problem: CF 1834 B - Maximum Strength
// https://codeforces.com/contest/1834/problem/B

/*
B. Maximum Strength
Algorithm: Greedy approach to maximize digit difference by choosing extremes of range
Time Complexity: O(log R * log R) per test case, where log R is the number of digits in R
Space Complexity: O(log R), for string representations of numbers

The problem involves finding two numbers in the range [L, R] such that 
the sum of absolute differences of their corresponding digits (padded with leading zeros to same length)
is maximized.

Approach:
1. For each test case, try to construct two numbers from L to R that maximize digit difference.
2. The maximum difference for a digit position is 9 (e.g., 0 vs 9).
3. To maximize total strength:
   - We want one number with as many 0s as possible in early positions
   - And another with as many 9s as possible in early positions
4. If L and R are not equal, we compare L and R to find best candidates.
   We try to make first digit of one as small as possible and the other as large as possible,
   and then continue with rest to maximize differences.
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string a, b;
    std::cin >> a >> b;
    long diff = a.size() - b.size();
    if (diff > 0) {
      b = std::string(diff, '0') + b; // Pad b with leading zeros to match size of a
    } else if (diff < 0) {
      a = std::string(-diff, '0') + a; // Pad a with leading zeros to match size of b
    }
    long cnt(0);
    for (long p = 0; p < a.size(); p++) {
      int dist = a[p] - b[p];
      if (!dist) {
        continue; // Skip if digits are same
      }
      cnt = ((dist > 0) ? dist : -dist); // Get absolute difference of current digit
      cnt += 9 * (a.size() - 1 - p);     // Add max possible contribution from remaining digits (each can contribute up to 9)
      break;
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/