// Problem: CF 536 A - Tavas and Karafs
// https://codeforces.com/contest/536/problem/A

/*
 * Problem: Tavas and Karafs
 * Algorithm: Binary Search on the answer
 * Time Complexity: O(n * log(max_height)) where n is number of queries and max_height is up to 10^6
 * Space Complexity: O(1) - only using a few variables
 *
 * The sequence of karafs heights is defined as s[i] = A + (i-1) * B
 * For each query (l, t, m), we need to find the largest r such that we can eat
 * karafs from index l to r using at most t operations, where each operation
 * can decrease at most m karafs by 1.
 *
 * The key idea is to binary search on r (the end index), and for each candidate
 * r, compute how many operations are needed to eat karafs from l to r.
 * The number of operations required is:
 *   sum = (s[l] + s[l+1] + ... + s[r]) / m, rounded up
 * This sum can be computed using arithmetic progression formula.
 *
 * The code uses a binary search to find the largest r satisfying the constraint.
 */

#include <stdio.h>
long long int MAX = 1;
int main() {
  for (int i = 1; i <= 14; i++)
    MAX *= 10;
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  for (int i = 1; i <= c; i++) {
    int d, e, f;
    scanf("%d%d%d", &d, &e, &f);
    long long int min = d, max = 1234567;
    long long int ans = -1;
    while (min <= max) {
      long long int h = (min + max) / 2;
      // Calculate the sum of heights from index d to h using arithmetic progression
      // s[d] + s[d+1] + ... + s[h] = (h - d + 1) * (a + (h - d + 1) * b / 2) 
      // However, the formula in code appears to be adapted to avoid overflow:
      long long int S1 =
          ((a * (h - d + 1) + (h + d - 2) * (h - d + 1) * b / 2) - 1) / f + 1;
      long long int S2 = S1 > a + (h - 1) * b ? S1 : a + (h - 1) * b;
      // Check if this number of operations is within the limit t
      if (S2 <= e) {
        ans = h;
        min = h + 1;  // Try to find a larger r
      } else
        max = h - 1;  // Try a smaller r
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/