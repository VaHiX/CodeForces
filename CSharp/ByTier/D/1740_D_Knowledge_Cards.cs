// Problem: CF 1740 D - Knowledge Cards
// https://codeforces.com/contest/1740/problem/D

/* 
 * Problem: D. Knowledge Cards
 * 
 * Purpose: Determine if it's possible to move k cards from cell (1,1) to cell (n,m) such that the final stack has numbers 1 to k in order from top to bottom.
 * 
 * Approach:
 * - This problem is about validating whether a given permutation can be rearranged using a specific movement rule.
 * - The key insight is that we simulate the process of moving cards using a greedy approach, tracking the state of intermediate positions.
 * - We use a SortedSet to maintain a set of "active" cards to simulate constraints.
 * 
 * Time Complexity: O(k * log k) per test case, due to operations on SortedSet.
 * Space Complexity: O(k) for storing the array and auxiliary data structures.
 * 
 * Techniques:
 * - Greedy simulation
 * - SortedSet for efficient insertion and deletion
 * - Tracking max element to optimize set operations
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
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      var b =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      bool can = true;
      int m = a[0];
      int n = a[1];
      int k = a[2];
      
      // Early check: if total cells minus 5 is less than k, impossible
      if (m * n - 5 < k) {
        SortedSet<int> sb = new SortedSet<int>(b);  // Copy of input to track remaining elements
        SortedSet<int> field = new SortedSet<int>(); // Tracks active cards that are not yet in final order
        int cm = sb.Max; // Max element currently in sb
        int om = cm;     // Keep original max to compare with
        for (int i = 0; i < k; i++) {
          int d = b[i];  // Current element to process
          sb.Remove(d);  // Remove from available set
          int limit = m * n - 4; // Capacity limit for field
          if (field.Count > limit) {  // If too many cards are currently active, impossible
            can = false;
            break;
          }
          if (d == cm) {  // If the current card is the max, update cm to next max
            cm = sb.Max;
            // Remove all elements from field that are larger than new max
            while (field.Max > cm)
              field.Remove(field.Max);
          } else {
            // Add current card to field (as it's not in final order yet)
            field.Add(d);
          }
        }
      }
      if (can)
        output.Add("YA");
      else
        output.Add("TIDAK");
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/