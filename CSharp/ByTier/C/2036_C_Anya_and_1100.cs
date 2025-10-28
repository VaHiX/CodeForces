// Problem: CF 2036 C - Anya and 1100
// https://codeforces.com/contest/2036/problem/C

/*
 * Problem: Anya and 1100
 * Purpose: Determine if the substring "1100" exists in a binary string after performing a series of updates.
 * Algorithm:
 *   - Maintain a fixed-size array a with padding of -1 at both ends to simplify boundary checks.
 *   - Track potential start positions (indices) of "1100" patterns using a HashSet for fast lookups.
 *   - Update the array when a character changes and adjust the set of valid pattern starters accordingly.
 *   - Each query operation updates one character and recalculates affected potential patterns in O(1) time per update.
 * 
 * Time Complexity: O(n + q) where n is the length of string s and q is number of queries.
 * Space Complexity: O(n) for storing the array and the hash set of pattern start positions.
 */

using System.Collections.Generic;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var s = Console.ReadLine().Trim();
      var q = int.Parse(Console.ReadLine().Trim());
      getAns(s, q);
    }
  }

  // Update the array and hash set when changing a[i] from 0 to 1
  static void check0to1(int n, int[] a, HashSet<int> hs, int p) {
    a[p] = 1;
    hs.Remove(p - 2);  // Remove invalid pattern starting at p-2 if it was in the set
    hs.Remove(p - 3);  // Remove invalid pattern starting at p-3 if it was in the set
    // Check new possible "1100" patterns that may now form due to this change
    if (a[p + 1] == 1 && a[p + 2] == 0 && a[p + 3] == 0)
      hs.Add(p);       // If we can now form "1100", add index p as potential start
    if (a[p - 1] == 1 && a[p + 1] == 0 && a[p + 2] == 0)
      hs.Add(p - 1);   // Check another possible starting pattern
  }

  // Update the array and hash set when changing a[i] from 1 to 0
  static void check1to0(int n, int[] a, HashSet<int> hs, int p) {
    a[p] = 0;
    hs.Remove(p);     // Remove index p if it's part of a current "1100"
    hs.Remove(p - 1); // Remove index p-1 if it was a potential start
    // Check newly possible patterns that now exist due to this change
    if (a[p - 3] == 1 && a[p - 2] == 1 && a[p - 1] == 0)
      hs.Add(p - 3);  // Add new valid start index if "1100" pattern forms
    if (a[p - 2] == 1 && a[p - 1] == 1 && a[p + 1] == 0)
      hs.Add(p - 2);  // Another newly formed valid pattern
  }

  static void getAns(string s, int q) {
    var n = s.Length;
    var a = new int[n + 6];  // Extend array to safely access indices beyond string bounds (with padding)

    // Initialize border elements with -1
    for (int i = 0; i < 3; i++) {
      a[i] = -1;
      a[i + n + 3] = -1;
    }

    // Copy string into array, shifted by 3 to use padding as buffer
    for (int i = 0; i < n; i++)
      a[i + 3] = s[i] - '0';

    var hs = new HashSet<int>();  // Hash set to track indices where "1100" could start

    // Precompute all initial valid starting positions of "1100"
    for (int i = 0; i < n; i++) {
      if (a[i] == 1 && a[i + 1] == 1 && a[i + 2] == 0 && a[i + 3] == 0) {
        hs.Add(i);
      }
    }

    // Process updates
    for (int i = 0; i < q; i++) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var p = int.Parse(line[0]) + 2;  // Adjust input index to account for padding
      var av = int.Parse(line[1]);

      if (a[p] != av) {  // Only proceed if value actually changes
        if (av == 1)
          check0to1(n, a, hs, p);
        else
          check1to0(n, a, hs, p);
      }

      // Output result based on whether any "1100" pattern exists
      Console.WriteLine(hs.Count > 0 ? "YES" : "NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/