// Problem: CF 2064 A - Brogramming Contest
// https://codeforces.com/contest/2064/problem/A

/*
 * Problem: Brogramming Contest
 * Purpose: Given a binary string s, determine the minimum number of moves 
 *          to make s contain only '0' and t contain only '1', using suffix moves.
 * Algorithm: Greedy approach based on transitions from '0' to '1'.
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1) excluding input/output storage.
 */

#include <stddef.h>
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
    
    // cnt initialized based on first and last character of string
    long cnt(2 * (s[0] == '1') - (s.back() == '1'));
    
    // Traverse the string to count transitions from '0' to '1'
    for (size_t p = 1; p < n; p++) {
      cnt += 2 * (s[p - 1] == '0' && s[p] == '1'); // increment by 2 for each such transition
    }
    
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/