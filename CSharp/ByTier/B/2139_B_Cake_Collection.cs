// Problem: CF 2139 B - Cake Collection
// https://codeforces.com/contest/2139/problem/B

/*
B. Cake Collection
Algorithms/Techniques: Greedy algorithm with sorting

Time Complexity: O(n log n + n) per test case, where n is the number of ovens.
Space Complexity: O(n) for storing the array of cake rates.

The problem involves maximizing the number of cakes collected over m seconds,
where each oven produces a_i cakes per second. At each second, Maple can switch
to any oven and collect all accumulated cakes from that oven. This is a greedy
problem where we want to collect from the oven with the highest production rate
at each step.

Approach:
1. Sort ovens in descending order of cake production rate.
2. For the first 'm' seconds, take the top 'min(n, m)' ovens and accumulate
   their contributions considering how many seconds have passed (multiplier).
3. The maximum total cakes is computed by summing (a[i] * (m - i)) for i from 0 to min(n, m) - 1.
*/

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var line = Console.ReadLine().Split();
      int n = int.Parse(line[0]);
      long m = long.Parse(line[1]);
      var arr = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
      // Sort ovens in descending order of cake production rate
      Array.Sort(arr, (x, y) => y.CompareTo(x));
      // Determine how many ovens to consider (up to m or n)
      long take = Math.Min(n, (int)m);
      long total = 0;
      // Accumulate maximum cakes by taking from highest production rate ovens
      for (int i = 0; i < take; i++) {
        total += arr[i] * (m - i);
      }
      Console.WriteLine(total);
    }
  }
}


// https://github.com/VaHiX/codeForces/