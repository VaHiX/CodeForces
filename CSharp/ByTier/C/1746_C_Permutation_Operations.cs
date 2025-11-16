// Problem: CF 1746 C - Permutation Operations
// https://codeforces.com/contest/1746/problem/C

﻿/*
 * Problem: C. Permutation Operations
 * 
 * Algorithm: Greedy approach with suffix operations to minimize inversions
 * 
 * Time Complexity: O(n log n) due to sorting the differences
 * Space Complexity: O(n) for storing operations and differences
 * 
 * Approach:
 * 1. For each operation i, we can increase a suffix by i.
 * 2. To minimize inversions, we want to make the array as sorted as possible.
 * 3. This problem can be solved by considering how much each element needs to "catch up"
 *    with the previous elements in a sorted way.
 * 4. Calculate the difference array and sort based on the required increments.
 * 5. Process differences greedily to assign operations.
 * 
 * Key Points:
 * - We track the required increments per suffix to bring the array closer to sorted.
 * - Apply operations in order of increasing increment requirement.
 * - Final elements are handled at the end.
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine()); // Read number of test cases
    List<string> output = new List<string>(); // Store results for output
    
    for (int z = 0; z < count; z++) {
      var a = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList(); // Read n
      var b = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList(); // Read permutation
      
      List<int> o = new List<int>(); // Store operations
      List<int[]> d = new List<int[]>(); // Store suffix indices and required increments
      
      // Compute differences for each position (from 1 to n-1)
      for (int i = 1; i < a[0]; i++) {
        d.Add(new int[2] { i + 1, (int)(-b[i] + b[i - 1]) }); // Difference represents needed adjustment
      }
      
      // Filter out non-positive differences and sort by difference value
      d = d.Where(i => i[1] > 0).OrderBy(i => i[1]).ToList();
      
      int ro = 1; // Operation counter
      
      // Process each difference
      for (int i = 0; i < d.Count; i++) {
        int k = d[i][1]; // Required increment
        int id = d[i][0]; // Suffix starting index
        
        // While we need more increments, perform operations
        while (k > 0) {
          k -= ro; // Apply operation of size ro
          ro++; // Increase operation size for next operation
          o.Add(id); // Record that we applied operation on suffix starting at id
        }
      }
      
      // Handle remaining operations for elements from ro to n
      for (int i = ro; i <= a[0]; i++)
        o.Add(1); // Apply operation on suffix starting at index 1
      
      output.Add(string.Join(" ", o)); // Add result to output
    }
    
    output.ForEach(d => Console.WriteLine(d)); // Print all results
  }
}
}


// https://github.com/VaHiX/CodeForces/