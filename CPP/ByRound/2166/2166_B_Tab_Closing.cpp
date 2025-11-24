// Problem: CF 2166 B - Tab Closing
// https://codeforces.com/contest/2166/problem/B

/*
 * Problem: Tab Closing
 * 
 * Purpose: Given a screen of length `a`, `n` tabs to close, each with a length 
 *          that changes as tabs are closed (len = min(b, a/m)), determine the 
 *          minimum number of mouse moves to close all tabs.
 *          
 *          Tabs are arranged tightly from left to right, with the x's at positions
 *          len, 2*len, ..., m*len. The cursor starts at position 0.
 *          
 *          The key insight is that once we know that all tabs can be covered by 
 *          a single move (i.e., the total space needed is <= a), we only need 1 move.
 *          Otherwise, we have to move at least twice (evenly splitting the tabs).
 * 
 * Algorithms/Techniques: 
 *   - Greedy approach based on interval coverage
 *   - Mathematical analysis to determine minimum moves
 * 
 * Time Complexity: O(T) where T is the number of test cases
 * Space Complexity: O(1)
 */

#include <iostream>

using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    long long a, b, n;
    cin >> a >> b >> n;
    
    // If b equals a, then each tab has length a, so we can close all
    // tabs in one move regardless of n
    if (b == a || b * n <= a)
      cout << 1 << endl;
    else
      // If tabs are large enough that they cannot all fit in one move,
      // we must make at least two moves to cover all tabs
      cout << 2 << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/