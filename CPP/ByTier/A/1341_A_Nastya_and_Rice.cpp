// Problem: CF 1341 A - Nastya and Rice
// https://codeforces.com/contest/1341/problem/A

/*
 * Problem: A. Nastya and Rice
 * Purpose: Determine if it's possible for n grains, each weighing between (a-b) and (a+b) grams,
 *          to sum up to a total weight between (c-d) and (c+d) grams.
 *
 * Algorithm: Check the constraints by computing the minimum and maximum possible total weights
 *            from the given grain weights and comparing them with the acceptable range for the package.
 *
 * Time Complexity: O(1) per test case - constant time operations
 * Space Complexity: O(1) - only using a fixed number of variables
 */

#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
  int t, n, a, b, c, d;
  for (cin >> t; t--;) { // Process each test case
    cin >> n >> a >> b >> c >> d;
    // Check if the possible range of total weight [n*(a-b), n*(a+b)] overlaps with [c-d, c+d]
    puts(((a - b) * n > c + d || (a + b) * n < c - d) ? "No" : "Yes");
  }
}


// https://github.com/VaHiX/codeForces/