// Problem: CF 2004 D - Colored Portals
// https://codeforces.com/contest/2004/problem/D

/*
 * D. Colored Portals
 * 
 * Purpose:
 * This code solves the problem of finding the minimum cost to travel between cities using colored portals.
 * Each city has two portals of different colors (B, G, R, Y). A move is possible from city i to city j if 
 * they share at least one common portal color. The cost of moving is the absolute difference in city indices.
 * 
 * Approach:
 * 1. For each pair of portal colors, we assign an index (0-5) in a mapping table.
 * 2. For each query, first check if cities share any colors; if yes, return their index difference.
 * 3. If no shared color, use binary search on precomputed lists to find the best intermediate city 
 *    such that a path exists using common portal colors.
 * 
 * Algorithms:
 * - Binary Search for range queries
 * - Preprocessing of portal pairs for fast lookup
 * 
 * Time Complexity: O(n + q * log n) per test case, where n is number of cities and q is number of queries.
 * Space Complexity: O(n + q) for storing lists and intermediate data structures.
 */

using System;
using System.Text;
using System.Collections.Generic;

public class Solution {
  public static void Main() {
    var input = Console.In.ReadToEnd();
    var tokens = input.Split(new char[] { ' ', '\n', '\r' },
                             StringSplitOptions.RemoveEmptyEntries);
    int ptr = 0;
    int t = int.Parse(tokens[ptr++]);
    Func<char, int> getColor = c => {
      switch (c) {
      case 'B':
        return 0;
      case 'G':
        return 1;
      case 'R':
        return 2;
      case 'Y':
        return 3;
      default:
        return -1;
      }
    };
    // Mapping table for color pairs to index
    int[,] pairIndexMap = new int[4, 4] {
      { -1, 0, 1, 2 }, { -1, -1, 3, 4 }, { -1, -1, -1, 5 }, { -1, -1, -1, -1 }
    };
    StringBuilder sb = new StringBuilder();
    for (int test = 0; test < t; test++) {
      if (ptr >= tokens.Length)
        break;
      int n = int.Parse(tokens[ptr++]);
      int q = int.Parse(tokens[ptr++]);
      string[] portalStrings = new string[n];
      for (int i = 0; i < n; i++) {
        portalStrings[i] = tokens[ptr++];
      }
      // Store city color pairs
      int[][] cityColors = new int [n + 1][];
      for (int i = 1; i <= n; i++) {
        string s = portalStrings[i - 1];
        int c1 = getColor(s[0]);
        int c2 = getColor(s[1]);
        cityColors[i] = new int[2] { c1, c2 };
      }
      // Group cities by their portal pairs
      List<int>[] lists = new List<int>[6];
      for (int i = 0; i < 6; i++)
        lists[i] = new List<int>();
      for (int i = 1; i <= n; i++) {
        int c1 = cityColors[i][0];
        int c2 = cityColors[i][1];
        // Normalize to ensure c1 <= c2
        if (c1 < c2) {
          int idx = pairIndexMap[c1, c2];
          if (idx != -1)
            lists[idx].Add(i);
        } else {
          int idx = pairIndexMap[c2, c1];
          if (idx != -1)
            lists[idx].Add(i);
        }
      }
      // Sort cities in each list to enable binary search
      for (int i = 0; i < 6; i++)
        lists[i].Sort();
      
      // Process queries
      for (int query = 0; query < q; query++) {
        if (ptr + 1 >= tokens.Length)
          break;
        int x = int.Parse(tokens[ptr++]);
        int y = int.Parse(tokens[ptr++]);
        bool share = false;
        int cx1 = cityColors[x][0];
        int cx2 = cityColors[x][1];
        int cy1 = cityColors[y][0];
        int cy2 = cityColors[y][1];
        // Check directly if cities share a portal color
        if (cx1 == cy1 || cx1 == cy2 || cx2 == cy1 || cx2 == cy2) {
          share = true;
        }
        if (share) {
          sb.AppendLine(Math.Abs(x - y).ToString());
        } else {
          int minCost = int.MaxValue;
          int low = Math.Min(x, y);
          int high = Math.Max(x, y);
          
          // Try all possible ways to connect via shared colors
          foreach (var c_x in new int[] { cx1, cx2 }) {
            foreach (var c_y in new int[] { cy1, cy2 }) {
              if (c_x == c_y)
                continue;
              int c1_p = c_x;
              int c2_p = c_y;
              int pairIdx = -1;
              // Ensure correct order for lookup
              if (c1_p < c2_p) {
                pairIdx = pairIndexMap[c1_p, c2_p];
              } else if (c2_p < c1_p) {
                pairIdx = pairIndexMap[c2_p, c1_p];
              }
              if (pairIdx == -1)
                continue;
              var list = lists[pairIdx];
              if (list.Count == 0)
                continue;
              
              // Binary search for insertion point in ordered list
              int left = 0, right = list.Count;
              while (left < right) {
                int mid = left + (right - left) / 2;
                if (list[mid] < low)
                  left = mid + 1;
                else
                  right = mid;
              }
              int idx_b = left; // First element >= low
              bool found = false;
              // Check if there's a city in the list that fits within [low, high]
              if (idx_b < list.Count && list[idx_b] <= high) {
                minCost = Math.Min(minCost, Math.Abs(x - y)); // Cost when direct access found
                found = true;
              }
              if (!found) {
                // Check surrounding points for optimal path
                if (idx_b > 0) {
                  int k1 = list[idx_b - 1];
                  int cost1 = x + y - 2 * k1; // Cost via previous point
                  if (cost1 < minCost)
                    minCost = cost1;
                }
                if (idx_b < list.Count) {
                  int k2 = list[idx_b];
                  int cost2 = 2 * k2 - x - y; // Cost via next point
                  if (cost2 < minCost)
                    minCost = cost2;
                }
              }
            }
          }
          if (minCost != int.MaxValue)
            sb.AppendLine(minCost.ToString());
          else
            sb.AppendLine("-1");
        }
      }
    }
    Console.Write(sb.ToString());
  }
}


// https://github.com/VaHiX/codeForces/