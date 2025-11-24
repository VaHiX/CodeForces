// Problem: CF 1772 D - Absolute Sorting
// https://codeforces.com/contest/1772/problem/D

using System;
namespace myApp {
class Solution {
  public static void Main(string[] args) {
    int t;
    t = int.Parse(Console.ReadLine());
    while (t > 0) {
      t--;
      Solve();
    }
  }
  private static void Solve() {
    int n = int.Parse(Console.ReadLine());
    int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    int l = 0, r = 1000000000, x;
    // Iterate through the array to find valid range for x
    for (int i = 0; i < n - 1; i++) {
      if (a[i] < a[i + 1]) {
        // If a[i] < a[i+1], we need x to make the transition smooth
        // x should be such that |a[i] - x| <= |a[i+1] - x|
        // This means x should be at most the midpoint of a[i] and a[i+1]
        x = (a[i] + a[i + 1]) / 2;
        r = Math.Min(x, r);
      } else if (a[i] > a[i + 1]) {
        // If a[i] > a[i+1], we need x to make the transition smooth
        // x should be such that |a[i] - x| >= |a[i+1] - x|
        // This means x should be at least the next integer after the midpoint
        x = (a[i] + a[i + 1] + 1) / 2;
        l = Math.Max(x, l);
      }
    }
    // If there's a valid range for x, output any value in that range
    if (l <= r) {
      Console.WriteLine(l);
    } else {
      Console.WriteLine(-1);
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/