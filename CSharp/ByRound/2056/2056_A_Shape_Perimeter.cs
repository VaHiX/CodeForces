// Problem: CF 2056 A - Shape Perimeter
// https://codeforces.com/contest/2056/problem/A

/*
 * Problem: Shape Perimeter
 * 
 * Algorithms/Techniques:
 * - Simulation of stamp movements on a grid
 * - Calculation of the perimeter based on overlapping and exposed edges
 * 
 * Time Complexity: O(n) per test case, where n is the number of operations.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n and m
      var n = int.Parse(line[0]);
      var m = int.Parse(line[1]);
      getAns(n, m); // Process current test case
    }
  }
  
  static void getAns(int n, int m) {
    Console.ReadLine(); // Consume empty line (unused)
    var c = 0; // Variable to store the count of internal edges
    for (int i = 0; i < n - 1; i++) { // Loop through all stamps except the last one
      string[] line = Console.ReadLine().Trim().Split(' '); // Read x and y coordinates
      c += int.Parse(line[0]) + int.Parse(line[1]); // Add to cumulative movement
    }
    Console.WriteLine(c * 2 + m * 4); // Output computed perimeter
  }
}


// https://github.com/VaHiX/codeForces/