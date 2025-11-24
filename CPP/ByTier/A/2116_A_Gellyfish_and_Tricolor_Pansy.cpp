// Problem: CF 2116 A - Gellyfish and Tricolor Pansy
// https://codeforces.com/contest/2116/problem/A

/*
 * Problem: A. Gellyfish and Tricolor Pansy
 * Purpose: Determine the winner of a turn-based game between Gellyfish and Flower,
 *          where each player has HP and a knight with HP. Players take turns attacking
 *          either opponent or opponent's knight, aiming to reduce opponent's HP to <= 0.
 *
 * Algorithm:
 *   - The key insight is that in optimal play, we can model the outcome based on
 *     minimal HP values of knights (c and d) and player HPs (a and b).
 *   - If the minimum of Gellyfish's HP and Flower's knight HP is less than or equal
 *     to the minimum of Flower's HP and Gellyfish's knight HP, then Flower wins.
 *   - This models how early in the game a player can defeat their opponent through
 *     rapid attack sequences, especially when one side has low HP for either main
 *     character or knight.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;           // Read HP values for Gellyfish (a), Flower (b),
                               // Gellyfish's knight (c), and Flower's knight (d)
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    long x = (a < c ? a : c);  // Minimum of Gellyfish's HP and knight HP
    long y = (b < d ? b : d);  // Minimum of Flower's HP and knight HP
    puts(x >= y ? "Gellyfish" : "Flower");  // Output winner based on comparison
  }
}


// https://github.com/VaHiX/codeForces/