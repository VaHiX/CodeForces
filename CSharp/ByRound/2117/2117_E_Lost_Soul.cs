// Problem: CF 2117 E - Lost Soul
// https://codeforces.com/contest/2117/problem/E

/*
 * Problem: E. Lost Soul
 * Purpose: Given two arrays a and b of length n, compute the maximum number of matches 
 *          achievable after performing operations on elements and optionally removing 
 *          one index from each array.
 * 
 * Algorithms/Techniques:
 * - Hash map to store indices for each value in both arrays
 * - Greedy approach to maximize matching positions by considering:
 *     1. Duplicate values in a or b (using second last occurrence)
 *     2. Same values in both arrays (using minimum of last occurrences)
 * 
 * Time Complexity: O(n), where n is the length of the array.
 * Space Complexity: O(n), for storing indices in hash maps.
 */

using static System.Math;
using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read length of arrays
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array a
      var a = Array.ConvertAll(line, int.Parse);
      line = Console.ReadLine().Trim().Split(' '); // Read array b
      var b = Array.ConvertAll(line, int.Parse);
      getAns(n, a, b); // Process the current test case
    }
  }
  
  static void getAns(int n, int[] a, int[] b) {
    var da = new Dictionary<int, List<int>>(); // Store indices for each value in array a
    var db = new Dictionary<int, List<int>>(); // Store indices for each value in array b
    
    // Populate dictionaries with indices of each element
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
    
    var ans = -1; // Initialize answer with -1
    
    // Check for duplicates in a and update answer with second-to-last index
    foreach (var x in da) {
      var t = x.Value.Count;
      if (t >= 2)
        ans = Max(ans, x.Value[t - 2]);
    }
    
    // Check for duplicates in b and update answer with second-to-last index
    foreach (var x in db) {
      var t = x.Value.Count;
      if (t >= 2)
        ans = Max(ans, x.Value[t - 2]);
    }
    
    // For common elements in both arrays, check optimal overlap
    foreach (var x in da) {
      if (db.ContainsKey(x.Key)) {
        var tt0 = x.Value[x.Value.Count - 1]; // Last index in array a for current key
        var tt1 = db[x.Key][db[x.Key].Count - 1]; // Last index in array b for current key
        var def = Abs(tt0 - tt1); // Absolute difference of last indices
        
        if (def == 0)
          ans = Max(ans, tt0); // If same index, use it
        else if (def > 1)
          ans = Max(ans, Min(tt0, tt1)); // If far apart, use the smaller index
      }
    }
    
    Console.WriteLine(ans + 1); // Print result (convert 0-based to 1-based indexing)
  }
}


// https://github.com/VaHiX/CodeForces/