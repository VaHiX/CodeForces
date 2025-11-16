// Problem: CF 1408 C - Discrete Acceleration
// https://codeforces.com/contest/1408/problem/C

/*
 * Problem: Discrete Acceleration
 * 
 * Description:
 * Two cars start from opposite ends of a road of length l and move towards each other.
 * Each car starts at speed 1 m/s. There are n flags at specific positions on the road.
 * When a car passes a flag, its speed increases by 1 m/s.
 * Find the time when the two cars meet.
 * 
 * Approach:
 * Use binary search on the time. For a given time, simulate both cars to see if they meet.
 * The check function simulates movement of both cars through flags, calculating how far each car
 * travels in the given time.
 * 
 * Time Complexity: O(n * log(max_time)) where max_time is around 1e10
 * Space Complexity: O(n) for storing flag positions
 * 
 * Algorithms/Techniques:
 * - Binary Search
 * - Simulation of car movement with discrete speed changes
 * 
 */

#include <cstdio>
#include <vector>
bool check(const std::vector<double> &a, double len, const double time) {
  double x(0), rem(time);
  for (long p = 1; p < a.size(); p++) {
    double dist = a[p] - a[p - 1];
    // If the distance to the next flag can be covered in remaining time
    if (dist < p * rem) {
      x += dist;
      rem -= dist / p;
    } else {
      // The car will not reach this flag in time, so add distance covered
      x += p * rem;
      rem = 0;
      break;
    }
  }
  double y(0);
  rem = time;
  // Same logic but for the car moving from end to start
  for (long p = a.size() - 2; p >= 0; p--) {
    double dist = a[p + 1] - a[p];
    double speed = (a.size() - 1 - p);
    if (dist < speed * rem) {
      y += dist;
      rem -= dist / speed;
    } else {
      y += speed * rem;
      rem = 0;
      break;
    }
  }
  return (x + y <= len);
}
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    double n, len;
    scanf("%lf %lf", &n, &len);
    std::vector<double> a(n + 2, 0);
    for (long p = 1; p <= n; p++) {
      scanf("%lf", &a[p]);
    };
    a[n + 1] = len;
    double left(0), right(1e10), eps(1e-7), res(0.0);
    while (right > left + eps) {
      double mid = (left + right) / 2.0;
      if (check(a, len, mid)) {
        res = mid;
        left = mid;
      } else {
        right = mid;
      }
    }
    printf("%.8lf\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/