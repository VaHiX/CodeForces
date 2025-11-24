// Problem: CF 1918 A - Brick Wall
// https://codeforces.com/contest/1918/problem/A

/*
 * Code Purpose: Calculate the maximum stability of a brick wall of size n×m.
 * 
 * Algorithm/Techniques: Greedy approach
 * - To maximize stability (horizontal bricks - vertical bricks), we want to use as many horizontal bricks as possible.
 * - Each horizontal brick covers 1 row and k columns (k >= 2).
 * - The optimal strategy is to place horizontal bricks of size 1×2 in each row.
 * - For each row, we can place floor(m / 2) horizontal bricks, and each contributes +1 to stability.
 * - Since there are n rows, total stability = n * floor(m / 2).
 * 
 * Time Complexity: O(1) - constant time calculation per test case.
 * Space Complexity: O(1) - only using a few variables regardless of input size.
 */

using System;
class Program {
  static void Main() {
    try {
      Console.SetIn(new System.IO.StreamReader(Console.OpenStandardInput(),
                                               Console.InputEncoding, false,
                                               bufferSize: 1024));
      Console.SetOut(new System.IO.StreamWriter(Console.OpenStandardOutput(),
                                                Console.OutputEncoding,
                                                bufferSize: 1024));
      int t = int.Parse(Console.ReadLine());
      for (int testCase = 0; testCase < t; testCase++) {
        long n, m;
        string[] input = Console.ReadLine().Split();
        n = long.Parse(input[0]); // Height of the wall
        m = long.Parse(input[1]); // Width of the wall
        long stability = CalculateStability(n, m); // Compute max stability
        Console.WriteLine($"{stability}");
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
  static long CalculateStability(long n, long m) { return (m / 2) * n; } // Max stability formula
}


// https://github.com/VaHiX/CodeForces/