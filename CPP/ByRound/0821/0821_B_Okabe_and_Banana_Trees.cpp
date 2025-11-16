// Problem: CF 821 B - Okabe and Banana Trees
// https://codeforces.com/contest/821/problem/B

/*
 * Problem: Okabe and Banana Trees
 * 
 * Algorithm/Technique: Brute-force with mathematical optimization
 * 
 * Purpose:
 *   Given a line equation y = m * x + b, we need to find the maximum number of bananas
 *   that can be collected by choosing a rectangle with axis-aligned sides, such that
 *   all points (x, y) inside or on the rectangle satisfy y <= m * x + b.
 *   Each point (x, y) contains (x + y) bananas.
 *   We try all possible values of y from 0 to b, compute the maximum x for that y,
 *   then calculate how many bananas can be collected in the rectangle.
 * 
 * Time Complexity: O(b)
 *   - We iterate through all possible values of y from 0 to b.
 *   - For each y, we compute x = m * (b - y) in O(1) time.
 *   - The calculation of bananas in the rectangle is also O(1).
 * 
 * Space Complexity: O(1)
 *   - Only a constant number of variables are used.
 */

#include <stdint.h>
#include <iostream>

int main() {
  int64_t m, b;
  std::cin >> m >> b;
  int64_t ans(0);
  for (int64_t y = 0; y <= b; y++) {
    // Compute maximum x for current y such that point (x, y) is on or below the line
    int64_t x = m * (b - y);
    // Calculate total bananas in the rectangle [0..x] x [0..y]
    // The formula for sum of (x + y) over all points in rectangle is:
    // sum_{i=0}^{x} sum_{j=0}^{y} (i + j) = (x+1)(y+1)(x+y+2)/2
    int64_t cur = (x + y) * (x + 1) * (y + 1) / 2;
    ans = (ans > cur) ? ans : cur;
  }
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/