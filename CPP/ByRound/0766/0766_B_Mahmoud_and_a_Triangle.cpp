// Problem: CF 766 B - Mahmoud and a Triangle
// https://codeforces.com/contest/766/problem/B

/*
 * Code Purpose: Determines if three line segments from a given list can form a non-degenerate triangle.
 * 
 * Algorithm: 
 * - Sort the array of line segment lengths.
 * - Iterate through the sorted array starting from index 2.
 * - For each triplet (a[p-2], a[p-1], a[p]), check the triangle inequality:
 *   a[p-2] + a[p-1] > a[p]. If true, a valid triangle exists.
 * 
 * Time Complexity: O(n log n) due to sorting; the loop is O(n).
 * Space Complexity: O(1) if we ignore input storage, otherwise O(n) for the vector.
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long n;
  std::cin >> n;
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    std::cin >> a[p]; // Read input values
  }
  sort(a.begin(), a.end()); // Sort the array to facilitate triangle checking
  std::string res("NO"); // Initialize result as "NO"
  for (int p = 2; p < n; p++) {
    if (a[p - 2] + a[p - 1] > a[p]) { // Check triangle inequality
      res = "YES"; // If valid triangle found, set result to "YES"
      break;
    }
  }
  std::cout << res << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/