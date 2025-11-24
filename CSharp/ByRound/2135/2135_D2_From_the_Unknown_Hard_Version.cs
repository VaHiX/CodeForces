// Problem: CF 2135 D2 - From the Unknown (Hard Version)
// https://codeforces.com/contest/2135/problem/D2

/*
 * Problem: D2. From the Unknown (Hard Version)
 * Purpose: Determine the width parameter W of an interactive text editor by making at most 2 queries.
 * Algorithm: Binary search approach using two strategically crafted queries to narrow down the value of W.
 * Time Complexity: O(log(W)) per test case due to binary search over possible values of W.
 * Space Complexity: O(1) excluding input/output buffers and temporary query arrays.
 *
 * Techniques:
 * - Interactive problem solving with binary search
 * - Query optimization to minimize total number of elements across all queries
 * - Adaptive interactor handling
 */

﻿using System.Text;
namespace FromTheUnknownHard;
class Program {
  static void Solve() {
    const int W = 113; // Initial guess for W, used as a reference point
    const int len = 11611; // Length of first query array
    int[] p = new int[len]; // Create array filled with W
    Array.Fill(p, W);
    int q = Ask(p); // First query to get initial result from editor
    if (q == 0) {
      // If first query fails (editor unable to display), then W must be less than len
      p = new int[(W - 1) * (W - 2)]; // Reuse p to hold new query array for smaller case
      Array.Fill(p, 1); // Fill with ones
      q = Ask(p); // Second query on small elements
      Ans(((W - 1) * (W - 2) + q - 1) / q); // Calculate and output W based on result
      return;
    }
    // Binary search bounds preparation
    int lo = (len + q - 1) / q; // Lower bound estimation for W
    int hi = Math.Max(lo + 1, (len + q - 2) / (q - 1)); // Upper bound estimation for W
    lo *= W;
    hi *= W;
    hi = Math.Min(100001, hi); // Cap upper limit at 100001
    
    List<int> ints = new() { lo }; // Prepare list of integers for second query
    int c = 1; // Counter for number of queries (for later use)
    for (int i = lo + 1; i < hi; i++) {
      ints.Add(lo); // Add repeated value to form pattern
      ints.Add(i - lo); // Add step difference to create spread
      c++; // Increment counter
    }
    int q2 = Ask(ints.ToArray()); // Query second pattern
    Ans(lo + c - (q2 - c) - 1); // Final W calculation using arithmetic trick from query results
  }

  static int Ask(int[] p) {
    writer.Write($"? {p.Length}"); // Output query header with array size
    foreach (var i in p) {
      writer.Write(' ');
      writer.Write(i); // Output each element of the array
    }
    writer.WriteLine(); // End line for query
    writer.Flush(); // Ensure output is sent immediately
    return int.Parse(reader.ReadLine()); // Read response from jury
  }

  static void Ans(int w) {
    writer.WriteLine($"! {w}"); // Output final answer in required format
    writer.Flush();
  }

  static void Main(string[] args) {
    int t = int.Parse(reader.ReadLine()); // Get number of test cases
    for (int i = 0; i < t; i++) {
      Solve(); // Process each test case
    }
    writer.Flush(); // Flush final output buffer
  }

  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10); // Buffered input stream
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10); // Buffered output stream
}


// https://github.com/VaHiX/codeForces/