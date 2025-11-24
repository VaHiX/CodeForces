// Problem: CF 1966 A - Card Exchange
// https://codeforces.com/contest/1966/problem/A

/*
 * Problem: Card Exchange
 * Algorithm: Greedy with Map Usage
 * Time Complexity: O(n * log n) per test case due to map operations
 * Space Complexity: O(n) for storing card counts in the map
 *
 * The solution uses a greedy approach:
 * - Count frequency of each card value.
 * - If any card appears at least k times, we can perform operations to reduce total cards.
 * - For each such card with count >= k, we can exchange k cards for k-1 cards,
 *   effectively reducing the total count by 1 per operation.
 * - If no card has frequency >= k, then no operations can be performed.
 *
 * Key Insight:
 * - We minimize total cards by repeatedly exchanging k same cards for k-1 cards
 *   whenever possible.
 * - If there exists a value with frequency >= k, the minimum is (k-1).
 * - Otherwise, we return n since no exchange is possible.
 */

#include <cstdio>
#include <map>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::map<long, long> m; // Map to store frequency of each card value
    bool reached(false);    // Flag to check if any card has count >= k
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++m[x];                  // Increment frequency of card value x
      if (m[x] >= k) {         // If frequency reaches k
        reached = true;        // Mark that an exchange is possible
      }
    }
    printf("%ld\n", reached ? (k - 1) : n); // Output result based on whether exchange was possible
  }
}


// https://github.com/VaHiX/codeForces/