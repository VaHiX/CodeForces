// Problem: CF 1139 A - Even Substrings
// https://codeforces.com/contest/1139/problem/A

/*
 * Problem: Even Substrings
 * Algorithm: Iterate through each character in the string and check if it's even.
 *            If so, add the index + 1 to the count (number of substrings ending at this position).
 * Time Complexity: O(n), where n is the length of the string.
 * Space Complexity: O(1), only using a few variables for computation.
 */

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;                    // Read the length of the string
  std::string s;
  std::cin >> s;                    // Read the string of digits
  long long cnt(0);                 // Initialize counter for even substrings
  for (long p = 0; p < s.size(); p++) {  // Iterate through each character
    if ((s[p] - '0') % 2 == 0) {    // Check if the digit is even
      cnt += (p + 1);               // Add number of substrings ending at this position
    }
  }
  printf("%lld\n", cnt);            // Print result
  return 0;
}


// https://github.com/VaHiX/codeForces/