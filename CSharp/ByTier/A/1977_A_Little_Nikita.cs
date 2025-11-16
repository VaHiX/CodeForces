// Problem: CF 1977 A - Little Nikita
// https://codeforces.com/contest/1977/problem/A

/*
 * Code Purpose: Determine whether it's possible to build a tower with exactly `m` cubes
 *               after `n` moves, where each move is either adding or removing one cube.
 * 
 * Algorithm: 
 *   - The total number of moves `n` must be at least `m` (we can't remove more cubes than we have).
 *   - The difference `n - m` must be even because each move either adds or removes one cube,
 *     so the net change in cubes must be an even number to achieve exactly `m` cubes.
 * 
 * Time Complexity: O(1) - constant time operations.
 * Space Complexity: O(1) - only a constant amount of space used.
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      string[] input = Console.ReadLine().Split(' '); // Read n and m from input
      int n = int.Parse(input[0]); // Parse n
      int m = int.Parse(input[1]); // Parse m
      if (IsPossible(n, m)) { // Check if it's possible to form m cubes with n moves
        Console.WriteLine("Yes");
      } else {
        Console.WriteLine("No");
      }
    }
  }
  static bool IsPossible(int n, int m) {
    // n >= m ensures we have enough moves to build up to m cubes
    // (n - m) % 2 == 0 ensures that the number of removals is even, 
    // which means the net result of moves leads to exactly m cubes
    return (n >= m) && ((n - m) % 2 == 0);
  }
}


// https://github.com/VaHiX/CodeForces/