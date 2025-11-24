// Problem: CF 1950 B - Upscaling
// https://codeforces.com/contest/1950/problem/B

/*
 * Problem: B. Upscaling
 * Algorithm/Technique: Grid construction with pattern simulation
 * 
 * Time Complexity: O(2^(2n)) - We generate a 2^n x 2^n grid, each cell requires constant time to compute and print.
 * Space Complexity: O(1) - Only using a constant amount of extra space, not counting the output.
 * 
 * The solution constructs a checkerboard of size 2^n x 2^n where each 2x2 square alternates between '#' and '.'.
 * The top-left corner is always '#'. The pattern is determined by (i/2 + j) % 2.
 * If the result is even, print "#", otherwise print ".".
 */

using System;
class Program {
  static void Print(int n) {
    if (n == 1)
      Console.Write("##"); // Print '#' for 2x2 square
    else
      Console.Write(".."); // Print '.' for 2x2 square
  }
  static void Solve() {
    int n = int.Parse(Console.ReadLine());
    for (int i = 0; i < 2 * n; i++) { // Loop through rows of 2^n
      for (int j = 0; j < n; j++) { // Loop through columns of n
        if ((i / 2 + j) % 2 == 0) { // Determine pattern based on row and column indices
          Print(1); // Print '#' 
        } else {
          Print(0); // Print '.'
        }
      }
      Console.WriteLine(); // Move to next line after each row
    }
  }
  static void Main(string[] args) {
    int n = int.Parse(Console.ReadLine());
    while (n > 0) {
      Solve(); // Process each test case
      n--;
    }
  }
}


// https://github.com/VaHiX/CodeForces/