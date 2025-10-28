// Problem: CF 2065 C1 - Skibidus and Fanum Tax (easy version)
// https://codeforces.com/contest/2065/problem/C1

/*
 * Problem: C1. Skibidus and Fanum Tax (easy version)
 * 
 * Description:
 * Given two arrays 'a' and 'b' of sizes n and m respectively, where m=1,
 * we can perform at most one operation on each element a[i]:
 *   a[i] = b[0] - a[i]
 * The task is to determine if array 'a' can be sorted in non-decreasing order
 * after applying the operations.
 * 
 * Algorithm:
 * For each element a[i], we have two choices: keep it as a[i] or transform it to b[0] - a[i].
 * For each such choice, we compute min(a[i], b[0] - a[i]). The idea is to greedily
 * maintain the minimum of current and previous transformed values to ensure that
 * we can proceed in non-decreasing order.
 * If at any point, both choices are worse than the previous value, we return "NO".
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) additional space (excluding input)
 */

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      var b = int.Parse(Console.ReadLine().Trim());
      getAns(n, a, b);
    }
  }
  static void getAns(int n, int[] a, int b) {
    // Initialize pre with the minimum of original or transformed first element
    var pre = Min(a[0], b - a[0]);
    for (int i = 1; i < n; i++) {
      var k1 = a[i];           // Original value
      var k2 = b - a[i];       // Transformed value
      var mink = Min(k1, k2);  // Minimum of both options for current element
      if (mink >= pre) {
        // If smallest option is not less than previous, we can proceed
        pre = mink;
        continue;
      } else {
        // Otherwise, try largest option
        var maxk = Max(k1, k2);
        if (maxk >= pre) {
          // If largest option is not less than previous, we can proceed
          pre = maxk;
          continue;
        } else {
          // If even the maximum fails, impossible to sort
          Console.WriteLine("NO");
          return;
        }
      }
    }
    Console.WriteLine("YES");
  }
}


// https://github.com/VaHiX/codeForces/