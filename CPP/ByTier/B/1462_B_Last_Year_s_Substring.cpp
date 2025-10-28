// Problem: CF 1462 B - Last Year's Substring
// https://codeforces.com/contest/1462/problem/B

/*
Problem: B. Last Year's Substring
Task: Determine if a string can be transformed into "2020" by removing at most one substring.

Algorithm:
- Check if the string already is "2020".
- Otherwise, check if we can form "2020" by matching characters from the beginning and end of the string.
  - Match first 4 characters from the start to "2020"
  - Match last 4 characters from the end to "2020"
  - If combined match count is at least 4, then it's possible.

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using fixed extra space

Techniques:
- Two-pointer approach from both ends
- Linear scan to match pattern "2020"
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::string g("2020"); // Target pattern
    long cnt(0), idx(0);
    
    // Check matching from the start of string to "2020"
    for (long p = 0; p < 4; p++) {
      if (s[p] == g[idx]) {
        ++idx;
        ++cnt;
      } else {
        break;
      }
    }
    
    idx = 3; // Reset index to end of "2020"
    
    // Check matching from the end of string to "2020"
    for (long p = s.size() - 1; p >= s.size() - 4; p--) {
      if (s[p] == g[idx]) {
        ++cnt;
        --idx;
      } else {
        break;
      }
    }
    
    // If we found at least 4 matching characters, it's possible
    std::cout << ((cnt >= 4) ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/