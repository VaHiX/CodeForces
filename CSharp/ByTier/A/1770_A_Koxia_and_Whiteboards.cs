// Problem: CF 1770 A - Koxia and Whiteboards
// https://codeforces.com/contest/1770/problem/A

/*
 * Problem: Koxia and Whiteboards
 * 
 * Purpose: 
 *   Given n whiteboards with initial values and m operations to replace values on whiteboards,
 *   find the maximum possible sum of integers on the whiteboards after performing all operations.
 * 
 * Approach:
 *   - For each operation, we greedily replace the smallest current value in the whiteboard array with the next value from the operation list.
 *   - This ensures that we are always replacing the smallest value, minimizing the loss in the total sum.
 * 
 * Algorithms/Techniques:
 *   - Greedy algorithm
 *   - Array manipulation using LINQ
 * 
 * Time Complexity: O(m * n)
 *   - For each of the m operations, we perform a Min() and IndexOf() operation on the array of size n.
 *   - These operations take O(n) time each.
 * 
 * Space Complexity: O(n + m)
 *   - Storing the arrays for whiteboards (n) and operations (m).
 * 
 * Note: 
 *   The problem description seems to have an error in the input parsing logic.
 *   Expected input: n m, then two lines of n and m integers, respectively.
 *   But the code parses a[1] as the number of operations and then uses a[0] as the number of whiteboards.
 *   This might cause incorrect parsing for some test cases.
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine()); // Read number of test cases
    List<string> output = new List<string>(); // Store results for each test case
    
    for (int z = 0; z < count; z++) {
      var a = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList(); // Read n and m
      var b = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList(); // Read initial whiteboard values
      var c = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList(); // Read operation values
      
      long o = 0; // Initialize result sum
      
      // For each operation, we replace the smallest element in b with the current operation value
      for (int i = 0; i < a[1]; i++) { // a[1] is m (number of operations)
        var m = b.Min(); // Find the minimum value in the current whiteboard array
        var d = b.IndexOf(m); // Find index of the minimum value
        b[d] = c[i]; // Replace the minimum value with the current operation value
      }
      
      o = b.Sum(); // Calculate final sum of whiteboard values
      output.Add(o.ToString()); // Add result to output list
    }
    
    string on = string.Join("\n", output); // Join results with newlines
    Console.WriteLine(on); // Print all results
  }
}
}


// https://github.com/VaHiX/CodeForces/