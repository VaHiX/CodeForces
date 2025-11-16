// Problem: CF 1979 B - XOR Sequences
// https://codeforces.com/contest/1979/problem/B

/*
 * Problem: XOR Sequences
 * 
 * Algorithm:
 * - Given two sequences a_n = n ⊕ x and b_n = n ⊕ y, we need to find the longest
 *   common subsegment between them.
 * - The key insight is that a subsegment a_i, a_i+1, ..., a_i+m-1 equals b_j, b_j+1, ..., b_j+m-1
 *   if and only if the XOR of corresponding elements aligns properly.
 * - This alignment occurs when the difference in indices (j - i) is such that the XOR of the
 *   differences results in a specific pattern.
 * - More precisely, the length of the longest common subsegment equals 2^r, where r is the
 *   number of trailing zeros in x ⊕ y.
 * 
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(t), to store the results.
 */

using System;
using System.Collections.Generic;
public class Program {
  // Function to count trailing zeros in the binary representation of a number
  public static int TrailingZeros(long num) {
    if (num == 0)
      return 64;
    int count = 0;
    while ((num & 1) == 0) {
      count++;
      num >>= 1;
    }
    return count;
  }
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    List<long> results = new List<long>(t); // Store results for each test case
    for (int i = 0; i < t; ++i) {
      string[] inputs = Console.ReadLine().Split(' ');
      long x = long.Parse(inputs[0]); // Read x
      long y = long.Parse(inputs[1]); // Read y
      long z = x ^ y; // Compute XOR of x and y
      long powerOfTwo = 1L << TrailingZeros(z); // Calculate 2^(trailing zeros of z)
      results.Add(powerOfTwo); // Add result to list
    }
    foreach (var result in results) {
      Console.WriteLine(result); // Output each result
    }
  }
}


// https://github.com/VaHiX/CodeForces/