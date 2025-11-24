// Problem: CF 822 C - Hacker, pack your bags!
// https://codeforces.com/contest/822/problem/C

/*
 * Problem: Choose two non-overlapping vouchers such that their total duration equals x,
 *          and their total cost is minimized.
 *
 * Algorithm:
 * - Use a sweep line approach with events:
 *   - For each voucher, create two events: start (l_i, 0, i) and end (r_i, 1, i)
 *   - Sort events by time
 *   - Process events:
 *     - When encountering a start event, check if there exists a previously seen
 *      voucher with duration (x - current_duration) to form a valid pair
 *     - When encountering an end event, update the minimum cost for that duration
 * - Time Complexity: O(n log n) due to sorting
 * - Space Complexity: O(n) for storing events and DP array
 */

#include <stdio.h>
#include <algorithm>
#include <tuple>
#include <vector>

std::vector<std::tuple<int, int, int>> op; // Stores events: (time, type, index)
int N, X;
int L[210000], R[210000], cost[210000];
int dp[210000]; // dp[d] = minimum cost of a voucher with duration d
int ans = -1;

int main() {
  scanf("%d%d", &N, &X);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d%d", &L[i], &R[i], &cost[i]);
    op.push_back(std::make_tuple(L[i], 0, i)); // Start event
    op.push_back(std::make_tuple(R[i], 1, i)); // End event
  }
  std::sort(op.begin(), op.end()); // Sort by time

  for (int i = 0; i < op.size(); ++i) {
    int o = std::get<1>(op[i]), ind = std::get<2>(op[i]); // o = event type, ind = voucher index

    if (o == 0) {
      // Start event: process current voucher
      int dur = R[ind] - L[ind] + 1; // Duration of current voucher
      int nec = X - dur; // Required duration from another voucher

      // If required duration is valid and a voucher of this duration exists
      if (nec >= 0 && dp[nec] != 0) {
        if (ans == -1 || ans > dp[nec] + cost[ind])
          ans = dp[nec] + cost[ind]; // Update minimum cost if better solution found
      }
    } else {
      // End event: update dp with cost of current voucher
      int dur = R[ind] - L[ind] + 1;
      if (dp[dur] == 0 || dp[dur] > cost[ind])
        dp[dur] = cost[ind]; // Keep minimum cost for same duration
    }
  }

  printf("%d\n", ans);
}


// https://github.com/VaHiX/CodeForces/