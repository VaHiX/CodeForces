// Problem: CF 1771 B - Hossam and Friends
// https://codeforces.com/contest/1771/problem/B

﻿/*
 * Problem: Hossam and Friends
 * 
 * Purpose:
 *   Given n friends arranged in a queue from 1 to n, and a list of m pairs who do not know each other,
 *   we need to count the number of "good" subsegments. A good subsegment is one where all pairs of friends
 *   in the subsegment are friends (i.e., no pair from the given list appears in the subsegment).
 *   
 * Algorithm:
 *   - Use a segment-based approach with a difference array technique.
 *   - For each pair (x, y) that are not friends, we mark intervals that cannot be part of any good subsegment.
 *   - We use two pointers or a greedy approach to track valid subsegments ending at each index.
 *   - For every index, calculate how many valid subsegments end at that index and add to total count.
 *   
 * Time Complexity: O(n + m)
 *   - We parse the input once (O(m)).
 *   - We iterate over n elements once (O(n)).
 *   
 * Space Complexity: O(n)
 *   - We store a 2D array of size n x 2 to represent segments.
 *   
 * Techniques:
 *   - Difference array technique to mark forbidden intervals.
 *   - Greedy approach to compute valid subsegments ending at each position.
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
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      long o = 0;  // Total number of good subsegments
      long n = a[0];
      long[,] d = new long[n, 2];  // Segment array to mark forbidden intervals
      for (int i = 0; i < a[1]; i++) {
        var b =
            Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
        // Swap so that b[0] is the larger index and b[1] is the smaller
        if (b[1] < b[0]) {
          d[b[0] - 1, 0] = Math.Max(d[b[0] - 1, 0], b[1]);
        } else {
          d[b[1] - 1, 0] = Math.Max(d[b[1] - 1, 0], b[0]);
        }
      }
      long cs = 0;  // Current start of the valid interval
      for (int i = 0; i < n; i++) {
        // Update the current valid start based on previous forbidden segments
        if (d[i, 0] > cs) {
          cs = d[i, 0];
        }
        // Count how many good intervals end at index i
        o += (i + 1 - cs);
      }
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/