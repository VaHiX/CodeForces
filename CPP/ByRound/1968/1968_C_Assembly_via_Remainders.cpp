// Problem: CF 1968 C - Assembly via Remainders
// https://codeforces.com/contest/1968/problem/C

/*
Purpose: 
This code solves the problem of reconstructing an array 'a' from given remainders 'x', where each x[i] is the remainder when a[i] is divided by a[i-1]. 
The approach is to start with an initial value for a[1], then compute subsequent values such that the modulo condition holds.

Algorithms/Techniques:
- Greedy construction: Start with a known value and iteratively compute next values to satisfy the modulo constraints.
- Mathematical reasoning: For each step, choose a[i] such that a[i] % a[i-1] = x[i], which can be achieved by setting a[i] = a[i-1] * k + x[i] for some suitable k, or simply use a[i] = a[i-1] + x[i] in many cases.

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input/output storage

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x;
    scanf("%ld", &x);
    long a(1501); // Initialize a[1] to a fixed large enough value to ensure a[2] > x[2]
    printf("%ld %ld ", a - x, a); // Output first two values: a[1] = a - x, a[2] = a
    for (long p = 2; p < n; p++) {
      scanf("%ld", &x);
      a += x; // Compute new a[i] such that a[i] % a[i-1] = x[i]
      printf("%ld ", a);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/