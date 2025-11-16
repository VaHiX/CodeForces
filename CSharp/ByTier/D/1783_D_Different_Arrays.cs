// Problem: CF 1783 D - Different Arrays
// https://codeforces.com/contest/1783/problem/D

/*
 * Purpose: Calculates the number of reachable arrays after performing a sequence of operations on the input array.
 * 
 * Algorithms/Techniques: 
 * - Dynamic Programming with a sliding window approach
 * - The state represents possible values at each step, updated iteratively
 * - Uses offset indexing to handle negative values in the array (mapping from index 0 to 200000)
 * 
 * Time Complexity: O(n * M) where n is the size of the array and M is the maximum possible value range (around 600 in practice)
 * Space Complexity: O(M) where M is the size of the offset array (200000 slots)
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = 1;
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = int.Parse(Console.ReadLine());
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      long o = 0;
      long[] d = new long[200000];
      // Initialize the first element of the difference array with a[1] offset
      d[100000 + a[1]]++; // use offset to avoid negative indices
      int min = 100000 - 700; // maintain range to optimize iterations
      int max = 100700;
      for (int i = 1; i < n - 1; i++) {
        long[] d1 = new long[200000]; // next state array
        for (int j = min - 300; j <= max + 300; j++) {
          var p = d[j];
          if (j == 100000) {
            // Special case for the root node
            if (p > 0) {
              d1[100000 + a[i + 1]] += p;
              d1[100000 + a[i + 1]] %= 998244353;
              min = Math.Min(min, 100000 + a[i + 1]);
              max = Math.Max(max, 100000 + a[i + 1]);
            }
          } else {
            // Standard transitions: add value to one neighbor, subtract from the other
            if (p > 0) {
              d1[j + a[i + 1]] += p;
              d1[j + a[i + 1]] %= 998244353;
              d1[200000 - j + a[i + 1]] += p;
              d1[200000 - j + a[i + 1]] %= 998244353;
              min = Math.Min(min, j + a[i + 1]);
              min = Math.Min(min, 200000 - j + a[i + 1]);
              max = Math.Max(max, j + a[i + 1]);
              max = Math.Max(max, 200000 - j + a[i + 1]);
            }
          }
        }
        d = d1; // update current state to next
      }
      o = 0;
      // Sum all valid states to get final count
      for (int i = min - 300; i <= max + 300; i++) {
        o += d[i];
        o %= 998244353;
      }
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/