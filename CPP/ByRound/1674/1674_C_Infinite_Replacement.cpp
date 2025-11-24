// Problem: CF 1674 C - Infinite Replacement
// https://codeforces.com/contest/1674/problem/C

/*
C. Infinite Replacement
Purpose: Determine the number of distinct strings that can be obtained by repeatedly replacing 'a' in string s with string t.
Algorithm: 
    - If t is just "a", only one string is possible (no change).
    - If t contains 'a', infinitely many strings are possible because we can keep replacing.
    - Otherwise, the number of distinct strings is 2^(length of s), since each 'a' can either be replaced or not.

Time Complexity: O(q * |s| + |t|) where q is number of test cases, and |s|, |t| are lengths of strings.
Space Complexity: O(|s| + |t|) for storing input strings.
*/
#include <iostream>
#include <string>
int main() {
  long q;
  std::cin >> q;
  while (q--) {
    std::string s, t;
    std::cin >> s >> t;
    long long res(1); // Initialize result to 1
    if (t.size() == 1 && t[0] == 'a') { // If t is just "a"
      res = 1; // Only one string possible
    } else if (t.find("a") != std::string::npos) { // If t contains 'a'
      res = -1; // Infinitely many strings possible
    } else { // If t does not contain 'a'
      res = (1LL << s.size()); // 2^(length of s) distinct strings
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/