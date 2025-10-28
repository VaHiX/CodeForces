// Problem: CF 2122 A - Greedy Grid
// https://codeforces.com/contest/2122/problem/A

/*
 * Problem: Grid with No Greedy Maximum Path
 * 
 * Description:
 * Determines whether there exists an n x m grid of non-negative integers such that 
 * no greedy path (which always moves to the neighbor with the greater value) achieves 
 * the maximum possible down/right path sum.
 * 
 * Algorithms/Techniques:
 * - Greedy path selection and comparison
 * - Mathematical analysis of grid properties for path existence
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      string[] input = Console.ReadLine().Split(" "); // Read n and m
      int n = int.Parse(input[0]);
      int m = int.Parse(input[1]);
      if (n > 1 && m > 1) // If both dimensions are greater than 1
        if (n == 2 && m == 2) { // Special case: 2x2 grid
          Console.WriteLine("NO"); // For 2x2, greedy path always achieves maximum
        } else
          Console.WriteLine("YES"); // For other grids > 1x1, answer is YES
      else
        Console.WriteLine("NO"); // If any dimension is 1, answer is NO
    }
  }
}


// https://github.com/VaHiX/codeForces/