// Problem: CF 1064 A - Make a triangle!
// https://codeforces.com/contest/1064/problem/A

/*
 * Problem: A. Make a triangle!
 * Purpose: Given three stick lengths, find the minimum number of minutes to make a valid triangle.
 *          A valid triangle satisfies the triangle inequality: sum of any two sides > third side.
 *          Since we can only increase stick lengths, we sort the sticks and try to minimize
 *          increases needed so that the smallest two are sufficient to cover the largest.
 *
 * Algorithms/Techniques:
 *   - Sorting the array to simplify comparisons
 *   - Mathematical calculation to determine how much to increase
 *
 * Time Complexity: O(1) - sorting 3 elements is constant time
 * Space Complexity: O(1) - only using a fixed-size vector and variables
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  std::vector<long> v(3); // Create vector to hold the three stick lengths
  scanf("%ld %ld %ld", &v[0], &v[1], &v[2]); // Read input stick lengths
  sort(v.begin(), v.end()); // Sort in ascending order: v[0] <= v[1] <= v[2]
  long diff = (1 + v[2] - v[1] - v[0]); // Calculate minimum required increases
  diff = (diff < 0) ? 0 : diff; // Ensure no negative result (if triangle is already valid)
  printf("%ld\n", diff); // Output the result
  return 0;
}


// https://github.com/VaHiX/codeForces/