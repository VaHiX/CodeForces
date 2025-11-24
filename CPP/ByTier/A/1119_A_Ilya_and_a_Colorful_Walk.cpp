// Problem: CF 1119 A - Ilya and a Colorful Walk
// https://codeforces.com/contest/1119/problem/A

#include <stdio.h>
int n, a[300000], i, j;
int main() {
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", a + i);
    if (a[i] != a[0]) // Track the first position where color differs from the first house
      j = i;
  }
  for (i = 0; i < n; i++)
    if (a[i] != a[n - 1]) // Find first position from the left where color differs from the last house
      break;
  if (j > n - i - 1) // Compare distances from first and last house to first differing positions
    printf("%d\n", j);
  else
    printf("%d\n", n - i - 1);
}
/*
Problem: Ilya and a Colorful Walk

Description:
Given a sequence of colored houses, find the maximum distance between two houses of different colors.

Algorithm:
The solution finds the maximum possible distance between two houses with different colors by:
1. Finding the first position where color differs from the first house (j)
2. Finding the first position from the right where color differs from the last house (i)
3. Taking the maximum of these two distances

Time Complexity: O(n) - Single pass through array
Space Complexity: O(1) - Only using constant extra space (excluding input array)

Techniques:
- Two-pointer approach to determine boundary colors
- Linear scan with early termination conditions
*/

// https://github.com/VaHiX/codeForces/