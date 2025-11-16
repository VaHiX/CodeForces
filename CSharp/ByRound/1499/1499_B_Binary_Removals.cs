// Problem: CF 1499 B - Binary Removals
// https://codeforces.com/contest/1499/problem/B

/*
 * Problem: Binary Removals
 * 
 * Algorithm/Technique: Greedy + Observation
 * 
 * Time Complexity: O(n) where n is the length of the string
 * Space Complexity: O(1) - only using a few variables for computation
 * 
 * Key Insight:
 * - A string can be made sorted by removing some non-adjacent '0's and '1's if and only if:
 *   - It does not have the pattern "11" followed by "00" in the wrong order
 *   - Specifically, if there exists a "11" pattern before a "00" pattern, then the string 
 *     cannot be sorted by removing non-adjacent characters.
 * 
 * Explanation:
 * - If we have "11...00" where "11" appears before "00", we cannot sort it by removing 
 *   non-adjacent characters.
 * - The case of "11" at the beginning or "00" at the end can be handled by a simple check:
 *   - If "11" exists somewhere and "00" exists somewhere, and the first "11" occurs 
 *     before the last "00", then the result is NO.
 *   - Otherwise, it is YES.
 * 
 * This is a clever observation that avoids the need for dynamic programming or complex 
 * backtracking approaches.
 */
using System;
using System.Collections.Generic;
using System.Linq;
class HelloWorld {
  static void Main() {
    int n;
    n = Convert.ToInt32(Console.ReadLine());
    for (int i = 0; i < n; i++) {
      string str;
      str = Console.ReadLine();
      // Check if there is a "11" and a "00" such that "11" appears before "00"
      // If so, it's impossible to sort the string by removing non-adjacent characters
      if (str.IndexOf("11") != -1 && str.LastIndexOf("00") != -1 &&
          str.IndexOf("11") < str.LastIndexOf("00")) {
        Console.WriteLine("NO");
      } else
        Console.WriteLine("YES");
    }
  }
}


// https://github.com/VaHiX/CodeForces/