// Problem: CF 1467 A - Wizard of Orz
// https://codeforces.com/contest/1467/problem/A

/*
Algorithm: Wizard of Orz
Techniques: Greedy, Simulation, Mathematical Construction

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding output

This problem asks us to find the largest possible n-digit number formed by pausing exactly one panel
among n panels that cycle through digits 0-9. When a panel is paused, it shows the digit that was
displayed on it at that moment, and adjacent panels are paused after 1, 2, ... seconds respectively.

To maximize the result:
- We should pause a panel that has a large digit (ideally 9).
- For n >= 1: The first panel can contribute '9' if paused at time 0.
- For n >= 2: The second panel can contribute '8' if paused at time 0, because it will be paused one second later and will show 9 - 1 = 8.
- For further positions (p + 2 < n), we construct digits greedily by using increasing values modulo 10.

The approach:
- First print '9' if n >= 1
- Then print '8' if n >= 2
- Then fill the rest with increasing values mod 10 starting from 9 for the remaining positions

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n >= 1) {
      printf("9"); // First panel shows '9' when paused at time 0
    }
    if (n >= 2) {
      printf("8"); // Second panel shows '8' when paused at time 0 and gets paused one second later, showing 9-1=8
    }
    for (long p = 0; p + 2 < n; p++) {
      printf("%ld", (9 + p) % 10); // Fill remaining positions with increasing digits mod 10
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/