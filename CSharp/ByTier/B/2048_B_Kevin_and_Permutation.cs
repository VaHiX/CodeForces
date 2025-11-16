// Problem: CF 2048 B - Kevin and Permutation
// https://codeforces.com/contest/2048/problem/B

/*
 * Code Purpose:
 * This code constructs a permutation of length n such that the sum of minimum values 
 * over all subarrays of length k is minimized.
 * 
 * Algorithm:
 * The strategy is to arrange elements in a way that minimizes the contribution of small 
 * values to the total sum. By placing numbers in a specific pattern, we can ensure that 
 * the smallest numbers appear in as few subarrays as possible.
 * 
 * Time Complexity: O(n), as we iterate through the array once to fill it.
 * Space Complexity: O(n), for storing the permutation array.
 */

using System;
public class KevinAndPermutation {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      int k = int.Parse(parts[1]);
      int[] p = new int[n];
      int d = 0;
      for (int j = 0; j < n; j++)
        // If current index is at the end of a group of size k, assign (j+1)/k
        // Otherwise, assign n - d++ to distribute larger values early
        p[j] = j % k == k - 1 ? (j + 1) / k : n - d++;
      Console.WriteLine(string.Join(" ", p));
    }
  }
}


// https://github.com/VaHiX/CodeForces/