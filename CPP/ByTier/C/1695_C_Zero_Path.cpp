// Problem: CF 1695 C - Zero Path
// https://codeforces.com/contest/1695/problem/C

/*
Algorithm/Techniques: Dynamic Programming with Bitset Optimization
Time Complexity: O(N * M) per test case, where N and M are grid dimensions
Space Complexity: O(M) for the bitset array, which stores possible sums

This solution uses a bitwise dynamic programming approach to track all possible sums 
that can be achieved when moving from the top-left to bottom-right of the grid.
Each bitset represents possible cumulative sums at each column, shifted left or right
depending on the value in the grid cell (1 or -1). The solution checks whether a sum of 0 
is achievable at the destination.
*/

#include <bitset>
#include <iostream>
using namespace std;

int T, N, M, k, A[1000];
bitset<2001> dp[1000]; // dp[j] stores possible sums at column j, shifted by 1000 to handle negative sums

int main() {
  cin >> T;
  for (; T--;) {
    cin >> N >> M;
    
    // Reset all bitsets for current test case
    for (int j = 0; j < M; j++)
      dp[j].reset();
    
    // Initialize starting position (sum = 0)
    dp[0][1000] = 1;
    
    // Traverse each cell in the grid
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++) {
        cin >> k;
        
        // Shift the current column's possible sums based on cell value
        if (k == 1)
          dp[j] <<= 1;  // Multiply sum by 2 (shift left) when adding 1
        else
          dp[j] >>= 1;  // Divide sum by 2 (shift right) when adding -1
        
        // Propagate possible sums to the next column if not in the last column
        if (j + 1 < M)
          dp[j + 1] |= dp[j];
      }
    
    // Output result: YES if sum of 0 (at index 1000) is achievable
    cout << (dp[M - 1][1000] == 1 ? "YES\n" : "NO\n");
  }
}


// https://github.com/VaHiX/CodeForces/