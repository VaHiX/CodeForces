// Problem: CF 1732 B - Ugu
// https://codeforces.com/contest/1732/problem/B

/*
Problem: Make a binary string non-decreasing with minimum operations.
Each operation flips all bits from index i to end.
Algorithm: Count number of transitions from 1 to 0 or 0 to 1, but only count transitions that require flipping.
Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(1) - only using a few variables.
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
    long ans(-1); // Initialize to -1 to account for first element
    for (long p = 0; p < s.size(); p++) {
      // Count transition from previous character to current one
      // If it's the first character and it's '1', or if there's a change in characters
      ans += ((!p && s[p] == '1') || (p && s[p] != s[p - 1]));
    }
    std::cout << (ans > 0 ? ans : 0) << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/