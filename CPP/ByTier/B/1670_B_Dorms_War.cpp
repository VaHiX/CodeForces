// Problem: CF 1670 B - Dorms War
// https://codeforces.com/contest/1670/problem/B

/*
B. Dorms War
Algorithms/Techniques: Two-pointer technique, simulation

Time Complexity: O(n) per test case, where n is the length of the string s.
Space Complexity: O(1) since we use a fixed-size vector of 26 elements.

The problem simulates a process where certain positions in a string are removed 
based on the presence of special characters. The goal is to determine how many 
times this operation can be performed before no valid deletions remain.
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
    std::string s;
    std::cin >> s;
    long k;
    std::cin >> k;
    std::vector<bool> v(26, 0); // Boolean vector to mark special characters
    for (long p = 0; p < k; p++) {
      char x;
      std::cin >> x;
      v[x - 'a'] = 1; // Mark the character as special
    }
    long mxlen(0), last(0);
    for (long p = 1; p < s.size(); p++) {
      if (v[s[p] - 'a']) { // If current character is special
        long len = p - last; // Calculate length of substring between last valid position and current
        mxlen = (mxlen > len ? mxlen : len); // Update maximum length
        last = p; // Update the last valid position
      }
    }
    std::cout << mxlen << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/