// Problem: CF 1063 C - Dwarves, Hats and Extrasensory Abilities
// https://codeforces.com/contest/1063/problem/C

/*
 * Problem: C. Dwarves, Hats and Extrasensory Abilities
 * 
 * Algorithm: Binary Search on a Line
 * 
 * Approach:
 * - The goal is to place n points on a 2D plane and then find a line that separates
 *   the points into two groups based on their color (black/white).
 * - We use a binary search strategy along a vertical line (y=1) to deduce the
 *   color pattern of points. Initially, we place the first point at (0,1) and get
 *   its color.
 * - For subsequent points, we place them at coordinates (mid, 1), where mid is
 *   the midpoint of a range [l, r]. Based on the color of the point at (mid, 1),
 *   we adjust the search range [l, r] to narrow down the position of the point
 *   with a different color.
 * - After placing all points and determining the color arrangement, we use two
 *   points (l, 0) and (r, 2) to define a separating line (vertical line at x = l
 *   to x = r) which successfully divides the points.
 * 
 * Time Complexity: O(n * log(1e9)) - for placing points using binary search.
 * Space Complexity: O(1) - only using a few integer variables.
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <iostream>
#include <string>

using namespace std;
int n, p = 0, l = 0, r = 1e9;
string s, st;
int main() {
  scanf("%d", &n);
  puts("0 1");  // Place first point at (0, 1)
  cin >> st;    // Read color of first point
  for (int i = 1; i < n; i++) {
    int mid = (l + r) >> 1;   // Compute midpoint of range [l, r]
    printf("%d 1\n", mid);    // Place point at (mid, 1)
    cin >> s;                 // Read color of this point
    if (s == st)              // If same color as first point
      l = mid;                // Adjust lower bound
    else
      r = mid;                // Adjust upper bound
  }
  printf("%d 0 %d 2", l, r);  // Output separating line through (l, 0) and (r, 2)
}


// https://github.com/VaHiX/CodeForces/