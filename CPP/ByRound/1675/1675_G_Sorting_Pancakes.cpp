// Problem: CF 1675 G - Sorting Pancakes
// https://codeforces.com/contest/1675/problem/G
 
/*
Algorithm: Dynamic Programming
Approach:
- The idea is to use dynamic programming where dp[i][j] represents the minimum moves required to make the first i dishes non-increasing, with total j pancakes in these dishes.
- We precompute prefix sums of pancakes to efficiently determine how many pancakes should be in the first i dishes.
- For each dish i and total pancakes j, we consider placing k pancakes in dish i (where k ranges from 0 to j), and compute the cost of moving the remaining pancakes from previous dishes.
- The cost of moving pancakes from dish i to neighboring dishes is the absolute difference between the current allocation and the prefix sum of pancakes up to dish i.
 
Time Complexity: O(n * m^2)
Space Complexity: O(n * m)
 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
 
using namespace std;
int i, j, k, n, m, a[255], dp[255][255];
int main() {
  scanf("%d %d", &n, &m);
  memset(dp, 63, sizeof(dp)); // Initialize dp with a large value (infinity)
  dp[0][0] = 0; // Base case: 0 pancakes in 0 dishes requires 0 moves
  for (i = 1; i <= n; i++)
    cin >> a[i], a[i] += a[i - 1]; // Compute prefix sums of pancakes
  for (k = m; k >= 0; k--) // Iterate through all possible numbers of pancakes
    for (i = 1; i <= n; i++) // For each dish
      for (j = k; j <= m; j++) // For each possible total number of pancakes
        dp[i][j] = min(dp[i][j], dp[i - 1][j - k] + abs(j - a[i])); // Update dp with minimum moves needed
  printf("%d\n", dp[n][m]); // Output result for all dishes and all pancakes
  return 0;
}
 
 
// https://github.com/VaHiX/CodeForces/