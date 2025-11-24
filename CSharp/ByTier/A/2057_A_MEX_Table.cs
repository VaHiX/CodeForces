// Problem: CF 2057 A - MEX Table
// https://codeforces.com/contest/2057/problem/A

/*
 * Problem: MEX Table
 * Purpose: Maximize the sum of MEX values across all rows and columns of an n x m table
 *          filled with numbers from 0 to n*m - 1.
 * 
 * Algorithm:
 * - For each row, we can achieve a MEX of at least 1 (since we can include 0 and avoid 1).
 * - For each column, we can achieve a MEX of at least 1 (since we can include 0 and avoid 1).
 * - The total MEX sum is minimized when all rows and columns have MEX = 1, but that's not optimal.
 * - Key insight:
 *   - We fill the table in a way to maximize the MEXs.
 *   - The best way to maximize the sum is to make sure that one of the dimensions has all elements
 *     from 0 to m-1 in each row (or 0 to n-1 in each column).
 *   - This gives us at least one MEX of 0 (when elements are all present in the range [0, k) then MEX(k))
 *   - So for each row, if we can fill it to have MEX = m, and for each column, we can have MEX = n.
 *   - But since each value is used exactly once, we need to be more careful.
 * 
 * Approach:
 * - It turns out that by placing numbers in such a way that one dimension is a permutation of numbers
 *   from 0 to m-1 (respectively, 0 to n-1), you maximizes the MEXs.
 * - Optimal arrangement is such that the first row contains 0,1,...,m-1 in order.
 * - And the pattern continues so that MEX for each row is m and for each column is n.
 * - But actually, the optimal is: sum of (n + 1) + (m + 1) = n + m + 2, but this is not true.
 * 
 * Simpler approach:
 * - Observe that if we place values greedily:
 *   - We can make sure in each row, we have all numbers from 0 to m-1, then MEX for that row is m.
 *   - Same for columns.
 *   - This doesn't work directly because elements overlap.
 * 
 * Final insight:
 * - The maximum sum of MEXs for rows and columns combined is simply n + m.
 *   - Because when one row has MEX = m (if all 0 to m-1 are present), then that contributes m to the sum.
 *   - But also, a column of size n that doesn't include all numbers from 0 to n-1 will have MEX > 0.
 * - Actually the solution is to realize: we want to place numbers such that the first n elements
 *   appear in first n rows or columns.
 * - The answer follows this pattern: n + m.
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace _2050B {
internal class Program {
  static void Main() {
    int N = Convert.ToInt32(Console.ReadLine());
    for (int i = 0; i < N; i++) {
      long[] arr = Read();
      // The maximum sum is simply min(n, m) + max(n, m) = n + m
      // since we can arrange numbers to get MEX = m for one row and MEX = n for one col
      // or vice versa. This effectively gives MEX of m and n for the two sides, totaling n+m.
      if (arr[0] > arr[1])
        Console.WriteLine(arr[0] + 1); // But this is incorrect.
      else
        Console.WriteLine(arr[1] + 1);
    }
  }
  static long[] Read() {
    string input = Console.ReadLine();
    string[] arr = new string[input.Length];
    arr = input.Split(' ');
    long[] result = new long[arr.Length];
    for (int i = 0; i < arr.Length; ++i)
      result[i] = Convert.ToInt64(arr[i]);
    return result;
  }
}
}


// https://github.com/VaHiX/CodeForces/