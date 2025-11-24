// Problem: CF 1777 A - Everybody Likes Good Arrays!
// https://codeforces.com/contest/1777/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0);
    long prev(0);
    scanf("%ld", &prev);
    prev %= 2; // Convert the first element to 0 if even, 1 if odd
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      x %= 2; // Convert current element to 0 if even, 1 if odd
      cnt += (x == prev); // If parity matches previous, increment operations needed
      prev = x; // Update previous parity
    }
    printf("%ld\n", cnt);
  }
}

/*
 * Problem: A. Everybody Likes Good Arrays!
 * Task: Find minimum operations to make an array "good" (adjacent elements have different parity).
 *
 * Algorithm:
 *   - Traverse the array and count how many adjacent elements have the same parity.
 *   - Each such pair requires one operation to merge into a single element.
 *   - The number of such pairs is the answer.
 *
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(1), only using a few variables for computation.
 */

// https://github.com/VaHiX/codeForces/