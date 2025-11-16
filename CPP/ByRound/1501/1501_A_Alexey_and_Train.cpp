// Problem: CF 1501 A - Alexey and Train
// https://codeforces.com/contest/1501/problem/A

/*
 * Problem: A. Alexey and Train
 * Purpose: Simulate train travel time considering delays and minimum stop times,
 *          calculating arrival time at the final station.
 *
 * Algorithms/Techniques:
 *   - Simulation
 *   - Ceiling division calculation
 *
 * Time Complexity: O(n) per test case, where n is the number of stations.
 * Space Complexity: O(n) per test case, due to storing station data and delays.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld %ld", &a[p], &b[p]); // Read arrival and departure times
    }
    std::vector<long> d(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &d[p]); // Read delay times for each segment
    }
    long t(0), depart(0); // t = arrival time, depart = departure time
    for (long p = 0; p < n; p++) {
      // Calculate arrival time at station p
      // Time to reach station p from previous station includes:
      // - Previous departure time
      // - Travel time = a[p] - b[p-1] + d[p] (with special case for first station)
      t = depart + (a[p] - (p ? b[p - 1] : 0) + d[p]);
      
      // Calculate next departure time:
      // - Departure happens after arriving at station p
      // - Must stay at station for at least ceil((b[p] - a[p]) / 2) units of time
      // - Departure cannot happen before b[p]
      depart = t + (b[p] - a[p] + 1) / 2; // Compute minimum required stop duration
      depart = (depart > b[p]) ? depart : b[p]; // Ensure departure is not earlier than b[p]
    }
    printf("%ld\n", t); // Output arrival time at final station
  }
}


// https://github.com/VaHiX/codeForces/