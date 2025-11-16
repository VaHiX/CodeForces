// Problem: CF 779 B - Weird Rounding
// https://codeforces.com/contest/779/problem/B

/*
B. Weird Rounding
Problem: Remove minimum digits from a number to make it divisible by 10^k.
Algorithm: Greedy approach - count trailing zeros from right to left,
           and determine how many digits to remove based on required trailing zeros.

Time Complexity: O(n), where n is the length of string s.
Space Complexity: O(1), only using a few variables for counting.

Techniques:
- String traversal from right to left
- Counting specific characters ('0' and non-'0')
- Greedy decision making based on required trailing zeros

Input: string s (number), int k (power of 10)
Output: minimum number of digits to delete
*/

#include <iostream>
#include <string>

int main() {
  std::string s;
  int k;
  std::cin >> s >> k;
  int zeros(0), pos(0);
  for (int p = s.size() - 1; p >= 0; p--) {
    if (s[p] == '0') {         // Count trailing zeros
      ++zeros;
    } else if (s[p] > '0') {   // Count non-zero digits from right
      ++pos;
    }
    if (zeros >= k) {          // If we have enough trailing zeros
      break;
    }
  }
  if (zeros >= k) {
    std::cout << pos << std::endl;  // Output number of non-zero digits before last k zeros
  } else {
    std::cout << (s.size() - 1) << std::endl;  // All but first digit (special case: 0)
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/