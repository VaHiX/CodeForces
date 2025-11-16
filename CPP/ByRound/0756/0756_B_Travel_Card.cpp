// Problem: CF 756 B - Travel Card
// https://codeforces.com/contest/756/problem/B

/*
 * Problem: Travel Card
 * 
 * Purpose: 
 *   Simulates a public transport ticketing system where a single travel card is used
 *   for all trips. For each trip, the system determines the optimal set of tickets
 *   to cover all trips from the beginning up to the current one, and charges the
 *   difference between the minimal cost and the previously paid amount.
 * 
 * Algorithms/Techniques:
 *   - Dynamic Programming with Sliding Windows
 *   - Efficiently maintaining indices for 90-minute and 1440-minute windows
 *   - Precomputing minimum cost for trips using 1-trip, 90-minute, and 1-day tickets
 * 
 * Time Complexity: O(n)
 *   - Each trip is processed once, and the while loops advance pointers at most n times total
 * 
 * Space Complexity: O(n)
 *   - Storing the trip times and fees for each trip
 * 
 * Input:
 *   - n: number of trips
 *   - t[i]: time of each trip (in ascending order)
 * 
 * Output:
 *   - For each trip, the amount charged after that trip
 */

#include <cstdio>
#include <vector>
int main() {
  const int R = 90;        // 90-minute ticket duration
  const int D = 1440;      // 1-day ticket duration (1440 minutes)
  const int S = 20;        // Cost of a single trip ticket
  const int B = 50;        // Cost of a 90-minute ticket
  const int L = 120;       // Cost of a 1-day ticket
  long n;
  scanf("%ld", &n);
  std::vector<long> t(n + 1, 0), fee(n + 1, 0);  // t: trip times, fee: cumulative fees
  long tb(0), td(0);  // tb: index for 90-min window, td: index for 1-day window
  for (int p = 1; p <= n; ++p) {
    scanf("%ld", &t[p]);
    // Move tb forward until the 90-minute window covers the current trip
    while (t[tb + 1] + R <= t[p]) {
      ++tb;
    }
    // Move td forward until the 1-day window covers the current trip
    while (t[td + 1] + D <= t[p]) {
      ++td;
    }
    // Compute the minimal cost to cover all trips up to current
    // Option 1: Buy a new single-trip ticket
    // Option 2: Buy a 90-minute ticket covering trips up to tb
    // Option 3: Buy a 1-day ticket covering trips up to td
    fee[p] =
        ((fee[p - 1] + S) < (fee[tb] + B)) ? (fee[p - 1] + S) : (fee[tb] + B);
    fee[p] = (fee[p] < (fee[td] + L)) ? fee[p] : (fee[td] + L);
    // Output the charge for the current trip (difference from previous fee)
    printf("%ld\n", fee[p] - fee[p - 1]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/