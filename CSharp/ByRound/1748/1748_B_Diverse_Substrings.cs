// Problem: CF 1748 B - Diverse Substrings
// https://codeforces.com/contest/1748/problem/B

/*
 * Problem: B. Diverse Substrings
 * 
 * Algorithm:
 * - For each substring, count the frequency of each digit (0-9) and determine if it's diverse.
 * - A substring is diverse if the maximum frequency of any digit does not exceed the number of distinct digits.
 * - Use a prefix sum technique to efficiently calculate digit counts for any substring.
 * 
 * Time Complexity: O(n^2 * 10) = O(n^2) where n is the length of the string.
 * Space Complexity: O(n * 10) = O(n) for the prefix sum array.
 * 
 * Techniques:
 * - Prefix Sum Array for efficient range queries
 * - Brute force enumeration of all substrings
 * - Check diversity condition for each substring
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = int.Parse(Console.ReadLine());
      var s = Console.ReadLine();
      long o = 0;
      // c[i,j] stores the count of digit j in the prefix s[0..i-1]
      int[,] c = new int[n + 1, 10];
      for (int i = 0; i < n; i++) {
        int m = s[i] - 48; // Convert char to int (ASCII to digit)
        // Copy previous counts to current row
        for (int j = 0; j < 10; j++) {
          c[i + 1, j] = c[i, j];
        }
        // Increment count of当前 digit
        c[i + 1, m]++;
      }
      // Enumerate all substrings
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
          int max = 0;
          int distinct = 0;
          // Count occurrences of each digit in substring s[i..j-1]
          for (int k = 0; k < 10; k++) {
            int y = c[j, k] - c[i, k]; // Frequency of digit k in s[i..j-1]
            if (y > 0) {
              distinct++; // Increment distinct digit count
              if (y > max)
                max = y; // Update maximum frequency
            }
          }
          // Check if the substring is diverse
          if (distinct >= max)
            o++;
          // Optimization: if max frequency is greater than 10, no need to check further
          if (max > 10) {
            break;
          }
        }
      }
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/