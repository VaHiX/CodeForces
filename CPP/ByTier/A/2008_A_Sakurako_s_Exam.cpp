// Problem: CF 2008 A - Sakurako's Exam
// https://codeforces.com/contest/2008/problem/A

/*
 * Problem: A. Sakurako's Exam
 *
 * Purpose:
 *   Determines whether it's possible to assign '+' or '-' signs to an array
 *   consisting of `a` ones and `b` twos such that the total sum equals zero.
 *
 * Algorithm/Techniques:
 *   - Mathematical analysis of parity and summation constraints.
 *   - For a valid solution, the total sum must be even (since we can split it into two equal parts).
 *     - Total sum = a*1 + b*2 = a + 2*b
 *     - To achieve zero sum, we must be able to partition the array into two subsets with equal sums.
 *     - Therefore, (a + 2*b) must be even and non-negative.
 *     - Also, if `a` is odd, then we cannot balance it with pairs of 2s alone.
 *   - The condition used in code:
 *     - If a is odd, or if b is odd and a < 2, then it's impossible.
 *     - Otherwise, it is possible.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    // Check if it's possible to make sum zero
    // Condition: (a is even) AND (if b is odd, then a >= 2)
    puts(((a % 2) || (b % 2 && a < 2)) ? "NO" : "YES");
  }
}


// https://github.com/VaHiX/codeForces/