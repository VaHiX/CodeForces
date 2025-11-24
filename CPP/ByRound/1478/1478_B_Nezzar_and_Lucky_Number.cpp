// Problem: CF 1478 B - Nezzar and Lucky Number
// https://codeforces.com/contest/1478/problem/B

/*
B. Nezzar and Lucky Number
time limit per test
1 second
memory limit per test
512 megabytes
input
standard input
output
standard output
Nezzar's favorite digit among 1,...,9 is d. He calls a positive integer lucky if d occurs at least once in its decimal representation. 
Given q integers a1,a2,...,aq, for each 1 <= i <= q Nezzar would like to know if ai can be equal to a sum of several (one or more) lucky numbers.

Algorithm:
The approach checks whether a number can be expressed as a sum of lucky numbers (numbers containing digit d).
- For large numbers (> 10*d), we directly answer YES because any such number can always be represented as sum of lucky numbers.
- For small numbers, we try to decompose them by checking if the number minus some lucky number (like 10*p + d) is divisible by d. If so, then it's a valid decomposition.

Time Complexity: O(q * d)
Space Complexity: O(1)

*/
#include <cstdio>
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    long q;
    int d;
    scanf("%ld %d", &q, &d);
    while (q--) {
      long x;
      scanf("%ld", &x);
      if ((x > 10 * d) || (x % d == 0)) {
        puts("YES");
      } else {
        bool res(false);
        for (int p = 1; p < d; p++) {
          if (x < 10 * p + d) {
            break;
          }
          if ((x - (10 * p + d)) % d == 0) {
            res = true;
            break;
          }
        }
        puts(res ? "YES" : "NO");
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/