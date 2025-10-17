// Problem: CF 2000 B - Seating in a Bus
// https://codeforces.com/contest/2000/problem/B

/*
 * Problem: B. Seating in a Bus
 *
 * Purpose: Determine whether all passengers followed the bus seating rules.
 *          A passenger can only sit in a seat adjacent to an already occupied seat,
 *          unless the bus is empty, in which case any seat is allowed.
 *
 * Algorithm:
 *   - Simulate the seating process using two pointers `left` and `right`.
 *     These represent the leftmost and rightmost occupied seats.
 *   - For each new passenger:
 *       - If their chosen seat matches `left - 1`, decrement `left`.
 *       - If their chosen seat matches `right + 1`, increment `right`.
 *       - Otherwise, the rule is violated.
 *
 * Time Complexity: O(n) per test case, where n is the number of passengers.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x;
    scanf("%ld", &x);
    long left(x - 1), right(x + 1); // Initialize bounds around first seat
    bool rule(true);
    for (long p = 1; p < n; p++) {
      scanf("%ld", &x);
      if (x == left) {
        --left; // Expand left boundary
      } else if (x == right) {
        ++right; // Expand right boundary
      } else {
        rule = false; // Violation of seating rule
      }
    }
    puts(rule ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/