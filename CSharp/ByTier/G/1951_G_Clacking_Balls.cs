// Problem: CF 1951 G - Clacking Balls
// https://codeforces.com/contest/1951/problem/G

/*
 * Code Purpose:
 * This code calculates the expected time for Alice to reduce n balls to 1 ball on a circular arrangement of m baskets.
 * 
 * Algorithm & Techniques:
 * - Uses a mathematical approach based on linearity of expectation.
 * - Computes the expected number of operations by considering the distance between consecutive balls.
 * - Applies modular arithmetic for large numbers and uses fast exponentiation for modular inverse.
 * 
 * Time Complexity: O(n * log(n)) due to sorting and processing each ball.
 * Space Complexity: O(n) for storing the positions and intermediate arrays.
 */

using System;

public class Program {
  const long M = 1000000007; // Modulo value
  const int N = 400000;      // Maximum size for arrays
  static long ksm(long a, long p) {
    long res = 1;
    while (p > 0) {
      if ((p & 1) != 0) {
        res = (res * a) % M; // Multiply result by a if p is odd
      }
      a = (a * a) % M; // Square a
      p >>= 1; // Right shift p by 1 bit (divide by 2)
    }
    return res;
  }
  
  // Computes combination C(n, 3) = n*(n-1)*(n-2)/6 modulo M
  static long C(long n) {
    return (n * (n - 1) % M * (n - 2) % M * ksm(6, M - 2)) % M;
  }
  
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      string[] input = Console.ReadLine().Split();
      int n = int.Parse(input[0]);
      int m = int.Parse(input[1]);
      long[] a = new long[N + 50]; // Array to store ball positions
      string[] numbers = Console.ReadLine().Split();
      for (int i = 0; i < n; i++) {
        a[i] = long.Parse(numbers[i]); // Read ball positions
      }
      
      Array.Sort(a, 0, n); // Sort the positions
      
      a[n] = a[0] + m; // Add the position of the first ball shifted by m (to handle circular arrangement)
      
      long res = C(m + 1); // Initialize result with combination of total positions
      
      // Process each consecutive pair of balls to compute expected operations
      for (int i = 1; i <= n; i++) {
        res = (res + M - C(a[i] - a[i - 1] + 1)) % M; // Subtract combinations of the gaps
      }
      
      // Final calculations using linearity of expectation
      res = (res * n) % M * ksm(m, M - 2) % M;
      
      Console.WriteLine(res);
    }
  }
}


// https://github.com/VaHiX/CodeForces/