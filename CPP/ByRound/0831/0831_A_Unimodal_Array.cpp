// Problem: CF 831 A - Unimodal Array
// https://codeforces.com/contest/831/problem/A

/*
 * Code Purpose: Checks if an array is unimodal.
 * An array is unimodal if it is strictly increasing at first,
 * then constant, and then strictly decreasing.
 * 
 * Algorithm:
 * - Traverse the array once, tracking the state of the sequence:
 *   - state = 0: strictly increasing
 *   - state = 1: constant
 *   - state = 2: strictly decreasing
 * - For each element, validate the transitions according to the rules.
 * 
 * Time Complexity: O(n), where n is the number of elements in the array.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long prev;
  scanf("%ld", &prev);
  int state(0);  // 0: increasing, 1: constant, 2: decreasing
  bool unimodal(true);
  for (long p = 1; p < n; p++) {
    long x;
    scanf("%ld", &x);
    // If current element is greater than previous and we're not in the increasing phase, invalid
    if (x > prev && state > 0) {
      unimodal = false;
      break;
    } else if (x == prev) {
      // If we have not yet entered the constant phase, enter it
      if (state == 0) {
        state = 1;
      } else if (state > 1) {
        // If we're already in decreasing phase, this is invalid
        unimodal = false;
        break;
      }
    } else if (x < prev) {
      // Enter the decreasing phase
      state = 2;
    }
    prev = x;
  }
  puts(unimodal ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/