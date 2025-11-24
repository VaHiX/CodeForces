// Problem: CF 1796 A - Typical Interview Problem
// https://codeforces.com/contest/1796/problem/A

/*
 * Problem: Determine if a given string s is a substring of the infinite FB-string.
 * 
 * The FB-string is constructed by iterating through positive integers:
 *   - If divisible by 3, append 'F'
 *   - If divisible by 5 (but not 3), append 'B'
 *   - If divisible by both 3 and 5 (i.e. 15), append 'F' then 'B'
 *
 * Key Observations:
 *   - The pattern of F and B repeats every 15 numbers (LCM of 3 and 5)
 *   - So we can precompute the pattern for 15 characters: "FBFFBFFBFB"
 *   - For each test case, check if any rotation of this pattern contains s as a substring.
 *
 * Algorithm:
 *   - Precompute base pattern of size 10 (since max length of s is 10)
 *   - For each test case:
 *     - Try all rotations of the pattern
 *     - Check if s matches a contiguous segment of any rotation
 *
 * Time Complexity: O(t * n * m) where t is number of test cases, n is pattern size (10), m is length of s.
 * Space Complexity: O(1) excluding input/output storage.
 */

#include <iostream>
#include <string>

int main() {
  const std::string pattern = "FBFFBFFB"; // Base repeating pattern of length 10
  const long len = pattern.size();       // Length of the repeating pattern
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    bool res(false);
    for (int fs = 0; fs < len; fs++) {       // Try each possible starting position in the pattern
      bool match(true);
      for (long p = 0; match && p < s.size(); p++) {  // Compare substring of s with rotated pattern
        if (s[p] != pattern[(p + fs) % len]) {  // Check character at offset
          match = false;
        }
      }
      if (match) {         // If match found, set result and break
        res = true;
        break;
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl;  // Output result
  }
}


// https://github.com/VaHiX/codeForces/