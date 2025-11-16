// Problem: CF 746 C - Tram
// https://codeforces.com/contest/746/problem/C

/*
 * Problem: C. Tram
 * Purpose: Determine the minimum time Igor needs to travel from point x1 to x2,
 *          considering he can either walk or take the tram.
 * 
 * Algorithms/Techniques:
 * - Mathematical simulation of tram movement with reflections
 * - Comparison of two strategies:
 *   1. Walking the entire distance
 *   2. Walking to the tram, taking it to the destination
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only using a fixed number of variables
 */

#include <iostream>
int main() {
  int s, x1, x2;
  std::cin >> s >> x1 >> x2;
  int t1, t2;
  std::cin >> t1 >> t2;
  int p, d;
  std::cin >> p >> d;
  
  // Normalize the coordinates so that x1 <= x2
  // This ensures we work with a consistent direction
  if (x1 > x2) {
    x1 = s - x1;
    x2 = s - x2;
    d = -d;
    p = s - p;
  }
  
  // Adjust the tram's position based on its direction
  // Convert to a relative coordinate system where the tram moves forward
  p *= d;
  
  // If the tram is ahead of x1, simulate it going past point 0 and back
  if (p > x1) {
    p -= 2 * s;
  }
  
  // Calculate time if Igor walks the whole distance
  int f1 = (x2 - x1) * t2;
  
  // Calculate time if Igor walks to tram and then takes it to destination
  int f2 = (x2 - p) * t1;
  
  // Choose the minimum time
  int ans = (f1 < f2) ? f1 : f2;
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/