// Problem: CF 1607 G - Banquet Preparations 1
// https://codeforces.com/contest/1607/problem/G

﻿/*
 * Problem: Banquet Preparations 1
 * 
 * Algorithm: Greedy approach with optimization
 * 
 * Time Complexity: O(n) per test case, where n is the number of dishes
 * Space Complexity: O(n) for storing dish information and intermediate results
 * 
 * Approach:
 * - Calculate minimum and maximum possible fish consumption from each dish
 * - Determine the overall balance based on these constraints
 * - For each dish, decide how much fish to consume to minimize the final balance
 * - Adjust consumption to meet the exact balance requirement
 * 
 * Key Concepts:
 * - Each dish contributes exactly m grams total (fish + meat)
 * - We want to minimize |sum(fish) - sum(meat)|
 * - Greedily decide how to distribute m grams between fish and meat in each dish
 * - Try three different strategies and select the one with minimal balance
 */

using System;
using System.IO;
using System.Linq;
using System.Text;
namespace Banquet_Preparations_1 {
internal class Program {
  private static readonly StreamReader reader = new StreamReader(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  private static readonly StreamWriter writer = new StreamWriter(
      Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
  private static void Main(string[] args) {
    int t = Next();
    for (int i = 0; i < t; i++) {
      Solve();
    }
    writer.Flush();
  }
  private static void Solve() {
    int n = Next();
    long m = Next();
    var a = new long[n];
    var b = new long[n];
    long min = 0;    // Minimum possible fish consumption
    long max = 0;    // Maximum possible fish consumption
    for (int i = 0; i < n; i++) {
      a[i] = Next();
      b[i] = Next();
      // For each dish, at least (m - b[i]) grams of fish must be eaten (if b[i] < m)
      // If b[i] >= m, then at least 0 grams of fish are needed
      min += Math.Max(0, m - b[i]);
      // For each dish, at most min(m, a[i]) grams of fish can be eaten 
      max += Math.Min(m, a[i]);
    }
    long sa = a.Sum();  // Total mass of fish across all dishes
    long sb = b.Sum();  // Total mass of meat across all dishes
    // Total mass that will remain after eating m grams from each dish
    long rem = sa + sb - m * n;
    // Try different strategies to minimize the balance:
    // Strategy 1: Minimize fish consumption
    if (2 * (sa - min) <= rem) {
      // If we can minimize the fish consumption to minimize balance
      writer.WriteLine(Math.Abs(rem - (sa - min) - (sa - min)));
      // For each dish, eat max(0, m - b[i]) grams of fish
      for (int i = 0; i < n; i++) {
        long aa = Math.Max(0, m - b[i]);
        writer.Write(aa);
        writer.Write(' ');
        writer.WriteLine(m - aa);
      }
    } else if (2 * (sa - max) >= rem) {
      // If we can maximize the fish consumption to minimize balance
      writer.WriteLine(Math.Abs(rem - (sa - max) - (sa - max)));
      // For each dish, eat min(m, a[i]) grams of fish
      for (int i = 0; i < n; i++) {
        long aa = Math.Min(m, a[i]);
        writer.Write(aa);
        writer.Write(' ');
        writer.WriteLine(m - aa);
      }
    } else {
      // In case the above two do not work:
      // If neither min nor max strategy works, we use a balanced approach
      writer.WriteLine(rem & 1);  // If rem is odd, balance will be 1; else 0
      var aa = new long[n];       // Final amount of fish to be eaten from each dish
      sa = 0;                     // Running sum of remaining fish (after eating)
      sb = 0;                     // Running sum of remaining meat (after eating)
      for (int i = 0; i < n; i++) {
        aa[i] = Math.Max(0, m - b[i]);  // Default case: start with min fish
        sa += a[i] - aa[i];      // Update running sum of remaining fish
        sb += b[i] - (m - aa[i]); // Update running sum of remaining meat
      }
      // Adjust if needed to make the balance as minimal as possible
      for (int i = 0; i < n; i++) {
        long aaa = Math.Min(m, a[i]);   // Maximum fish that can be eaten from dish i
        // If fish is in deficit compared to meat, try to increase fish consumption
        if (sa > sb) {
          if (aaa > aa[i]) {  // If we can eat more fish from i'th dish
            long d = Math.Min(aaa - aa[i], (sa - sb + 1) / 2); // Amount to increase fish consumption
            aa[i] += d;        // Increase fish consumption
            sa -= d;           // Reduce fish deficit
            sb += d;           // Increase meat consumption
          }
        } else {
          break;  // If meat is more than fish, no more adjustment needed
        }
      }
      for (int i = 0; i < n; i++) {
        writer.Write(aa[i]);
        writer.Write(' ');
        writer.WriteLine(m - aa[i]);  // Write fish and meat consumption for dish i
      }
    }
  }
  private static int Next() {
    int c;
    int res = 0;
    do {
      c = reader.Read();
      if (c == -1)
        return res;
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return res;
      res *= 10;
      res += c - '0';
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/