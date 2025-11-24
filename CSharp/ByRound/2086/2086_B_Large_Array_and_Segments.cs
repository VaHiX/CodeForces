// Problem: CF 2086 B - Large Array and Segments
// https://codeforces.com/contest/2086/problem/B

/*
 * Problem: B. Large Array and Segments
 * 
 * Purpose:
 *   Given an array 'a' of n positive integers and a positive integer k,
 *   create an infinite periodic array 'b' where b[i] = a[i % n].
 *   For each starting position l in [1, n*k], we count how many such l exist
 *   for which there exists a position r >= l such that the sum of elements 
 *   from b[l] to b[r] is at least x.
 *   
 * Algorithm:
 *   - Compute the total sum of array 'a' as 'asum'.
 *   - If x is divisible by asum, use prefix sums and reverse array logic for optimization.
 *   - Otherwise, iterate through elements in reversed order to determine valid segments.
 *   - Use a sliding window approach combined with prefix techniques.
 *   
 * Time Complexity: O(n * k) per test case, but optimized with early termination.
 * Space Complexity: O(n), for storing the input array and temporary variables.
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var k = int.Parse(line[1]);
      var x = long.Parse(line[2]);
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, long.Parse);
      getAns(n, k, x, a); // Process current test case
    }
  }
  
  static void getAns(int n, int k, long x, long[] a) {
    var asum = a.Sum(); // Calculate total sum of array 'a'
    var t = x / asum; // Number of full cycles of 'a' needed in the segment (approximate)
    
    Array.Reverse(a); // Reverse the array to simulate backward scan
    var tsum = t * asum; // Sum from t complete cycles
    var w = tsum; // Current sum while scanning
    
    if (w == x) { // If full multiples exact match
      var ww = n * (k - t) + 1; // Compute result using formula for remaining positions
      if (ww <= 0)
        Console.WriteLine(0); // Output zero if negative or zero
      else
        Console.WriteLine(ww);
      return;
    }
    
    // Iterate through reversed array to find valid segments and count suitable indices
    for (int i = 0; i < n; i++) {
      w += a[i]; // Add next element from reversed prefix
      if (w >= x) { // If we've reached or exceeded target sum
        var www = (long)n * k - (t * n + i); // Calculate number of valid positions left
        if (www <= 0)
          Console.WriteLine(0); // Output zero if negative or zero
        else
          Console.WriteLine(www);
        return;
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/