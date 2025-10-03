// Problem: CF 2151 C - Incremental Stay
// https://codeforces.com/contest/2151/problem/C

/*
C. Incremental Stay
time limit per test
2 seconds
memory limit per test
256 megabytes
Input
standard input
Output
standard output
Danimal Cannon, Zef - The Lunar Whale

Algorithms/Techniques: 
Prefix sums, sliding window technique, greedy assignment of visitors to maximize total stay time under capacity constraints.

Time Complexity: O(n) per test case, where n is the number of visitor pairs (2n total events).
Space Complexity: O(n), for storing prefix sums and input array.

This problem involves optimizing the total stay time of visitors in a museum given that at most k visitors can be present simultaneously. 
The approach uses prefix sums to efficiently calculate stay times and dynamic adjustment across different capacity limits k from 1 to n.
*/
using System.Text;
using System.IO;
using System;
public class Program {
  static void Main(string[] args) {
    long t = Next();
    for (int i = 0; i < t; i++)
      Solve();
    writer.Flush();
  }
  static void Solve() {
    int n = Next();
    long[] a = new long[n * 2]; // Array to store all 2n timestamps
    for (int i = 0; i < a.Length; i++)
      a[i] = Next();
    long[,] sums = new long[2, n * 2 + 1]; // Prefix sums for even and odd indices
    for (int i = 0; i < a.Length; i++) {
      sums[i & 1, i + 1] = a[i];
      sums[0, i + 1] += sums[0, i]; // Prefix sum for even indices (entrances)
      sums[1, i + 1] += sums[1, i]; // Prefix sum for odd indices (exits)
    }
    long s = 0; // Current total stay time
    for (int i = 1, l = 0, r = a.Length - 1; i <= n; i++, l++, r--) {
      s -= a[l]; // Remove contribution of leftmost entrance
      s += a[r]; // Add contribution of rightmost exit
      writer.Write(s + sums[i & 1, r] - sums[i & 1, l + 1] -
                   (sums[1 - (i & 1), r] - sums[1 - (i & 1), l + 1])); // Compute adjusted stay time
      writer.Write(' ');
    }
    writer.WriteLine();
  }
  static int Next() {
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
  static readonly StreamReader reader = new StreamReader(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer = new StreamWriter(
      Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/CodeForces/