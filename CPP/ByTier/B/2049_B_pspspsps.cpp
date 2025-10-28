// Problem: CF 2049 B - pspspsps
// https://codeforces.com/contest/2049/problem/B

/*
Problem: B. pspspsps
Purpose: Determine if a permutation of length n exists such that:
  - If s[i] == 'p', then [p1, p2, ..., pi] forms a permutation of length i
  - If s[i] == 's', then [pi, pi+1, ..., pn] forms a permutation of length n-i+1
  - If s[i] == '.', no restriction

Algorithms/Techniques:
- Greedy approach with forward/backward checks
- Time complexity: O(n) per test case
- Space complexity: O(1)

Key logic:
- First set first character to '.' if it's 's', last to '.' if it's 'p'
- Then traverse the string to check if we have at least one 's' and one 'p'
  - If both present, then a valid permutation might exist (NO otherwise)
  - In this particular formulation, checking presence of s and p is sufficient as
    we are verifying that enough elements exist to form valid prefixes/suffixes

Note: This is a simplified version of the problem - it only checks for basic
feasibility in terms of number of 's' and 'p', not full permutation validation.
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
    // If first character is 's', set it to '.' as per problem logic
    if (s[0] == 's') {
      s[0] = '.';
    }
    // If last character is 'p', set it to '.' as per problem logic
    if (s.back() == 'p') {
      s.back() = '.';
    }
    bool fs(0), fp(0);
    // Traverse the string to check for presence of both 's' and 'p'
    for (long p = 0; p < s.size() && !(fs && fp); p++) {
      if (s[p] == 's') {
        fs = true;
      } else if (s[p] == 'p') {
        fp = true;
      }
    }
    // If both 's' and 'p' are present, the answer is "NO", otherwise "YES"
    std::cout << (fs && fp ? "NO" : "YES") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/