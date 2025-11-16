// Problem: CF 1358 A - Park Lighting
// https://codeforces.com/contest/1358/problem/A

/*
 * Problem: Park Lighting
 * Algorithm: Mathematical approach to compute minimum number of lanterns needed
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The park is an n x m grid of squares. Each lantern placed on a street can light
 * up at most 2 adjacent squares. To cover all squares with minimum lanterns,
 * we calculate the total number of squares (n * m) and divide by 2, rounding up.
 * This is equivalent to computing (n * m + 1) / 2 using integer division.
 *
 * Sample Input:
 * 5
 * 1 1
 * 1 3
 * 2 2
 * 3 3
 * 5 3
 *
 * Sample Output:
 * 1
 * 2
 * 2
 * 5
 * 8
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long res = (n * m + 1) / 2;  // Minimum lanterns needed to cover all squares
    printf("%ld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/