// Problem: CF 1737 C - Ela and Crickets
// https://codeforces.com/contest/1737/problem/C

/*
Algorithm:
The problem involves determining if a cricket piece can reach a target square on
an n×n chessboard, given that the crickets are arranged in an "L" shape and move
by jumping over adjacent crickets.

Key Insight:
- A cricket can only move to a square that is immediately after another cricket
in a straight line (horizontal, vertical, or diagonal).
- The movement is like a knight move, but constrained to jump over other
crickets.

Approach:
1. Identify the "L" shape formed by three crickets.
2. Determine the two possible positions for the "anchor" cricket in the L-shape
(the one that is not at the tip).
3. Based on the anchor's position:
   - If the anchor is on the edge (either row 1 or n, or column 1 or n), then
it's only reachable from a position in the same row or column.
   - Otherwise, the problem reduces to checking if the target square is
reachable by checking parity (color) constraints.

Time Complexity: O(1) per test case
Space Complexity: O(1)
*/

#include <iostream>
#include <set>

using namespace std;
#define ll long long
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int r1, c1, r2, c2, r3, c3;
    cin >> r1 >> c1 >> r2 >> c2 >> r3 >> c3;
    int r4, c4;
    cin >> r4 >> c4;
    int x = 0, y = 0;
    set<int> st;
    set<int> st1;
    x = r1;
    y = c1;
    if (r2 == r3)
      x = r2;
    if (c2 == c3)
      y = c3;
    // If anchor is at the edge of the board
    if ((x == 1 || x == n) && (y == 1 || y == n))
      cout << ((x == r4 || y == c4) ? "YES" : "NO") << endl;
    else
      // Otherwise check for parity constraints
      cout << (((x % 2 != r4 % 2) && (y % 2 != c4 % 2)) ? "NO" : "YES") << "\n";
  }
}

// https://github.com/VaHiX/CodeForces/