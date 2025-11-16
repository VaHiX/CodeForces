// Problem: CF 2033 E - Sakurako, Kosuke, and the Permutation
// https://codeforces.com/contest/2033/problem/E

using System;
using System.Collections.Generic;

class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      List<long> p = new List<long>(
          Array.ConvertAll(Console.ReadLine().Split(), long.Parse));
      bool[] vis = new bool[n + 1];
      long res = 0;
      for (int i = 1; i <= n; i++) {
        if (vis[i].Equals(false)) {
          int cnt = 0;
          int j = i;
          // Traverse the cycle starting from node i
          for (; !vis[j]; cnt++) {
            vis[j] = true;
            j = (int)p[j - 1]; // Move to the next element in the cycle
          }
          // For each cycle of length 'cnt', we need (cnt - 1) / 2 swaps to make it simple
          // Each swap can fix two elements, so we only count necessary swaps
          res += Math.Max(0, (cnt - 1) / 2);
        }
      }
      Console.WriteLine(res);
    }
  }
}
/*
 * Problem: Make a permutation simple by swapping elements.
 * 
 * Algorithm:
 * - This problem is based on decomposing the permutation into cycles.
 * - Each cycle of length 'cnt' requires (cnt - 1) / 2 swaps to become simple.
 * - A cycle is simple if it can be rearranged such that for every element p[i] = i or p[p[i]] = i.
 * 
 * Key insight:
 * - For each cycle of length `cnt`, we compute how many swaps are needed.
 * - A cycle of length `cnt` can be made simple with at most `floor((cnt-1)/2)` swaps.
 * 
 * Time Complexity: O(n) - Each element is visited once in the entire traversal.
 * Space Complexity: O(n) - For the visited array and input parsing.
 */

// https://github.com/VaHiX/CodeForces/