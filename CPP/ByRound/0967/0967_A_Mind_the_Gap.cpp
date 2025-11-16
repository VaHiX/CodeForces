// Problem: CF 967 A - Mind the Gap
// https://codeforces.com/contest/967/problem/A

/*
 * Problem: Mind the Gap
 * Purpose: Find the earliest time to insert a takeoff such that it is at least 's' minutes away from any landing.
 * Algorithm: Greedily scan through the landing times and find the first valid gap.
 *            For each landing, check if there's enough space before it to insert the takeoff.
 *            If yes, break early and return that time.
 *            Otherwise, update the res to be after the landing + safety margin.
 *
 * Time Complexity: O(n) - Single pass through the landings
 * Space Complexity: O(1) - Only using a few variables regardless of input size
 */

#include <cstdio>
int main() {
  long H = 60;  // Minutes in an hour
  long n, s;    // Number of landings and safety margin
  scanf("%ld %ld", &n, &s);
  long res(0);  // Earliest valid time for takeoff in minutes from start

  // Process each landing
  while (n--) {
    long h, m;        // Landing time in hours and minutes
    scanf("%ld %ld", &h, &m);
    long time = h * H + m;  // Convert landing time to minutes from start

    // If the gap between the last takeoff and this landing is sufficient
    if (time - res >= s + 1) {
      break;  // We found a valid spot for takeoff
    }
    res = time + s + 1;  // Update takeoff time to after this landing with safety margin
  }

  // Output the result in hours and minutes
  printf("%ld %ld\n", res / H, res % H);
  return 0;
}


// https://github.com/VaHiX/CodeForces/