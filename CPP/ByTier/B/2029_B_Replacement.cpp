// Problem: CF 2029 B - Replacement
// https://codeforces.com/contest/2029/problem/B

/*
B. Replacement
Algorithm: Greedy simulation with character count tracking
Time Complexity: O(n) per test case, where n is the length of string s
Space Complexity: O(1) additional space (not counting input storage)

The problem involves simulating a game where we reduce a binary string s of length n to a single character
by performing n-1 operations. In each operation, we must choose an adjacent pair of different characters,
and replace the pair with a character from r. The goal is to determine if it's possible to perform all operations.

Approach:
- Count the number of 0s and 1s in s.
- For each step in simulation, check if we can continue:
  - We need at least one 0 and one 1 to make a valid operation.
  - Based on r[i], we decrease the count of either 0 or 1.
- If at any point we run out of valid pairs (e.g., all 0s or all 1s), return false.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::string r;
    std::cin >> r;
    long a(0), z(0); // Count of '1's and '0's in s
    for (long p = 0; p < s.size(); p++) {
      z += (s[p] == '0'); // Count number of zeros
      a += (s[p] == '1'); // Count number of ones
    }
    bool res(true); // Whether we can complete all operations
    for (long p = 0; p < n - 1 && res; p++) {
      if (!z || !a) { // If there's no valid adjacent pair left
        res = false;
      }
      if (r[p] == '0') { // If replacement character is '0', we decrease count of '1's
        --a;
      } else { // Else, decrease count of '0's
        --z;
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/