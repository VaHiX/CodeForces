// Problem: CF 2152 A - Increase or Smash
// https://codeforces.com/contest/2152/problem/A

/*
 * Problem: A. Increase or Smash
 * Purpose: Find the minimum number of operations (Increase and Smash) to transform an array of zeros into a given target array.
 * Algorithms/Techniques:
 *   - Greedy approach: Each unique value in the target array contributes to the number of operations.
 * Time Complexity: O(n), where n is the length of the array. Parsing input and set operations are linear.
 * Space Complexity: O(n), due to storing unique values in a HashSet.
 */

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    if (!int.TryParse(Console.ReadLine(), out int t)) // Read number of test cases
      return;
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine() ?? "0"); // Read size of array
      var values = Console.ReadLine()?.Split(); // Read the target array values
      if (values == null)
        continue;
      var uniqueNumbers = new HashSet<int>(); // Store unique numbers to determine how many increases are needed
      for (int i = 0; i < n; i++) {
        uniqueNumbers.Add(int.Parse(values[i])); // Add each number to set
      }
      int result = 2 * uniqueNumbers.Count - 1; // Minimum operations = 2 * unique_count - 1
      Console.WriteLine(result); // Output the result
    }
  }
}


// https://github.com/VaHiX/CodeForces/