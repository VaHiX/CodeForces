// Problem: CF 2108 A - Permutation Warm-Up
// https://codeforces.com/contest/2108/problem/A

/*
 * Problem: Count distinct values of function f(p) = sum of |p[i] - i| over all permutations of 1..n
 * Algorithm: Mathematical pattern recognition
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 * 
 * For n=2: f(p) can take values {0, 2} => 2 distinct values
 * For n=3: f(p) can take values {0, 2, 4} => 3 distinct values
 * 
 * The pattern emerges as:
 * - If n is even: ans = n*n/4 + 1
 * - If n is odd: ans = (n+1)*(n-1)/4 + 1
 * 
 * This is derived from analyzing how the sum |p[i] - i| varies across all permutations.
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read current n
      getAns(n); // Compute and print the answer for this n
    }
  }
  
  static void getAns(int n) { // Function to compute distinct values of f(p)
    int ans;
    if (n % 2 == 0) // If n is even
      ans = n * n / 4 + 1; // Apply formula for even case
    else // If n is odd
      ans = (n + 1) * (n - 1) / 4 + 1; // Apply formula for odd case
    Console.WriteLine(ans); // Output the result
  }
}


// https://github.com/VaHiX/codeForces/