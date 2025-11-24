// Problem: CF 2126 B - No Casino in the Mountains
// https://codeforces.com/contest/2126/problem/B

﻿/*
B. No Casino in the Mountains
Algorithms/Techniques: Sliding window, greedy approach

Time complexity: O(n) per test case, where n is the length of the array 'a'
Space complexity: O(n) for the array 'a'

The problem is to find the maximum number of k-day hikes Jean can take 
such that each hike occurs on consecutive good weather days (0), and 
there must be at least one break day (1) between two hikes.

Approach:
- Use a sliding window technique to identify valid k-day segments where all elements are 0.
- When a valid segment is found, mark the next day as 1 (to simulate a mandatory break).
- Greedily count how many such non-overlapping segments exist.
*/
using System.Text;
namespace NoCasinoInIheMountains;
class Program {
  static int Solve() {
    int n = Next();
    int k = Next();
    int[] a = new int[n];
    for (int i = 0; i < n; i++)
      a[i] = Next();
    int ans = 0;
    for (int i = 0, c = 0; i < n; i++) {
      if (a[i] == 0) { // If current day is good weather
        c++; // Increment counter of consecutive good days
        if (c == k) { // If we have k consecutive good days
          ans++; // Increment hike count
          if (i + 1 < n)
            a[i + 1] = 1; // Mark next day as break (simulate mandatory rest)
          c = 0; // Reset counter for next potential segment
        }
      } else {
        c = 0; // Reset counter when encountering bad weather
      }
    }
    return ans;
  }
  static void Main(string[] args) {
    long t = Next();
    for (int i = 0; i < t; i++)
      writer.WriteLine(Solve());
    writer.Flush();
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
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/