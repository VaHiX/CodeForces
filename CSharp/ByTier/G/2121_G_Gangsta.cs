// Problem: CF 2121 G - Gangsta
// https://codeforces.com/contest/2121/problem/G

/*
 * Problem: G. Gangsta
 * Purpose: Calculate the sum of maximum character frequencies (f(s[l..r])) for all substrings s[l..r] of a binary string.
 * Algorithm:
 *   - Use prefix sums to efficiently compute contribution of each character in substrings.
 *   - For each substring, f(s[l..r]) equals max(count('0'), count('1')) in that substring.
 *   - Transform the problem using a prefix sum technique where we map '0' to -1 and '1' to +1.
 *   - Then, for each prefix value, we calculate how many times it contributes to the total sum.
 * Time Complexity: O(n log n) per test case due to sorting of prefix array
 * Space Complexity: O(n) for storing prefix sums
 */
using System;
using System.Text;
class Program {
  static long Solve(string s, int n) {
    long ans = 0;
    int[] pref = new int[n + 1];
    for (int i = 0; i < n; i++) {
      // Map '0' to -1 and '1' to 1, and build prefix sum
      pref[i + 1] = pref[i] + (s[i] == '1' ? 1 : -1);
    }
    // Calculate base contribution of all intervals
    for (int i = 1; i <= n; i++) {
      ans += (long)i * (n - i + 1);
    }
    // Sort prefix values to help compute final answer efficiently
    Array.Sort(pref);
    for (int i = 0; i <= n; i++) {
      // Use sorted prefix sums to calculate contributions based on balance
      ans += (long)pref[i] * (2L * i - n);
    }
    return ans / 2;
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int ti = 0; ti < t; ti++) {
      int n = int.Parse(Console.ReadLine());
      string s = Console.ReadLine();
      Console.WriteLine(Solve(s, n));
    }
  }
}


// https://github.com/VaHiX/codeForces/