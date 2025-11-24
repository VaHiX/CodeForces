// Problem: CF 2021 B - Maximize Mex
// https://codeforces.com/contest/2021/problem/B

/*
B. Maximize Mex
Algorithm: Greedy + Hash Map
Time Complexity: O(n)
Space Complexity: O(n)

The problem asks to maximize the MEX (minimum excluded value) by incrementing array elements by x any number of times.

Approach:
1. Group all numbers by their modulo x value.
2. For each group, we can make any number in that group equal to any other number in the same group (by adding multiples of x).
3. We use a greedy strategy: iterate from 0 upwards and try to form a sequence 0, 1, 2, ..., MEX-1 such that each number is available.
4. If for some i, no element exists with mod x == i, it means we can form this number, hence increase MEX.

Key steps:
- Count frequency of elements modulo x
- Iterate up to n + 10 (safety margin)
- For each number i:
  - If there's an element with mod x = i, decrease count and redistribute among other groups.
  - Else if we can form it with current group counts, then break and return this number as MEX.

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
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      getAns(n, x, a);
    }
  }
  static void getAns(int n, int x, int[] a) {
    var d = new Dictionary<int, int>(); // Frequency map of modulo x values
    foreach (var z in a) {
      if (d.ContainsKey(z))
        d[z]++;
      else
        d[z] = 1;
    }
    var r = new Dictionary<int, int>(); // Tracks how many elements we have of each mod x group
    for (int i = 0; i <= n + 10; i++) { // Iterate up to safe limit
      if (d.ContainsKey(i)) {
        d[i]--;
        if (d[i] > 0) {
          var w = i % x;
          if (r.ContainsKey(w))
            r[w] += d[i];
          else
            r[w] = d[i];
        }
      } else {
        var rr = i % x; // Current value's modulo
        if (r.ContainsKey(rr)) {
          r[rr]--; // Use one element from this group
          if (r[rr] == 0)
            r.Remove(rr);
        } else {
          Console.WriteLine(i); // Found missing number, return it as MEX
          return;
        }
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/