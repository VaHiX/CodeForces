// Problem: CF 1881 E - Block Sequence
// https://codeforces.com/contest/1881/problem/E

﻿/*
 * Problem: E. Block Sequence
 * 
 * Algorithm/Technique: Dynamic Programming
 * 
 * Time Complexity: O(n) where n is the length of the sequence. Each element is processed once.
 * Space Complexity: O(n) for the dp array.
 * 
 * The approach uses dynamic programming to determine the minimum number of deletions required
 * to make a sequence beautiful. A beautiful sequence consists of blocks where each block
 * starts with its own length, followed by that many elements.
 * 
 * The DP state dp[i] represents the minimum number of operations needed to make the sequence
 * starting from index i beautiful.
 * 
 * Transition:
 * - If we can form a valid block starting at index i (i + a[i] + 1 <= n), then:
 *   - We can either skip the current element (add 1 to dp[i+1]) or
 *   - Use the block (take dp[i + a[i] + 1] if valid)
 * - Otherwise, we must delete the current element.
 * 
 * The base case is dp[n - 1] = 1, since a single element is never a valid block and needs to be deleted.
 */

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int l = 0; l < t; l++) {
      int n = int.Parse(Console.ReadLine());
      int[] a = Console.ReadLine().Split().Select(x => int.Parse(x)).ToArray();
      int[] dp = new int[n];
      dp[n - 1] = 1; // Base case: last element must be deleted
      for (int i = n - 2; i >= 0; i--) {
        // Check if a valid block can be formed from current position
        if (i + a[i] + 1 > n) {
          // Cannot form block, must delete
          dp[i] = dp[i + 1] + 1;
        } else {
          // If we can form the block
          if (i + a[i] + 1 == n) {
            // At the end of the sequence, no more elements to process
            dp[i] = 0;
          } else {
            // Choose min cost: delete current element or use the block
            dp[i] = Math.Min(dp[i + 1] + 1, dp[i + a[i] + 1]);
          }
        }
      }
      Console.ForegroundColor = ConsoleColor.Red;
      Console.WriteLine(dp[0]);
      Console.ForegroundColor = ConsoleColor.White;
    }
  }
}


// https://github.com/VaHiX/CodeForces/