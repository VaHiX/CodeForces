// Problem: CF 1954 A - Painting the Ribbon
// https://codeforces.com/contest/1954/problem/A

/*
 * Problem: A. Painting the Ribbon
 * Algorithm: Greedy + Mathematical Analysis
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Alice paints the ribbon with m colors, then Bob can repaint at most k parts.
 * Alice wants to prevent Bob from making all parts the same color.
 * We determine if Alice can arrange her painting such that no matter how Bob repaints up to k parts,
 * he cannot make all parts uniform.
 *
 * Key Observation:
 * - If there are m colors and n parts, in the worst case, we try to distribute n parts into m groups
 *   with as equal sizes as possible.
 * - The minimum number of parts that must remain unchaged for Bob to be unable to make all same color:
 *   This is computed as (m - 1) * (n / m) + (n % m > 0) * (n % m - 1).
 * - If k < need, then Alice wins.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    // Compute the minimum number of parts Alice needs to leave in different groups
    // so that Bob cannot make all parts the same color with at most k changes
    long need = (m - 1) * (n / m) + (n % m > 0) * (n % m - 1);
    // If Bob can change fewer than 'need' parts, he can't make all colors same
    puts(k < need ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/