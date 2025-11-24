// Problem: CF 1989 A - Catch the Coin
// https://codeforces.com/contest/1989/problem/A

/*
A. Catch the Coin

Algorithms/Techniques: Simulation and geometric reasoning

Time Complexity: O(n), where n is the number of coins. We process each coin once.
Space Complexity: O(1), only using a constant amount of extra space.

The problem involves determining whether Monocarp can collect each coin given:
- He starts at (0, 0)
- Each coin moves down by 1 unit after each move
- He can move in 8 directions (including diagonals)

Key insight:
To reach a coin at (x, y), Monocarp must be able to get to a position from which he can collect it,
in one move. Since coins fall down by 1 unit after each move, if a coin is at (x, y), then:
- If Monocarp can reach (x, y+1) in one move, he will collect it
- Otherwise, he cannot collect it

If he can reach the position that was originally at (x, y) when it is at (x, y+1),
this means if his current position is (x, y), then he can move to (x, y+1) after one second.
Hence, all valid positions are those such that:
- y >= -1

Because if a coin is below y = -1, it will be too far for Monocarp to reach even with
the first movement (since from center he can move up by at most 1 unit).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    puts(y >= -1 ? "YES" : "NO"); // Check if coin can be reached
  }
}


// https://github.com/VaHiX/codeForces/