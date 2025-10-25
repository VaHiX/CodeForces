// Problem: CF 1499 A - Domino on Windowsill
// https://codeforces.com/contest/1499/problem/A

/*
 * Problem: Domino on Windowsill
 * Algorithm: Greedy + Mathematical Check
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1)
 *
 * The board is a 2×n grid where first k1 cells in first row and first k2 cells in second row are white.
 * We need to determine if we can place all w white dominoes and b black dominoes.
 *
 * Key Insight:
 * - Each domino covers exactly 2 adjacent cells.
 * - To place w white dominoes, we need at least 2*w white cells.
 * - To place b black dominoes, we need at least 2*b black cells.
 * - We check if total required white and black cells are less than or equal to available ones.
 *
 * Available white cells = k1 + k2
 * Available black cells = (n - k1) + (n - k2)
 *
 * The logic is:
 * - Check if 2*w <= k1 + k2 (enough white cells for w white dominoes)
 * - Check if 2*b <= (n - k1) + (n - k2) (enough black cells for b black dominoes)
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k1, k2;
    scanf("%ld %ld %ld", &n, &k1, &k2);
    long w, b;
    scanf("%ld %ld", &w, &b);
    // Check if we can place all dominoes
    bool ans = (2 * w <= k1 + k2 && 2 * b <= (n - k1) + (n - k2));
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/