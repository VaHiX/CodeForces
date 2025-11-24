// Problem: CF 2002 A - Distanced Coloring
// https://codeforces.com/contest/2002/problem/A

/*
 * Problem: Distanced Coloring
 * Algorithm/Techniques: Grid coloring with distance constraint
 * 
 * The problem asks us to find the minimum number of colors to color an n×m grid such that
 * any two cells with the same color must have a Chebyshev distance (maximum of row/column difference) 
 * of at least k.
 * 
 * Key Insight:
 * The optimal strategy is to place colors in a grid pattern where each color occupies a 
 * k×k square region. Thus, the number of such non-overlapping regions needed is:
 * ceil(n/k) * ceil(m/k).
 * 
 * This can be computed simply as: (n + k - 1) / k * (m + k - 1) / k
 * However, in this implementation, a simpler approach is used:
 *   For each dimension, we take min(n,k) and min(m,k), then compute product.
 *   This works because the maximum number of colors needed corresponds to how many 
 *   non-overlapping k×k blocks fit or overlap in an n×m grid.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    // Compute minimum number of colors needed using the formula:
    // For an n x m grid with distance constraint k,
    // we place colors such that each color covers a k x k area.
    // The total number of colors is (n / k) * (m / k) rounded up.
    long res = (n < k ? n : k) * (m < k ? m : k);
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/