// Problem: CF 2126 D - This Is the Last Time
// https://codeforces.com/contest/2126/problem/D

/*
 * Problem: D. This Is the Last Time
 * 
 * Purpose: Given a set of casinos with coin requirements and rewards,
 *          find the maximum number of coins achievable starting with k coins.
 * 
 * Algorithm: Greedy approach combined with sorting.
 *            1. Sort casinos by their lower bound 'l' (ascending).
 *            2. Iterate through sorted list, for each casino that can be visited
 *               (current coins >= l), update the current number of coins to max(current, real).
 *            3. Return final number of coins.
 * 
 * Time Complexity: O(n log n) due to sorting; the traversal is O(n), so overall is O(n log n)
 * Space Complexity: O(n) for storing casino data
 * 
 * Techniques Used:
 *   - Greedy algorithm
 *   - Sorting
 *   - Efficient input/output handling with StreamReader/Writer
 */

﻿using System.Text;
namespace ThisIsTheLastTime;
class Program {
  static int Solve() {
    int n = Next(); // Read number of casinos
    int k = Next(); // Read initial coins
    var a = new(int l, int r, int real)[n]; // Store casino data: (lower, upper, reward)
    for (int i = 0; i < n; i++)
      a[i] = (Next(), Next(), Next()); // Read each casino's parameters
    
    Array.Sort(a); // Sort casinos by lower bound 'l' to process in order
    for (int i = 0; i < n; i++) {
      if (a[i].l <= k) // If current coins allow visiting this casino
        k = Math.Max(k, a[i].real); // Update coins to maximum of current and reward
      else
        break; // Since sorted, no further casinos can be visited
    }
    return k; // Return the maximum coins achieved
  }
  
  static void Main(string[] args) {
    long t = Next(); // Read number of test cases
    for (int i = 0; i < t; i++)
      writer.WriteLine(Solve()); // Process each test case
    writer.Flush(); // Flush output buffer
  }
  
  static int Next() { // Fast input reader for integers
    int c;
    int m = 1;
    int res = 0;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1;
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return m * res;
      res *= 10;
      res += c - '0';
    }
  }
  
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/