// Problem: CF 2007 B - Index and Maximum Value
// https://codeforces.com/contest/2007/problem/B

/*
 * Problem: B. Index and Maximum Value
 * Algorithms/Techniques: Simulation with tracking of maximum value
 * Time Complexity: O(n + m), where n is the size of array and m is number of operations
 * Space Complexity: O(m), for storing results
 *
 * The solution simulates the given operations on an array. For each operation,
 * it updates the maximum value of the array based on whether elements fall within
 * the specified range [l, r]. It keeps track of current maximum and outputs it after
 * each operation.
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n and m
      var n = int.Parse(line[0]); // Size of array
      var m = int.Parse(line[1]); // Number of operations
      line = Console.ReadLine().Trim().Split(' '); // Read initial array elements
      var a = Array.ConvertAll(line, long.Parse); // Convert to long array
      getAns(n, m, a); // Process the operations
    }
  }
  static void getAns(int n, int m, long[] a) {
    var t = a.Max(); // Initialize maximum value with max of initial array
    var ans = new long[m]; // Array to store results after each operation
    for (int i = 0; i < m; i++) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read operation details
      var L = long.Parse(line[1]); // Lower bound of range
      var r = long.Parse(line[2]); // Upper bound of range
      if (t >= L && t <= r) { // If current max falls in the given range
        if (line[0] == "+") // Increment
          t++;
        else // Decrement
          t--;
      }
      ans[i] = t; // Store current maximum value after this operation
    }
    Console.WriteLine(string.Join(" ", ans)); // Output all results
  }
}


// https://github.com/VaHiX/codeForces/