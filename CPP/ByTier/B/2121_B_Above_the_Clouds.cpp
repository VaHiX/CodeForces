// Problem: CF 2121 B - Above the Clouds
// https://codeforces.com/contest/2121/problem/B

/*
 * Problem: B. Above the Clouds
 * 
 * Purpose: Determine whether a given string can be split into three non-empty parts a, b, c such that b is a substring of a + c.
 * 
 * Algorithm:
 * - For each test case, iterate through the string and check if there exists any character in the middle of the string
 *   (between first and last positions) that has already appeared earlier. If so, a valid split is possible.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1), since we use a fixed-size vector of 26 elements (for 26 lowercase letters).
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int B = 26; // Size of alphabet (lowercase a-z)
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::vector<bool> v(B, 0); // Vector to track characters seen so far
    v[s[0] - 'a'] = 1;         // Mark first character as seen
    v[s.back() - 'a'] = 1;     // Mark last character as seen
    bool possible(false);      // Flag to indicate if a valid split is found
    
    // Iterate through the middle characters of the string (from index 1 to n-2)
    for (long p = 1; !possible && p < s.size() - 1; p++) {
      int x = s[p] - 'a';      // Convert current character to index (0-25)
      if (v[x]) {              // If this character was seen before, a valid split exists
        possible = true;
      }
      v[x] = 1;                // Mark the current character as seen
    }
    
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/