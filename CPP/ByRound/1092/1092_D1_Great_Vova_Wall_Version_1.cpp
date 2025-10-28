// Problem: CF 1092 D1 - Great Vova Wall (Version 1)
// https://codeforces.com/contest/1092/problem/D1

/*
 * D1. Great Vova Wall (Version 1)
 *
 * Algorithm: Stack-based simulation with parity checking
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * The problem involves determining whether a sequence of wall heights can be made uniform
 * using two types of operations:
 *   1. Place a 2x1 brick horizontally between adjacent parts of equal height (increases both by 1)
 *   2. Place a 2x1 brick vertically on any part (increases that part by 2)
 *
 * Key insight:
 * - Horizontal bricks can only be placed where adjacent heights are equal
 * - Vertical bricks can increase any height by 2 (even numbers)
 * - After processing, if there's at most one element left in the stack,
 *   then all elements can potentially be made equal.
 *
 * The algorithm uses a stack to simulate the process:
 *   - If the stack is empty or the current element has different parity than the top of stack,
 *     push it onto the stack.
 *   - Otherwise, pop from the stack (this represents placing a horizontal brick).
 * - At the end, if more than one element remains in the stack, return "NO", else "YES".
 */

#include <stdio.h>
#include <stdlib.h>

int n, wa[200005], sta[200005], top;

int main() {
  scanf("%d", &n);
  top = 0;
  for (int i = 0; i < n; i++) {
    int k;
    scanf("%d", &k);
    // If stack is empty or k has different parity than the top element, push it
    if (!top || abs(sta[top] - k) & 1)
      sta[++top] = k;
    else
      // Otherwise, pop (simulate horizontal brick placement)
      top--;
  }
  // If more than one element remains, it's impossible to make all equal
  if (top > 1)
    printf("NO");
  else
    printf("YES");
  return 0;
}


// https://github.com/VaHiX/codeForces/