// Problem: CF 2113 A - Shashliks
// https://codeforces.com/contest/2113/problem/A

#include <cstdio>
// Flowerbox describing the code purpose, algorithms, and complexities
/*
 * Problem: A. Shashliks
 *
 * Purpose:
 *   Given initial grill temperature 'k', and two types of shashlik with their
 *   respective minimum required temperatures (a and b) and temperature drops (x and y),
 *   determine the maximum number of shashlik portions that can be cooked.
 *
 * Algorithms/Techniques:
 *   - Greedy approach: Try to maximize the count by choosing the better option at each step.
 *   - Optimization: If one type requires less energy (in terms of temperature drop), prioritize it.
 *   - Mathematical calculation: Use division and remainder operations to compute how many times
 *     a type can be cooked given remaining temperature.
 *
 * Time Complexity: O(1) per test case — constant time operations.
 * Space Complexity: O(1) — only a fixed number of variables are used.
 */

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long k, a, b, x, y;
    scanf("%ld %ld %ld %ld %ld", &k, &a, &b, &x, &y);
    
    // Optimization: Ensure x <= y so that we handle the type with smaller drop first
    if (x > y) {
      long tmp = x;
      x = y;
      y = tmp;
      tmp = a;
      a = b;
      b = tmp;
    }
    
    long cnt(0);  // Count of shashlik portions cooked
    
    // Cook as many of the first type as possible
    if (k >= a) {
      long div = 1 + (k - a) / x;  // Number of times first type can be cooked after one initial cook
      cnt += div;
      k -= div * x;  // Reduce the temperature accordingly
    }
    
    // Cook as many of the second type as possible with remaining temperature
    if (k >= b) {
      cnt += 1 + (k - b) / y;
    }
    
    printf("%ld\n", cnt);
  }
}

// https://github.com/VaHiX/codeForces/