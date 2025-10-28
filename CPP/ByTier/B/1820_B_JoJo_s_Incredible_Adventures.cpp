// Problem: CF 1820 B - JoJo's Incredible Adventures
// https://codeforces.com/contest/1820/problem/B

/*
 * Problem: B. JoJo's Incredible Adventures
 *
 * Purpose:
 * Given a binary string s of length n, we construct an n×n table where each row is
 * a cyclic right shift of the string s by k positions (k from 0 to n-1). Then we find
 * the maximum area of a rectangle consisting only of '1's in this table.
 *
 * Algorithms/Techniques:
 * - Preprocessing: For each row, compute the longest consecutive sequence of '1's
 *   that includes the current position, using dynamic programming and cyclic shifts.
 * - Optimization: The key idea is to find for each column, how many contiguous rows
 *   starting from some row have a '1' in that column. This leads to a maximum rectangle
 *   problem per column.
 * - The approach uses an efficient scan through the repeated string (2*n size) to 
 *   determine the maximum consecutive sequence of 1s and then uses it to compute the area.
 *
 * Time Complexity: O(n) for each test case, as we traverse the string twice (2n) at most.
 * Space Complexity: O(1) additional space (excluding input/output).
 */

#include <iostream>
#include <string>

typedef long long ll;
int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    ll len = s.size();
    ll mx(0), cnt(0);
    bool z(false);
    for (ll p = 0; p < 2 * len; p++) {
      // If we encounter '1', increment the count
      if (s[p % len] == '1') {
        ++cnt;
      } else {
        // If we encounter '0', update the flag and reset counter
        z = true;
        cnt = 0;
      }
      // Keep track of maximum consecutive 1s found so far
      mx = (mx > cnt) ? mx : cnt;
    }
    // If there are no zeros, then entire string is 1s, area is len * len
    // Otherwise, if there's at least one zero, compute the optimal rectangle area.
    ll res = z ? ((mx + 1) / 2) * ((mx + 2) / 2) : (len * len);
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/