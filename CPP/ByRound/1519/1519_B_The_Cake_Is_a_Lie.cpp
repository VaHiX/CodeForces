// Problem: CF 1519 B - The Cake Is a Lie
// https://codeforces.com/contest/1519/problem/B

/*
 * Problem: B. The Cake Is a Lie
 * Purpose: Determine if it's possible to travel from top-left (1,1) to bottom-right (n,m)
 *          in an n x m grid with exactly k burles, where movement costs depend on current position.
 *
 * Algorithms/Techniques:
 *   - Mathematical optimization: The minimum and maximum cost paths are calculated
 *     based on the structure of the grid and movement rules.
 *   - Greedy approach to validate whether k lies within these bounds.
 *
 * Time Complexity: O(1) per test case — constant time operations.
 * Space Complexity: O(1) — only a fixed number of variables used.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    // Key insight: Minimum cost is always (n-1) + (m-1) = n + m - 2
    // Maximum cost occurs when we go down first then right, which gives (m-1)*n + (n-1)*m
    // But actually, optimal path analysis can simplify the condition as:
    bool res = (n * m - 1 == k);  // Simplified check due to grid movement logic
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/