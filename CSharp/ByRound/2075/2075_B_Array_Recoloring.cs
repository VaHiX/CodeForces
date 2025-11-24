// Problem: CF 2075 B - Array Recoloring
// https://codeforces.com/contest/2075/problem/B

/*
B. Array Recoloring
Algorithm: Greedy with sorting and case analysis.
Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing the array.

The problem involves choosing k elements to paint blue, then propagating blue color 
to neighboring red elements until all are blue. The cost is the sum of the first k 
elements chosen and the last element painted (which may not be among the first k).

Approach:
- If k == 1, we consider two cases: either the maximum element is at an endpoint,
  or it's in the middle. In the former case, we sort and pick the max + second largest.
  In the latter, take max + max of first and last.
- For k > 1:
  - Sort the array in descending order.
  - Take the sum of the first k+1 elements (since the last one painted will be
    the k-th element in the sorted list).
  - Return that sum.
*/

using static System.Math;
using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var k = int.Parse(line[1]);
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, long.Parse);
      getAns(n, k, a);
    }
  }
  static long k1(int n, long[] a) {
    var amax = a.Max();
    if (a[0] == amax | a[n - 1] == amax) { // If max is at an endpoint
      Array.Sort(a); // Sort ascending to get second largest at index n-2
      return amax + a[n - 2];
    } else
      return Max(a[0], a[n - 1]) + amax; // Max of first/last + overall max
  }
  static void getAns(int n, int k, long[] a) {
    if (k == 1) {
      Console.WriteLine(k1(n, a));
      return;
    }
    Array.Sort(a); // Sort descending to get largest elements first
    Array.Reverse(a);
    var s = a.Take(k + 1).Sum(); // Take first k+1 elements (sum includes last painted)
    Console.WriteLine(s);
  }
}


// https://github.com/VaHiX/codeForces/