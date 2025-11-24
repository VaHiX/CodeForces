// Problem: CF 1549 A - Gregor and Cryptography
// https://codeforces.com/contest/1549/problem/A

/*
 * Problem: Gregor and Cryptography
 * 
 * Purpose: For a given prime number P, find two bases a and b such that:
 *          P mod a = P mod b, where 2 <= a < b <= P.
 * 
 * Algorithm:
 *   - Observe that P mod a = P mod b implies that P - (P mod a) = P - (P mod b)
 *     which means the quotients when dividing P by a and b are equal.
 *   - Let's denote Q = P / a and R = P mod a, then P = Q * a + R.
 *   - Similarly, P = Q * b + R.
 *   - From this, we can derive a simple solution.
 *   - If we set a = (P - 1) / 2 and b = P - 1, then:
 *     - P mod a = P mod (P - 1) = 1 (since P > P - 1, remainder is P - (P - 1) = 1)
 *     - P mod b = P mod (P - 1) = 1 (as above)
 *   - So this yields a valid pair a, b as long as P - 1 > (P - 1) / 2 => P > 3.
 *   - This condition is guaranteed because input P >= 5.
 * 
 * Time Complexity: O(t), where t is number of test cases; each case requires constant time.
 * Space Complexity: O(1), only using a fixed amount of space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long p;
    scanf("%ld", &p);
    printf("%ld %ld\n", (p - 1) / 2, (p - 1));  // Outputs a = (P - 1) / 2, b = P - 1
  }
}


// https://github.com/VaHiX/CodeForces/