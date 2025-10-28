// Problem: CF 1955 B - Progressive Square
// https://codeforces.com/contest/1955/problem/B

using System;
using System.Collections.Generic;

/*
 * Problem: Progressive Square
 * 
 * Algorithm:
 * - Given an n × n matrix and rules for constructing it:
 *   a[i+1,j] = a[i,j] + c
 *   a[i,j+1] = a[i,j] + d
 * - The matrix is built such that:
 *   a[i,j] = a[1,1] + (i-1)*c + (j-1)*d
 * 
 * Approach:
 * - First, find the minimum value in the array `b`, which will be a[1,1].
 * - For each cell (i,j) in the matrix, compute what the value should be:
 *   a[i,j] = a[1,1] + (i-1)*c + (j-1)*d
 * - Use a sorted dictionary to count occurrences of each element.
 * - For each position (i,j), check if the expected value exists in the dictionary.
 * - If it does, reduce its count or remove it if count becomes zero.
 * - Finally, check that all elements are matched (dictionary is empty).
 * 
 * Time Complexity: O(n^2 * log(n^2)) due to operations on SortedDictionary
 * Space Complexity: O(n^2) for storing counts in the dictionary
 */

public class ProgressiveSquare {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      short n = short.Parse(parts[0]);
      int c = int.Parse(parts[1]);
      int d = int.Parse(parts[2]);
      parts = Console.ReadLine().Split();
      SortedDictionary<int, int> counts = new SortedDictionary<int, int>();
      int bMin = 1000000001; // Initialize with large value to track minimum
      int nn = n * n;
      for (int j = 0; j < nn; j++) {
        int bj = int.Parse(parts[j]);
        bMin = Math.Min(bMin, bj); // Track the minimum value in b
        if (counts.ContainsKey(bj))
          counts[bj]++; // Increment count if key exists
        else
          counts.Add(bj, 1); // Add new key with count 1
      }
      bool ans = true; // Flag to determine validity of matrix
      for (short j = 0; j < n && ans; j++) // Iterate over rows
        for (short k = 0; k < n && ans; k++) { // Iterate over columns
          int bjk = bMin + j * c + k * d; // Compute expected value at (j,k)
          if (!counts.ContainsKey(bjk)) // If expected value is not in array
            ans = false; // Not a valid matrix
          else if (counts[bjk] > 1) // If multiple copies exist
            counts[bjk]--; // Decrease count
          else // If only one copy left
            counts.Remove(bjk); // Remove the key from dictionary
        }
      ans = ans && (counts.Count == 0); // Validate that all elements are matched
      Console.WriteLine(ans ? "YES" : "NO");
    }
  }
}

// https://github.com/VaHiX/CodeForces/