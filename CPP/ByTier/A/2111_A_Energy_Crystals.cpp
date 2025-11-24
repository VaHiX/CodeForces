// Problem: CF 2111 A - Energy Crystals
// https://codeforces.com/contest/2111/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    long g(1), cnt(0); // g represents the maximum energy level that can be achieved with 'cnt' steps, starting from 0
    while (g < x) {    // incrementally build up the maximum possible value using the recurrence relation g = 2*g + 1
      g = 2 * g + 1;
      ++cnt;
    }
    printf("%ld\n", 2 * cnt + 3); // the number of operations needed is derived from the structure of the optimal charging strategy
  }
}
/*
Problem: A. Energy Crystals

Algorithm/Techniques: Mathematical analysis and binary representation concepts to simulate optimal charging process.

Time Complexity: O(log x) per test case — The loop runs until g >= x, and each step doubles g and adds 1, so it's logarithmic in x.
Space Complexity: O(1) — Only a constant amount of extra space is used.

The problem involves optimally charging three crystals under synchronization constraints. 
Each operation must maintain a valid energy ratio between crystals (ai ≥ floor(aj / 2)) for all pairs i,j.
The solution uses a recursive structure that mirrors the binary representation and optimal growth pattern.
*/

// https://github.com/VaHiX/codeForces/