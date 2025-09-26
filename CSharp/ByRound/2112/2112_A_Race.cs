// Problem: CF 2112 A - Race
// https://codeforces.com/contest/2112/problem/A

/*
 * Problem: Bob vs Alice Race
 * Purpose: Determine if Bob can choose a starting point such that he always reaches the prize faster than Alice,
 *          regardless of where the prize appears (either at x or y).
 * 
 * Algorithm:
 * - For each test case, we examine all possible positions Bob can take (from 1 to 100, excluding 'a').
 * - For each candidate position b for Bob:
 *   - Compute distances from Bob's position to x and y.
 *   - Compute distances from Alice's position (a) to x and y.
 *   - Check if both of Bob's distances are strictly less than Alice's respective distances.
 *   - If such a position exists, answer is "YES", otherwise "NO".
 * 
 * Time Complexity: O(100 * t) = O(t), since 100 is a constant and doesn't grow with input size.
 * Space Complexity: O(1), only using a fixed number of variables.
 */

using System;

public class HelloWorld {
  public static void Main(string[] args) {
    int t = Convert.ToInt32(Console.ReadLine()); // Read number of test cases
    int c, u, p, counter = 0; // Unused variables (can be removed)
    int[] f = new int[3]; // Array to store a, x, y values
    
    for (int q = 0; q < t; q++) {
      string[] x = Console.ReadLine().Split(); // Read input line and split into parts
      for (int i = 0; i < 3; i++) {
        f[i] = int.Parse(x[i]); // Parse a, x, y from input
      }
      
      c = f[0]; // Alice's starting point (a)
      bool bobWins = false; // Flag to indicate if Bob has found a winning position
      
      for (int b = 1; b <= 100; b++) { // Loop through all possible positions for Bob
        if (b == f[0]) // Skip Alice's position (as Bob can't start there)
          continue;
          
        int bobToX = Math.Abs(b - f[1]); // Distance from Bob to prize at x
        int bobToY = Math.Abs(b - f[2]); // Distance from Bob to prize at y
        int aliceToX = Math.Abs(f[0] - f[1]); // Distance from Alice to prize at x
        int aliceToY = Math.Abs(f[0] - f[2]); // Distance from Alice to prize at y
        
        if (bobToX < aliceToX && bobToY < aliceToY) { // Check if Bob is faster in both cases
          bobWins = true;
          break; // Found a winning position for Bob, exit early
        }
      }
      
      Console.WriteLine(bobWins ? "YES" : "NO"); // Print result
    }
  }
}


// https://github.com/VaHiX/codeForces/