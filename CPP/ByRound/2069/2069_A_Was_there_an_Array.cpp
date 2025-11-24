// Problem: CF 2069 A - Was there an Array?
// https://codeforces.com/contest/2069/problem/A

/*
 * Problem: Determine if an array 'a' exists such that the given array 'b'
 *          represents its equality characteristic.
 *
 * Algorithms/Techniques:
 * - Greedy approach with forward checking.
 * - For each element in 'b', we check whether it's possible to form a valid
 *   sequence of 'a' elements, ensuring that b[i] = 1 means a[i] == a[i-1] and a[i] == a[i+1].
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) - only using a few variables for tracking state
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long pprev(0), prev(0); // Track previous two values in the sequence
    bool possible(true);    // Flag to track whether a valid array can be formed
    for (long p = 2; p < n; p++) {
      long x;
      scanf("%ld", &x);
      // If we have a pattern like [0, 0, 1], it's impossible to maintain valid continuity
      if (pprev && !prev && x) {
        possible = false;
      }
      pprev = prev;   // Shift window forward
      prev = x;       // Update current value
    }
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/