// Problem: CF 2117 E - Lost Soul
// https://codeforces.com/contest/2117/problem/E

/*
E. Lost Soul

Algorithm: 
The problem involves maximizing the number of matching elements between two arrays a and b by performing operations where we can change an element of one array to the next element of the other array. We are allowed to remove at most once from both arrays.

Approach:
1. First, we precompute occurrences of each value in both arrays a and b to identify which values appear multiple times.
2. For elements that occur more than once, we track their positions and consider using the second last occurrence as a potential candidate for maximizing matches.
3. Also, for each common value between arrays, we examine if it's better to take minimum of last occurrences or use one of the last indices directly.
4. Since there's an option to remove an element from both arrays at most once, we track the best possible scenario considering that removal.

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm processes each array element once to build position mappings and then applies multiple passes to evaluate match configurations.
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
      var a = Array.ConvertAll(line, int.Parse);
      line = Console.ReadLine().Trim().Split(' ');
      var b = Array.ConvertAll(line, int.Parse);
      getAns(n, a, b);
    }
  }
  static void getAns(int n, int[] a, int[] b) {
    var da = new Dictionary<int, List<int>>(); // Store positions of each value in array a
    var db = new Dictionary<int, List<int>>(); // Store positions of each value in array b
    for (int i = 0; i < n; i++) {
      if (da.ContainsKey(a[i]))
        da[a[i]].Add(i);
      else
        da[a[i]] = new List<int>() { i };
      if (db.ContainsKey(b[i]))
        db[b[i]].Add(i);
      else
        db[b[i]] = new List<int>() { i };
    }
    var ans = -1;
    // Check all values in a that appear at least twice
    foreach (var x in da) {
      var t = x.Value.Count;
      if (t >= 2)
        ans = Max(ans, x.Value[t - 2]); // Consider the second last occurrence index
    }
    // Check all values in b that appear at least twice
    foreach (var x in db) {
      var t = x.Value.Count;
      if (t >= 2)
        ans = Max(ans, x.Value[t - 2]); // Consider the second last occurrence index
    }
    // Compare matching values from both arrays
    foreach (var x in da) {
      if (db.ContainsKey(x.Key)) {
        var tt0 = x.Value[x.Value.Count - 1]; // Last occurrence of value in a
        var tt1 = db[x.Key][db[x.Key].Count - 1]; // Last occurrence of same value in b
        var def = Abs(tt0 - tt1);
        if (def == 0)
          ans = Max(ans, tt0); // If they're equal, we consider it as matched
        else if (def > 1)
          ans = Max(ans, Min(tt0, tt1)); // If there's a gap larger than 1, we can align at the smaller index
      }
    }
    Console.WriteLine(ans + 1);
  }
}


// https://github.com/VaHiX/CodeForces/