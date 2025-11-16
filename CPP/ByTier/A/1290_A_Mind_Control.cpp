// Problem: CF 1290 A - Mind Control
// https://codeforces.com/contest/1290/problem/A

/*
 * Problem: Mind Control
 * 
 * Purpose:
 *   This code solves a game theory problem where players take turns picking elements
 *   from either end of an array, with the goal being to determine the minimum value
 *   that the player in position 'm' can guarantee to obtain under optimal control
 *   of up to k other players.
 * 
 * Algorithm:
 *   1. For each valid starting position where we begin our turn (from 0 to k),
 *      simulate all possible subarrays of length (m - k) that could be left for us.
 *   2. For each such subarray, compute the maximum of the two ends of the range
 *      and track the minimum among them — representing worst-case gain for our turn.
 *   3. Optimize by trying all possible placements of our controlled players,
 *      taking the best such value across all configurations.
 *
 * Time Complexity: O(k * (m - k)) per test case = O(n^2) in worst case.
 * Space Complexity: O(n) for the array storage and auxiliary space.
 */

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int t, n, m, k, ans, s;
  cin >> t;
  vector<int> a;
  
  while (t--) {
    cin >> n >> m >> k;
    ans = INT_MIN; // Initialize to minimum possible value
    a.resize(n); // Resize array to hold n elements
    
    for (int i = 0; i < n; i++)
      cin >> a[i]; // Read input elements
    
    k = min(k, m - 1); // Limit k to number of valid positions before m
    
    for (int i = 0; i <= k; i++) { // Iterate over possible start positions
      s = INT_MAX; // Initialize to maximum value for minimizing worst case
      
      for (int j = 0; j < (m - k); j++) {
        // Compute max between the two ends of subarray (i+j, i+j+n-m)
        // This represents potential elements available at our turn
        s = min(s, max(a[i + j], a[i + j + n - m]));
      }
      
      ans = max(s, ans); // Track the best guaranteed minimum value
    }
    
    cout << ans << endl; // Output result for current test case
  }
  
  return 0;
}


// https://github.com/VaHiX/codeForces/