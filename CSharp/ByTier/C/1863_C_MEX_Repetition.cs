// Problem: CF 1863 C - MEX Repetition
// https://codeforces.com/contest/1863/problem/C

/*
 * Problem: MEX Repetition
 * 
 * Purpose:
 *   Given an array of distinct integers from 0 to n, perform k operations where each operation
 *   replaces each element with the MEX (Minimum EXcluded) of the entire array.
 *   
 * Algorithm:
 *   - The key insight is that after a few operations, the array will start to cycle.
 *   - After at most n+1 operations, the array begins to repeat the same pattern.
 *   - We compute the MEX for the initial array and store it at index n.
 *   - Then, we simulate only up to n+1 operations to detect the cycle.
 *   - Finally, we use modular arithmetic to determine the result after k operations.
 *   
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) per test case
 * 
 * Techniques:
 *   - MEX calculation
 *   - Cycle detection in array transformations
 *   - Modular arithmetic for large k values
 */

using System;

public class MexRepetition {
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]); // Read array size
      int k = int.Parse(parts[1]); // Read number of operations
      parts = Console.ReadLine().Split();
      int[] aExt = new int[n + 1]; // Extended array to hold original values and MEX
      bool[] contains = new bool[n + 1]; // Track which numbers are present
      for (int j = 0; j < n; j++) {
        int aj = int.Parse(parts[j]); // Parse current element
        aExt[j] = aj; // Store in extended array
        contains[aj] = true; // Mark that number is present
      }
      // Find MEX (smallest non-negative integer not in array)
      aExt[n] = Array.IndexOf(contains, false); 
      // Determine index from which to start the result based on cycle
      int idx = n - (k - 1) % (n + 1);
      int[] ans = new int[n]; // Final result array
      for (int j = 0; j < n; j++) {
        ans[j] = aExt[idx]; // Assign values from extended array
        idx = (idx + 1) % (n + 1); // Move to next index in circular fashion
      }
      Console.WriteLine(string.Join(" ", ans)); // Output result
    }
  }
}


// https://github.com/VaHiX/CodeForces/