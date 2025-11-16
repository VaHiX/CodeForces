// Problem: CF 1948 D - Tandem Repeats?
// https://codeforces.com/contest/1948/problem/D

/*
Purpose: This code solves the problem of finding the maximum length of a tandem repeat substring in a given string that may contain question marks. A tandem repeat is a string of even length where the first half matches the second half. Question marks can be replaced with any lowercase letter.

Algorithms/Techniques:
- Brute-force approach checking all possible tandem repeat lengths
- For each possible length (from 1 to n/2), we check if there exists a substring of that length that can form a tandem repeat by matching characters or using '?' as wildcards.

Time Complexity: O(n^2), where n is the length of the string, due to nested loops.
Space Complexity: O(1), as only a constant amount of extra space is used.
*/

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main(string[] args) {
    int tt = Convert.ToInt32(Console.ReadLine());
    while (tt-- > 0) {
      Solution();
    }
  }
  static void Solution() {
    string s = Console.ReadLine();
    int d = 0;
    // Iterate over all possible lengths of tandem repeats (from 1 to half the string length + 1)
    for (int i = 1; i <= s.Length / 2 + 1; i++) {
      int c = 0;
      // For each possible starting index of the first half of the tandem repeat
      for (int j = 0; j < s.Length - i; j++) {
        // Check if characters at symmetric positions match or one of them is '?'
        if (s[i + j] == s[j] || s[i + j] == '?' || s[j] == '?') {
          c++;  // Increment match counter
          // If we've matched the full length of the tandem repeat
          if (c == i) {
            d = i * 2;  // Length of full tandem repeat (2 * length of half)
            break;      // No need to check further for this length
          }
        } else {
          c = 0;  // Reset match counter on mismatch
        }
      }
    }
    Console.WriteLine(d);
  }
}


// https://github.com/VaHiX/CodeForces/