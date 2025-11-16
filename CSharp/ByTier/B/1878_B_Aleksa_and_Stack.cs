// Problem: CF 1878 B - Aleksa and Stack
// https://codeforces.com/contest/1878/problem/B

using System;
namespace codeForces {
internal class Program {
  static void Main(string[] args) {
    // Flowerbox: 
    // Purpose: This program constructs a strictly increasing array of positive integers of length n,
    // such that for every triplet a_i, a_{i+1}, a_{i+2}, the condition 3*a_{i+2} is not divisible by a_i + a_{i+1} holds.
    // Algorithm: The solution uses a simple pattern where a_i = 1 + 2*i for all i. This ensures a strictly increasing sequence,
    // and it avoids divisibility issues due to small increments.
    // Time Complexity: O(n) per test case, as we iterate through n elements once.
    // Space Complexity: O(1) additional space, not counting input/output storage.
    
    long testCases = long.Parse(Console.ReadLine());
    for (long i = 0; i < testCases; ++i) {
      long arrayLen = long.Parse(Console.ReadLine());
      for (long j = 0; j < arrayLen; ++j)
        Console.Write(1 + (j * 2) + " ");  // Generate array elements as 1, 3, 5, ..., (2n-1) to ensure strictly increasing and avoid divisibility conflicts
      Console.WriteLine();  // Print new line after each test case
    }
  }
}
}

// https://github.com/VaHiX/CodeForces/