// Problem: CF 1400 C - Binary String Reconstruction
// https://codeforces.com/contest/1400/problem/C

/*
C. Binary String Reconstruction
Algorithm: Greedy reconstruction with forward/backward propagation
Time Complexity: O(n) where n is the length of string s
Space Complexity: O(n) for storing the result string w

The problem involves reconstructing a binary string w from a given string s and integer x,
where s is generated from w using specific rules involving shifts of x positions.

Approach:
1. Initialize result string w with all '1's.
2. First pass (forward): For each '0' in s, mark the corresponding positions in w as '0'
   if they are within bounds based on x distance.
3. Second pass (backward): For each '1' in s, verify that at least one of the two corresponding
   positions in w is '1'. If not, return "-1".
4. Output the reconstructed string w or "-1" if impossible.

Techniques Used:
- Greedy reconstruction with careful boundary handling
- Forward and backward propagation for constraints checking
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long x;
    std::cin >> x;
    std::string w(s.size(), '1'); // Initialize result string with all '1's
    
    // First pass: Mark positions that must be '0' based on '0's in s
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '1') {
        continue; // Skip if s[p] is already '1'
      }
      
      // If p - x >= 0, set w[p - x] to '0' to ensure s[p] becomes '0'
      if (p - x >= 0) {
        w[p - x] = '0';
      }
      
      // If p + x < size, set w[p + x] to '0' to ensure s[p] becomes '0'
      if (p + x < w.size()) {
        w[p + x] = '0';
      }
    }
    
    // Second pass: Validate that each '1' in s can be satisfied by corresponding positions in w
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '0') {
        continue; // Skip if s[p] is already '0'
      }
      
      // Check if either of the two conditions for making s[p] = '1' are met
      if (p - x >= 0 && w[p - x] == '1') {
        continue;
      }
      if (p + x < w.size() && w[p + x] == '1') {
        continue;
      }
      
      // If neither condition is satisfied, reconstruction is impossible
      w = "-1";
      break;
    }
    
    std::cout << w << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/