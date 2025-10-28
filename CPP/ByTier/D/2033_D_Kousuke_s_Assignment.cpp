// Problem: CF 2033 D - Kousuke's Assignment
// https://codeforces.com/contest/2033/problem/D

/*
D. Kousuke's Assignment
time limit per test2 seconds
memory limit per test256 megabytes

Task:
Given an array of integers, find the maximum number of non-overlapping subarrays (segments) such that the sum of elements in each segment equals zero.

Algorithms/Techniques:
- Prefix Sum + Map for tracking previous prefix sums.
- Dynamic Programming to track the maximum number of valid segments ending at each position.
- Greedy approach combined with DP: whenever a prefix sum repeats, we can form a new segment from the last occurrence to current index.

Time Complexity: O(n) per test case (linear time due to single pass with map lookups)
Space Complexity: O(n) for the map and dp array storage

*/

#include <stdio.h>
#include <algorithm>
#include <map>

std::map<long long, int> mp; // Map to store prefix sum and its earliest index
int dp[100005];              // dp[i] stores max number of non-overlapping segments up to index i
int T, n;
long long s;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    mp.clear();         // Clear map for new test case
    mp[0] = 0;          // Initialize prefix sum 0 at index 0
    s = 0;              // Running prefix sum
    for (int i = 1, x; i <= n; ++i) {
      scanf("%d", &x);
      s += x;           // Add current element to prefix sum
      
      dp[i] = dp[i - 1]; // Default: carry forward the previous count
      
      if (mp.count(s))  // If this prefix sum has been seen before
        dp[i] = std::max(dp[i], dp[mp[s]] + 1); // Update with better count using earlier segment
      
      mp[s] = i;        // Store/update current index for this prefix sum
    }
    printf("%d\n", dp[n]); // Output the result for current test case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/