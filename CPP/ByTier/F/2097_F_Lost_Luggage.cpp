// Problem: CF 2097 F - Lost Luggage
// https://codeforces.com/contest/2097/problem/F

/*
F. Lost Luggage
Algorithm: Dynamic Programming with bitmasking and optimized processing for n <= 12
Time Complexity: O(m * N * 2^N) where m is number of days, N is number of airports
Space Complexity: O(2^N) for dp arrays

This problem models a system where lost luggage can be transported between airports.
Each day, flights move luggage between adjacent airports (with wraparound), and at 
the end of each day, some of the baggage gets recovered based on thresholds defined by b[i][j].
We're to compute the maximum possible amount of un-found luggage after each day.
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

#pragma GCC optimize "O3"
#pragma GCC target "avx2"
#define LL long long
#define INF_LL 0x3f3f3f3f3f3f3f3f

int T, N, M, s[13], a[13], b[13], c[13];
LL dp[(1 << 12) + 5], tp[(1 << 12) + 5], qq[(1 << 12) + 5][2];

signed main(void) {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
      scanf("%d", &s[i]);
    }
    
    // Precompute dp array: for each subset of airports, 
    // calculate initial total luggage in those not included
    for (int i = 0; i < (1 << N); i++) {
      dp[i] = 0;
      for (int j = 1; j <= N; j++) {
        if (((i >> j - 1) & 1) == 0)
          dp[i] += s[j];
      }
    }

    while (M--) {
      // Read input for this day
      for (int i = 1; i <= N; i++)
        scanf("%d", &a[i]);
      for (int i = 1; i <= N; i++)
        scanf("%d", &b[i]);
      for (int i = 1; i <= N; i++)
        scanf("%d", &c[i % N + 1]); // Next airport, wrapping around

      // Initialize tp array with large value
      memset(tp, 0x3f, sizeof(tp));
      
      // Process two subproblems based on parity of indices
      for (int st = 0; st < 2; st++) {
        // Reset qq for each subproblem
        memset(qq, 0x3f, sizeof(qq));
        
        // Initialize qq with dp values for selected subsets (based on st)
        for (int j = st; j < (1 << N); j += 2)
          qq[j][(j >> N - 1)] = dp[j];
          
        // Process layers of the DP in increasing order
        for (int j = 1; j <= N; j++) {
          int qc = 0;
          if (j == N && st)  // Special handling for last index when st = 1
            qc = a[1];
          // For each segment of size 2^j, update QQ accordingly
          for (int k = 0; k < (1 << N); k += (1 << j)) {
            // Compute vq: cost associated with current bit pattern
            LL vq = ((k >> j) & 1) * a[j + 1] + qc;
            // Inner loop updating the values for lower halves of the segments
            for (int k1 = k; k1 < k + (1 << j - 1); k1++) {
              int k2 = k1 + (1 << j - 1);
              LL aa = qq[k1][0], bb = qq[k1][1], cc = qq[k2][0], dd = qq[k2][1];
              // Update qq using dynamic programming recurrence
              qq[k1][0] = std::min(aa, bb + c[j]) + vq;
              qq[k1][1] = std::min(cc, dd + c[j]) + vq + b[j];
              qq[k2][0] = std::min(aa, bb);
              qq[k2][1] = std::min(cc, dd);
            }
          }
        }
        
        // Update tp with the minimum value of qq for each state
        for (int k = 0; k < (1 << N); k++) {
          tp[k] = std::min(tp[k], qq[k][0]);
          tp[k] = std::min(tp[k], qq[k][1]);
        }
      }
      
      // Update dp with values from tp
      for (int i = 0; i < (1 << N); i++)
        dp[i] = tp[i];
        
      // Output maximum luggage count after this day
      printf("%lld\n", dp[0]);
    }
  }
}


// https://github.com/VaHiX/codeForces/