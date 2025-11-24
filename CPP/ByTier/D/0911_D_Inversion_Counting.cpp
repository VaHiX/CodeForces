// Problem: CF 911 D - Inversion Counting
// https://codeforces.com/contest/911/problem/D

/*
 * Code Purpose:
 *   This program determines the parity (odd/even) of the number of inversions
 *   in a permutation after a series of reverse queries on segments.
 *
 * Algorithm:
 *   - The initial number of inversions is computed using a nested loop approach.
 *   - For each query that reverses a segment [l, r], we compute how the inversion count changes.
 *   - The key insight is that reversing a segment of length k changes the number of inversions
 *     by an amount which depends on k % 4. Specifically:
 *     - If (r - l + 1) % 4 == 0 or 2, the parity of the inversion count does not change.
 *     - If (r - l + 1) % 4 == 1 or 3, the parity toggles.
 *   - This allows efficient updates without recomputing all inversions from scratch.
 *
 * Time Complexity:
 *   O(n^2) for initial inversion counting + O(m) for queries => O(n^2 + m)
 *
 * Space Complexity:
 *   O(n) for storing the permutation array.
 */
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  bool b(0);  // b tracks the parity of the number of inversions
  for (long p = 0; p < n; p++) {
    for (int q = p + 1; q < n; q++) {
      b = a[p] < a[q] ? b : (1 - b);  // Toggle parity if a[p] > a[q]
    }
  }
  long m;
  scanf("%ld", &m);
  while (m--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    // Determine if the parity changes based on segment length mod 4
    if ((r - l + 1) % 4 > 1) {
      b = 1 - b;  // Toggle the parity
    }
    puts(b ? "odd" : "even");  // Output the result
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/