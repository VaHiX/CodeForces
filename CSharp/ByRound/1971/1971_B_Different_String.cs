// Problem: CF 1971 B - Different String
// https://codeforces.com/contest/1971/problem/B

/*
 * Problem: Rearrange characters of a string to form a new string that is not equal to the original.
 * If impossible, output "NO", otherwise output "YES" and any valid rearrangement.
 * 
 * Algorithm:
 * - For each string, check if all characters are the same.
 *   - If yes, it's impossible to rearrange to a different string → "NO"
 *   - If no, find the first character that differs from the first one and swap it with the previous one.
 * 
 * Time Complexity: O(n) per string, where n is the length of the string.
 * Space Complexity: O(n) for storing the list of characters.
 */

using System;
using System.Collections.Generic;
class Program {
  static void Main(string[] args) {
    int n = int.Parse(Console.ReadLine()); // Read number of test cases
    List<string> ans = new List<string>(); // To store answers for each test case
    for (int i = 0; i < n; i++) {
      string a = Console.ReadLine(); // Read the input string
      List<char> c = new List<char>(); // Convert string to list of characters
      char b = a[0]; // Store the first character for comparison
      int d = 0; // Counter for different characters
      int e = 0; // Index of the first different character
      foreach (char x in a) {
        c.Add(x); // Add character to list
        if (x != b) { // If current character is different from first
          d++; // Increment counter
          e = c.Count - 1; // Record index of the different character
        }
        b = x; // Update b to current character
      }
      if (d == 0) {
        // All characters are the same → no valid rearrangement possible
        ans.Add("NO");
      } else {
        // At least one character is different, so rearrangement is possible
        ans.Add("YES");
        char s = c[e]; // Store the different character
        c[e] = c[e - 1]; // Swap it with the previous character
        c[e - 1] = s;
        ans.Add(new string(c.ToArray())); // Convert back to string and add to result
      }
    }
    foreach (string j in ans) {
      Console.WriteLine(j); // Output all results
    }
  }
}


// https://github.com/VaHiX/CodeForces/