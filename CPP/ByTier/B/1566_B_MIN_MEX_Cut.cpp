// Problem: CF 1566 B - MIN-MEX Cut
// https://codeforces.com/contest/1566/problem/B

/*
B. MIN-MEX Cut
Algorithm: Greedy approach to minimize MEX of substrings
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables

For each test case, we try to cut the string such that the sum of MEX values of all substrings is minimized.
The key insight is:
- If we have both '0' and '1', the MEX is 2.
- If we have only '0', the MEX is 1.
- If we have only '1', the MEX is 0.
- If we have no '0' or no '1' (but not both missing), we can minimize by splitting appropriately.

However, this code uses a slightly different logic:
It tracks whether we've seen a '0' and then a '1' after that to see how many distinct characters are in the string.
If we find '0' and later find '1', it's a transition indicating we could have avoided having '2' as MEX.
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    bool nz(0), na(0); // nz tracks if we've seen '0', na tracks if we've seen '1' after seeing '0'
    int ans(0);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '0') {
        ans = 1; // If there is at least one '0', MEX of substring with only '0' will be 1
        if (nz && na) {
          ans = 2; // If we have both '0' and '1' seen, MEX is 2
          break;
        }
        nz = true; // Mark that we've seen a '0'
      } else if (s[p] == '1' && nz) {
        na = true; // Mark that we've seen '1' after seeing a '0'
      }
    }
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/