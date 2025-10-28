// Problem: CF 1447 B - Numbers Box
// https://codeforces.com/contest/1447/problem/B

/*
Problem: Numbers Box
Algorithm: Greedy with manipulation of signs
Time Complexity: O(n * m) per test case
Space Complexity: O(1)

Approach:
- For each grid, we calculate the sum of absolute values of all elements.
- Count how many negative numbers exist.
- If there's an odd number of negatives, we must leave one negative, so we subtract twice the smallest absolute value from the total.
- This greedy approach works because we can flip signs of adjacent cells to move negativity around and reduce the total loss.

Key insight:
If an odd number of elements are negative, we must keep exactly one negative element. To minimize the impact on the sum, we choose the element with the smallest absolute value.

Sample Input-Output:
Input:
2
2 2
-1 1
1 1
3 4
0 -1 -2 -3
-1 -2 -3 -4
-2 -3 -4 -5

Output:
2
30
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long mn(107), cnt(0), res(0);
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        long x;
        scanf("%ld", &x);
        if (x < 0) {
          x = -x;
          ++cnt; // Count negative numbers
        }
        mn = (mn < x) ? mn : x; // Track minimum absolute value
        res += x; // Add absolute value to total sum
      }
    }
    // If odd number of negatives, we must leave one negative
    // So subtract 2 * min absolute value from sum
    res -= 2 * (cnt % 2) * mn;
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/