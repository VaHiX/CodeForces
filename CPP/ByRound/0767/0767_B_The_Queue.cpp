// Problem: CF 767 B - The Queue
// https://codeforces.com/contest/767/problem/B

/*
 * Problem: B. The Queue
 * 
 * Purpose: Given a passport office schedule, service time per person, and a list of visitor arrival times,
 * determine the earliest time Vasya can arrive to minimize his waiting time in the queue.
 * 
 * Algorithm/Approach:
 * - Simulate the queue process by tracking when the receptionist becomes free.
 * - For each visitor, we check if they can be served before the office closes.
 * - When a visitor arrives, if the receptionist is free, the service starts immediately.
 * - If the receptionist starts serving a visitor, the next available time is updated.
 * - We evaluate potential arrival times for Vasya to minimize their wait and ensure service.
 * 
 * Time Complexity: O(n), where n is the number of visitors. Each visitor is processed once.
 * Space Complexity: O(1), only using a few variables regardless of input size.
 */

#include <stdint.h>
#include <cstdio>

int main() {
  int64_t ts, tf, t;
  scanf("%lld %lld %lld", &ts, &tf, &t); // Read the start time, end time, and service time
  int64_t n;
  scanf("%lld", &n); // Read number of visitors
  int64_t m(1e18), ans(1e18); // m tracks minimum gap, ans tracks best arrival time
  while (n--) {
    int64_t a;
    scanf("%lld", &a); // Read visitor arrival time
    if (a > 0 && a <= tf - t) { // Ensure visitor arrives before the office closes and before last service
      int64_t prev = (ts > (a - 1)) ? ts : (a - 1); // Determine the earliest possible start time for this visitor
      if (prev <= tf - t && ts - a + 1 < m) { // If previous time is valid and better than current min
        m = ts - a + 1; // Update minimum gap
        ans = (a - 1) < ts ? (a - 1) : ts; // Update best arrival time
      }
      ts = ((ts > a) ? ts : a) + t; // Update the next available time after this visitor
    }
  }
  if (ts <= tf - t) { // If the office has not closed yet
    ans = ts; // Set the arrival time as the current time
  }
  printf("%lld\n", ans); // Output the optimal arrival time
  return 0;
}


// https://github.com/VaHiX/CodeForces/