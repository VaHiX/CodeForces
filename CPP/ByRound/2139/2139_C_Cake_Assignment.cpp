// Problem: CF 2139 C - Cake Assignment
// https://codeforces.com/contest/2139/problem/C

/*
C. Cake Assignment
Algorithms/Techniques: Binary representation manipulation, simulation using stack
Time Complexity: O(k) per test case
Space Complexity: O(k) due to the stack usage

The problem involves redistributing cakes between two people such that one ends up with exactly x cakes.
Operations allowed:
1. Chocola gives half her cakes to Vanilla (if Chocola has even number of cakes)
2. Vanilla gives half her cakes to Chocola (if Vanilla has even number of cakes)

This is modeled as a binary representation problem: we reverse the process from target state (x, 2^(k+1)-x) back to initial state (2^k, 2^k).
We simulate the reverse process using a stack to record operations.
*/

#include <stdio.h>
#include <algorithm>
#include <stack>

using namespace std;
int T;
long long k, x, y, sum;
stack<int> s;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%lld%lld", &k, &x);
    sum = 1ll << (k + 1); // Total number of cakes
    y = sum - x;          // Vanilla's desired cakes
    while (x != y) {
      if (x < y) {
        s.emplace(1);     // Operation 1: Chocola gives half to Vanilla
        y -= x;
        x <<= 1;          // Double Chocola's cakes (reverse of giving half)
      } else {
        s.emplace(2);     // Operation 2: Vanilla gives half to Chocola
        x -= y;
        y <<= 1;          // Double Vanilla's cakes (reverse of giving half)
      }
    }
    printf("%d\n", (int)s.size()); // Output number of operations
    for (; !s.empty(); s.pop())
      printf("%d ", s.top());     // Print the operations in reverse order
    putchar('\n');
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/