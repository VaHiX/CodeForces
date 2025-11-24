// Problem: CF 1932 B - Chaya Calendar
// https://codeforces.com/contest/1932/problem/B

/*
B. Chaya Calendar

Purpose:
This program calculates the year when all n signs of the apocalypse occur sequentially,
given their respective periodicities. Each sign occurs every 'a_i' years, and they must
occur in sequence, starting from the year after the previous sign occurred.

Algorithm:
- For each test case, we simulate the process of waiting for each sign to appear.
- We maintain a running total (ans) that represents the current year.
- For each sign with periodicity 'x', we compute the next occurrence year based on:
    - The current year divided by x gives how many full cycles have passed.
    - We add 1 to move to the next cycle, then multiply by x to get the next occurrence.
- This simulates sequential waiting for signs.

Time Complexity: O(n * t), where n is the number of signs and t is the number of test cases.
Space Complexity: O(1) — only a constant amount of extra space used.

Techniques:
- Modular arithmetic and cycle simulation
- Sequential accumulation of time based on periodic events

*/

#include <cstdio>
int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    long n; // number of signs
    scanf("%ld", &n);
    long ans(0); // maintains current year
    for (long p = 0; p < n; p++) {
      long x; // periodicity of current sign
      scanf("%ld", &x);
      // Compute next occurrence year after current ans
      ans = ((ans / x) + 1) * x;
    }
    printf("%ld\n", ans); // output final year when last sign occurs
  }
}


// https://github.com/VaHiX/codeForces/