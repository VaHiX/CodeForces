// Problem: CF 1203 A - Circle of Students
// https://codeforces.com/contest/1203/problem/A

/*
 * Problem: A. Circle of Students
 * 
 * Purpose:
 *   Determines whether a group of students arranged in a circle can form a valid round dance.
 *   A valid round dance is either:
 *     - Clockwise: students 1,2,...,n appear consecutively in clockwise order.
 *     - Counterclockwise: students 1,2,...,n appear consecutively in counterclockwise order.
 *
 * Algorithms/Techniques:
 *   - Simulation of circular permutation
 *   - Two passes: one for clockwise and one for counterclockwise condition
 *   - Linear scan through the permutation to validate sequence
 *
 * Time Complexity:
 *   O(n) per query, where n is the number of students.
 *   We process each student exactly once in a linear sweep.
 *
 * Space Complexity:
 *   O(1) - Only using a constant amount of extra variables regardless of input size.
 */

#include <cstdio>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long n;
    scanf("%ld", &n);
    bool up(true), down(true); // Flags to check if sequence is valid in clockwise or counter-clockwise
    long prev;
    scanf("%ld", &prev); // Read first student index
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x); // Read next student index
      
      // Check for clockwise condition: each element should be one more than previous (with wraparound)
      if (up) {
        if (x == prev + 1) {
          // Valid increment
        } else if (x == 1 && prev == n) {
          // Wraparound from n to 1 in clockwise direction
        } else {
          up = false; // Invalid sequence for clockwise
        }
      }

      // Check for counter-clockwise condition: each element should be one less than previous (with wraparound)
      if (down) {
        if (x == prev - 1) {
          // Valid decrement
        } else if (x == n && prev == 1) {
          // Wraparound from 1 to n in counter-clockwise direction
        } else {
          down = false; // Invalid sequence for counter-clockwise
        }
      }
      prev = x; // Update previous value for next iteration
    }
    puts(up || down ? "YES" : "NO"); // Output result if either direction works
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/