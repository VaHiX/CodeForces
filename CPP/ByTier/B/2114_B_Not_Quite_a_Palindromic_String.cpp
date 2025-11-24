// Problem: CF 2114 B - Not Quite a Palindromic String
// https://codeforces.com/contest/2114/problem/B

/*
B. Not Quite a Palindromic String

Algorithms/Techniques: Greedy, Math, String Manipulation

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1), as we use only a constant amount of extra space (excluding input storage).

The problem asks whether we can rearrange characters in a binary string to have exactly k good pairs.
A good pair (i, n-i+1) exists when s[i] == s[n-i+1]. For a valid arrangement:
- Each good pair requires two identical characters (both 0s or both 1s).
- If we need k good pairs, then we require 2*k characters of same type in symmetric positions.
- This leaves (n/2 - k) symmetric pairs to be filled with remaining characters.

We count number of 0s and 1s in the string. Then, for k good pairs:
- We must have at least (n/2 - k) 0s and (n/2 - k) 1s to form these pairs.
- The remaining 0s and 1s should satisfy parity conditions so that we can create valid symmetric pairs.

*/
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    long a(0), z(0);
    for (long p = 0; p < s.size(); p++) {
      z += (s[p] == '0');  // Count number of 0s
      a += (s[p] == '1');  // Count number of 1s
    }
    const long d = n / 2 - k;  // Number of symmetric pairs needed to be left unmatched
    bool possible((z >= d) && (a >= d) && ((a - d) % 2 == 0) && ((z - d) % 2 == 0));
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/