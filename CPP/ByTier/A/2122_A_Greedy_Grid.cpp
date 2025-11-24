// Problem: CF 2122 A - Greedy Grid
// https://codeforces.com/contest/2122/problem/A

/*
 * Problem: Grid with No Greedy Max Path
 * Algorithm/Technique: Greedy Grid Analysis
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Approach:
 * - For an n×m grid, we need to determine if there exists a configuration 
 *   such that no greedy path achieves the maximum path sum.
 * - A greedy path always moves to the neighbor with the greater value (or either if equal).
 * - Key insight: If n = 1 or m = 1, then all paths are trivial (only one direction), so we cannot avoid
 *   the greedy behavior achieving max.
 * - If both n > 1 and m > 1, it's possible to construct a grid such that no greedy path achieves maximum.
 * - Special case: when n = 2 and m = 2, it is still impossible to create such a configuration.
 * 
 * So the condition for "NO" answer is:
 *   (n == 1) OR (m == 1) OR (n == 2 AND m == 2)
 * Otherwise, answer is "YES".
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    puts((n == 1 || m == 1 || (n == 2 && m == 2)) ? "NO" : "YES");
  }
}


// https://github.com/VaHiX/codeForces/