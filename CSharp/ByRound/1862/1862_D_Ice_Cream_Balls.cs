// Problem: CF 1862 D - Ice Cream Balls
// https://codeforces.com/contest/1862/problem/D

/*
 * Problem: Ice Cream Balls
 * 
 * Purpose:
 *   Given the number of unique two-ball ice cream combinations (n), 
 *   determine the minimum number of balls required to form all those combinations.
 * 
 * Approach:
 *   - Each combination is a pair of ball types (with repetition allowed).
 *   - With 'k' distinct ball types, the number of unique pairs (including same type twice) 
 *     is given by the formula: k*(k+1)/2 (this includes combinations like (1,1), (1,2), ..., (k,k)).
 *   - We need to find the smallest k such that k*(k+1)/2 >= n.
 *   - Once k is found, the minimum number of balls needed is calculated as: n + k*(3-k)/2.
 * 
 * Time Complexity: O(1) per test case - only simple arithmetic operations and a while loop that runs at most a few times.
 * Space Complexity: O(1) - only a constant amount of extra space.
 */

using System;
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      long n = long.Parse(Console.ReadLine()); // Read number of desired ice cream types
      
      // Initial estimate using square root approximation
      long k = (long)Math.Ceiling(Math.Sqrt(2 * n) - 3);
      
      // Adjust k until k*(k+1)/2 >= n
      while (k * (k + 1) / 2 <= n) {
        k++;
      }
      
      // Calculate and print the result using the derived formula
      Console.WriteLine(n + k * (3 - k) / 2);
    }
  }
}


// https://github.com/VaHiX/CodeForces/