// Problem: CF 2070 C - Limited Repainting
// https://codeforces.com/contest/2070/problem/C

/*
C. Limited Repainting

Algorithms/Techniques: Binary Search + Greedy Segment Selection
Time Complexity: O(n * log(max_a)) where max_a is the maximum value in array a
Space Complexity: O(n)

Problem Description:
We are given a strip of n cells, initially all red. Each cell has a desired color ('R' or 'B') and a penalty value if it ends up wrong.
We can perform at most k operations, each operation painting a segment of consecutive cells blue (cannot paint to red).
Goal is to minimize the maximum penalty among all incorrectly colored cells.

Approach:
Binary search on the answer (penalty value). For a given penalty threshold,
we greedily select segments of operations such that we avoid coloring cells with penalty > threshold.
The greedy selection uses two pointers to find the minimal number of operations needed.
*/

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var input = Console.ReadLine().Split();
      int n = int.Parse(input[0]), k = int.Parse(input[1]);
      string s = Console.ReadLine();
      var a = Console.ReadLine().Split().Select(long.Parse).ToList();
      long maxA = a.Max(); // Find maximum penalty to set binary search bounds
      long lo = 0, hi = maxA, ans = hi; // Binary search on penalty value
      while (lo <= hi) {
        long mid = lo + (hi - lo) / 2; // Midpoint of current search range
        int ops = 0, i = 0;
        while (i < n) { // Traverse the string to count operations needed
          if (s[i] == 'B' && a[i] > mid) { // If cell should be blue but penalty exceeds threshold
            ops++; // We need an operation starting from this position
            while (i < n && !(s[i] == 'R' && a[i] > mid)) // Skip until next red cell with high penalty or end
              i++;
          } else {
            i++; // Move forward in string
          }
        }
        if (ops <= k) { // If operations needed are within limit
          ans = mid; // Record this as valid answer
          hi = mid - 1; // Try smaller penalty
        } else {
          lo = mid + 1; // Need more operations, try higher penalty
        }
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/codeForces/