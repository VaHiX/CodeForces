// Problem: CF 1697 C - awoo's Favorite Problem
// https://codeforces.com/contest/1697/problem/C

/*
C. awoo's Favorite Problem
Purpose: Determine if string s can be transformed into string t using allowed operations:
         - Replace "ab" with "ba"
         - Replace "bc" with "cb"

Algorithms/Techniques:
- Process strings character by character to extract non-'b' characters and track positions of 'a' and 'c'
- Compare simplified strings (without 'b') and ensure positional constraints for 'a' and 'c' are satisfied

Time Complexity: O(n) per test case, where n is the length of the strings
Space Complexity: O(n) for storing vectors and auxiliary strings

Operations:
- Each string is processed once to build filtered versions and position lists
- Constraints check on positions of 'a' and 'c' ensures valid transformation
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s, t;
    std::cin >> s >> t;
    std::string ss(""), tt(""); // Build simplified strings without 'b'
    std::vector<long> sav, scv, tav, tcv; // Store positions of 'a' and 'c' in s and t
    for (long p = 0; p < n; p++) {
      if (s[p] != 'b') { // Only add non-'b' characters to simplified string
        ss += s[p];
      }
      if (t[p] != 'b') { // Only add non-'b' characters to simplified string
        tt += t[p];
      }
      if (s[p] == 'a') { // Record positions of 'a'
        sav.push_back(p);
      } else if (s[p] == 'c') { // Record positions of 'c'
        scv.push_back(p);
      }
      if (t[p] == 'a') { // Record positions of 'a' in t
        tav.push_back(p);
      } else if (t[p] == 'c') { // Record positions of 'c' in t
        tcv.push_back(p);
      }
    }
    bool ans(ss == tt && sav.size() == tav.size() && scv.size() == tcv.size()); // Check if simplified strings and counts match
    
    for (long p = 0; ans && p < sav.size(); p++) { // Ensure 'a' in s appears at or before corresponding 'a' in t
      if (sav[p] > tav[p]) {
        ans = false;
      }
    }
    for (long p = 0; ans && p < scv.size(); p++) { // Ensure 'c' in s appears at or after corresponding 'c' in t
      if (scv[p] < tcv[p]) {
        ans = false;
      }
    }
    std::cout << (ans ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/