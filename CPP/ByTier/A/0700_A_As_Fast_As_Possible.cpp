// Problem: CF 700 A - As Fast As Possible
// https://codeforces.com/contest/700/problem/A

/*
 * Problem: A. As Fast As Possible
 * 
 * Algorithm: 
 * - The bus makes multiple trips to transport all pupils.
 * - The key idea is to calculate the effective speed of the bus considering its returns.
 * - We first determine how many trips are needed: ceil(n / k).
 * - Then we compute the effective speed of the bus taking into account the time spent returning.
 * - Finally, we calculate the total time required.
 * 
 * Time Complexity: O(1) - constant time operations.
 * Space Complexity: O(1) - only a constant amount of space is used.
 */

#include <cmath>
#include <cstdio>
int main() {
  double n, l, v1, v2, k;
  scanf("%lf%lf%lf%lf%lf", &n, &l, &v1, &v2, &k);
  // Calculate number of trips needed (ceiling of n/k)
  double m = floor((n + k - 1) / k);
  // Calculate effective speed of the bus considering returns
  double speed = m * v2 - 1.0 * (m - 1) * v2 * (v2 - v1) / (v2 + v1);
  // Time for bus to travel the full distance at effective speed
  double t = l / speed;
  // Total time is time for bus + time for remaining walk
  double time = t + 1.0 * (l - v2 * t) / v1;
  printf("%.8lf\n", time);
  return 0;
}


// https://github.com/VaHiX/CodeForces/