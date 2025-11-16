// Problem: CF 1991 C - Absolute Zero
// https://codeforces.com/contest/1991/problem/C

/*
 * Purpose: Solve the "Absolute Zero" problem where we need to make all array elements zero
 *          using at most 40 operations. Each operation chooses a value x and replaces each
 *          element a[i] with |a[i] - x|.
 *
 * Algorithm:
 *   - Use a greedy approach: in each step, compute the median of current non-zero values
 *     and apply the operation using that median.
 *   - If at any point we have more than one non-zero value and they have different parity,
 *     it's impossible.
 *   - Continue until all elements are zero or we exceed 40 operations.
 *
 * Time Complexity: O(n * log(n)) per test case due to sorting operations involved in finding min/max.
 * Space Complexity: O(n) for storing the input array and result list.
 */
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
class P {
  static void Main() {
    using (var r = new StreamReader(Console.OpenStandardInput())) using (
        var w = new StreamWriter(Console.OpenStandardOutput())) {
      int t = int.Parse(r.ReadLine());
      for (int _ = 0; _ < t; _++) {
        int n = int.Parse(r.ReadLine());
        var a = r.ReadLine().Split().Select(long.Parse).ToArray();
        var res = S(n, a);
        if (res[0] == -1) {
          w.WriteLine(-1);
        } else {
          w.WriteLine(res[0]);
          for (int i = 1; i < res.Count; i++) {
            w.Write(res[i] + " ");
          }
          w.WriteLine();
        }
      }
    }
  }
  static List<long> S(int n, long[] a) {
    var o = new List<long>(); // Stores the sequence of operations (x values)
    while (a.Max() > 0) { // Continue while there are non-zero elements
      if (o.Count >= 40) { // If more than 40 operations, impossible
        return new List<long> { -1 };
      }
      var nz = a.Where(v => v != 0).ToList(); // Get non-zero values
      if (nz.Count > 1 && (nz[0] % 2) != (nz[1] % 2)) { // Check if parity differs
        return new List<long> { -1 };
      }
      long mn = a.Min(); // Find minimum
      long mx = a.Max(); // Find maximum
      long mid = (mn + mx) / 2; // Calculate median
      o.Add(mid); // Add operation
      for (int i = 0; i < a.Length; i++) {
        a[i] = Math.Abs(a[i] - mid); // Apply the operation to all elements
      }
    }
    var r = new List<long> { o.Count }; // Prepare result list
    r.AddRange(o); // Add operations to result
    return r;
  }
}


// https://github.com/VaHiX/CodeForces/