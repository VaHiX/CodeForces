// Problem: CF 2019 B - All Pairs Segments
// https://codeforces.com/contest/2019/problem/B

/*
B. All Pairs Segments
Algorithm: Segment Counting with Difference Array Technique
Time Complexity: O(n + q)
Space Complexity: O(n)

This problem involves counting how many integer points lie on exactly k segments,
where each segment [x_i, x_j] is formed by choosing any two points from given n points.
The key insight is to use a difference array technique to count how many segments
each point lies on. For each pair (i,j), we increment the start of the range and 
decrement after the end.

We use a dictionary to store frequency of segment lengths that contribute to 
the final result for fast query lookups.
*/

using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var q = int.Parse(line[1]);
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      line = Console.ReadLine().Trim().Split(' ');
      var b = Array.ConvertAll(line, long.Parse);
      getAns(n, q, a, b);
    }
  }
  static void getAns(int n, int q, int[] a, long[] b) {
    var d = new Dictionary<long, long>();
    d[n - 1] = 1; // Initialize with the base case: one segment of length n-1
    for (int i = 1; i < n; i++) {
      // Calculate contribution of segment [a[i], a[i-1]] to total count of segments per point
      var w = ((long)i + 1) * ((long)n - i) - 1;
      if (d.ContainsKey(w))
        d[w]++;
      else
        d[w] = 1;
      
      var w2 = i * ((long)n - i);
      // Skip if adjacent elements are consecutive
      if (a[i] - a[i - 1] == 1)
        continue;
      
      // Add the number of gaps between current and previous point to the dictionary
      if (d.ContainsKey(w2))
        d[w2] += a[i] - a[i - 1] - 1;
      else
        d[w2] = a[i] - a[i - 1] - 1;
    }
    var ans = new long[q];
    for (int i = 0; i < q; i++) {
      // For each query, check if value exists in dictionary and return frequency
      if (!d.ContainsKey(b[i]))
        ans[i] = 0;
      else
        ans[i] = d[b[i]];
    }
    Console.WriteLine(string.Join(" ", ans));
  }
}


// https://github.com/VaHiX/codeForces/