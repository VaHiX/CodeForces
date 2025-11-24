// Problem: CF 1536 B - Prinzessin der Verurteilung
// https://codeforces.com/contest/1536/problem/B

/*
B. Prinzessin der Verurteilung
Time Complexity: O(26^3 * n) = O(n) where n is the length of the string.
Space Complexity: O(1) - only using a constant amount of extra space for variables.

The algorithm finds the MEX (minimum excludant) of a given string,
which is the shortest string that does not appear as a contiguous substring
in the input. If multiple such strings exist, it outputs the lexicographically
smallest one.

Approach:
1. First, check for all single-character substrings ('a' to 'z').
2. Then, check all two-character combinations.
3. Finally, check all three-character combinations.
4. Return the first missing substring in lexicographical order.

This approach works because any string of length > 3 must contain a shorter
substring that is also missing, unless all shorter substrings are present.
For large enough inputs, this can be optimized but for small constraints,
brute force on up to 3 characters is sufficient and acceptable.
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
    bool done(false);
    // First check all single characters from 'a' to 'z'
    for (char p = 'a'; p <= 'z'; p++) {
      std::string t = std::string(1, p);     // Create a string of one character
      if (s.find(t) == std::string::npos) { // If this substring is not found in s
        std::cout << t << std::endl;
        done = true;
        break;
      }
    }
    // Then check all two-character combinations
    for (char p = 'a'; p <= 'z'; p++) {
      if (done) {
        break;
      }
      for (char q = 'a'; q <= 'z'; q++) {
        std::string t = std::string(1, p);   // Create a two-character string
        t.push_back(q);
        if (s.find(t) == std::string::npos) { // If this substring is not found in s
          std::cout << t << std::endl;
          done = true;
          break;
        }
      }
    }
    // Finally check all three-character combinations
    for (char p = 'a'; p <= 'z'; p++) {
      if (done) {
        break;
      }
      for (char q = 'a'; q <= 'z'; q++) {
        if (done) {
          break;
        }
        for (char r = 'a'; r <= 'z'; r++) {
          std::string t = std::string(1, p);   // Create a three-character string
          t.push_back(q);
          t.push_back(r);
          if (s.find(t) == std::string::npos) { // If this substring is not found in s
            std::cout << t << std::endl;
            done = true;
            break;
          }
        }
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/