// Problem: CF 703 C - Chris and Road
// https://codeforces.com/contest/703/problem/C

/*
 * Code Purpose: 
 *   This program computes the minimum time required for a pedestrian to cross a road
 *   without being hit by a moving bus. The bus is modeled as a convex polygon moving
 *   horizontally with speed v, and the pedestrian moves vertically with speed u.
 *   
 * Algorithm:
 *   - For each vertex of the bus polygon, calculate the time difference between when
 *     the bus reaches the x-coordinate of the vertex and when the pedestrian reaches
 *     the y-coordinate of the vertex.
 *   - These time differences define a "safe window" for crossing the road.
 *   - The minimum of these time differences is used to determine if there's a gap
 *     in which the pedestrian can start crossing without being hit.
 *   - If such a gap exists (minTime < 0), the pedestrian starts at the earliest possible
 *     time and adds the travel time to cross the road and the delay caused by the bus.
 *   - If no gap exists, the pedestrian must wait for the bus to pass completely,
 *     and the total time is simply the time to cross the road.
 *   
 * Time Complexity: O(n) where n is the number of vertices in the polygon.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long n, w, v, u;
  scanf("%ld %ld %ld %ld", &n, &w, &v, &u);
  double minTime(1e9), maxTime(0);
  for (long p = 0; p < n; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    double timeDiff = 1.0 * x / v - 1.0 * y / u;  // Time difference for this vertex
    minTime = (minTime < timeDiff) ? minTime : timeDiff;  // Track minimum time diff
    maxTime = (maxTime > timeDiff) ? maxTime : timeDiff;  // Track maximum time diff
  }
  double timeToCross = 1.0 * w / u;  // Time to walk across the road
  if (minTime < 0) {
    timeToCross += maxTime;  // Add delay if there's overlap/interference
  }
  printf("%.7lf\n", timeToCross);
  return 0;
}


// https://github.com/VaHiX/CodeForces/