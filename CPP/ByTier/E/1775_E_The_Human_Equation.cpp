// Problem: CF 1775 E - The Human Equation
// https://codeforces.com/contest/1775/problem/E

/*
 * Problem: E. The Human Equation
 * 
 * Approach:
 * This problem can be solved using a prefix sum technique.
 * The key insight is that each operation affects the sequence by adding/subtracting 1 
 * to elements at odd/even positions of a chosen subsequence. 
 * We can think of each operation as a "delta" that is applied to a range of the sequence.
 * 
 * Let's define a difference array where each operation modifies the prefix sum.
 * By tracking the running sum (prefix sum), we can determine how much "net" 
 * change is needed at any point.
 * 
 * The minimum number of operations needed is the difference between the maximum and minimum 
 * prefix sums.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define int long long
const int N = 2e5 + 5;
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int TC;
  cin >> TC;
  while (TC--) {
    int n, k;
    cin >> n;
    int mx = 0, mn = 0, cur = 0;
    for (int i = 0; i < n; i++) {
      cin >> k;
      cur += k;          // Update prefix sum
      mx = max(mx, cur); // Track maximum prefix sum
      mn = min(mn, cur); // Track minimum prefix sum
    }
    cout << mx - mn << "\n"; // The difference gives the minimum operations needed
  }
}


// https://github.com/VaHiX/CodeForces/