// Problem: CF 1386 A - Colors
// https://codeforces.com/contest/1386/problem/A

/*
 * Problem: Find the critical color difference C using binary search and 
 *          smart query strategy in an interactive setting.
 * 
 * Algorithm:
 * - The key insight is to use binary search to locate C.
 * - First, determine an upper bound for C by querying colors that are far apart.
 * - Then, use binary search on the range [1, N] to find the exact value of C.
 * 
 * Time Complexity: O(log N) per test case due to binary search.
 * Space Complexity: O(1) - only a few variables are used.
 */

#include <iostream>

using namespace std;
int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    long long n, k, p = 1, l = 1, r, u = 1, s;
    cin >> n;
    k = n >> 1, r = n - 1, s = n;
    // This loop appears to be setting up a specific query strategy 
    // to find a rough estimate of where C might be located.
    while (k < n - 1) {
      p += (k + n >> 1) - k;
      for (int i = 0; i < 2; i++)
        k = k + n >> 1;
    }
    // First query to establish baseline behavior
    cout << "? " << p << endl;
    cin >> k;
    // Binary search for the exact value of C
    while (l <= r) {
      long long m = l + r >> 1;  // Midpoint of current search range
      p += m * u;                // Adjust query based on search direction
      cout << "? " << p << endl;
      cin >> k;
      // If Archie notices the change (k == 1), C is at most m, so search left
      // Otherwise, C is greater than m, so search right
      k ? (s = m, r = m - 1) : (l = m + 1);
      u = -u;  // Toggle direction for next query
    }
    cout << "= " << s << endl;  // Output the determined critical value C
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/