// Problem: CF 1891 B - Deja Vu
// https://codeforces.com/contest/1891/problem/B

/*
 * Problem: B. Deja Vu
 * 
 * Algorithms/Techniques: Bit manipulation, Preprocessing queries, Efficient array modification
 * 
 * Time Complexity: O(n * log(max(a)) + q * log(q)) where n is the size of array 'a' and q is the number of queries.
 * Space Complexity: O(n + q) for storing the array 'a', the list of unique queries 'x', and auxiliary variables.
 * 
 * The problem requires applying a series of modifications to an array based on divisibility conditions.
 * Each query x_i adds 2^(x_i - 1) to elements in the array that are divisible by 2^x_i.
 * 
 * Optimizations:
 * 1. Preprocess queries to remove duplicates to avoid redundant operations.
 * 2. Instead of simulating each operation, we compute the final result directly using bit manipulation.
 * 3. For each element, we determine how many trailing zeros it has in binary representation to identify the highest power of 2 that divides it.
 */

using System;
using System.Collections.Generic;
public class DejaVu {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      int q = int.Parse(parts[1]);
      string[] partsA = Console.ReadLine().Split();
      string[] partsX = Console.ReadLine().Split();
      
      // Boolean array to track which query values have been seen (used to deduplicate queries)
      bool[] v = new bool[31];
      // List to store unique queries in order of appearance
      List<byte> x = new List<byte>();
      
      // Process queries and remove duplicates
      for (int j = 0; j < q; j++) {
        byte xj = byte.Parse(partsX[j]);
        if (!v[xj]) {
          x.Add(xj);
          v[xj] = true;
        }
      }
      
      // Result array initialized to store final values
      int[] ans = new int[n];
      
      // Process each element in the array
      for (int j = 0; j < n; j++) {
        int aj = int.Parse(partsA[j]);
        byte countTrail0 = 0; // Number of trailing zeros in binary representation of aj
        int m = 1; // Mask to detect trailing zeros
        
        // Count the number of trailing zeros
        while ((aj & m) == 0) {
          m <<= 1;
          countTrail0++;
        }
        
        // Apply all relevant modifications to the current element
        for (byte k = 0; k < x.Count && countTrail0 > 0; k++) {
          if (x[k] <= countTrail0) {
            countTrail0 = Convert.ToByte(x[k] - 1);
            aj ^= 1 << countTrail0; // Apply the modification using XOR
          }
        }
        
        ans[j] = aj;
      }
      
      // Output the resulting array
      Console.WriteLine(string.Join(" ", ans));
    }
  }
}


// https://github.com/VaHiX/CodeForces/