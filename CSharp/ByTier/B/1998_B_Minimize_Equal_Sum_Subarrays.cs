// Problem: CF 1998 B - Minimize Equal Sum Subarrays
// https://codeforces.com/contest/1998/problem/B

/*
 * Problem: Minimize Equal Sum Subarrays
 * 
 * Purpose: Given a permutation p of length n, find another permutation q such that the number of equal subarray sums is minimized.
 * 
 * Approach:
 * The key observation is that we want to minimize the number of pairs (i, j) such that the sum of elements from index i to j is the same in both p and q.
 * A simple strategy is to create q by shifting p one position to the left (circular shift), i.e., q[0] = p[1], q[1] = p[2], ..., q[n-1] = p[0].
 * This ensures that no subarray of p and q have the same sum for the entire array, and minimizes the total number of matching subarrays.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the permutation q
 */

using System;
public class MinimizeEqualSumSubarrays {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine()); // Read length of permutation
      string[] parts = Console.ReadLine().Split(); // Read the permutation p
      int[] q = new int[n]; // Initialize result permutation q
      int idxLast = n - 1; // Index of last element in array
      for (int j = 0; j < idxLast; j++)
        q[j] = int.Parse(parts[j + 1]); // Copy elements from p[1] to p[n-1] to q[0] to q[n-2]
      q[idxLast] = int.Parse(parts[0]); // Place p[0] at the end of q
      Console.WriteLine(string.Join(" ", q)); // Output the constructed permutation q
    }
  }
}


// https://github.com/VaHiX/CodeForces/