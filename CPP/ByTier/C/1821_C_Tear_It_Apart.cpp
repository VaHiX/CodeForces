// Problem: CF 1821 C - Tear It Apart
// https://codeforces.com/contest/1821/problem/C

/*
C. Tear It Apart
Purpose: Given a string of lowercase Latin letters, determine the minimum number of operations 
         to make all characters in the string the same. Each operation allows selecting non-adjacent 
         positions and removing those characters.

Algorithm:
- For each character from 'a' to 'z', compute the maximum length of consecutive non-matching 
  segments when replacing all occurrences of that character with a placeholder.
- Find the minimal such maximum among all 26 characters.
- The result is the number of bits required to represent that minimum value in binary (i.e., 
  floor(log2(minimum)) + 1).

Time Complexity: O(26 * n) = O(n), where n is the length of the string
Space Complexity: O(1)

Techniques:
- Greedy approach with character frequency analysis
- Bit manipulation to compute log base 2
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long mnmxlen(s.size()); // Initialize with maximum possible value
    
    // Try each character from 'a' to 'z'
    for (char x = 'a'; x <= 'z'; x++) {
      long len(0), mxlen(0); // len: current segment length, mxlen: max segment length
      
      // Traverse the string and compute maximum non-matching segment lengths
      for (long p = 0; p < s.size(); p++) {
        if (s[p] == x) {
          len = 0; // Reset segment when encountering target character
        } else {
          ++len; // Extend current segment
        }
        mxlen = (mxlen > len ? mxlen : len); // Update maximum segment length
      }
      
      mnmxlen = (mnmxlen < mxlen ? mnmxlen : mxlen); // Keep minimum of all max segments
    }
    
    long ans(0); // Result will be number of bits needed to represent mnmxlen
    
    // Count number of bits in mnmxlen (equivalent to floor(log2(mnmxlen)) + 1)
    while (mnmxlen) {
      ++ans;
      mnmxlen /= 2;
    }
    
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/