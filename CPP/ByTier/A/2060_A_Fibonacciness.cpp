// Problem: CF 2060 A - Fibonacciness
// https://codeforces.com/contest/2060/problem/A

/*
Problem: Fibonacciness
Task: Given an array of 5 integers where a1, a2, a4, a5 are known, and a3 is free to set,
find the maximum number of valid Fibonacci-like relations among the first three elements.
A relation a[i+2] = a[i] + a[i+1] is valid if it holds.

Algorithms/Techniques:
- Brute-force analysis of possible values for a3 to maximize valid conditions
- Check all combinations of 3 conditions that can be satisfied by setting a3 optimally

Time Complexity: O(1) per test case — constant number of calculations
Space Complexity: O(1) — only using a fixed amount of variables
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, d, e;
    scanf("%ld %ld %ld %ld", &a, &b, &d, &e);
    // f1: checks if a3 = d - 2*b and a4 = a + b + d
    int f1 = (d == a + 2 * b) + (e == a + b + d);
    // f2: checks if a3 = d - 2*b and 2*a4 = a2 + a5
    int f2 = (d == a + 2 * b) + (2 * d == b + e);
    // f3: checks if a5 = a + b + a4 and 2*a4 = a2 + a5
    int f3 = (e == a + b + d) + (2 * d == b + e);
    // Take maximum of the three conditions scored
    int f = (f1 > f2 ? f1 : f2);
    f = (f > f3 ? f : f3);
    printf("%d\n", 1 + f);  // Add 1 because we're counting valid indices from 1 to 3, but the problem says 0-based
  }
}


// https://github.com/VaHiX/codeForces/