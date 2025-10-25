// Problem: CF 1701 A - Grass Field
// https://codeforces.com/contest/1701/problem/A

/*
 * Problem: A. Grass Field
 * Algorithm/Techniques: Greedy approach with case analysis
 * 
 * Time Complexity: O(1) per test case (constant time operations)
 * Space Complexity: O(1) (only using a constant amount of extra space)
 *
 * Description:
 * Given a 2x2 grid where each cell is either 0 (empty) or 1 (grass),
 * we can cut grass by choosing any row or column to cut all grass in that row/column.
 * We need to find the minimum number of such moves to clear all grass.
 *
 * Key Observations:
 * - If all cells are 0, no moves needed (0).
 * - If there's at least one 1, we need at least one move.
 * - The maximum required moves is 2 (e.g., when grass is at positions (1,1) and (2,2)).
 * - If the sum of all cells is 4, it means all cells have grass, so we can cover with 2 moves
 *   by cutting row 1 and column 1.
 * - If the sum is > 0 but < 4, then at least one move is needed (the optimal answer is 1).
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long cnt(0);
    for (int row = 0; row < 2; row++) {
      for (int col = 0; col < 2; col++) {
        long x;
        scanf("%ld", &x); // Read each cell value
        cnt += x;         // Sum up all grass values
      }
    }
    long res(0);
    if (cnt == 4) {
      res = 2; // All cells have grass, requires 2 moves (cut row and column)
    } else if (cnt > 0) {
      res = 1; // At least one cell has grass, but not all, so 1 move suffices
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/