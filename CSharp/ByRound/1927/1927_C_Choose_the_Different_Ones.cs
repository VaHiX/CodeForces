// Problem: CF 1927 C - Choose the Different Ones!
// https://codeforces.com/contest/1927/problem/C

/*
 * Problem: Choose the Different Ones!
 * 
 * Purpose: Determine if it's possible to choose exactly k/2 elements from each array such that
 *          all integers from 1 to k are included in the chosen elements.
 * 
 * Algorithm:
 * 1. Sort both arrays to facilitate processing.
 * 2. Create two hash sets to store unique elements from each array that are <= k.
 * 3. Check if each set contains at least k/2 elements; otherwise, it's impossible.
 * 4. Combine the sets and verify that all integers from 1 to k are present.
 * 
 * Time Complexity: O(n log n + m log m + k)
 *   - Sorting arrays: O(n log n + m log m)
 *   - Hash set creation and operations: O(n + m + k)
 * 
 * Space Complexity: O(n + m + k)
 *   - Storing elements in hash sets and arrays.
 */

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main(string[] args) {
    long t = long.Parse(Console.ReadLine());
    while (t-- > 0) {
      var tokens = Console.ReadLine().Split().Select(long.Parse).ToArray();
      long n = tokens[0];
      long m = tokens[1];
      long k = tokens[2];
      var a = Console.ReadLine().Split().Select(long.Parse).ToArray();
      var b = Console.ReadLine().Split().Select(long.Parse).ToArray();
      Array.Sort(a); // Sort array a
      Array.Sort(b); // Sort array b
      var st1 = new HashSet<long>(); // Set to store unique elements from a that are <= k
      var st2 = new HashSet<long>(); // Set to store unique elements from b that are <= k
      foreach (var num in a) {
        if (num <= k)
          st1.Add(num);
      }
      foreach (var num in b) {
        if (num <= k)
          st2.Add(num);
      }
      // If either set doesn't have enough unique elements, impossible to choose k/2 from each
      if (st1.Count < k / 2 || st2.Count < k / 2)
        Console.WriteLine("NO");
      else {
        bool f = true; // Flag to check if all numbers 1..k are covered
        var s = new HashSet<long>(); // Combined set of unique elements from both arrays
        foreach (var num in st1) {
          s.Add(num);
        }
        foreach (var num in st2) {
          s.Add(num);
        }
        // Check if all numbers from 1 to k are present in the combined set
        for (long i = 1; i <= k; i++) {
          if (!s.Contains(i)) {
            f = false;
            break;
          }
        }
        if (f)
          Console.WriteLine("YES");
        else
          Console.WriteLine("NO");
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/