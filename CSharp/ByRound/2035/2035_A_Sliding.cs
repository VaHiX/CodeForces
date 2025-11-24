// Problem: CF 2035 A - Sliding
// https://codeforces.com/contest/2035/problem/A

/*
 * Problem: Calculate the sum of Manhattan distances when a person at position (r, c) leaves,
 *          causing all subsequent people to shift leftward in row-major order.
 * 
 * Algorithms/Techniques:
 *   - Sliding
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 * 
 * Input Format:
 *   - First line contains number of test cases t
 *   - Each test case consists of four integers n, m, r, c representing rows, columns,
 *     and the position (r,c) where a person leaves.
 * 
 * Output Format:
 *   - For each test case, output a single integer denoting the total Manhattan distance sum.
 * 
 * Example:
 *   Input: 4
 *   2 3 1 2    -> Output: 6
 *   2 2 2 1    -> Output: 1
 *   1 1 1 1    -> Output: 0
 *   1000000 1000000 1 1   -> Output: 1999998000000
 */

using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());  // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');  // Read input line and split into parts
      var h = long.Parse(line[0]);  // Number of rows
      var w = long.Parse(line[1]);  // Number of columns
      var r = long.Parse(line[2]) - 1;  // Convert to 0-based row index
      var c = long.Parse(line[3]) - 1;  // Convert to 0-based column index
      getAns(h, w, r, c);  // Compute and print result for current test case
    }
  }

  static void getAns(long h, long w, long r, long c) {
    var d = h - 1 - r;  // Distance from current row to bottommost row (in terms of rows)
    var ans = d * (w * 2L - 1) + w - c - 1;  // Compute final answer using derived formula
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/