// Problem: CF 2135 D1 - From the Unknown (Easy Version)
// https://codeforces.com/contest/2135/problem/D1

﻿/*
 * Problem: D1. From the Unknown (Easy Version)
 * 
 * Purpose:
 * This is an interactive problem to determine the width parameter W of a text editor (RiOI Editor).
 * The editor displays articles (sequences of word lengths) line by line, where each line's total 
 * length must not exceed W. For each query, we can input an article and observe how many lines it uses.
 * Only 2 queries are allowed to determine W.
 * 
 * Algorithm:
 * - First, we try a large article with all elements equal to W to see if the output is 0 (meaning W < max element).
 * - If not, use binary-search style technique with two queries to bound W in a range and then compute it precisely.
 * 
 * Time Complexity: O(1) per test case, because we perform a constant number of operations.
 * Space Complexity: O(1), only using a few variables and fixed-size arrays.
 */

using System.Text;
namespace FromTheUnknownHard;
class Program {
  static void Solve() {
    const int W = 113; // Initial attempt value for constructing test articles
    const int len = 11611; // Length of initial article used to test if W is too small
    int[] p = new int[len]; // Array to store first query article data
    Array.Fill(p, W); // Fill with W since all elements are same
    int q = Ask(p); // Query the editor with this article
    if (q == 0) {
      // If returned 0, W is too small, so we know max element > W
      p = new int[(W - 1) * (W - 2)]; // Construct another article to find range of W
      Array.Fill(p, 1); // All elements are 1 now
      q = Ask(p); // Query using this smaller values article
      Ans(((W - 1) * (W - 2) + q - 1) / q); // Compute final answer mathematically using bounds
      return;
    }
    // Otherwise, W >= max(element), so we proceed to binary search for more precise range
    int lo = (len + q - 1) / q; // Lower boundary estimate
    int hi = Math.Max(lo + 1, (len + q - 2) / (q - 1)); // Upper boundary estimate
    lo *= W;
    hi *= W;
    hi = Math.Min(100001, hi); // Ensure it doesn't exceed max limit
    List<int> ints = new() { lo }; // Start building a second article for refinement
    int c = 1;
    // Building second query article progressively
    for (int i = lo + 1; i < hi; i++) {
      ints.Add(lo);
      ints.Add(i - lo);
      c++;
    }
    int q2 = Ask(ints.ToArray()); // Second query
    Ans(lo + c - (q2 - c) - 1); // Final calculation to determine W based on second query results
  }

  static int Ask(int[] p) {
    writer.Write($"? {p.Length}");
    foreach (var i in p) {
      writer.Write(' ');
      writer.Write(i);
    }
    writer.WriteLine();
    writer.Flush();
    return int.Parse(reader.ReadLine());
  }

  static void Ans(int w) {
    writer.WriteLine($"! {w}");
    writer.Flush();
  }

  static void Main(string[] args) {
    int t = int.Parse(reader.ReadLine());
    for (int i = 0; i < t; i++) {
      Solve();
    }
    writer.Flush();
  }

  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/