// Problem: CF 2144 B - Maximum Cost Permutation
// https://codeforces.com/contest/2144/problem/B

/*
 * Problem: Maximum Cost Permutation
 * 
 * Algorithm/Techniques:
 * - Greedy approach to maximize the cost of sorting a permutation
 * - Identify fixed positions (where value equals index)
 * - Handle special case when only one zero exists and it can be placed to make a fixed position
 * - Calculate the minimum segment that requires sorting by finding the first and last non-fixed positions
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array
 * Space Complexity: O(n) due to auxiliary arrays of size n+1
 */

using System;
using System.Collections.Generic;
public class Program {
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int[] a = new int[n + 1]; // 1-indexed array to store input
      bool[] pr = new bool[n + 1]; // marks which numbers from 1 to n are present
      bool[] fx = new bool[n + 1]; // marks which positions are fixed (value equals index)
      int z = 0; // count of zeros
      string[] input = Console.ReadLine().Split();
      for (int i = 1; i <= n; i++) {
        a[i] = int.Parse(input[i - 1]);
        if (a[i] == 0) {
          z++; // count zeros
        } else if (a[i] >= 1 && a[i] <= n) {
          pr[a[i]] = true; // mark presence of numbers
        }
      }
      for (int i = 1; i <= n; i++) {
        if (a[i] == i) {
          fx[i] = true; // mark fixed positions
        }
      }
      bool bol = false;
      int zi = -1;
      int miss = -1;
      if (z == 1) { // if exactly one zero, check if placing it at its own index makes a fixed position
        for (int i = 1; i <= n; i++) {
          if (a[i] == 0) {
            zi = i; // store index of the zero
          }
        }
        for (int v = 1; v <= n; v++) {
          if (!pr[v]) {
            miss = v; // find the missing number
          }
        }
        if (zi == miss) { // if the zero's index equals the missing number
          bol = true; // then placing it will make it a fixed position
        }
      }
      int L = 1;
      // Find first non-fixed position
      while (L <= n && (fx[L] || (bol && L == zi))) {
        L++;
      }
      if (L > n) { // if all positions are fixed, cost is 0
        Console.WriteLine(0);
        continue;
      }
      int R = n;
      // Find last non-fixed position
      while (R >= 1 && (fx[R] || (bol && R == zi))) {
        R--;
      }
      // Output the length of the segment that needs sorting
      Console.WriteLine(R - L + 1);
    }
  }
}


// https://github.com/VaHiX/CodeForces/