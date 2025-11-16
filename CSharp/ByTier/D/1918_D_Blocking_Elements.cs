// Problem: CF 1918 D - Blocking Elements
// https://codeforces.com/contest/1918/problem/D

/*
 * Problem: Blocking Elements
 * 
 * Algorithm: Binary Search + Dynamic Programming with Deque Optimization
 * 
 * Time Complexity: O(n * log(max_sum)) where n is the length of the array and max_sum is up to 1e17
 * Space Complexity: O(n)
 * 
 * Approach:
 * - Use binary search on the answer (cost).
 * - For each candidate cost, use dynamic programming with a deque to find if it's possible to block elements
 *   such that the cost does not exceed the candidate.
 * - The DP state represents the minimum cost to partition the array up to index i.
 * - A deque is used to maintain potential previous indices efficiently in the DP transition.
 * 
 * The key idea is to check if there exists a way to block some elements such that:
 * 1. Sum of blocked elements <= candidate cost
 * 2. Maximum sum of segments after blocking <= candidate cost
 * 
 * This is done via DP optimization with a monotonic deque.
 */

using System;
using System.Collections.Generic;
public class MainClass {
  static void Solve() {
    int T = NextInt();
    while (T-- > 0) {
      int N = NextInt();
      long[] v = new long[N + 1];
      long[] s = new long[N + 1];
      for (int i = 1; i <= N; i++) {
        v[i] = NextInt();
        s[i] = s[i - 1] + v[i]; // Prefix sum array
      }
      long l = 0, h = (long)1e17; // Binary search bounds
      while (l < h) {
        long m = (l + h) / 2; // Midpoint for binary search
        long[] w = new long[N + 1]; // DP array for minimum cost to reach index i
        int[] z = new int[N + 1]; // Deque to keep track of indices
        int zs = 0, ze = 0; // Deque pointers
        
        for (int i = 1; i <= N; i++) {
          // Find the smallest j such that s[i-1] - s[j] <= m
          int j = LowerBound(s, s[i - 1] - m);
          
          // Remove outdated indices from the front of deque
          while (zs < ze && z[zs] < j) {
            zs++;
          }
          
          // If valid index found, update j
          if (zs < ze && w[z[zs]] < w[j]) {
            j = z[zs];
          }
          
          w[i] = w[j] + v[i]; // DP transition
          
          // Maintain deque in decreasing order of w values
          while (zs < ze && w[z[ze - 1]] > w[i]) {
            ze--;
          }
          z[ze++] = i;
        }
        
        bool ok = false;
        long sum = 0;
        // Check if it's possible to split the array with cost <= m
        for (int i = N; i >= 1; i--) {
          if (w[i] <= m) {
            ok = true;
          }
          sum += v[i];
          if (sum > m) {
            break; // Early termination
          }
        }
        
        if (!ok) {
          l = m + 1; // Need a larger cost
        } else {
          h = m; // Current cost is feasible
        }
      }
      Console.WriteLine(h);
    }
  }
  static int LowerBound(long[] array, long target) {
    int low = 0, high = array.Length;
    while (low < high) {
      int mid = (low + high) / 2;
      if (array[mid] < target) {
        low = mid + 1;
      } else {
        high = mid;
      }
    }
    return low;
  }
  public static void Main(string[] args) { Solve(); }
  static string[] tokens = null;
  static int tokensIndex = 0;
  static int NextInt() {
    if (tokens == null || tokensIndex == tokens.Length) {
      tokens = Console.ReadLine().Split();
      tokensIndex = 0;
    }
    return int.Parse(tokens[tokensIndex++]);
  }
}


// https://github.com/VaHiX/CodeForces/