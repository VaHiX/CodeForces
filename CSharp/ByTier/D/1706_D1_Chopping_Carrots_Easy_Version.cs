// Problem: CF 1706 D1 - Chopping Carrots (Easy Version)
// https://codeforces.com/contest/1706/problem/D1

/*
 * Problem: D1. Chopping Carrots (Easy Version)
 * 
 * Approach:
 * - For each element in the array, we compute all possible quotients a[i]/p[i] where p[i] ranges from 1 to k.
 * - We use a greedy approach by iterating over possible threshold values (quotient values) and try to assign values to each element
 *   such that the resulting quotient is at least the threshold.
 * - The goal is to minimize the difference between the maximum and minimum quotient values.
 * 
 * Time Complexity: O(n * k * log(k)) where n <= 3000 and k <= 3000
 * Space Complexity: O(n * k) for storing quotient lists and thresholds
 * 
 * Algorithms/Techniques:
 * - Greedy approach with thresholding
 * - Preprocessing quotient values
 * - Efficient lookup using SortedSet and List
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      var b =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      long o = int.MaxValue;
      int k = a[1];
      int mn = b.Min();
      List<int>[] quotients = new List<int>[a[0]];
      SortedSet<int> thresholds = new SortedSet<int>();
      thresholds.Add(mn);
      for (int j = 0; j < a[0]; j++) {
        quotients[j] = new List<int>();
        for (int i = Math.Min(b[j], k); i > 0; i--) {
          int c = b[j] / i;
          if (quotients[j].Count == 0 || c > quotients[j].Last()) {
            quotients[j].Add(c);
            thresholds.Add(c);
            if (c > mn)
              break;
          }
        }
      }
      int[] ids = new int[a[0]];
      var ts = thresholds.ToList();
      for (int i = 0; i < ts.Count && ts[i] <= mn; i++) {
        int cm = -1;
        for (int j = 0; j < a[0]; j++) {
          while (quotients[j][ids[j]] < ts[i])
            ids[j]++;
          cm = Math.Max(cm, quotients[j][ids[j]]);
        }
        if (cm - ts[i] < o)
          o = cm - ts[i];
      }
      output.Add(o.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/