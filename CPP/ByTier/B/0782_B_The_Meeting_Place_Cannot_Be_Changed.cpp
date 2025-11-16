// Problem: CF 782 B - The Meeting Place Cannot Be Changed
// https://codeforces.com/contest/782/problem/B

/*
 * Problem: B. The Meeting Place Cannot Be Changed
 * Algorithm: Ternary Search on the answer
 * Time Complexity: O(n * log(max_range / eps)) where max_range is the difference between max and min coordinates
 * Space Complexity: O(n) for storing coordinates and speeds
 *
 * The problem is to find the minimum time for all friends to meet at some point on a line,
 * where each friend has a position and a maximum speed.
 * We use ternary search because the function "time to meet at a point" is convex.
 * For a fixed meeting point, the time needed is the maximum time any friend takes to reach it.
 * We minimize this maximum time using ternary search over possible meeting points.
 */

#include <cstdio>
#include <vector>
double getTime(const std::vector<double> &x, const std::vector<double> &v,
               double probe) {
  double maxTime(0);
  for (long p = 0; p < x.size(); p++) {
    double time = (probe - x[p]) / v[p];
    if (time < 0) {
      time = -time; // Take absolute value since direction doesn't matter
    }
    maxTime = (maxTime > time) ? maxTime : time; // Keep track of maximum time
  }
  return maxTime;
}
int main() {
  const double eps = 1e-8;  // Precision threshold for ternary search
  long n;
  scanf("%ld", &n);
  std::vector<double> x(n), v(n);
  for (long p = 0; p < n; p++) {
    scanf("%lf", &x[p]);  // Read positions
  }
  for (long p = 0; p < n; p++) {
    scanf("%lf", &v[p]);  // Read speeds
  }
  double left(0.0), right(1e9 + 10.0);  // Set bounds for possible meeting points
  
  // Ternary search to find optimal meeting point
  while (right - left >= eps) {
    double m1 = (2.0 * left + right) / 3.0;   // First mid point
    double m2 = (left + 2.0 * right) / 3.0;   // Second mid point
    double t1 = getTime(x, v, m1);            // Time if meeting at m1
    double t2 = getTime(x, v, m2);            // Time if meeting at m2
    if (t1 < t2) {
      right = m2;  // Move right since t1 is smaller, so better solution exists on left side
    } else {
      left = m1;   // Move left since t2 is smaller, so better solution exists on right side
    }
  }
  
  // Output the minimal time using the midpoint of final search interval
  printf("%.9lf\n", getTime(x, v, (left + right) / 2));
  return 0;
}


// https://github.com/VaHiX/CodeForces/