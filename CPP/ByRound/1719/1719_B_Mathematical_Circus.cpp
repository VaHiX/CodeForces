// Problem: CF 1719 B - Mathematical Circus
// https://codeforces.com/contest/1719/problem/B

/*
Code Purpose:
This program determines whether it's possible to split integers from 1 to n into pairs (a, b)
such that for each pair, the value (a + k) * b is divisible by 4. If possible, it outputs the pairs.
The algorithm uses modular arithmetic and greedy pairing to construct valid pairs efficiently.

Algorithms/Techniques:
- Modular arithmetic to check divisibility conditions
- Greedy pairing strategy based on residue classes modulo 4
- Special handling for edge cases

Time Complexity: O(n) per test case, where n is the input number. Since sum of n over all test cases is bounded by 2*10^5, total time complexity is O(N) where N is the sum of n.
Space Complexity: O(1) - constant extra space used, not counting input/output storage.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if (k % 4 == 0) {
      puts("NO");
      continue;
      ;
    }
    puts("YES");
    for (long p = 1; p <= n; p += 2) {
      long a(p), b(p + 1);
      long tst = ((p + k) * (p + 1)) % 4;
      if (tst) {
        printf("%ld %ld\n", b, a);
      } else {
        printf("%ld %ld\n", a, b);
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/