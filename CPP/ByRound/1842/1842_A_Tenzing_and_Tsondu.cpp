// Problem: CF 1842 A - Tenzing and Tsondu
// https://codeforces.com/contest/1842/problem/A

#include <cstdio>
// Flowerbox:
// Problem: A. Tenzing and Tsondu
// Purpose: Determine the winner of a game between Tsondu and Tenzing based on monster ability values.
//          Each player has monsters with given ability values. Players alternate turns, with Tsondu going first.
//          In each turn, a player chooses one of their monsters and fights against an opponent's monster.
//          The outcome of the fight reduces both monster's abilities by the other's value (x - y and y - x).
//          If any monster's ability becomes <= 0, it dies. Game ends when one or both players have no monsters left.
// Algorithm: The key insight is to simulate the optimal play using total sums:
//            - Tsondu wins if sum of his abilities > sum of Tenzing's
//            - Tenzing wins if sum of his abilities > sum of Tsondu's
//            - Draw if sums are equal.
// Time Complexity: O(n + m) per test case, where n and m are monster counts.
// Space Complexity: O(1), constant extra space used.

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long long x(0), y(0); // x = sum of Tsondu's monsters, y = sum of Tenzing's monsters
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      x += a; // Accumulate Tsondu's monster abilities
    }
    for (long p = 0; p < m; p++) {
      long b;
      scanf("%ld", &b);
      y += b; // Accumulate Tenzing's monster abilities
    }
    puts(x == y ? "Draw" : (x > y ? "Tsondu" : "Tenzing")); // Output result based on sum comparison
  }
}

// https://github.com/VaHiX/codeForces/