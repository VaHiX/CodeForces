// Problem: CF 1717 C - Madoka and Formal Statement
// https://codeforces.com/contest/1717/problem/C

/*
 * Problem: Madoka and Formal Statement
 * 
 * Purpose: Determine whether array 'a' can be transformed into array 'b' using allowed operations.
 *          An operation allows incrementing an element if it is less than or equal to the next element,
 *          or the last element can be incremented if it is <= first element.
 * 
 * Algorithm:
 *   - For each element in array 'a', we check:
 *     1. If 'a[i]' is less than 'b[i]', then 'b[i]' must be greater than or equal to 'b[i+1] + 1'
 *        to allow transformation to achieve 'b[i]'.
 *     2. Also checks that all elements in 'a' are less than or equal to corresponding elements in 'b'.
 * 
 * Time Complexity: O(n) per test case, since we iterate through the arrays twice.
 * Space Complexity: O(n) for storing the input arrays.
 */

#include <stdio.h>

int main() {
  int t, n, f, i, a[200003], b[200003]; // 'f' is flag for feasibility
  for (scanf("%d", &t); t; --t, printf("%s\n", f ? "YES" : "NO")) {
    for (scanf("%d", &n), i = 0; i < n; ++i)
      scanf("%d", &a[i]); // Read input array 'a'
    for (f = 1, i = 0; i < n; ++i)
      scanf("%d", &b[i]), f = f && a[i] <= b[i]; // Read 'b' and check initial condition
    for (i = 0; i < n && f; ++i)
      if (a[i] < b[i] && b[i] > b[(i + 1) % n] + 1) // Check if the target value 'b[i]' is too large to reach
        f = 0; // Set flag to 0 if condition fails
  }
}


// https://github.com/VaHiX/CodeForces/