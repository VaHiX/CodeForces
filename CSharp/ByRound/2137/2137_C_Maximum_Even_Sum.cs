// Problem: CF 2137 C - Maximum Even Sum
// https://codeforces.com/contest/2137/problem/C

// C. Maximum Even Sum
// 
// Problem Description:
// Given two integers a and b, we choose an integer k such that b is divisible by k,
// then multiply a by k and divide b by k. The goal is to maximize the even value of a+b.
// If it's impossible to make a+b even, return -1.
//
// Algorithms/Techniques:
// - Bit manipulation for checking odd/even properties
// - Mathematical analysis to determine valid k values
// - Optimization based on binary representation of b and parity of a
//
// Time Complexity: O(1) per test case (constant time operations)
// Space Complexity: O(1) (only using a fixed amount of memory)

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()!);
    while (t-- > 0) {
      string[] parts = Console.ReadLine()!.Split();
      long a = long.Parse(parts[0]);
      long b = long.Parse(parts[1]);
      if ((b & 1) == 1) { // If b is odd
        if ((a & 1) == 1) { // If a is also odd
          Console.WriteLine(a * b + 1); // Then a+b will be even
        } else {
          Console.WriteLine("-1"); // Otherwise impossible to make sum even
        }
        continue;
      }
      long bb = b;
      int powerOfTwo = 0;
      while ((bb & 1) == 0) { // Count how many times b can be divided by 2
        bb >>= 1; // Right shift to divide by 2
        powerOfTwo++;
      }
      if ((a & 1) == 1 && powerOfTwo == 1) { // Special case: a is odd and b has exactly one factor of 2
        Console.WriteLine("-1"); // Impossible to get even sum
        continue;
      }
      long kMin = ((a & 1) == 1) ? 2 : 1; // Choose minimal k based on parity of a
      long s1 = a * kMin + b / kMin; // Compute first candidate for a+b
      long s2 = a * (b / 2) + 2; // Compute second candidate for a+b (using k = b/2)
      Console.WriteLine(Math.Max(s1, s2)); // Output maximum of both candidates
    }
  }
}


// https://github.com/VaHiX/codeForces/