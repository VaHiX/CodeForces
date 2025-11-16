// Problem: CF 1976 B - Increase/Decrease/Copy
// https://codeforces.com/contest/1976/problem/B

/*
 * Problem: Increase/Decrease/Copy
 * 
 * Purpose: Transform array 'a' into array 'b' using three operations:
 *   - Increase/decrease any element of 'a' by 1
 *   - Copy any element of 'a' and append to 'a'
 * 
 * Algorithm:
 *   - For each element in 'a', calculate the absolute difference to the corresponding element in 'b'
 *   - For the last element of 'b', compute the difference from each element of 'a' and the last element of 'b'
 *   - If copying the last element of 'b' is beneficial, we can avoid one of the differences
 *   - Use a greedy approach to minimize changes
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing arrays
 */
using System;
public class IncreaseDecreaseCopy {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine()); // Read length of array 'a'
      string[] parts = Console.ReadLine().Split(); // Read elements of array 'a'
      int[] a = new int[n];
      for (int j = 0; j < n; j++)
        a[j] = int.Parse(parts[j]); // Parse and store elements of 'a'
      
      parts = Console.ReadLine().Split(); // Read elements of array 'b'
      int[] b = new int[n + 1];
      for (int j = 0; j <= n; j++)
        b[j] = int.Parse(parts[j]); // Parse and store elements of 'b'
      
      long ans = 0; // Initialize total operations count
      int dMin = 1000000000; // Initialize minimum difference for last element
      int bLast = b[n]; // Store last element of 'b' for reuse
      for (int j = 0; j < n; j++) {
        int dAB = Math.Abs(a[j] - b[j]); // Calculate absolute difference between a[j] and b[j]
        ans += dAB; // Add difference to total operations
        
        int dA = Math.Abs(a[j] - bLast); // Difference from current 'a' element to last 'b' element
        int dB = Math.Abs(b[j] - bLast); // Difference from current 'b' element to last 'b' element
        
        // Check if copying last element gives better solution
        if (dA + dB == dAB)
          dMin = 0; // If perfect fit, no more operations needed for this index
        else
          dMin = Math.Min(dMin, Math.Min(dA, dB)); // Otherwise update minimum difference
      }
      
      ans += dMin + 1; // Add minimum difference plus one for copying operation
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/