// Problem: CF 1926 A - Vlad and the Best of Five
// https://codeforces.com/contest/1926/problem/A

using System;
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      Solve(); // Process each test case
    }
  }
  static void Solve() {
    string s = Console.ReadLine().Trim(); // Read the input string
    int countA = 0, countB = 0; // Initialize counters for A and B
    foreach (char c in s) { // Iterate through each character in the string
      if (c == 'A') {
        countA++; // Increment A counter if character is A
      } else {
        countB++; // Increment B counter if character is B
      }
    }
    Console.WriteLine(countA > countB ? "A" : "B"); // Print the character with higher count
  }
}
/*
Purpose: This program determines which character ('A' or 'B') appears most frequently in a 5-character string.

Algorithms/Techniques: 
- Single pass iteration through string to count occurrences
- Simple comparison to determine maximum

Time Complexity: O(n) where n is the length of the string (5 in this case)
Space Complexity: O(1) - only using a constant amount of extra space
*/

// https://github.com/VaHiX/CodeForces/