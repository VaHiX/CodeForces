// Problem: CF 2003 A - Turtle and Good Strings
// https://codeforces.com/contest/2003/problem/A

using System;
class Program {
  static void Main(string[] args) {
    // Flowerbox describing the code purpose, algorithms, and complexities
    /*
     * Code Purpose:
     * This program determines whether a given string is a "good string" as per the problem definition.
     * A good string can be split into at least two parts such that no part's first character equals any later part's last character.
     * 
     * Algorithm/Techniques:
     * The key insight is that if we split the string into exactly two parts, the condition is satisfied if and only if 
     * the first character of the first part is not equal to the last character of the second part.
     * Therefore, we simply check if the first character of the full string is different from its last character.
     * 
     * Time Complexity: O(n) where n is the length of the string. We only read the first and last character for each string.
     * Space Complexity: O(1). Only a constant amount of extra space is used.
     */

    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()); // Read length of the string
      string s = Console.ReadLine(); // Read the string itself
      if (s[0] != s[n - 1]) { // Check if first and last characters are different
        Console.WriteLine("YES"); // If different, it's a good string
      } else {
        Console.WriteLine("NO"); // If same, it's not a good string
      }
    }
  }
}

// https://github.com/VaHiX/CodeForces/