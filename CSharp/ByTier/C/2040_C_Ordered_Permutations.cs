// Problem: CF 2040 C - Ordered Permutations
// https://codeforces.com/contest/2040/problem/C

/*
C. Ordered Permutations

Algorithm:
This code generates the k-th lexicographically smallest permutation among those with maximum S(p) value.
The approach uses binary representation to directly construct a valid permutation in O(n) time.
Maximum value of S(p) is achieved by placing largest elements as early as possible, and the order
of smaller elements is determined via a binary encoding mechanism.
Time Complexity: O(n)
Space Complexity: O(n)

The idea is to construct permutations that yield maximum sum S(p), which is known to have 
a specific form. We represent k in binary and use that to determine how to place numbers 
from 1 to n in two groups, then combine them appropriately.

*/
using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    int testCases = int.Parse(Console.ReadLine());
    while (testCases-- > 0) {
      string[] inputs = Console.ReadLine().Split();
      int n = int.Parse(inputs[0]);
      long k = long.Parse(inputs[1]);
      List<int> firstGroup = new List<int>();
      List<int> secondGroup = new List<int>();
      if (n <= 60 && (1L << (n - 1)) < k) { // Check if k exceeds number of valid permutations
        Console.WriteLine(-1);
        continue;
      }
      k--; // Convert to 0-based indexing
      
      List<int> binaryDigits = new List<int>();
      while (k > 0) {
        binaryDigits.Add((int)(k % 2)); // Extract least significant bit
        k /= 2; // Right shift
      }
      
      // Pad binary digits with zeros to ensure length n-1
      while (binaryDigits.Count < n - 1)
        binaryDigits.Add(0);
        
      // Distribute numbers into first and second groups based on binary representation
      for (int i = n - 2, j = 1; i >= 0; i--, j++) {
        if (binaryDigits[i] == 0)
          firstGroup.Add(j);
        else
          secondGroup.Add(j);
      }
      
      secondGroup.Reverse(); // Reverse to maintain correct order
      
      // Output the permutation: first group, then n, then reversed second group
      foreach (int num in firstGroup)
        Console.Write(num + " ");
      Console.Write(n + " "); // Always include n at middle
      foreach (int num in secondGroup)
        Console.Write(num + " ");
      Console.WriteLine();
    }
  }
}


// https://github.com/VaHiX/codeForces/