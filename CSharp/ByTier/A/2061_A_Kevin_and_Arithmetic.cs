// Problem: CF 2061 A - Kevin and Arithmetic
// https://codeforces.com/contest/2061/problem/A

/*
 * Problem: Kevin and Arithmetic
 * Purpose: Maximize the number of points Kevin can earn by rearranging an array of integers,
 *          where each step adds an element to a running sum, and if the sum becomes even,
 *          it is repeatedly divided by 2 until odd, earning one point per such operation.
 *
 * Algorithms/Techniques:
 *   - Greedy strategy based on parity (odd/even)
 *   - Count odd and even numbers
 *   - If there are even numbers, we can use them to create more points by placing them early,
 *     because they allow earlier sums to be even (and thus earn points). The key insight is:
 *     - Even numbers help increase the chance of getting even sum at some point.
 *     - Odd numbers only contribute once to a point if the current total becomes even after adding them.
 *
 * Time Complexity: O(n) per test case due to single pass through array
 * Space Complexity: O(n) for input storage and auxiliary variables
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp1 {
  public class A2061_KevinAndArithmetic {
    static void Main(string[] args) {
      int n, b, t, result, odd, even;
      string[] input;
      int[] array;
      t = int.Parse(Console.ReadLine().ToString()); // Read number of test cases
      while (t-- > 0) { // Process each test case
        n = int.Parse(Console.ReadLine().ToString()); // Read size of array
        input = Console.ReadLine().Split(' '); // Read the array elements as string and split by space
        array = new int[n]; // Initialize integer array
        even = 0; // Count of even numbers
        odd = 0; // Count of odd numbers
        for (int i = 0; i < n; i++) {
          b = int.Parse(input[i]); // Parse current element
          if (b % 2 == 0) { // Check if number is even
            even++;
          } else if (b % 2 == 1) { // Check if number is odd
            odd++;
          }
        }
        if (even > 0) { // If there exists at least one even number
          Console.WriteLine(odd + 1); // We can earn one point more by placing even number strategically
        } else {
          Console.WriteLine(odd - 1); // No even numbers present, so no way to earn points from last even sum
        }
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/