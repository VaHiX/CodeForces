// Problem: CF 2140 D - A Cruel Segment's Thesis
// https://codeforces.com/contest/2140/problem/D

/*
D. A Cruel Segment's Thesis
Algorithms/Techniques: Greedy with sorting and prefix sums
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing segments and auxiliary arrays

Problem Description:
Given n segments on a number line, we repeatedly combine two unmarked segments into one,
with the new segment's left endpoint being from the first segment and right endpoint from the second.
The goal is to maximize the sum of lengths of all marked segments.

Approach:
1. For even number of segments: always take the k largest values (where k = n/2) 
   where value = l[i] + r[i], and compute the result accordingly.
2. For odd number of segments: iterate through each segment, compute optimal value
   by considering whether including or excluding it leads to a better total.

*/

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int testCases;
    if (!int.TryParse(Console.ReadLine(), out testCases))
      return;
    while (testCases-- > 0) {
      int n = int.Parse(Console.ReadLine()!);
      long[] l = new long[n];
      long[] r = new long[n];
      long[] v = new long[n]; // v[i] = l[i] + r[i]
      long sumL = 0, rangeTotal = 0;
      for (int i = 0; i < n; i++) {
        var parts = Console.ReadLine()!.Split();
        l[i] = long.Parse(parts[0]);
        r[i] = long.Parse(parts[1]);
        sumL += l[i];
        rangeTotal += (r[i] - l[i]); // total length of original segments
        v[i] = l[i] + r[i]; // precompute for sorting
      }
      var pairs = new List<(long val, int idx)>(n);
      for (int i = 0; i < n; i++)
        pairs.Add((v[i], i)); // create list of (value, index)
      
      // Sort by value descending, then by index ascending
      pairs.Sort((x, y) => {
        if (x.val != y.val)
          return y.val.CompareTo(x.val);
        return x.idx.CompareTo(y.idx);
      });
      
      int[] pos = new int[n]; // position of each segment in sorted list
      long[] prefix = new long[n + 1]; // prefix sum array for efficient range sum queries
      for (int i = 0; i < n; i++) {
        pos[pairs[i].idx] = i; // update the position of original index in new sorted order
        prefix[i + 1] = prefix[i] + pairs[i].val; // compute prefix sums
      }
      
      if (n % 2 == 0) {
        // Even case: Take first half of sorted items, add their sum to total length
        int k = n / 2;
        long t = prefix[k];
        Console.WriteLine(rangeTotal + (t - sumL));
      } else {
        // Odd case: For each segment, try removing it and see if we get better result
        int k = (n - 1) / 2;
        long best = long.MinValue;
        for (int i = 0; i < n; i++) {
          long t = (pos[i] >= k) ? prefix[k] : (prefix[k + 1] - v[i]); // compute sum of top k elements
          long add = t - (sumL - l[i]); // adjust for current segment's contribution
          best = Math.Max(best, rangeTotal + add);
        }
        Console.WriteLine(best);
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/