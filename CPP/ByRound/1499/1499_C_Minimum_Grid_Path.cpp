// Problem: CF 1499 C - Minimum Grid Path
// https://codeforces.com/contest/1499/problem/C

/*
 * Problem: C. Minimum Grid Path
 * 
 * Purpose: Find the minimum cost path from (0,0) to (n,n) on a grid, where each step
 *          is either horizontal or vertical, and the path alternates directions.
 *          Each segment has a cost c_i, and the total cost is the sum of (length * cost).
 * 
 * Algorithm: 
 *   - For each possible number of segments (from 1 to n), calculate the minimal cost
 *     by considering the optimal way to assign the segments to either horizontal or
 *     vertical directions.
 *   - Keep track of the minimum cost among all valid segment counts.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 * 
 * Techniques:
 *   - Greedy optimization
 *   - Prefix sum tracking
 *   - Alternating direction cost minimization
 */

#include <algorithm>
#include <iostream>

#define ll long long
using namespace std;

int main() {
  ll T, n, i, x;
  cin >> T;
  while (T--) {
    cin >> n;
    ll ml = 1e9, mr = 1e9;  // ml: minimum cost for odd-indexed segments (horizontal), mr: for even-indexed (vertical)
    ll ans = 1e16, sum = 0, cnt1 = 0, cnt2 = 0;  // cnt1: count of odd segments, cnt2: count of even segments
    
    for (i = 1; i <= n; i++) {
      cin >> x;
      sum += x;  // prefix sum of costs
      
      // Update minimum cost for the current direction
      if (i % 2)
        ml = min(ml, x), cnt1++;  // odd positions are for horizontal movement
      else
        mr = min(mr, x), cnt2++;  // even positions are for vertical movement
      
      // Calculate the minimal cost for current number of segments
      // sum: sum of costs for the first i segments
      // ml * (n - cnt1): cost of remaining horizontal segments if we use the minimum cost for them
      // mr * (n - cnt2): cost of remaining vertical segments if we use the minimum cost for them
      ans = min(ans, sum + ml * (n - cnt1) + mr * (n - cnt2));
    }
    
    cout << ans << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/