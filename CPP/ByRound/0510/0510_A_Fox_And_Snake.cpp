// Problem: CF 510 A - Fox And Snake
// https://codeforces.com/contest/510/problem/A

/*
 * Code Purpose: This program draws a snake pattern on an n x m grid.
 * The snake starts at (1,1) and moves right, then down two rows, then left,
 * repeating this pattern to form a zigzag snake pattern.
 *
 * Algorithm/Techniques: 
 * - Iterates through each row and determines the pattern based on row index.
 * - For even rows (0-indexed), fills the entire row with '#'.
 * - For odd rows, checks modulo 4 to determine tail or head of the snake.
 * 
 * Time Complexity: O(n * m) - Each cell is visited once.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */

#include <cstdio>
int main() {
  int n, m;
  scanf("%d %d\n", &n, &m);
  for (int p = 0; p < n; p++) {
    if (p % 2 == 0) { // Even rows (0-indexed) are filled completely with '#'
      for (int k = 0; k < m; k++) {
        printf("#");
      };
      puts(""); // Print newline after the row
    } else if (p % 4 == 1) { // Odd rows with mod 4 == 1: tail of snake at the end
      for (int k = 0; k < m - 1; k++) {
        printf(".");
      };
      puts("#"); // Place '#' at the end of the row
    } else if (p % 4 == 3) { // Odd rows with mod 4 == 3: head of snake at the start
      printf("#"); // Place '#' at the start of the row
      for (int k = 0; k < m - 1; k++) {
        printf(".");
      };
      puts(""); // Print newline after the row
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/