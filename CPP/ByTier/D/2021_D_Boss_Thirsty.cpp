// Problem: CF 2021 D - Boss, Thirsty
// https://codeforces.com/contest/2021/problem/D

/*
 * Problem: D. Boss, Thirsty
 * Purpose: Find maximum total profit by selecting contiguous subarrays of drinks each day,
 *          where each day's selection must overlap with the previous day's selection in at least one element
 *          and differ in at least one element.
 *
 * Algorithm:
 *   - Use dynamic programming with state transitions based on valid intervals
 *   - For each day, for each possible interval [i,j], compute best profit considering constraint
 *     that current interval must have intersection with previous day's interval but differ from it
 *   - Reversal trick helps simulate transitions efficiently
 *
 * Time Complexity: O(n * m) per test case, due to nested loops over days and drinks
 * Space Complexity: O(m) for dp arrays (optimization possible)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void doWork() {
  int n, m;
  cin >> n >> m;
  vector<long long> a(m), dp(m + 1, -1e15), ndp(m + 1); // dp: current state, ndp: next state
  for (int i = 0; i < n; i++) {
    for (auto &x : a)
      cin >> x;
    fill(ndp.begin(), ndp.end(), -1e15); // Reset next DP array
    for (int f = 0; f < 2; f++) {        // Two passes to handle both directions
      long long maxDP = -1e15;           // Max DP value seen so far
      long long maxSum = -1e15;          // Max prefix sum seen so far
      for (int j = 0; j < m; j++) {
        maxDP = max(maxDP, i ? dp[j] + maxSum : 0ll); // Update maxDP using previous state and maxSum
        maxSum = max(maxSum, 0ll);                    // Reset or continue prefix sum
        maxDP += a[j];                                // Add current element to maxDP
        maxSum += a[j];                               // Add current element to prefix sum
        ndp[j + 1] = max(ndp[j + 1], maxDP);          // Store maximum in next DP array
      }
      reverse(a.begin(), a.end());               // Reverse array to simulate other direction
      reverse(dp.begin(), dp.end());             // Reverse dp array for consistency
      reverse(ndp.begin(), ndp.end());           // Reverse ndp array for consistency
    }
    swap(dp, ndp); // Swap DP arrays to move to next iteration
  }
  cout << *max_element(dp.begin(), dp.end()) << endl; // Output maximum profit found
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    doWork();
}


// https://github.com/VaHiX/codeForces/