// Problem: CF 2119 B - Line Segments
// https://codeforces.com/contest/2119/problem/B

/*
B. Line Segments
time limit per test1.5 seconds
memory limit per test256 megabytes

Algorithm/Techniques:
- Geometric reasoning using the triangle inequality
- For a sequence of moves with specified distances, we check whether it's possible to reach from start point p to end point q within the constraints of total distance and minimum required distance.

Time Complexity: O(n) per test case, because we iterate through n elements once to compute sum and max.
Space Complexity: O(n), due to storing array 'a' of size n.

The problem reduces to checking if the Euclidean distance between start (p) and end (q) lies within the range 
defined by:
- Minimum possible distance: max(0, max_a - (sum_a - max_a))
- Maximum possible distance: sum_a
*/

using System;
using System.Collections.Generic;
using System.IO;
public class Program {
  const long MOD = 1000000007;
  static void Solve() {
    int n = int.Parse(Console.ReadLine()); // Read number of operations
    string[] pq = Console.ReadLine().Split(); // Read start and end point coordinates
    long px = long.Parse(pq[0]);
    long py = long.Parse(pq[1]);
    long qx = long.Parse(pq[2]);
    long qy = long.Parse(pq[3]);
    long[] a = new long[n]; // Array to store distances for each operation
    string[] aInput = Console.ReadLine().Split();
    long sum_a = 0; // Sum of all distances in sequence
    long max_a = 0; // Maximum single distance in the sequence
    for (int i = 0; i < n; ++i) {
      a[i] = long.Parse(aInput[i]);
      sum_a += a[i];
      if (a[i] > max_a) {
        max_a = a[i];
      }
    }
    long dx = px - qx;
    long dy = py - qy;
    long D_sq = dx * dx + dy * dy; // Squared Euclidean distance between start and end points
    long R_max = sum_a; // Maximum possible distance after all moves
    long R_min; // Minimum possible distance after all moves
    if (n == 0) {
      R_min = 0;
    } else {
      long sum_other_a = sum_a - max_a;
      R_min = Math.Max(0L, max_a - sum_other_a); // Calculating the tightest constraint using triangle inequality
    }
    long R_min_sq = R_min * R_min; // Square of minimum possible distance
    long R_max_sq = R_max * R_max; // Square of maximum possible distance
    if (D_sq >= R_min_sq && D_sq <= R_max_sq) { // Check if actual distance fits within valid range
      Console.WriteLine("Yes");
    } else {
      Console.WriteLine("No");
    }
  }
  public static void Main(string[] args) {
    if (args.Length > 0 && args[0] == "LOCAL") {
      Console.SetIn(new StreamReader("a2.txt"));
      Console.SetOut(new StreamWriter("a2.txt"));
    }
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      Solve(); // Process each test case
    }
    if (Console.Out is StreamWriter) {
      Console.Out.Flush();
      Console.Out.Close();
    }
  }
}


// https://github.com/VaHiX/codeForces/