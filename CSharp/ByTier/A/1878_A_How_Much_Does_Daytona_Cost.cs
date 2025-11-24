// Problem: CF 1878 A - How Much Does Daytona Cost?
// https://codeforces.com/contest/1878/problem/A

using System;
namespace codeForces {
internal class Program {
  static void Main(string[] args) {
    long testCases = long.Parse(Console.ReadLine()); // Read number of test cases
    for (long i = 0; i < testCases; ++i) {
      string[] NK = Console.ReadLine().Split(); // Read n and k
      string[] vals = Console.ReadLine().Split(); // Read the array elements
      bool found = false; // Flag to check if k exists in the array
      for (int j = 0; j < vals.Length; ++j) {
        if (vals[j] == NK[1]) { // Check if current element equals k
          found = true;
          break; // If found, no need to continue
        }
      }
      Console.WriteLine(found ? "Yes" : "No"); // Output result
    }
  }
}
}
/*
Purpose: Determine if a given integer k appears in the array such that it can be the most common element in some subsegment.
Algorithm: Check if k exists in the input array. If it does, then there exists at least one subsegment where k is the most common element (since it occurs at least once and no other element can have higher frequency in a single-element subsegment).
Time Complexity: O(n) per test case where n is the size of the array.
Space Complexity: O(n) for storing the array elements.
*/

// https://github.com/VaHiX/CodeForces/