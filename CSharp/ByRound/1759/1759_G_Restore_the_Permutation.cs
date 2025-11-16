// Problem: CF 1759 G - Restore the Permutation
// https://codeforces.com/contest/1759/problem/G

/*
 * Problem: Restore the Permutation
 * Algorithm: Segment Tree + Greedy Approach
 * 
 * Time Complexity: O(n log n) per test case due to sorting and segment tree operations
 * Space Complexity: O(n) for the segment tree and auxiliary arrays
 * 
 * Key Idea:
 * - Given an array b where each element b[i] is the maximum of two consecutive elements in permutation p
 * - We need to reconstruct the lexicographically minimal permutation p
 * - We use a segment tree to maintain which numbers are still available
 * - For each b[i] from right to left, we greedily choose the smallest available number such that max(current, chosen) = b[i]
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace ACM_csharp {
internal class Program {
  public static int[] Tree;
  public static void PushValue(int v, int tl, int tr, int pos, int val) {
    // Update segment tree: set value at position pos to val
    if (tl == tr) {
      Tree[v] = val;
      return;
    }
    var tm = (tl + tr) / 2;
    if (pos <= tm) {
      PushValue(2 * v, tl, tm, pos, val);
    } else {
      PushValue(2 * v + 1, tm + 1, tr, pos, val);
    }
    Tree[v] = Tree[2 * v] + Tree[2 * v + 1];
  }
  public static int GetFirstSum(int v, int tl, int tr, int pos) {
    // Get sum of elements from 1 to pos in segment tree
    if (tl == tr) {
      return Tree[v];
    }
    var tm = (tl + tr) / 2;
    if (pos <= tm) {
      return GetFirstSum(2 * v, tl, tm, pos);
    }
    return Tree[2 * v] + GetFirstSum(2 * v + 1, tm + 1, tr, pos);
  }
  public static int GetIndexFromSum(int v, int tl, int tr, int sum) {
    // Find index of k-th set bit in segment tree
    if (tl == tr) {
      return tl;
    }
    var tm = (tl + tr) / 2;
    if (sum <= Tree[2 * v]) {
      return GetIndexFromSum(2 * v, tl, tm, sum);
    }
    return GetIndexFromSum(2 * v + 1, tm + 1, tr, sum - Tree[2 * v]);
  }
  static void Main(string[] args) {
    var t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var n = int.Parse(Console.ReadLine());
      var a = Console.ReadLine().Split().Select(int.Parse).ToArray();
      var sortedArr = a.ToList();
      sortedArr.Sort();
      var cur = 0;
      var error = false;
      Tree = new int[4 * (n + 1)];
      foreach (var x in sortedArr) {
        // Check if we have consecutive equal elements in b which is invalid
        if (x == cur) {
          error = true;
          break;
        }
        // Mark all numbers between cur and x as available in segment tree
        for (int i = cur + 1; i < x; i++) {
          PushValue(1, 1, n, i, 1);
        }
        cur = x;
      }
      if (error) {
        Console.WriteLine(-1);
        continue;
      }
      var ans = new List<int>();
      // Process b elements from right to left
      for (int i = a.Length - 1; i >= 0; i--) {
        var x = a[i];
        // If b[i] is 1, impossible to form valid permutation
        if (x == 1) {
          error = true;
          break;
        }
        // Find how many elements are less than x that are still available
        var k = GetFirstSum(1, 1, n, x);
        if (k == 0) {
          error = true;
          break;
        }
        // Get the index (number) that should be paired with x to result in max
        var y = GetIndexFromSum(1, 1, n, k);
        ans.Add(x);
        ans.Add(y);
        // Mark y as used
        PushValue(1, 1, n, y, 0);
      }
      if (error) {
        Console.WriteLine(-1);
        continue;
      }
      // Print result in reverse order (since we built it backwards)
      for (int i = ans.Count - 1; i >= 0; i--) {
        Console.Write(ans[i] + " ");
      }
      Console.WriteLine();
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/