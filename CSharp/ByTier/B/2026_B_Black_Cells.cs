// Problem: CF 2026 B - Black Cells
// https://codeforces.com/contest/2026/problem/B

/*
 * Problem: B. Black Cells
 * 
 * Purpose:
 *   Given a list of white cells that must be painted black, and at most one additional
 *   cell that can be painted black, determine the minimum value of k such that all
 *   required cells can be painted using operations where two cells i and j are painted
 *   if |i - j| <= k.
 * 
 * Approach:
 *   For each test case, we sort the list of black cells first. Then, for even-length
 *   arrays, we calculate maximum gap between consecutive pairs starting from index 0.
 *   For odd-length arrays, we consider several cases: 
 *   - First and last pair
 *   - One possible extra cell that minimizes the maximum gap
 *   - Try different positions where an additional cell can be used to reduce gaps.
 *
 * Time Complexity:
 *   O(n^2) per test case. For even-length arrays, O(n), for odd-length arrays,
 *   O(n^2) in worst-case due to checking each possible extra cell insertion point.
 * 
 * Space Complexity:
 *   O(1) additional space (excluding input).
 */

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read size of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements
      var a = Array.ConvertAll(line, long.Parse); // Convert to long array
      getAns(n, a); // Process the case
    }
  }

  // Calculate maximum difference between consecutive pairs in range [start, end)
  static long calc(long[] a, int start, int end) {
    var res = 0L;
    for (int i = start; i < end; i += 2)
      res = Max(res, a[i + 1] - a[i]);
    return res;
  }
  
  // For even-length arrays: find maximum gap between consecutive pairs starting from index 0
  static void even(int n, long[] a) { Console.WriteLine(calc(a, 0, n)); }

  // For odd-length arrays: handle special case and try different combinations
  static void odd(int n, long[] a) {
    var ans = calc(a, 1, n); // Check gaps excluding first element
    ans = Min(ans, calc(a, 0, n - 1)); // Check gaps excluding last element

    if (n < 3) { // If array length less than 3, output result directly
      Console.WriteLine(ans);
      return;
    }

    // Try placing an extra cell to minimize maximum gap between segments
    for (int i = 2; i < n - 1; i += 2) {
      var t = Max(calc(a, 0, i - 1), calc(a, i + 1, n)); // Test splitting at index i
      ans = Min(ans, t); // Keep track of minimum of maximum gaps
    }
    Console.WriteLine(ans);
  }

  // Main function to process different cases based on even or odd array length
  static void getAns(int n, long[] a) {
    if (n == 1) {
      Console.WriteLine(1); // Special case: only one element
      return;
    }
    
    if (n % 2 == 1)
      odd(n, a);
    else
      even(n, a);
  }
}


// https://github.com/VaHiX/codeForces/