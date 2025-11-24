// Problem: CF 1696 D - Permutation Graph
// https://codeforces.com/contest/1696/problem/D

/*
 * Problem: D. Permutation Graph
 * 
 * Purpose: Given a permutation of integers from 1 to n, construct an undirected graph where nodes are indices 
 *          and edges exist based on specific min/max conditions over subarrays. Find the shortest path from node 1 to node n.
 * 
 * Approach:
 * - We process the permutation from left to right, keeping track of the current "peak" value and the direction of the sequence (increasing or decreasing).
 * - We use a greedy method to determine when to increment the path length, based on whether we are in an increasing or decreasing subsequence.
 * - Precompute maximum and minimum values to the right of each index (upcomingMax and upcomingMin arrays).
 * 
 * Time Complexity: O(n) per test case, as we make a single pass through the array and precompute arrays in linear time.
 * Space Complexity: O(n) for storing the arrays and auxiliary variables.
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = int.Parse(Console.ReadLine());
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      long o = 0; // Output counter for number of edges in shortest path
      long[] upcomingMax = new long[n]; // Precompute max values to the right of each index
      long[] upcomingMin = new long[n]; // Precompute min values to the right of each index
      long cmin = n + 2; // current minimum value seen so far from the right
      long cmax = -1; // current maximum value seen so far from the right
      for (int i = n - 1; i >= 0; i--) {
        upcomingMax[i] = cmax; // Store max value to the right
        upcomingMin[i] = cmin; // Store min value to the right
        if (a[i] > cmax)
          cmax = a[i]; // Update max
        if (a[i] < cmin)
          cmin = a[i]; // Update min
      }
      int currentFirstEdge = 0; // Tracks if we are in an increasing (1) or decreasing (-1) sequence
      long currentFirstValue = a[0]; // Current value at the start of the current segment
      long currentPeak = 0; // Tracks peak value of current segment
      for (int i = 1; i < n; i++) {
        if (currentFirstEdge == 0) {
          // Initialize direction based on first two elements
          if (a[1] > a[0])
            currentFirstEdge = -1; // Decrementing
          else
            currentFirstEdge = 1; // Incrementing
          currentPeak = a[1]; // Set initial peak
          o++; // Always increment count on first transition
        } else {
          if (currentFirstEdge == 1) {
            // We are in an increasing segment
            if (a[i] < currentPeak) {
              // If value is less than current peak, we are breaking the increasing sequence
              currentPeak = a[i]; // Update peak
              continue;
            }
            // Check for transition to decreasing sequence
            if (a[i] > currentFirstValue || upcomingMin[i] > currentPeak) {
              o++; // Increment path length
              currentFirstValue = currentPeak; // Reset start of new segment
              currentPeak = a[i]; // Update peak
              currentFirstEdge *= -1; // Change direction to decreasing
            }
          } else {
            // We are in a decreasing segment
            if (a[i] > currentPeak) {
              // If value is greater than current peak, we are breaking the decreasing sequence
              currentPeak = a[i]; // Update peak
              continue;
            }
            // Check for transition to increasing sequence
            if (a[i] < currentFirstValue || upcomingMax[i] < currentPeak) {
              o++; // Increment path length
              currentFirstValue = currentPeak; // Reset start of new segment
              currentPeak = a[i]; // Update peak
              currentFirstEdge *= -1; // Change direction to increasing
            }
          }
        }
      }
      output.Add(o.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/