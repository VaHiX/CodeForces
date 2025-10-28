// Problem: CF 1105 B - Zuhair and Strings
// https://codeforces.com/contest/1105/problem/B

/*
B. Zuhair and Strings
Purpose: Find the maximum number of non-overlapping substrings of length k,
         where all characters in each substring are the same.
Algorithm: For each character from 'a' to 'z', we traverse the string
           and count how many valid non-overlapping substrings of that
           character we can form. We update the maximum count across all characters.

Time Complexity: O(26 * n) = O(n), where n is the length of the string.
Space Complexity: O(1), only using a constant amount of extra space.

*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;
  long mx(0); // Stores the maximum level found
  for (char x = 'a'; x <= 'z'; x++) { // Try each character from 'a' to 'z'
    long let(0), cnt(0); // let: length of current consecutive substring, cnt: count of valid substrings
    for (long p = 0; p < n; p++) {
      if (s[p] != x) { // If current character is not the target character
        let = 0;       // Reset the count
      } else {
        ++let;         // Increment the consecutive count
        if (let >= k) { // If we have at least k consecutive characters
          ++cnt;        // Increment the valid substring count
          let = 0;      // Reset to start looking for next substring
        }
      }
    }
    mx = (mx > cnt) ? mx : cnt; // Update maximum level
  }
  printf("%ld\n", mx);
  return 0;
}


// https://github.com/VaHiX/codeForces/