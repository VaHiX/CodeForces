// Problem: CF 1093 A - Dice Rolling
// https://codeforces.com/contest/1093/problem/A

/*
 * Problem: Mishka wants to get exactly x points by rolling a dice with faces showing
 *          integers from 2 to 7. The task is to find any number of rolls that can
 *          produce exactly x points.
 *
 * Approach:
 * - Each roll contributes between 2 and 7 points.
 * - To minimize the number of rolls, we want to maximize the points per roll.
 * - The maximum points per roll is 7.
 * - Therefore, the minimum number of rolls to achieve x points is floor(x / 7).
 * - But we can also use combinations of 2 to 7 points.
 * - If x is even, we can always use only 2s (e.g., x=2 -> 1 roll, x=4 -> 2 rolls etc.).
 * - The key insight is that we can always find a solution with at most x/2 rolls:
 *   - Use 2s as much as possible, so the number of rolls is floor(x / 2).
 *   - This works because 2 is the minimum face value and x >= 2.
 * 
 * Time Complexity: O(n), where n is the number of test cases.
 * Space Complexity: O(1), constant extra space.
 */

#include <stdio.h>
int main() {
  int n, s;
  scanf("%d", &n);
  while (n--) {
    scanf("%d", &s);
    printf("%d\n", s / 2);  // Output the minimum number of rolls needed.
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/