// Problem: CF 1303 A - Erasing Zeroes
// https://codeforces.com/contest/1303/problem/A

/*
Problem: A. Erasing Zeroes
Purpose: Given a binary string, find the minimum number of '0's to erase so that all '1's form a contiguous subsegment.

Algorithms/Techniques: Two-pointer approach, single pass through string

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables for tracking

The algorithm works by:
1. Finding the first '1' and the last '1'
2. Counting all '0's between these two positions
3. These middle '0's are the ones that must be erased to make the '1's contiguous

Example:
For string "010011":
- First '1' at index 1, last '1' at index 5
- Between them (indices 2 and 4), there are 2 '0's
- Hence we need to erase 2 '0's
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long last(-1), cnt(0);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '0') {
        continue; // Skip over zeros, we only care about ones
      }
      if (last >= 0) { // If this is not the first one we've seen
        cnt += (p - last - 1); // Count zeros between current and previous one
      }
      last = p; // Update position of last seen '1'
    }
    std::cout << cnt << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/