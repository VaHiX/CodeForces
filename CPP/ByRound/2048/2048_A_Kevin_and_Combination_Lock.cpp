// Problem: CF 2048 A - Kevin and Combination Lock
// https://codeforces.com/contest/2048/problem/A

/*
 * Problem: Kevin and Combination Lock
 * Algorithm/Techniques: Mathematical analysis, modular arithmetic
 *
 * The problem asks whether a given number x can be reduced to 0 using two allowed operations:
 * 1. Remove two consecutive '3's if x ≠ 33.
 * 2. Subtract 33 from x if x ≥ 33.
 *
 * Key Insight:
 * - Operation 2 allows us to subtract 33 repeatedly.
 * - Operation 1 removes pairs of '3's, which means we're essentially removing multiples of 33
 *   in a way that does not affect the value modulo 33.
 * - If x is divisible by 33, then we can reduce it to 0 using operation 2 only.
 * - Otherwise:
 *   - If we can remove all '3's without violating conditions, then the remaining number
 *     must also be divisible by 33 to reach 0.
 *   - But if any such sequence leads to a non-zero remainder modulo 33, it cannot be solved.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    long n; // input number
    scanf("%ld", &n);
    puts(n % 33 ? "NO" : "YES"); // if n is divisible by 33, output YES, else NO
  }
}


// https://github.com/VaHiX/codeForces/