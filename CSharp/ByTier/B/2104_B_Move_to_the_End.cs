// Problem: CF 2104 B - Move to the End
// https://codeforces.com/contest/2104/problem/B

/*
B. Move to the End
Algorithm: Preprocessing with prefix and suffix arrays to efficiently compute maximum sums of last k elements after moving one element to the end.
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

For each k from 1 to n:
- We want to maximize the sum of the last k elements after moving one element to the end.
- To do this efficiently, we precompute:
  - b[i]: maximum value from a[0] to a[i]
  - c[i]: sum of elements from a[i] to a[n-1]
- Then for each position i, we decide whether moving a[i] to the end gives a better result.

The approach is based on choosing the element that maximizes the final sum:
- If a[i] >= b[i-1], moving a[i] makes the k-largest elements in the last k positions include the full sum from index i onwards.
- Otherwise, we can replace a[i] with the maximum value seen so far (from prefix) to achieve a higher sum.
*/

using static System.Math;
using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, long.Parse);
      getAns(n, a);
    }
  }
  static void getAns(int n, long[] a) {
    var b = new long[n]; // b[i] stores maximum value from index 0 to i
    b[0] = a[0];
    for (int i = 1; i < n; i++)
      b[i] = Max(b[i - 1], a[i]);
    
    var c = new long[n]; // c[i] stores suffix sum from index i to n-1
    c[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; i--)
      c[i] = c[i + 1] + a[i];
    
    var ans = new List<long>();
    for (int i = n - 1; i >= 1; i--) {
      // If current element is greater than or equal to maximum seen so far,
      // moving it to the end won't affect the suffix sum
      if (a[i] >= b[i - 1])
        ans.Add(c[i]);
      else
        // Otherwise, replace a[i] with the best possible value (the max seen before)
        ans.Add(c[i] - a[i] + b[i - 1]);
    }
    ans.Add(c[0]); // Add full sum for k = n
    Console.WriteLine(string.Join(" ", ans));
  }
}


// https://github.com/VaHiX/codeForces/