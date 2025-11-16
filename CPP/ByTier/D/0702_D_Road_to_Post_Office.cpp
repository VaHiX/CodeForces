// Problem: CF 702 D - Road to Post Office
// https://codeforces.com/contest/702/problem/D

/*
Purpose: 
  This code calculates the minimum time required for Vasiliy to travel from home to the post office,
  considering he can use his car (which breaks every k km and requires t seconds to repair) or walk.
  The decision is made optimally to minimize total travel time.

Algorithms/Techniques:
  - Greedy approach with conditional logic
  - Optimization of car usage vs walking based on distances and times

Time Complexity: O(1)
Space Complexity: O(1)

Input Format:
  d k a b t
  - d: total distance to post office
  - k: distance car can travel before breaking
  - a: time to travel 1 km by car
  - b: time to walk 1 km
  - t: time to repair car after it breaks

Output:
  Minimum time to reach the post office
*/
#include <stdint.h>
#include <algorithm>
#include <iostream>

int main() {
  int64_t d, k, a, b, t;
  std::cin >> d >> k >> a >> b >> t;
  if (d <= k) {
    // If total distance is less than or equal to k, just drive the whole way
    std::cout << (d * a) << std::endl;
  } else {
    // Subtract the first k km from the total distance
    d -= k;
    // Compute minimum time using the formula:
    // k*a: time for first k km by car
    // (d/k) * min(k*a + t, k*b): cost of full car segments (drive + repair or walk)
    // min(t + (d%k)*a, (d%k)*b): cost of remaining km (either repair + drive or walk)
    std::cout << (k * a + (d / k) * std::min(k * a + t, k * b) +
                  std::min(t + (d % k) * a, (d % k) * b))
              << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/