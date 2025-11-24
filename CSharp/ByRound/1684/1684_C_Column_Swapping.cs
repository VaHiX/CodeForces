// Problem: CF 1684 C - Column Swapping
// https://codeforces.com/contest/1684/problem/C

/*
 * Column Swapping Problem
 * 
 * Algorithm/Techniques:
 * - For each column, count how many cells differ from the sorted row (sorted in non-decreasing order)
 * - If 0 columns differ, the grid is already good (swap any column with itself)
 * - If 2 columns differ, try swapping them and check if the resulting grid is good
 * - If 3 or more columns differ, it's impossible to make grid good with one swap
 * 
 * Time Complexity: O(n * m * log(m)) per test case due to sorting each row
 * Space Complexity: O(n * m) for storing the grid and sorted rows
 */

using System;
using System.Collections.Generic;
class Program {
  static void Main(string[] args) {
    int T = int.Parse(Console.ReadLine());
    for (var t = 0; t < T; t++) {
      string[] str = Console.ReadLine().Split();
      int N = int.Parse(str[0]);
      int M = int.Parse(str[1]);
      int[,] A = new int[N, M];
      int[][] B = new int [N][];
      for (var i = 0; i < N; i++) {
        string[] str2 = Console.ReadLine().Split();
        for (var j = 0; j < M; j++) {
          A[i, j] = int.Parse(str2[j]);
        }
      }
      for (var i = 0; i < N; i++) {
        B[i] = new int[M];
        for (var j = 0; j < M; j++) {
          B[i][j] = A[i, j];
        }
        Array.Sort(B[i]); // Sort each row to know what the correct order should be
      }
      int[] C = new int[M];
      for (var i = 0; i < N; i++) {
        for (var j = 0; j < M; j++) {
          if (A[i, j] != B[i][j]) {
            C[j]++; // Count mismatches for each column
          }
        }
      }
      int cta = 0;
      var list = new List<int>();
      for (var i = 0; i < M; i++) {
        if (C[i] > 0) {
          cta++;
          list.Add(i);
        }
      }
      if (cta == 0) {
        Console.WriteLine("1 1"); // Grid is already good, swap column 1 with itself
      } else if (cta >= 3) {
        Console.WriteLine("-1"); // Too many mismatches to fix with one swap
      } else if (cta == 2) {
        // Try swapping the two mismatched columns
        for (var i = 0; i < N; i++) {
          int a1 = A[i, list[0]];
          A[i, list[0]] = A[i, list[1]];
          A[i, list[1]] = a1;
        }
        int ctb = 0;
        for (var i = 0; i < N; i++) {
          for (var j = 0; j < M; j++) {
            if (A[i, j] != B[i][j]) {
              ctb++; // Check if swapping fixed the grid
            }
          }
        }
        if (ctb > 0) {
          Console.WriteLine("-1"); // Swapping didn't fix the grid
        } else {
          Console.WriteLine((list[0] + 1) + " " + (list[1] + 1)); // Output 1-based indices of columns swapped
        }
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/