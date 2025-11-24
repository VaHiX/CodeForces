// Problem: CF 712 C - Memory and De-Evolution
// https://codeforces.com/contest/712/problem/C

/*
 * Code Purpose:
 * This program calculates the minimum number of operations required to reduce
 * an equilateral triangle of side length x to one of side length y.
 * Each operation allows increasing one side of the triangle such that it remains a valid triangle.
 * The algorithm uses a greedy approach: always increase the smallest side to minimize steps.
 *
 * Algorithms/Techniques:
 * - Greedy algorithm with sorting
 * - Simulated triangle evolution from x to y
 *
 * Time Complexity: O(log x) due to logarithmic number of operations to reduce from x to y
 * Space Complexity: O(1) as only a fixed-size vector and few variables are used
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long x, y;
  scanf("%ld %ld", &x, &y);
  std::vector<long> v(3, y);  // Initialize triangle with all sides equal to y
  long count(0);              // Counter for operations
  while (v[0] < x) {          // While the smallest side is less than x
    v[0] = v[1] + v[2] - 1;   // Increase the smallest side to just under sum of two others
    v[0] = (v[0] < x) ? v[0] : x;  // Cap at x if overshooting
    sort(v.begin(), v.end()); // Re-sort to keep smallest at index 0
    ++count;                  // Increment operation count
  }
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/