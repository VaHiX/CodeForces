// Problem: CF 1772 E - Permutation Game
// https://codeforces.com/contest/1772/problem/E

/*
 * Purpose: Determine the winner of a permutation game between two players.
 * 
 * Algorithm:
 * - For each test case, we count how many elements are misplaced in ascending and descending order.
 * - We also keep track of how many elements are in "conflict" (i.e., misplaced in both orders).
 * - Using these counts, we decide the outcome based on a set of rules that simulate optimal play.
 * 
 * Time Complexity: O(n) per test case, where n is the size of the permutation.
 * Space Complexity: O(n) for storing the permutation and its reverse.
 * 
 * Techniques:
 * - Greedy simulation with counting
 * - Comparison of counts in ascending vs descending order
 */

#include <stdio.h>
int main() {
  long int b, f, s, bo, t, i, m, n, f1, x, s1;
  scanf("%ld", &m);
  for (n = 0; n < m; n++) {
    scanf("%ld", &b);
    long int a[b + 1], a1[b + 1]; // Arrays to store original and reversed permutation
    f = 0; // Count of elements misplaced in ascending order
    s = 0; // Count of elements misplaced in descending order
    bo = 0; // Count of elements that are misplaced in both orders
    for (i = 1; i <= b; i++) {
      scanf("%ld", &a[i]);
      a1[b - i + 1] = a[i]; // Reverse permutation for easier comparison
      t = 0;
      if (a[i] != i) { // Check if element i is at index i (ascending order)
        f++;
        t++;
      }
      if (a[i] != (b - i + 1)) { // Check if element is at its correct position in reverse (descending order)
        s++;
        if (t == 1) { // If element was already counted as misplaced in ascending, it's also misplaced in descending
          bo++;
        }
      }
    }
    if (f > s) { // If more misplaced in ascending than descending
      f = f - bo; // Remove conflicts
      if ((f == s) || (f < s)) { // If after removing conflicts, equal or less than descending
        printf("Tie\n");
      } else {
        printf("Second\n"); // Second player wins
      }
    } else if (f == s) { // If equal in both orders
      if (bo == 0) { // If no overlaps (conflicts)
        printf("First\n"); // First player wins
      } else {
        printf("Tie\n"); // Tie due to overlapping conflicts
      }
    } else { // If more misplaced in descending than ascending
      s = s - bo; // Remove conflicts
      if ((s < f)) { // If after removing conflicts, descending is less than ascending
        printf("Tie\n");
      } else {
        printf("First\n"); // First player wins
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/