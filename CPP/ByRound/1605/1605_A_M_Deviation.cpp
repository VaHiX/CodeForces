// Problem: CF 1605 A - A.M. Deviation
// https://codeforces.com/contest/1605/problem/A

/*
 * Problem: Arithmetic Mean Deviation
 * Algorithm: Mathematical analysis of the deviation formula
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The key insight is that we want to minimize d(a1, a2, a3) = |a1 + a3 - 2*a2|.
 * Through allowed operations (increment one value, decrement another), we can adjust values
 * but the sum a1 + a3 + a2 remains constant.
 *
 * The minimum possible value of |a1 + a3 - 2*a2| is equivalent to finding:
 *   (a1 + a3 - 2*a2) mod 3, because shifting values maintains the parity
 *   with respect to divisibility by 3.
 *
 * If (a1 + a3 - 2*a2) % 3 == 0, then we can make it zero.
 * Otherwise, the minimal absolute deviation is 1.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, z;
    scanf("%ld %ld %ld", &x, &y, &z);
    // Check if the expression (x + z - 2*y) is divisible by 3
    puts(((x + z - 2 * y) % 3 == 0) ? "0" : "1");
  }
}


// https://github.com/VaHiX/codeForces/