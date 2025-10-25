// Problem: CF 1901 A - Line Trip
// https://codeforces.com/contest/1901/problem/A

/*
 * Problem: Line Trip
 * Algorithm: Greedy + Simulation
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) due to vector storage
 *
 * We need to find the minimum gas tank capacity to travel from 0 to x and back,
 * visiting only stations at positions a[1]...a[n]. The key insight is that we must
 * ensure the car can make it through the largest gap between consecutive points
 * (including start and end), both going forward and returning.
 *
 * The strategy:
 * - Add a "virtual" station at x + (x - a[n]) to simulate the return trip.
 * - Compute the maximum distance between two consecutive stations (including 0 and final point).
 * - That max distance is our minimum required tank capacity.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x;
    scanf("%ld", &x);
    std::vector<long> a(n + 2, 0); // Create vector with extra space for start and end
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]); // Read station positions
    }
    // Add a virtual station at the mirrored position to simulate return journey
    a[n + 1] = x + (x - a[n]);
    long ans(0);
    for (long p = 1; p <= n + 1; p++) {
      long diff = a[p] - a[p - 1]; // Calculate distance between consecutive points
      ans = (ans > diff) ? ans : diff; // Keep track of the maximum such distance
    }
    printf("%ld\n", ans); // Output minimum required tank capacity
  }
}


// https://github.com/VaHiX/codeForces/