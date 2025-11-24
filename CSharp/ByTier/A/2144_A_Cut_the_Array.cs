// Problem: CF 2144 A - Cut the Array
// https://codeforces.com/contest/2144/problem/A

/*
Problem: A. Cut the Array

Algorithm/Technique: Prefix Sum with Brute Force
Time Complexity: O(n^2) per test case, where n is the length of the array.
Space Complexity: O(n) for the prefix sum array.

The task is to partition an array into three non-empty parts such that 
either all three sums modulo 3 are equal or all three are different.
We use a prefix sum array for efficient range sum calculation and iterate 
through all valid l,r pairs to check the required condition.
*/

using System;
using System.Linq;
class Program {
  static void Solve() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int[] arr = Console.ReadLine().Split().Select(int.Parse).ToArray();
      int[] pref = new int[n + 1]; // Prefix sum array
      for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] + arr[i]; // Build prefix sum
      bool found = false;
      for (int l = 1; l < n && !found; l++) { // Try all valid left boundaries
        for (int r = l + 1; r < n; r++) { // Try all valid right boundaries
          int s1 = pref[l] % 3; // Sum of prefix mod 3
          int s2 = (pref[r] - pref[l]) % 3; // Sum of middle part mod 3
          int s3 = (pref[n] - pref[r]) % 3; // Sum of suffix mod 3
          // Check if all three remainders are equal OR all different
          if ((s1 == s2 && s2 == s3) || (s1 != s2 && s2 != s3 && s1 != s3)) {
            Console.WriteLine($"{l} {r}");
            found = true;
            break;
          }
        }
      }
      if (!found) {
        Console.WriteLine("0 0");
      }
    }
  }
  static void Main() { Solve(); }
}


// https://github.com/VaHiX/codeForces/