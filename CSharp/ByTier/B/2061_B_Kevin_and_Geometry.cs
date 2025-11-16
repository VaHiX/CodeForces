// Problem: CF 2061 B - Kevin and Geometry
// https://codeforces.com/contest/2061/problem/B

/*
B. Kevin and Geometry

Purpose:
This code solves the problem of finding four sticks that can form an isosceles trapezoid (including rectangles and squares).
The algorithm uses sorting and greedy selection to find two equal-length sides (legs) and two different-length parallel sides (bases).

Algorithms/Techniques:
- Sorting
- Greedy approach
- Two-pointer technique for finding pairs

Time Complexity: O(n log n) per test case due to sorting, where n is the number of sticks.
Space Complexity: O(n) for storing the array of stick lengths.

*/
using System;
using System.Linq;
using System.Collections.Generic;
class DJ {
  void solve() {
    int n = Convert.ToInt32(Console.ReadLine());
    List<int> a =
        Console.ReadLine().Split(' ').Select(s => int.Parse(s)).ToList();
    a.Sort(); // Sort the stick lengths
    int A = -1, B = -1, C = -1;
    // Find two equal-length sticks (potential legs of trapezoid)
    for (int i = n - 1; i >= 1; i--) {
      if (a[i] == a[i - 1]) {
        A = a[i];
        a.RemoveAt(i - 1); // Remove one stick from list
        a.RemoveAt(i - 1); // Remove another stick from list
        break;
      }
    }
    // Find two other sticks to form bases of trapezoid (with minimal difference)
    for (int i = 1; i < n - 2; i++) {
      if (C == -1 || C - B > a[i] - a[i - 1]) {
        C = a[i];
        B = a[i - 1];
      }
    }
    // If no valid pair of legs found or the trapezoid cannot have positive area
    if (A == -1 || 2 * A + B <= C) {
      Console.WriteLine(-1);
      return;
    }
    Console.WriteLine(A + " " + A + " " + B + " " + C); // Output result
  }
  static void Main() {
    int T = 1;
    T = Convert.ToInt32(Console.ReadLine());
    DJ d = new DJ();
    while (T-- > 0) {
      d.solve();
    }
  }
}


// https://github.com/VaHiX/codeForces/