// Problem: CF 1156 A - Inscribed Figures
// https://codeforces.com/contest/1156/problem/A

/*
 * Problem: Inscribed Figures
 * Algorithms/Techniques: Simulation, Geometry
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * The problem involves calculating the number of distinct points where figures
 * touch when each figure is inscribed into the previous one in a specific way:
 * - Circle inscribed in another figure has maximum radius
 * - Square inscribed in another figure has maximum side length
 * - Triangle (isosceles with height equal to base) inscribed in another figure
 *   has maximum side length.
 *
 * The sequence of figures is given as 1 = circle, 2 = triangle, 3 = square.
 * Each pair of consecutive figures contributes a certain number of points
 * depending on their types. Special cases like when the same figure appears
 * consecutively or specific combinations lead to infinite points.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long cnt(0);
  long prev(-1), pprev(-1);
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    // If two consecutive figures are the same type, or if they form forbidden pairs
    if ((a == prev) || (a == 2 && prev == 3) || (a == 3 && prev == 2)) {
      cnt = -1;
      break;
    }
    // Add points for specific figure transitions
    if ((a == 1 && prev == 2) || (a == 2 && prev == 1)) {
      cnt += 3;
    }
    if ((a == 1 && prev == 3) || (a == 3 && prev == 1)) {
      cnt += 4;
    }
    // Subtract points for special configuration involving triangle, square, circle
    if (a == 2 && prev == 1 && pprev == 3) {
      cnt -= 1;
    }
    pprev = prev;
    prev = a;
  }
  if (cnt < 0) {
    puts("Infinite");
  } else {
    printf("Finite\n%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/