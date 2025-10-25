// Problem: CF 1553 A - Digits Sum
// https://codeforces.com/contest/1553/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld\n", (n + 1) / 10);
  }
}
/*
Algorithm: Mathematical pattern recognition
Time Complexity: O(1) per test case
Space Complexity: O(1)

The key insight is that an integer x is "interesting" if S(x+1) < S(x).
This happens when x ends with a sequence of 9s.
For example:
- x = 9: S(9) = 9, S(10) = 1, so 9 is interesting
- x = 99: S(99) = 18, S(100) = 1, so 99 is interesting
- In general, numbers of the form 10^k - 1 are interesting

For any n, we need to count how many numbers from 1 to n are of the form 10^k - 1.
This is equivalent to counting how many powers of 10 (starting from 10^1) are <= n+1.
The answer is simply floor((n+1)/10).
*/

// https://github.com/VaHiX/codeForces/