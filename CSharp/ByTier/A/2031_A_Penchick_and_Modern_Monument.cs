// Problem: CF 2031 A - Penchick and Modern Monument
// https://codeforces.com/contest/2031/problem/A

/*
A. Penchick and Modern Monument

Algorithms/Techniques: Greedy, Frequency Counting

Time Complexity: O(n) per test case, where n is the number of pillars.
Space Complexity: O(n) for the count array used to store frequency of pillar heights.

The problem requires transforming a non-increasing sequence into a non-decreasing one with minimum operations.
Each operation allows changing the height of any pillar to any positive integer.
The key insight is that we want to minimize the number of changes, so we should try to keep as many elements as possible
in their original positions. The optimal approach is to find how many elements can remain unchanged,
and this corresponds to finding the maximum frequency of a value in the array (since we can make all elements equal to
the most frequent one). Then, the number of operations is `n - max_frequency`.

*/

using System;
using static System.Console;
using System.Linq;
using System.Collections.Generic;
class Program {
  static int NN => int.Parse(ReadLine());
  static int[] NList => ReadLine().Split().Select(int.Parse).ToArray();
  static string[] SList(long n) => Enumerable.Repeat(0, (int)n)
                                       .Select(
                                           _ => ReadLine())
                                       .ToArray();
  public static void Main() { Solve(); }
  static void Solve() {
    var t = NN; // Number of test cases
    var ans = new int[t];
    for (var u = 0; u < t; ++u) {
      var n = NN; // Number of pillars
      var a = NList; // Array of pillar heights
      var count = new int[n + 1]; // Frequency array to count occurrences of each height
      foreach (var ai in a)
        ++count[ai]; // Increment the frequency of current height
      
      ans[u] = n - count.Max(); // Minimum operations = total pillars - max frequency of any height
    }
    WriteLine(string.Join("\n", ans));
  }
}


// https://github.com/VaHiX/codeForces/