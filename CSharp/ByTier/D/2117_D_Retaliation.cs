// Problem: CF 2117 D - Retaliation
// https://codeforces.com/contest/2117/problem/D

/*
 * Problem: D. Retaliation
 * Purpose: Determine if an array can be reduced to all zeros using two types of operations:
 *          1. Subtract i from each element at index i (1-indexed)
 *          2. Subtract (n - i + 1) from each element at index i (1-indexed)
 * 
 * Algorithm:
 * - First check if the array is an arithmetic sequence with a common difference d.
 * - If not, return "NO".
 * - Compute hypothetical starting and ending values based on direction of difference.
 * - Validate if the computed conditions for total operations are valid using modular arithmetic.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) due to array conversion and temporary storage
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read array size
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      getAns(n, a); // Process the current test case
    }
  }
  
  static void getAns(int n, int[] a) {
    var d = a[1] - a[0]; // Compute the common difference of arithmetic sequence
    
    // Check if the array forms an arithmetic sequence
    for (int i = 1; i < n - 1; i++) {
      if (a[i + 1] - a[i] != d) {
        Console.WriteLine("NO");
        return;
      }
    }
    
    // Determine start and end values depending on direction of progression
    var start = d >= 0 ? a[0] : a[n - 1];
    var end = d >= 0 ? a[n - 1] : a[0];
    
    // Compute total value based on arithmetic progression sum formula
    var av1 = (long)n * start - end;
    
    // If computed value is negative, impossible to reach zero
    if (av1 < 0) {
      Console.WriteLine("NO");
      return;
    }
    
    // Compute denominator for modular division check
    var av2 = (long)n * n - 1;
    
    // If divisible by av2, answer is YES; otherwise NO
    Console.WriteLine(av1 % av2 == 0 ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/CodeForces/