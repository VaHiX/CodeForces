// Problem: CF 1726 B - Mainak and Interesting Sequence
// https://codeforces.com/contest/1726/problem/B

/*
Code Purpose:
This program determines whether there exists an "interesting" sequence of length n with sum m,
and if so, outputs such a sequence. An interesting sequence satisfies the condition that
for each element, the XOR of all elements strictly less than it equals zero.

Algorithm:
The key insight is:
- For n = 1, any single-element sequence [m] is interesting.
- For n > 1, we can construct a sequence mostly of 1s, with the last two elements adjusted
  to make the full sum equal to m and maintain the interesting property.
- We also use a parity check: if n is even, m must be even; if n is odd, m can be odd or even.

Time Complexity: O(n) per test case, as we construct the sequence in linear time.
Space Complexity: O(1) extra space, not counting the output.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    if (n > m) {
      // If n > m, it's impossible to have a sequence of positive integers summing to m
      puts("NO");
      continue;
    } else if (n % 2 == 0 && m % 2) {
      // If n is even but m is odd, it's impossible due to parity constraint
      puts("NO");
      continue;
    } else if (n == 1) {
      // For n=1, just output m itself
      printf("YES\n%ld\n", m);
      continue;
    }
    puts("YES");
    // Print n-2 ones
    for (long p = 0; p < n - 2; p++) {
      printf("1 ");
    }
    if (n % 2) {
      // If n is odd, we can place 1 and (m - n + 1) at the end
      printf("1 %ld\n", m - n + 1);
    } else {
      // If n is even, we split (m - n + 2) equally into two parts
      printf("%ld %ld\n", (m - n + 2) / 2, (m - n + 2) / 2);
    }
  }
}


// https://github.com/VaHiX/CodeForces/