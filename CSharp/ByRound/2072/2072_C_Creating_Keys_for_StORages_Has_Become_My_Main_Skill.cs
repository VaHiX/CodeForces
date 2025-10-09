// Problem: CF 2072 C - Creating Keys for StORages Has Become My Main Skill
// https://codeforces.com/contest/2072/problem/C

/*
 * Problem: Creating Keys for StORages Has Become My Main Skill
 * Description:
 *   Given n and x, construct an array of length n such that:
 *     1. The bitwise OR of all elements equals x.
 *     2. The MEX (minimum excludant) of the array is maximized.
 *
 * Algorithm:
 *   - Find the smallest bit position where x has a zero (this determines the MEX limit).
 *   - Fill the array with numbers from 0 to (MEX-1), then fill remaining slots with x or other values
 *     ensuring overall OR equals x.
 *
 * Time Complexity: O(n) per test case, since we process each element at most once.
 * Space Complexity: O(n) for storing the result array.
 */

using System.Collections.Generic;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var x = int.Parse(line[1]);
      getAns(n, x);
    }
  }

  static void getAns(int n, int x) {
    var mex = 0;
    // Find the first bit position where x is 0
    for (int i = 0; i < 31; i++) {
      if (((x >> i) & 1) == 0) {
        mex = (1 << i);
        break;
      }
    }

    var ans = new List<int>();
    var ttt = 0;

    // Add all numbers from 0 to mex-1 into the answer array
    for (int i = 0; i < mex; i++) {
      ans.Add(i);
      ttt |= i;
      if (ans.Count == n)
        break;
    }

    var anscount = ans.Count;

    // If we've filled exactly n elements, check if their OR equals x
    if (anscount == n) {
      if (ttt != x) {
        // If not, try to adjust the last element to make OR equal x
        if (ans[n - 1] != x)
          ans[n - 1] = x;
      }
    } else {
      // Fill remaining positions with copies of x
      var cc = n - anscount;
      for (int i = 0; i < cc; i++)
        ans.Add(x);
    }

    Console.WriteLine(string.Join(" ", ans));
  }
}


// https://github.com/VaHiX/codeForces/