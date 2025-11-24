// Problem: CF 1411 A - In-game Chat
// https://codeforces.com/contest/1411/problem/A

/*
 * Code Purpose: This program determines whether a given string is considered "bad" based on a specific condition.
 *               A string is bad if the number of trailing ')' characters is strictly greater than the number of non-')' characters.
 * 
 * Algorithm/Techniques: 
 *   - Traverse the string from the end to count consecutive ')' characters.
 *   - Compare the count of trailing ')' with the remaining characters.
 * 
 * Time Complexity: O(n) where n is the length of the string. In the worst case, we traverse the entire string once.
 * Space Complexity: O(1) excluding input storage; only a constant amount of extra space is used.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using static System.Console;
public class q {
  public static void Main() {
    int n = int.Parse(ReadLine()); // Read number of test cases
    string[] r = new string[n]; // Array to store results
    while (n-- > 0)
      r[r.Length - 1 - n] = Compute(int.Parse(ReadLine()), ReadLine()); // Process each test case and store result
    while (n++ < r.Length - 1) // Output results
      WriteLine(r[n]);
  }
  static string Compute(int n, string s) {
    int i = n - 1; // Start from the last index
    int k = 0; // Counter for trailing ')'
    while (i >= 0 && s[i--] == ')') // Count trailing ')'
      k++;
    return k > (n - k) ? "Yes" : "No"; // Check if trailing ')' count is greater than non-')' characters
  }
}


// https://github.com/VaHiX/CodeForces/