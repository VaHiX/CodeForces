// Problem: CF 1730 B - Meeting on the Line
// https://codeforces.com/contest/1730/problem/B

/*
 * Problem: Meeting on the Line
 * 
 * Purpose: Find the optimal position x0 on a line where all people can meet 
 *          such that the maximum time taken by any person to reach x0 is minimized.
 * 
 * Algorithm:
 * - For each person i, define their effective range as [x_i - t_i, x_i + t_i].
 * - The optimal meeting point x0 is the midpoint of the union of all these ranges.
 * - The idea is based on the fact that the cost function (max time for any person) 
 *   is minimized when x0 is chosen to balance the ranges.
 * 
 * Time Complexity: O(n) per test case, for processing n people.
 * Space Complexity: O(n) for storing the positions.
 * 
 * Techniques:
 * - Sorting ranges and finding their union.
 * - Using the midpoint of range union as optimal x0.
 */

#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    double a[100001]; // Array to store positions of people
    double mn = 2e8 + 5, mx = 0; // Initialize min and max bounds
    for (int i = 1; i <= n; i++)
      cin >> a[i]; // Read positions
    
    for (int i = 1; i <= n; i++) {
      int b;
      cin >> b; // Read dressing times
      // Compute the effective range for person i
      mn = min(a[i] - b, mn); // Leftmost point of range
      mx = max(a[i] + b, mx); // Rightmost point of range
    }
    // Print midpoint of the combined range
    printf("%7lf\n", (mx + mn) / 2);
  }
}


// https://github.com/VaHiX/CodeForces/