// Problem: CF 2057 B - Gorilla and the Exam
// https://codeforces.com/contest/2057/problem/B

/*
B. Gorilla and the Exam
Problem Description:
Given an array 'a' of length n and an integer k, we can change at most k elements in the array.
We define f(b) as the minimum number of operations to empty array b, where each operation removes 
all occurrences of the minimum element in some contiguous subarray.
Goal: Minimize f(a) after making at most k changes.

Algorithms/Techniques:
- Count frequency of elements in array
- Sort frequencies in ascending order
- Greedily remove the least frequent elements to minimize operations
- Time complexity: O(n log n) due to sorting
- Space complexity: O(n) for dictionary storage

*/

using System.Linq;
using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var k = int.Parse(line[1]);
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      getAns(n, k, a);
    }
  }
  static void getAns(int n, int k, int[] a) {
    var d = new Dictionary<int, int>(); // Count frequency of each element
    foreach (var x in a)
      if (d.ContainsKey(x))
        d[x]++;
      else
        d[x] = 1;
    var e = d.OrderBy(x => x.Value).ToArray(); // Sort by frequency
    var c = 0; // Number of elements we can remove completely
    for (int i = 0; i < d.Count - 1; i++) {
      if (k - e[i].Value >= 0) { // If we have enough changes to remove all occurrences of this element
        k -= e[i].Value;
        c++; // Increment count of removed elements
      } else
        break;
    }
    Console.WriteLine(d.Count - c); // Remaining number of distinct elements is the answer
  }
}


// https://github.com/VaHiX/codeForces/