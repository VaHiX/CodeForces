// Problem: CF 1716 D - Chip Move
// https://codeforces.com/contest/1716/problem/D

/*
Purpose: This code counts the number of ways to reach each point from 1 to n on a coordinate line,
         where each move's length must be divisible by k, k+1, k+2, etc. for the 1st, 2nd, 3rd... moves.
         The solution uses dynamic programming with a sliding window technique.

Algorithms/Techniques: 
- Dynamic Programming with rolling array optimization
- Modular arithmetic to prevent overflow
- Precomputation of dp states up to a fixed limit (650)

Time Complexity: O(n * sqrt(n)) - The loop runs up to sqrt(n) times, and for each iteration, 
                                 we process up to n elements. In practice, it's more efficient 
                                 due to the early termination condition.

Space Complexity: O(n) - Only two rows of dp array and ans array are used, both of size n.

*/
#include <stdio.h>
#include <iostream>

int n, k, dp[2][200005] = {1}, ans[200005]; // dp is the rolling array, ans stores final results
int main() {
  std::cin >> n >> k;
  for (int i = 1; i <= 650; i++) // Loop up to a fixed threshold to compute dp values
    for (int j = 0; j <= n; j++)
      ans[j] = (ans[j] + (dp[i & 1][j] = j < i + k - 1 // Compute current dp state
                                             ? 0
                                             : (dp[i & 1][j - i - k + 1] + // Add previous dp states
                                                dp[i & 1 ^ 1][j - i - k + 1]) %
                                                   998244353)) %
               998244353; // Apply modulo to avoid overflow
  for (int i = 1; i <= n; i++)
    printf("%d ", ans[i]); // Output the results
}


// https://github.com/VaHiX/CodeForces/