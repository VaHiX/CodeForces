// Problem: CF 2137 A - Collatz Conjecture
// https://codeforces.com/contest/2137/problem/A

/*
 * Problem: Reverse Collatz Conjecture
 * 
 * Purpose: This program determines a possible initial value of x given the final value after k steps
 *          of a modified Collatz-like process. The transformation rules are:
 *            - If x is even, divide by 2.
 *            - If x is odd, multiply by 3 and add 1.
 *          
 *          However, here we reverse-engineer the process to find an initial value given final x after k steps.
 * 
 * Algorithms/Techniques:
 *   - Reverse Simulation of Collatz-like sequence
 *   - Backtracking through possible predecessors
 * 
 * Time Complexity: O(k) per test case, where k is the number of iterations. Each iteration takes constant time.
 * Space Complexity: O(1), only using a constant amount of space regardless of input size.
 */
using System;
public class Test {
  public static void Main() {
    int T = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < T; i++) {
      int[] input = Array.ConvertAll(Console.ReadLine().Split(), int.Parse); // Read k and x
      int k = input[0];
      int x = input[1];
      for (int j = 0; j < k; j++) {
        // If x is 4 modulo 6, then it must have come from (x - 1) / 3 in forward step;
        // otherwise, x was obtained by multiplying by 2 (since even numbers are halved)
        if (x % 6 == 4)
          x = (x - 1) / 3;
        else
          x = 2 * x;
      }
      Console.WriteLine(x); // Output the reconstructed initial value
    }
  }
}


// https://github.com/VaHiX/codeForces/