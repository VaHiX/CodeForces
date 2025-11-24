// Problem: CF 2031 B - Penchick and Satay Sticks
// https://codeforces.com/contest/2031/problem/B

/*
 * Problem: B. Penchick and Satay Sticks
 * 
 * Purpose:
 *   Determine whether a permutation of satay stick lengths can be sorted using swaps
 *   of neighboring elements whose values differ by exactly 1.
 * 
 * Algorithm:
 *   - For each element in the permutation, record its current position.
 *   - Check if any element is more than one position away from its correct position (i.e., value i should be at index i).
 *   - If all elements are within distance 1 of their correct positions, then it's possible to sort using allowed swaps.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the position array
 */
using System;
using System.Collections.Generic;
class Program {
  static string CheckPositions(int n, List<int> p) {
    int[] pos = new int[n + 1]; // Array to store the current positions of each value (1-based indexing)
    for (int j = 0; j < n; j++) {
      pos[p[j]] = j + 1; // Store the index+1 where value p[j] is located
    }
    for (int i = 1; i <= n; i++) {
      if (Math.Abs(pos[i] - i) > 1) { // Check if value i is more than one position away from its correct place
        return "NO";
      }
    }
    return "YES";
  }
  static void Main() {
    int testCount = int.Parse(Console.ReadLine()); // Read number of test cases
    List<string> results = new List<string>();
    for (int t = 0; t < testCount; t++) {
      int n = int.Parse(Console.ReadLine()); // Read the size of permutation
      List<int> p = new List<int>();
      string[] input = Console.ReadLine().Split(' '); // Read the permutation values
      for (int i = 0; i < n; i++) {
        p.Add(int.Parse(input[i])); // Parse and store each value
      }
      results.Add(CheckPositions(n, p)); // Process current test case
    }
    Console.WriteLine(string.Join(Environment.NewLine, results)); // Output all results
  }
}


// https://github.com/VaHiX/codeForces/