// Problem: CF 1909 C - Heavy Intervals
// https://codeforces.com/contest/1909/problem/C

/*
Algorithm: Greedy + Event Processing
Time Complexity: O(n log n) due to sorting operations
Space Complexity: O(n) for storing lists and tuples

This solution uses a sweep line approach to determine the optimal assignment of intervals.
We process all interval endpoints (left and right) as events and track how many intervals
are active at any point. The key insight is that to minimize total weight, we should:
1. Assign the largest weights (c values) to the intervals with the largest lengths.
2. We use a sweep line to compute interval lengths optimally by matching left and right endpoints.
3. We sort weights in descending order and lengths in ascending order to apply greedy strategy.
*/

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    try {
      Console.SetIn(new System.IO.StreamReader(Console.OpenStandardInput(),
                                               Console.InputEncoding, false,
                                               bufferSize: 1024));
      Console.SetOut(new System.IO.StreamWriter(Console.OpenStandardOutput(),
                                                Console.OutputEncoding,
                                                bufferSize: 1024));
      int t = int.Parse(Console.ReadLine());
      for (int testCase = 0; testCase < t; testCase++) {
        int n = int.Parse(Console.ReadLine());
        List<long> l = new List<long>();
        List<long> r = new List<long>();
        List<long> c = new List<long>();
        List<long> w = new List<long>(); // Stores interval lengths
        List<Tuple<long, long>> v = new List<Tuple<long, long>>(); // Stores events (endpoint, type: 0 for left, 1 for right)
        string[] lArray = Console.ReadLine().Split();
        foreach (string num in lArray) {
          l.Add(long.Parse(num));
          v.Add(new Tuple<long, long>(long.Parse(num), 0)); // 0 indicates left endpoint
        }
        string[] rArray = Console.ReadLine().Split();
        foreach (string num in rArray) {
          r.Add(long.Parse(num));
          v.Add(new Tuple<long, long>(long.Parse(num), 1)); // 1 indicates right endpoint
        }
        string[] cArray = Console.ReadLine().Split();
        foreach (string num in cArray) {
          c.Add(long.Parse(num));
        }
        List<long> cur = new List<long>(); // Tracks active left endpoints
        v.Sort(); // Sort events by endpoint value
        foreach (Tuple<long, long> x in v) {
          if (x.Item2 == 0) {
            // Left endpoint: add to current active set
            cur.Add(x.Item1);
          } else {
            // Right endpoint: compute length and remove corresponding left endpoint
            w.Add(x.Item1 - cur[cur.Count - 1]);
            cur.RemoveAt(cur.Count - 1);
          }
        }
        w.Sort(); // Sort lengths in ascending order
        c.Sort((a, b) => b.CompareTo(a)); // Sort weights in descending order
        long ans = 0;
        for (int i = 0; i < n; i++) {
          // Multiply smallest length with largest weight to minimize sum
          ans += (w[i] * c[i]);
        }
        Console.WriteLine($"{ans}");
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
}


// https://github.com/VaHiX/CodeForces/