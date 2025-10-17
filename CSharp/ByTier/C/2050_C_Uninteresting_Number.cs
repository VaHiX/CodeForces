// Problem: CF 2050 C - Uninteresting Number
// https://codeforces.com/contest/2050/problem/C

/*
C. Uninteresting Number

Algorithm:
The problem asks whether we can make a number divisible by 9 by replacing digits with their squares (if square < 10).
Only digits 0-3 can be squared to remain single digits (0²=0, 1²=1, 2²=4, 3²=9).
We analyze the sum of digits and see if we can adjust it to make the total divisible by 9.
For each digit in input:
  - Count how many 2s and 3s are present.
  - For each 2 or 3, we can replace them with 4 or 9 respectively.
  - Try combinations of such replacements (up to 8 2s and up to 2 3s) and check if resulting sum is divisible by 9.

Time Complexity: O(1) per test case since max number of replacements is bounded (c2 <= 8, c3 <= 2).
Space Complexity: O(1) — only using fixed-size variables.
*/

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var s = Console.ReadLine().Trim(); // Read current number as string
      getAns(s); // Process the number
    }
  }
  static void getAns(string s) {
    var c2 = 0; // Count of digit '2'
    var c3 = 0; // Count of digit '3'
    var sum = 0; // Sum of all digits initially
    foreach (var x in s) { // Iterate through each character/digit
      var w = x - '0'; // Convert char to int
      sum += w; // Accumulate sum
      if (w == 2)
        c2++; // Count occurrences of digit 2
      else if (w == 3)
        c3++; // Count occurrences of digit 3
    }
    var t = sum; // Store initial sum for later use
    c2 = Min(c2, 8); // Limit to max possible replacements (since 2^8 = 256, not helpful but cap for loop)
    c3 = Min(c3, 2); // Limit to max possible replacements (since 3^2 = 9, still valid)
    for (int i = 0; i <= c2; i++) { // Try all combinations of replacing 2s with 4s
      for (int j = 0; j <= c3; j++) { // Try all combinations of replacing 3s with 9s
        var ww = t + i * 2 + j * 6; // Calculate new sum after replacements: add (i*2) for 2->4, and (j*6) for 3->9
        if (ww % 9 == 0) { // Check if sum is divisible by 9
          Console.WriteLine("YES"); // If so, output YES and return
          return;
        }
      }
    }
    Console.WriteLine("NO"); // No valid combination found to make number divisible by 9
  }
}


// https://github.com/VaHiX/codeForces/