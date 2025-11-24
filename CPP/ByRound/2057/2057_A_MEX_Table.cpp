// Problem: CF 2057 A - MEX Table
// https://codeforces.com/contest/2057/problem/A

/*
 * Problem: MEX Table
 * Algorithm/Technique: Greedy approach to maximize sum of MEX across rows and columns.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The solution observes that we want to maximize the sum of MEX values for each row and column.
 * Since the numbers from 0 to n*m - 1 are placed in the table, and MEX of a set is the smallest
 * non-negative integer not present in it:
 *
 * For any row/column with k elements, its MEX can be at most k.
 * To maximize sum, we try to minimize the number of times we get MEX = 0 (when 0 is missing).
 * A good strategy involves placing numbers such that as many rows/columns as possible contain 0,
 * but still allow for maximum total MEX value.
 *
 * In short, by analyzing optimal assignments:
 * - The answer turns out to be: max(n, m) + 1
 * - This is derived from the fact that in an optimal configuration,
 *   each row/column contributes a value close to the MEX of a full range up to n or m.
 */

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int a, b;
    cin >> a >> b;
    cout << max(a, b) + 1 << '\n'; // Output the maximum possible sum of MEX across all rows and columns
  }
}


// https://github.com/VaHiX/codeForces/