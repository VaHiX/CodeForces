// Problem: CF 1354 B - Ternary String
// https://codeforces.com/contest/1354/problem/B

/*
Problem: B. Ternary String
Purpose: Find the shortest contiguous substring that contains all three characters (1, 2, 3) at least once.

Algorithm:
- Use a sliding window approach with two pointers.
- Maintain an array `last` to track the most recent index of each character (1, 2, 3).
- For each position in the string:
  - Update the last occurrence of the current character.
  - Compute the minimum of the last occurrences among all three characters.
  - If this minimum is valid (>= 0), then we have a valid substring ending at current position.
  - Update the minimum length found so far.

Time Complexity: O(n) where n is the length of the string. Each character is processed once.
Space Complexity: O(1) as we use only a fixed-size array of size 4 and a few variables.

*/

#include <stdio.h>
#include <iostream>
#include <string>

long mn(long x, long y) { return (x < y) ? x : y; }
int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long last[4] = {-1, -1, -1, -1}; // Track last index for characters '1','2','3' (indices 1,2,3)
    long len(s.size() + 1);          // Initialize with a value larger than any possible substring
    bool found(false);
    for (long p = 0; p < s.size(); p++) {
      last[s[p] - '0'] = p;          // Update last seen index of current character
      long prev = mn(mn(last[1], last[2]), last[3]); // Get the earliest index among all 3 characters
      if (prev < 0) {
        continue;                    // Not all characters are seen yet
      }
      found = true;
      long tst = p - prev + 1;       // Length of current valid substring
      len = mn(len, tst);            // Keep the minimum length
    }
    printf("%ld\n", found * len);    // Print 0 if not found, else the minimal length
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/