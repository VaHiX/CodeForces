// Problem: CF 2110 F - Faculty
// https://codeforces.com/contest/2110/problem/F

/*
F. Faculty
Purpose: This program computes the "beauty" of prefixes of an array, where the beauty is defined as the maximum value of f(a_i, a_j) = (a_i % a_j) + (a_j % a_i) over all pairs in the prefix.

Algorithms/Techniques:
- Sliding window / Prefix processing with dynamic tracking of maximum values
- Efficient I/O using FastIO class for performance

Time Complexity: O(n^2) worst-case per test case due to nested loop for computing max; however, in practice it's often much faster due to early exits and efficient data structures.
Space Complexity: O(n) for storing the array and list of elements processed so far.

*/

using System;
using System.IO;
using System.Collections.Generic;

class P {
  static void Main() {
    var sr = new StreamReader(Console.OpenStandardInput());
    var sw = new StreamWriter(Console.OpenStandardOutput());
    var io = new FastIO(sr, sw);
    int t = io.NextInt();
    while (t-- > 0) {
      int n = io.NextInt();
      if (n == 0) {
        io.Write("\n");
        continue;
      }
      var a = new long[n];
      for (int i = 0; i < n; ++i)
        a[i] = io.NextLong(); // Read array elements

      long cm = a[0], cms = 0; // cm: current maximum element, cms: current max beauty
      var e = new List<long> { cm }; // e: list of processed elements
      io.Write("0"); // Beauty of first prefix (single element) is 0
      for (int i = 1; i < n; ++i) {
        long x = a[i];
        e.Add(x); // Add current element to list

        if (x > cm) { // If new element is greater than max so far
          long pm = cm;
          cm = x;
          if (pm > cm / 2) { // Check condition for efficiency
            cms = Math.Max(cms, cm);
          } else {
            long m = 0;
            for (int j = 0; j < e.Count - 1; ++j) { // Loop through all prev elements except last one
              long y = e[j];
              long s = y + (cm % y); // Compute f(y, cm)
              m = Math.Max(m, s);
            }
            cms = Math.Max(cms, m); // Update max beauty
          }
        } else {
          if (x < cm) { // If new element is smaller than max so far
            long s = (cm % x) + x; // Compute f(cm, x)
            cms = Math.Max(cms, s); // Update max beauty
          }
        }
        io.Write(" " + cms);
      }
      io.Write("\n");
    }
    io.Flush();
  }
}

class FastIO {
  private readonly StreamReader r;
  private readonly StreamWriter w;
  private string[] t = Array.Empty<string>();
  private int i = 0;
  public FastIO(StreamReader r, StreamWriter w) {
    this.r = r;
    this.w = w;
  }
  public string Next() {
    while (i >= t.Length) {
      t = r.ReadLine()?.Split() ?? Array.Empty<string>();
      i = 0;
    }
    return t[i++];
  }
  public int NextInt() => int.Parse(Next());
  public long NextLong() => long.Parse(Next());
  public void Write(string s) => w.Write(s);
  public void Flush() => w.Flush();
}


// https://github.com/VaHiX/CodeForces/