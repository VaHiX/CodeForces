// Problem: CF 2096 B - Wonderful Gloves
// https://codeforces.com/contest/2096/problem/B

﻿/*
 * Problem: B. Wonderful Gloves
 * 
 * Purpose: 
 *   Given left and right gloves of different colors, find the minimum number of gloves to pick to guarantee at least k matching pairs of different colors.
 * 
 * Approach:
 *   1. For each color, determine the maximum and minimum of left and right gloves (used to compute max pairs possible).
 *   2. Sum up all maximums to get the worst-case number of gloves needed to form at least one pair per color.
 *   3. Sort the minimums in descending order to pick the largest ones to form k-1 pairs (as one pair is already formed from total max).
 *   4. Add the top (k-1) minimums to the sum for worst-case scenario.
 *   5. Add 1 to account for the last glove needed to ensure minimum k pairs.
 * 
 * Algorithms/Techniques:
 *   - Greedy approach
 *   - Sorting
 *   - Prefix sums
 * 
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing arrays
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace NewContest {
internal class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    for (int o = 0; o < t; o++) {
      string[] input = Console.ReadLine().Split(
          new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
      int n = int.Parse(input[0]);
      int k = int.Parse(input[1]);
      input = Console.ReadLine().Split(new char[] { ' ' },
                                       StringSplitOptions.RemoveEmptyEntries);
      long[] leftNumbers = new long[n];
      long[] rightNumbers = new long[n];
      for (int i = 0; i < n; i++) {
        leftNumbers[i] = long.Parse(input[i]);
      }
      input = Console.ReadLine().Split(new char[] { ' ' },
                                       StringSplitOptions.RemoveEmptyEntries);
      for (int i = 0; i < n; i++) {
        rightNumbers[i] = long.Parse(input[i]);
      }
      long[] max = new long[n];
      long[] min = new long[n];
      for (int i = 0; i < n; i++) {
        // Determine max and min for each color's left and right glove count
        if (rightNumbers[i] > leftNumbers[i]) {
          max[i] = rightNumbers[i];
          min[i] = leftNumbers[i];
        } else {
          max[i] = leftNumbers[i];
          min[i] = rightNumbers[i];
        }
      }
      long sum = 0;
      // Add all maximums (worst case to ensure at least one pair per color)
      for (int i = 0; i < n; i++) {
        sum += max[i];
      }
      // Sort min array in descending order to pick the largest values for minimum pairs
      Array.Sort(min);
      Array.Reverse(min);
      // Add k-1 most significant minimums to accumulate worst-case scenario
      for (int i = 0; i < k - 1; i++) {
        sum += min[i];
      }
      // +1 because we must ensure at least k pairs, so one more glove guarantees that
      Console.WriteLine(sum + 1);
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/