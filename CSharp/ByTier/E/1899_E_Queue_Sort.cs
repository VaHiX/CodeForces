// Problem: CF 1899 E - Queue Sort
// https://codeforces.com/contest/1899/problem/E

// Purpose: 
// This code determines the minimum number of operations required to sort an array 
// using a specific set of operations: extract the first element and insert it at the end,
// then swap it with the previous element until it becomes the first or strictly greater than the previous one.
// The algorithm identifies the minimum element and checks if the array can be sorted by rotating it to start at the minimum element.
//
// Algorithms/Techniques:
// - Linear search to find the index of the minimum element
// - Check if the subarray from the minimum element to the end is sorted in non-decreasing order
//
// Time Complexity: O(n) per test case, where n is the size of the array
// Space Complexity: O(n) due to storing the input array

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()); // Read array length
      List<int> v = Console.ReadLine().Split().Select(int.Parse).ToList(); // Read array elements
      int mini = int.MaxValue;
      int idx = -1;
      for (int i = 0; i < n; i++) {
        if (v[i] < mini) { // Find the index of the minimum element
          mini = v[i];
          idx = i;
        }
      }
      bool isSorted = true;
      for (int i = idx; i < n - 1; i++) {
        if (v[i] > v[i + 1]) { // Check if the subarray from minimum index to end is sorted
          isSorted = false;
          break;
        }
      }
      if (isSorted)
        Console.WriteLine(idx); // If sorted, output number of operations (index of minimum element)
      else
        Console.WriteLine("-1"); // If not possible, output -1
    }
  }
}


// https://github.com/VaHiX/CodeForces/