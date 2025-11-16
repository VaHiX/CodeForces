// Problem: CF 1690 A - Print a Pedestal (Codeforces logo?)
// https://codeforces.com/contest/1690/problem/A

/*
Code Purpose:
This program solves the problem of building a pedestal using exactly n blocks, where the pedestal consists of three platforms for 1st, 2nd, and 3rd places. The heights must satisfy: h3 < h2 < h1 and all heights > 0. The goal is to minimize h1 among all valid configurations.

Algorithm:
- The idea is to distribute n blocks into three heights h1, h2, h3 such that h3 < h2 < h1 and h1 + h2 + h3 = n.
- To minimize h1, we try to make h1 as small as possible while ensuring that h2 and h3 can be chosen accordingly.
- We use modular arithmetic to evenly distribute the blocks with minimal increments to achieve distinct positive integers for h1, h2, h3.

Time Complexity: O(1) per test case
Space Complexity: O(1)

Approach:
- Based on n % 3, we handle different cases to find optimal distribution:
  - If n % 3 == 0: assign base value and increment h1 and h2.
  - If n % 3 == 1: adjust base values and set increments accordingly.
  - If n % 3 == 2: adjust base values and set increments accordingly.
- The solution ensures h3 < h2 < h1 and h1 + h2 + h3 = n.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a, b, c;  // a = h3, b = h2, c = h1
    if (n % 3 == 0) {
      a = b = c = (n - 3) / 3;  // Start with base value
      a += 1;  // Increase h3
      b += 2;  // Increase h2
    } else if (n % 3 == 1) {
      a = b = c = (n - 4) / 3;  // Start with base value
      a += 1;  // Increase h3
      b += 3;  // Increase h2
    } else if (n % 3 == 2) {
      a = b = c = (n - 5) / 3;  // Start with base value
      a += 2;  // Increase h3
      b += 3;  // Increase h2
    }
    printf("%ld %ld %ld\n", a, b, c);
  }
}


// https://github.com/VaHiX/CodeForces/