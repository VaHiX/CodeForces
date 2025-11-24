// Problem: CF 817 A - Treasure Hunt
// https://codeforces.com/contest/817/problem/A

/*
 * Code Purpose: Determines whether Captain Bill the Hummingbird can reach the treasure using the teleportation potion.
 *               The potion allows four types of moves: (x, 0), (-x, 0), (0, y), (0, -y).
 *               The problem reduces to checking if the Manhattan distance in x and y directions can be covered
 *               with an equal number of steps in x and y directions (with appropriate parity consideration).
 *
 * Algorithm: 
 *   - Compute the absolute differences in x and y coordinates.
 *   - Check if these differences are divisible by x and y respectively.
 *   - Then, check that the number of steps in each direction have the same parity (both even or both odd),
 *     ensuring that a valid sequence of moves exists.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long x1, y1, x2, y2;
  scanf("%ld %ld %ld %ld", &x1, &y1, &x2, &y2);
  long x, y;
  scanf("%ld %ld", &x, &y);
  long diffx = (x2 > x1) ? (x2 - x1) : (x1 - x2); // Compute absolute difference in x
  long diffy = (y2 > y1) ? (y2 - y1) : (y1 - y2); // Compute absolute difference in y
  // Check if both diffx and diffy are divisible by x and y respectively,
  // and have same parity when divided by x and y to ensure valid move sequence
  bool possible = (diffx % x == 0) && (diffy % y == 0) &&
                  ((diffx / x) % 2 == (diffy / y) % 2);
  puts(possible ? "YES" : "NO"); // Output the result
  return 0;
}


// https://github.com/VaHiX/CodeForces/