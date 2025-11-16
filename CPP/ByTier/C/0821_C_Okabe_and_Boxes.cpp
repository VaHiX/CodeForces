// Problem: CF 821 C - Okabe and Boxes
// https://codeforces.com/contest/821/problem/C

/*
 * Problem: C. Okabe and Boxes
 * 
 * Approach:
 * - Simulate the stack operations (add and remove)
 * - Track the expected removal order (1 to n)
 * - When removing a box, check if it's at the top of the stack
 * - If not, we must reorder the stack to make it possible to remove the next expected box
 * - Count the number of reordering operations needed
 * 
 * Key insight:
 * - We don't need to actually reorder the stack, just track when we have to
 * - If the top box doesn't match the expected removal number, we must reorder
 * - We can simulate reordering by clearing the stack (top = 0), incrementing the count
 * 
 * Time Complexity: O(2*n) = O(n) - Single pass through all commands
 * Space Complexity: O(n) - Stack storage for up to n boxes
 */

#include <stdio.h>
int main() {
  char op[10];
  int n, count = 0;
  int s[300005]; // Stack to hold box numbers
  scanf("%d", &n);
  int top = 0, j = 1; // top: stack pointer, j: expected removal number
  for (int i = 0; i < 2 * n; i++) {
    scanf("%s", op);
    if (op[0] == 'a') {
      // Add operation: push box number to stack
      scanf("%d", &s[++top]);
    } else {
      // Remove operation: check if the top of stack matches expected box number
      if (top) {
        if (s[top] == j)
          top--; // Box matches, remove from stack
        else {
          // Box doesn't match; need to reorder
          top = 0; // Clear stack to simulate reordering
          count++;
        }
      }
      j++; // Move to next expected box number
    }
  }
  printf("%d", count);
}


// https://github.com/VaHiX/CodeForces/