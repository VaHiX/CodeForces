// Problem: CF 1997 A - Strong Password
// https://codeforces.com/contest/1997/problem/A

using System;
using System.Text;
class Program {
  // Algorithm: Brute-force search
  // Time Complexity: O(n * 26 * n) = O(n^2) per test case, where n is length of string
  // Space Complexity: O(n) for storing the result string and temporary substrings
  static long C(string s) {
    long t = 2; // First character takes 2 seconds
    for (int i = 1; i < s.Length; ++i) {
      if (s[i] == s[i - 1]) { // Same as previous character
        t += 1; // Takes 1 second
      } else {
        t += 2; // Takes 2 seconds
      }
    }
    return t;
  }
  static void Main() {
    int n = int.Parse(Console.ReadLine()); // Read number of test cases
    StringBuilder o = new StringBuilder(); // For efficient output building
    while (n-- > 0) {
      string s = Console.ReadLine(); // Read current password
      string b = ""; // Best password found so far
      long m = -1; // Maximum time found so far
      for (int i = 0; i <= s.Length; ++i) { // Try inserting at each position
        for (char c = 'a'; c <= 'z'; ++c) { // Try each lowercase letter
          // Create new password by inserting character c at position i
          string p = s.Substring(0, i) + c + s.Substring(i);
          long t = C(p); // Calculate typing time of new password
          if (t > m) { // If this is better than current best
            m = t; // Update maximum time
            b = p; // Update best password
          }
        }
      }
      o.AppendLine(b); // Store result for this test case
    }
    Console.Write(o.ToString()); // Output all results
  }
}


// https://github.com/VaHiX/CodeForces/