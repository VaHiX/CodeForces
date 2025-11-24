// Problem: CF 2092 E - She knows...
// https://codeforces.com/contest/2092/problem/E

/*
E. She knows...
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm: 
- The problem asks to count the number of ways to color the remaining green cells (not in the k given cells)
  such that the number of adjacent cells with different colors is even.
- Key insight:
  - Consider a checkerboard coloring where each cell (i,j) has a color depending on (i+j) % 2.
  - For any valid configuration (even number of adjacent different pairs), 
    we can think of it as having all boundary edges forming an "even" parity.
  - If we color the fixed k cells, then there are at most two possible colorings that satisfy the condition,
    depending on whether the total number of "odd" edges among boundary fixed cells is even or odd.
- Time complexity: O(k log n) per test case due to modular exponentiation and iteration over k.
- Space complexity: O(1) — only constant extra space used.

Techniques:
- Modular exponentiation using binary exponentiation (qp function)
- Bit manipulation for parity handling
- Efficient handling of large inputs up to 1e9 by avoiding full matrix operations

*/

#include <iostream>
using namespace std;
const int mod = 1e9 + 7;          // Modulo value
const int iv = 5e8 + 4;           // Modular inverse of 2
using ll = long long;

// Fast modular exponentiation: returns (x^y) % mod
ll qp(ll x, ll y, ll z = 1) {
  while (y) {
    if (y & 1)
      z = x * z % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return z;
}

// Global variables
ll _, n, m, k, x, y, c, z, w, s;

// Function to determine if a cell is on the border
inline int chk(ll x, ll y) {
  // Returns true if cell (x,y) is a corner or edge cell 
  if (x == 1 || x == n)
    return y != 1 && y != m;
  return y == 1 || y == m;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> _;

  while (_--) {
    cin >> n >> m >> k;

    w = 1;                         // Tracks if we're in even or odd state
    z = 2 * (n + m - 4);          // Total edges on the border
    s = n * m - k;                // Number of green cells left to color

    while (k--) {
      cin >> x >> y >> c;

      if (chk(x, y)) {            // If cell is on edge/border
        z--;                      // Decrease count of edges
        if (c)                    // If it's black (1), toggle state
          w ^= 1;
      }
    }

    // Output based on the remaining edge count z:
    // If z remains 0: all border cells have been evaluated -> answer = w * 2^s
    // Else: we must account for one less degree of freedom -> answer = 2^(s-1)
    if (!z)
      cout << w * qp(2, s) << '\n';
    else
      cout << qp(2, s - 1) << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/