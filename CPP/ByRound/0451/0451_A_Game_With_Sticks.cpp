// Problem: CF 451 A - Game With Sticks
// https://codeforces.com/contest/451/problem/A

/*
 * Problem: Game With Sticks
 * 
 * Algorithm/Technique: Game Theory, Mathematical Analysis
 * 
 * Approach:
 * - The game is played on a grid with n horizontal and m vertical sticks.
 * - Each move removes all sticks passing through a chosen intersection point.
 * - This means each move reduces the number of available intersection points by one.
 * - The total number of intersection points is n * m.
 * - The player who makes the last valid move wins.
 * - Since players alternate and play optimally, the outcome depends on the parity of the total number of intersection points.
 * - If the total number of intersection points (n * m) is odd, the first player (Akshat) wins.
 * - If the total number of intersection points (n * m) is even, the second player (Malvika) wins.
 * - However, this logic isn't directly used here.
 * - The key insight is that we're essentially playing a game where it's optimal to minimize the size of the grid.
 * - A more accurate observation is: the game ends when no intersections remain.
 * - So the total number of moves possible is n * m.
 * - If the total number of moves is odd, Akshat (first player) wins.
 * - If the total number of moves is even, Malvika (second player) wins.
 * - Instead of calculating n * m, we check which player makes the final move.
 * - Since both players play optimally, it’s about minimizing the number of remaining moves.
 * - Let us consider a turn-based optimal play.
 * - The player who plays first has a winning strategy if, after the first move, we have an odd number of intersection points remaining.
 * - In this case, the number of moves to be made is n*m - 1 (since one intersection is removed).
 * - If n * m is even, that means the first player (Akshat), will make an even number of moves, making the last odd move for Malvika.
 * - So, if the total number of intersection points is even, Malvika wins. If it's odd, Akshat wins.
 * - But actually, let's simplify it:
 *   - The game starts with n * m intersection points.
 *   - Each move eliminates one intersection point and all sticks going through it.
 *   - The game ends when no intersection point is left.
 *   - Total number of moves = n * m.
 *   - If the number of moves is odd, the first player (Akshat) makes the last move.
 *   - If the number of moves is even, the second player (Malvika) makes the last move.
 *   - Therefore:
 *     - if n * m % 2 == 1: Akshat wins
 *     - else: Malvika wins.
 *   - However, in the provided simplified code:
 *     - It computes the minimum of n and m.
 *     - If the minimum is odd, Akshat wins.
 *     - Else Malvika wins.
 *   - This works because in any game like this, the number of optimal moves equals min(n,m).
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
#include <cstdio>
int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  int smallest = n;  // Set smallest to n initially
  if (m < n) {       // If m is smaller than n, update smallest
    smallest = m;
  }
  if (smallest % 2) { // If smallest is odd
    puts("Akshat");   // Akshat wins
  } else {
    puts("Malvika");  // Malvika wins
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/