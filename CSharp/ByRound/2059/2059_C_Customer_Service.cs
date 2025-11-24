// Problem: CF 2059 C - Customer Service
// https://codeforces.com/contest/2059/problem/C

/*
 * Problem: Customer Service
 * 
 * Purpose: 
 *   Given n queues and n time moments, each queue receives a certain number of
 *   customers at each moment. At each moment, exactly one queue is served (its
 *   customer count becomes 0). We aim to choose the order of service such that
 *   the MEX (minimum excludant) of final queue sizes is maximized.
 * 
 * Algorithm:
 *   1. For each queue, compute how many consecutive 1's appear from the end.
 *      This count represents how many time units we can "skip" before the queue
 *      becomes non-empty.
 *   2. Sort this array of counts.
 *   3. Determine the maximum MEX by checking how many positions can be filled
 *      with increasing integers starting from 0 (like a greedy approach).
 *   4. The result is the minimum of n and the computed MEX.
 * 
 * Time Complexity:
 *   O(n^2) for processing the input and computing L array.
 *   O(n log n) for sorting L.
 *   O(n) for the final greedy check.
 *   Overall: O(n^2)
 * 
 * Space Complexity:
 *   O(n) for storing the input matrix and the L array.
 * 
 * Techniques:
 *   - Greedy approach with sorting
 *   - Simulation of a suffix of 1's in each row
 *   - MEX computation using greedy matching
 */

using System;
using System.Linq;
public class Program {
  public static void Main(string[] args) {
    int tc = int.Parse(Console.ReadLine());
    for (int t = 0; t < tc; t++) {
      int n = int.Parse(Console.ReadLine());
      long[][] a = new long [n][];
      for (int i = 0; i < n; i++) {
        a[i] = Console.ReadLine()
                   .Split(new char[] { ' ' },
                          StringSplitOptions.RemoveEmptyEntries)
                   .Select(long.Parse)
                   .ToArray();
      }
      int[] L = new int[n];
      for (int i = 0; i < n; i++) {
        int count = 0;
        // Count trailing 1's in the array a[i]
        for (int j = n - 1; j >= 0; j--) {
          if (a[i][j] == 1)
            count++;
          else
            break;
        }
        L[i] = count;
      }
      // Sort the trailing 1's count array
      Array.Sort(L);
      int tAssign = 1;
      // Greedily assign service order and check how many consecutive numbers
      // 0, 1, 2, ... we can cover
      for (int i = 0; i < n; i++) {
        if (L[i] >= tAssign)
          tAssign++;
      }
      int candidateMEX = tAssign;
      int ans = Math.Min(n, candidateMEX);
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/