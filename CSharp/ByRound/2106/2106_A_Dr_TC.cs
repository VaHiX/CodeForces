// Problem: CF 2106 A - Dr. TC
// https://codeforces.com/contest/2106/problem/A

/*
 * Problem: Dr. TC's Binary String Grid
 * 
 * Purpose:
 *   Given a binary string s of length n, we generate n strings by flipping each character 
 *   of s one at a time (i.e., for each position i, flip the bit at that position in s).
 *   These n strings are arranged in a grid where row i corresponds to the string obtained by
 *   flipping the i-th character of s. The task is to count the total number of '1's in this grid.
 *
 * Algorithm:
 *   For each string in the grid:
 *     - Original string s contributes c1 ones, where c1 = count of '1's in s
 *     - Each flipped position changes one bit from s, so flipping the i-th character in s affects the i-th row
 *     - Total number of 1s = (total count of zeros in original s) * n + (total count of ones in original s)
 *       This is because:
 *         - For each '0' in s, it becomes '1' once in one of the n rows
 *         - For each '1' in s, it becomes '0' once in one of the n rows, and stays '1' in (n-1) rows
 *       Simplifying: (n - c1) * 1 + c1 * (n - 1) + c1 = (n - c1) + c1 * n = c1 * n - c1 + n = c1 * (n - 2) + n
 *
 * Time Complexity: O(n) per test case — we read the string and count occurrences of '1'
 * Space Complexity: O(1) — only using a few variables for computation
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read length of binary string
      var s = Console.ReadLine().Trim(); // Read the binary string
      getAns(n, s); // Compute and output result
    }
  }
  
  static void getAns(int n, string s) {
    var c1 = s.Count(x => x == '1'); // Count number of '1's in the input string
    Console.WriteLine(c1 * (n - 2) + n); // Apply formula to compute total 1s in grid
  }
}


// https://github.com/VaHiX/codeForces/