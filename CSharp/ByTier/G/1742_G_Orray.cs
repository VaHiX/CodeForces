// Problem: CF 1742 G - Orray
// https://codeforces.com/contest/1742/problem/G

﻿/*
 * Purpose: Rearrange an array of non-negative integers to achieve the lexicographically maximum prefix OR array.
 * Algorithm: Greedily select elements that maximize the prefix OR value at each step.
 * 
 * Time Complexity: O(n^2) in worst case due to nested loops, but in practice much faster due to early exits.
 * Space Complexity: O(n) for storing the input and output arrays.
 * 
 * Techniques:
 * - Greedy approach to maximize lexicographical prefix OR
 * - Dynamic selection of elements based on OR results
 * - Bitwise OR operations to compute prefix values
 */

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int fyt = int.Parse(Console.ReadLine()); // Read number of test cases
    List<string> output = new List<string>(); // Store results for output
    for (int z = 0; z < fyt; z++) {
      var n = long.Parse(Console.ReadLine()); // Read array length
      var a = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList(); // Read array elements
      List<long> o = new List<long>(); // Result list to store rearranged array
      long dp = 1; // Variable to track whether we found a better element
      long cp = 0; // Current prefix OR value
      while (dp > 0) { // Continue until no improvement can be made
        int id = 0; // Index of best element found
        long np = cp; // New prefix OR value if we select that element
        dp = 0; // Reset for next iteration
        for (int i = 0; i < n; i++) { // Loop through all available elements
          if ((a[i] | cp) > np) { // Check if including this element gives a higher prefix OR
            np = a[i] | cp; // Update new prefix OR
            id = i; // Update index
          }
        }
        if (np > cp) { // If we found a better prefix OR
          dp = np - cp; // Difference (not directly used, but helps control loop)
          cp = np; // Update current prefix OR
          o.Add(a[id]); // Add element to result
          a[id] = 0; // Mark as used
        }
      }
      for (int i = 0; i < n; i++) { // Add remaining unused elements
        if (a[i] != 0) {
          o.Add(a[i]);
        }
      }
      output.Add(string.Join(" ", o)); // Format result
    }
    string on = string.Join("\n", output); // Join outputs
    Console.WriteLine(on); // Print all outputs
  }
}
}


// https://github.com/VaHiX/CodeForces/