// Problem: CF 1807 E - Interview
// https://codeforces.com/contest/1807/problem/E

/*
 * Purpose: This code solves an interactive problem where the goal is to find the pile containing a special stone that weighs 2 grams instead of 1 gram.
 *          The solution uses binary search to efficiently locate the pile in at most 30 queries.
 * 
 * Algorithm: Binary Search
 *            - We perform a binary search on the piles to identify which pile contains the special stone.
 *            - For each step of the binary search:
 *              1. Choose the left half of the current range.
 *              2. Query the sum of weights of stones in the chosen piles.
 *              3. Compare the actual sum with the expected sum (if all stones were 1 gram).
 *              4. Adjust the search range accordingly.
 * 
 * Time Complexity: O(n * log(n)) - For each of the log(n) iterations, we make a query that takes O(n) time in the worst case.
 * Space Complexity: O(n) - The space used to store the array of pile sizes.
 */

using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;
class Solution {
  public static void Main(string[] args) {
    int t1 = Convert.ToInt32(Console.ReadLine());
    for (int a1 = 1; a1 <= t1; a1++) {
      int n = Convert.ToInt32(Console.ReadLine());
      int[] arr = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
      int l = 0;
      int r = n - 1;
      while (l < r) {
        int mid = l + (r - l) / 2;
        var req = new StringBuilder();
        req.Append("? ");
        long ss = 0;
        req.Append((mid - l + 1).ToString() + " "); // Query size
        for (int x = l; x <= mid; x++) {
          ss += arr[x]; // Sum of weights if all stones were 1
          req.Append((x + 1).ToString() + " "); // Add pile index (1-based)
        }
        Console.WriteLine(req);
        long ssu = Convert.ToInt64(Console.ReadLine()); // Actual sum returned
        if (ssu == ss) {
          l = mid + 1; // If actual sum equals expected sum, special stone is not in left half
        } else {
          r = mid; // If actual sum is greater, special stone is in left half
        }
      }
      Console.WriteLine("! " + (r + 1).ToString()); // Output the index of pile with special stone
    }
  }
}


// https://github.com/VaHiX/CodeForces/