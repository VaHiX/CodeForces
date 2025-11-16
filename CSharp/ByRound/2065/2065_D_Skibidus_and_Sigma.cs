// Problem: CF 2065 D - Skibidus and Sigma
// https://codeforces.com/contest/2065/problem/D

/*
 * Problem: D. Skibidus and Sigma
 * 
 * Purpose:
 *   Given n arrays of m integers each, we are to concatenate them in an optimal order
 *   such that the total "sigma score" is maximized. The sigma score of an array b
 *   with k elements is defined as the sum S_1 + S_2 + ... + S_k where S_i is the prefix sum
 *   up to index i.
 * 
 * Algorithm:
 *   - For each array, compute its prefix sum and total sum (using calc function)
 *   - Sort arrays by their total sum in ascending order
 *   - Compute the final score using greedy assignment: assign smaller sums earlier to reduce 
 *     the impact of repeated prefix sums at later positions (this is a classic greedy optimization).
 * 
 * Time Complexity:
 *   O(n * m + n * log n) per test case, dominated by sorting and processing arrays.
 *   
 * Space Complexity:
 *   O(n) for storing array data and intermediate results.
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var m = int.Parse(line[1]);
      getAns(n, m); // Process the current test case
    }
  }
  
  // Calculates prefix sum based score and total sum of array a
  static (long s, long f) calc(int m, long[] a) {
    var p = m;
    var res = 0L;
    var s = 0L;
    for (int i = 0; i < m; i++) {
      res += p-- * a[i]; // Multiply current element by its "weight" in the final sum
      s += a[i];
    }
    return (s, res);
  }
  
  // Computes the maximum possible score by optimally arranging arrays
  static void getAns(int n, int m) {
    var t = new(long s, int id)[n]; // Array to store total sum and original index of each array
    var sum = 0L;
    for (int i = 0; i < n; i++) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, long.Parse);
      var w = calc(m, a); // Get total sum and weighted sum for current array
      t[i] = (w.s, i);   // Store total sum with index
      sum += w.f;        // Add the contribution of this array to overall score
    }
    
    t = t.OrderBy(x => x.s).ToArray(); // Sort by total sum ascending
    
    // Now compute the additional contribution from ordering: 
    // earlier arrays contribute less to later prefix sums, so we want smaller ones first
    for (int i = 1; i < n; i++) {
      sum += (m * (long)(i)) * t[i].s; // Multiply total sum of array by its position weight
    }
    
    Console.WriteLine(sum); // Output the maximum possible score
  }
}


// https://github.com/VaHiX/codeForces/