// Problem: CF 1999 E - Triple Operations
// https://codeforces.com/contest/1999/problem/E

/// <summary>
/// Problem: E. Triple Operations
/// 
/// Purpose:
///   For each query [l, r], compute the total number of operations required to reduce all numbers in that range to 0,
///   using a specific transformation rule:
///     - Pick two numbers x and y.
///     - Replace them with 3*x and floor(y/3).
/// 
/// Algorithm:
///   - Precompute how many times a number needs to be reduced to 0 via the operation (i.e., log base 3 of the number).
///   - Use prefix sums to quickly answer range queries.
/// 
/// Time Complexity: O(maxN + T), where maxN = 2*10^5 and T is number of test cases.
/// Space Complexity: O(maxN)
/// 
/// Techniques:
///   - Logarithmic computation for base-3 exponent
///   - Prefix sum array for range queries
/// </summary>
using static System.Math;
using System;
public class hello {
  public static int[] a, psum; // a[i]: operations needed to reduce i to 0; psum: prefix sums of a
  static void Main() {
    var max = 200000;
    a = new int[max + 1]; // Precompute for each number up to max
    var Log3 = Log10(3);
    for (int i = 1; i <= max; i++)
      a[i] = (int)(Log10(i) / Log3) + 1; // Compute how many times i must be divided by 3 until it becomes 0
    psum = new int[max + 1];
    psum[1] = a[1];
    for (int i = 2; i <= max; i++)
      psum[i] = psum[i - 1] + a[i]; // Build prefix sum for fast range queries
    
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var L = int.Parse(line[0]);
      var r = int.Parse(line[1]);
      getAns(L, r);
    }
  }
  static void getAns(int L, int r) {
    // Query: Sum of operations from L to r.
    // Note: a[L] is added explicitly due to overlap in logic and how the problem maps to sum of logs
    var ans = psum[r] - psum[L - 1] + a[L];
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/