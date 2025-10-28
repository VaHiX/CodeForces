// Problem: CF 2137 D - Replace with Occurrences
// https://codeforces.com/contest/2137/problem/D

/*
D. Replace with Occurrences
Algorithm: Greedy construction based on frequency mapping and grouping.
Time Complexity: O(n) amortized per test case, due to sum of n over all test cases being bounded by 2*10^5.
Space Complexity: O(n) for storing positions and result array.

Approach:
- For each value v from 1 to n, we collect all indices where b[i] == v.
- Check if the count of such indices is divisible by v. If not, no valid assignment exists.
- Otherwise, assign labels greedily: group the indices in chunks of size v and assign sequential labels starting from 1.

The problem is about reconstructing an array a such that f(a_i) = b_i for all i,
where f(x) is the count of occurrences of x in a.
*/

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()!); // Read number of test cases
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()!); // Read array size
      int[] b = Console.ReadLine()!.Split().Select(int.Parse).ToArray(); // Read b array
      List<int>[] positions = new List<int>[n + 1]; // Positions where each value occurs
      for (int i = 0; i <= n; i++)
        positions[i] = new List<int>();
      for (int i = 0; i < n; i++) {
        positions[b[i]].Add(i); // Group indices by their values in b
      }
      bool valid = true;
      for (int v = 1; v <= n; v++) {
        if (positions[v].Count % v != 0) { // If count of occurrences is not divisible by v, impossible to assign
          valid = false;
          break;
        }
      }
      if (!valid) {
        Console.WriteLine("-1"); // No valid solution exists
        continue;
      }
      int[] a = new int[n]; // Result array to be constructed
      int label = 1; // Label for assigning unique numbers to positions
      for (int v = 1; v <= n; v++) {
        var posList = positions[v]; // Get list of indices where value v appears
        for (int i = 0; i < posList.Count; i += v) { // For each group of size v
          for (int j = 0; j < v; j++) {
            a[posList[i + j]] = label; // Assign same label to all indices in current group
          }
          label++; // Move to next label for next group
        }
      }
      Console.WriteLine(string.Join(" ", a)); // Output constructed array
    }
  }
}


// https://github.com/VaHiX/codeForces/