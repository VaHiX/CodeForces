// Problem: CF 1730 F - Almost Sorted
// https://codeforces.com/contest/1730/problem/F

/*
 * Problem: F. Almost Sorted
 * 
 * Purpose: Given a permutation p of length n and a positive integer k,
 *          find the minimum number of inversions in a permutation q such that
 *          for any i < j, p[q_i] <= p[q_j] + k.
 * 
 * Algorithm:
 * - Dynamic Programming with Bitmasking
 * - State: dp[i][mask] = minimum inversions when placing first i elements
 *   with a bitmask indicating which positions of the current segment are filled.
 * - For each element, we try placing it in valid positions based on the constraint.
 * 
 * Time Complexity: O(n * 2^k * k * k)
 * Space Complexity: O(n * 2^k)
 * 
 * Techniques used:
 * - Bitmask DP
 * - Sliding window / segment management
 * - Greedy placement with constraint checking
 */

#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
int n, k, p, a[5005], dp[5005][515], s[5005], N;

int main() {
  cin >> n >> k;
  ++k, N = (1 << k) - 1; // k is incremented and N is 2^k - 1 for bitmask operations
  
  // Store positions of elements in original permutation p
  for (int i = 1; i <= n; i++)
    cin >> p, a[p] = i;
    
  // Initialize DP table with large values
  memset(dp, 0x3f, sizeof dp);
  dp[0][0] = 0; // Base case: 0 elements placed, 0 inversions

  // Iterate through all elements
  for (int i = 0; i <= n; i++) {
    // Update segment count array s
    if (i > 0)
      for (int j = 1; j <= a[i]; j++)
        ++s[j];
        
    // Process all valid masks
    for (int j = 0; j <= N; j += 2) { // Only even masks are valid (based on algorithm logic)
      if (dp[i][j] != dp[5001][0]) { // If state is valid
        // Try placing next x elements
        for (int x = 1; x <= min(k, n - i); x++) {
          // Skip if x-th position already filled (bit set)
          if (!(j >> (x - 1) & 1)) {
            int p = i, q = j | (1 << (x - 1)), cnt = s[a[i + x] + 1]; // Count inversions
            
            // Adjust q to find valid segment
            while (q & 1)
              ++p, q >>= 1;
              
            // Count inversions for the current element against previous ones
            for (int y = 1; y <= k; y++)
              if ((j >> (y - 1) & 1) && a[i + y] > a[i + x])
                ++cnt;
                
            // Update DP state
            dp[p][q] = min(dp[p][q], dp[i][j] + cnt);
          }
        }
      }
    }
  }
  
  cout << dp[n][0]; // Result is minimum inversions for full permutation
}


// https://github.com/VaHiX/CodeForces/