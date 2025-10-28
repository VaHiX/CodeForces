// Problem: CF 2096 D - Wonderful Lightbulbs
// https://codeforces.com/contest/2096/problem/D

/*
D. Wonderful Lightbulbs
Algorithm: XOR-based solution using properties of the operation.
Techniques: Bit manipulation, XOR, Gaussian elimination concept (implicit).
Time Complexity: O(n) per test case.
Space Complexity: O(1) excluding input.

The key insight is that each operation toggles 4 bulbs in a specific pattern.
By analyzing how these operations interact with XOR, we can deduce the original
position of the treasure using bitwise operations on coordinates.

The algorithm uses:
- XOR of all x-coordinates to find a component of the answer.
- XOR of (x + y) for all coordinates to get another relation.
- From there, compute one possible (s, t) such that s ^ x = s and t ^ (x + y) = t + s.

The operations are defined as toggling:
(x, y), (x, y+1), (x+1, y-1), (x+1, y)

Because each operation affects 4 positions, we can solve the problem
using XOR properties to determine a consistent and valid position of treasure.
*/

#include <stdio.h>

void solve() {
  int n;
  scanf("%i", &n);
  int a = 0, b = 0;
  for (int x, y, i = 0; i < n; ++i) {
    scanf("%i%i", &x, &y);
    a ^= x;              // XOR of all x coordinates
    b ^= (x + y);        // XOR of (x + y) for each coordinate
  }
  printf("%i %i\n", a, b - a);  // Output the possible treasure position
}

int main() {
  int t;
  scanf("%i", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/