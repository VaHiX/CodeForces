// Problem: CF 1987 B - K-Sort
// https://codeforces.com/contest/1987/problem/B

/*
 * Problem: B. K-Sort
 * 
 * Purpose: Given an array of integers, find the minimum number of coins needed to make the array non-decreasing.
 *          Each operation allows choosing k indices and increasing their values by 1, costing k+1 coins.
 * 
 * Algorithm:
 *   - For each element in the array, calculate how much we need to "lift" it to maintain non-decreasing order.
 *   - Maintain a variable `m` representing the maximum value seen so far.
 *   - For each element, compute the deficit (how much we need to add to make it >= previous max).
 *   - Keep track of the overall deficit (`a`) and the maximum deficit seen (`o`).
 *   - The final answer is `a + o`, where `a` is the total coins for increments and `o` accounts for the cost of operations.
 * 
 * Time Complexity: O(n), where n is the size of the array.
 * Space Complexity: O(1), only using a few variables regardless of input size.
 */

using System;
class Program {
  static void Main() {
    long t;
    t = long.Parse(Console.ReadLine());
    while (t-- > 0) {
      ComeOnPrahlad();
    }
  }
  static void ComeOnPrahlad() {
    long n;
    n = long.Parse(Console.ReadLine());
    long m = 0;              // Maximum value seen so far in the array
    long a = 0;              // Total deficit (sum of how much we must increase elements)
    long o = 0;              // Maximum deficit encountered during traversal
    string[] input = Console.ReadLine().Split(' ');
    for (long i = 0; i < n; ++i) {
      long x = long.Parse(input[i]);  // Current element
      a += Math.Max(0, m - x);        // Add deficit needed to make x >= m
      o = Math.Max(o, m - x);         // Track maximum deficit seen
      m = Math.Max(m, x);             // Update maximum value seen so far
    }
    Console.WriteLine(a + o);  // Output total coins needed
  }
}


// https://github.com/VaHiX/CodeForces/