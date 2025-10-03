// Problem: CF 2135 A - Against the Difference
// https://codeforces.com/contest/2135/problem/A

/*
Algorithm: Dynamic Programming with HashMap-like Structure
Time Complexity: O(n)
Space Complexity: O(n)

This code solves the problem of finding the longest "neat" subsequence in an array,
where a neat subsequence is one that can be split into blocks, where each block
consists of k elements all equal to k.

The approach uses dynamic programming with a vector-based storage for indices of elements.
For each position, we check if the current element forms a complete block (i.e., 
its count equals its value). If so, we extend the previous valid subsequence and update dp[i].
Otherwise, we carry forward the best result from the previous position.

Key data structures used:
- w[a[i]]: stores indices where value 'a[i]' appears.
- dp[i]: maximum length of neat subsequence ending at index i.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int t, n, a[200005], dp[200005];
vector<int> w[200005];
int main() {
  cin >> t;
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]), w[a[i]].emplace_back(i); // Store index of each element
      if ((int)w[a[i]].size() >= a[i]) // If we have enough occurrences to form a block
        dp[i] = max(dp[i - 1], dp[w[a[i]][w[a[i]].size() - a[i]] - 1] + a[i]); // Update with block length
      else
        dp[i] = dp[i - 1]; // No valid block formed, carry previous result
    }
    printf("%d\n", dp[n]);
    for (int i = 1; i <= n; i++)
      w[i].clear(); // Clear vectors for next test case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/