// Problem: CF 2090 A - Treasure Hunt
// https://codeforces.com/contest/2090/problem/A

/*
A. Treasure Hunt
time limit per test1 second
memory limit per test256 megabytes

Code Purpose:
This code determines whether Little B or Little K will dig up the treasure first,
given that they take turns digging, starting with Little B. Each day, Little B
digs x meters and Little K digs y meters. The total depth dug after each day is
accumulated, and the person who causes the total to exceed 'a' meters (the treasure's depth) wins.

Algorithm/Techniques:
- Simulation of turn-based digging: we simulate the process until the total depth exceeds 'a'.
- Optimization using modular arithmetic: instead of simulating all turns, we only simulate
  up to one cycle of turns (x + y), since after that, the pattern repeats.
- Efficiently check who digs first in a cycle by computing remaining depth modulo (x + y).

Time Complexity:
O(1) - We perform constant time operations per test case, regardless of input size.

Space Complexity:
O(1) - Only using a fixed amount of space for variables.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, a;
    scanf("%ld %ld %ld", &x, &y, &a);
    a %= (x + y);  // Reduce to equivalent position within one full cycle (B then K)
    puts(a < x ? "NO" : "YES");  // If a is less than x, B digs first in this partial turn; otherwise K does
  }
}


// https://github.com/VaHiX/codeForces/