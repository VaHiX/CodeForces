// Problem: CF 1844 D - Row Major
// https://codeforces.com/contest/1844/problem/D

/*
 * Problem: Find a string of length n with minimum distinct characters such that it is not the row-major order of any bad grid.
 * 
 * Approach:
 * - A "bad grid" is one where adjacent cells (sharing an edge) have the same character.
 * - We want to construct a string of length n that cannot be the row-major order of any such bad grid.
 * - The key idea is to use a pattern that avoids adjacent repeating characters in any possible grid layout.
 * - We try to find the smallest number of distinct characters (cnt) such that n is not divisible by cnt.
 *   This ensures that we can't distribute the characters evenly in a grid without creating a bad configuration.
 * - Then we construct a string with cnt distinct characters, cycling through them to avoid invalid patterns.
 * 
 * Time Complexity: O(n) per test case, as we loop through n characters to construct the result.
 * Space Complexity: O(n) for storing the result string.
 */

using System;
using System.Text;
using System.Linq;
class Program {
  static String Solution() {
    int n = int.Parse(Console.ReadLine());
    int cnt = 2;  // Start checking from 2 distinct characters
    for (; cnt <= 26; ++cnt) {  // Loop up to 26 (all lowercase letters)
      if (n % cnt != 0) {  // If n is not divisible by cnt, we can use cnt distinct chars
        break;
      }
    }
    char[] result = new char[n];  // Create a character array of size n
    for (int i = 0; i < n; ++i) {
      result[i] = (char)('a' + i % cnt);  // Fill with cyclic pattern of cnt characters
    }
    return new String(result);
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Console.WriteLine(Solution());
    }
  }
}


// https://github.com/VaHiX/CodeForces/