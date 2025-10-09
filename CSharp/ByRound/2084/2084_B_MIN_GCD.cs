// Problem: CF 2084 B - MIN = GCD
// https://codeforces.com/contest/2084/problem/B

/*
 * Problem: B. MIN = GCD
 * Purpose: Determine if a sequence can be rearranged such that there exists an index i where 
 *          the minimum of the first i elements equals the GCD of the remaining elements.
 * 
 * Algorithm:
 * 1. Count frequencies of each number in the array.
 * 2. Sort unique numbers in ascending order.
 * 3. Check if any number appears at least twice — if so, answer is "YES".
 * 4. Otherwise, identify numbers that are multiples of the smallest number.
 * 5. Compute GCD of all such multiples and check if it equals the smallest number.
 * 
 * Time Complexity: O(n log n), dominated by sorting; each element is processed once.
 * Space Complexity: O(n), for storing frequency map and sorted list.
 */

using System.Linq;
using System.Collections.Generic;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read length of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements
      var a = Array.ConvertAll(line, long.Parse); // Convert to long array
      getAns(n, a); // Process the test case
    }
  }
  
  static void getAns(int n, long[] a) {
    var d = new Dictionary<long, int>(); // Frequency map of elements
    foreach (var x in a)
      if (d.ContainsKey(x))
        d[x]++; // Increment count if already present
      else
        d[x] = 1; // Initialize count to 1
    
    var e = d.OrderBy(x => x.Key).ToArray(); // Sort unique elements by value
    
    if (e[0].Value >= 2) { // If smallest element occurs at least twice
      Console.WriteLine("YES");
      return;
    }
    
    var f = new List<long>(); // Store multiples of the smallest number
    var m = e.Length;
    var emin = e[0].Key; // Smallest number
    
    for (int i = 1; i < m; i++) { // Check all numbers greater than the smallest
      if (e[i].Key % emin == 0) // If current element is a multiple of the smallest
        f.Add(e[i].Key);
    }
    
    var fc = f.Count; // Count of multiples
    
    if (fc <= 1) { // Less than two multiples => no valid split
      Console.WriteLine("NO");
      return;
    }
    
    var g = Gcd(f[0], f[1]); // Compute GCD of first two multiples
    
    if (g == emin) { // If GCD equals smallest number, we're done
      Console.WriteLine("YES");
      return;
    }
    
    if (fc == 2) { // Only two multiples and their GCD != emin
      Console.WriteLine("NO");
      return;
    }
    
    for (int i = 2; i < fc; i++) { // Continue compute GCD of more multiples
      g = Gcd(g, f[i]);
      if (g == emin) {
        Console.WriteLine("YES");
        return;
      }
    }
    
    Console.WriteLine("NO"); // Final fallback if conditions not met
  }
  
  public static long Gcd(long a, long b) {
    if (a < b)
      return Gcd(b, a); // Ensure a >= b
    
    while (b != 0) {
      var w = a % b; // Remainder of division
      a = b; // Move b into a
      b = w; // Update b
    }
    
    return a; // Return GCD
  }
}


// https://github.com/VaHiX/codeForces/