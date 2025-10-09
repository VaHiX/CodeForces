// Problem: CF 2125 A - Difficult Contest
// https://codeforces.com/contest/2125/problem/A

/*
 * Problem: A. Difficult Contest
 * 
 * Purpose: Rearrange the characters of a given string to avoid the substrings "FFT" or "NTT".
 *          If the original string is already safe, it may be left as is.
 * 
 * Approach:
 *   - Sort the input string in descending order (to get largest possible lexicographical arrangement).
 *   - This ensures that we place as many 'T's as early as possible,
 *     which reduces the chance of forming forbidden substrings like "FFT" or "NTT".
 * 
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(n) for storing the character array and output string.
 */

﻿using System.Text;
namespace AA;
class Program {
  static void Solve() {
    var s = reader.ReadLine().ToCharArray(); // Read the input string and convert to char array
    Array.Sort(s); // Sort the characters in ascending order
    Array.Reverse(s); // Reverse to get descending order (largest lexicon)
    writer.WriteLine(new string(s)); // Write the rearranged string
  }
  
  static void Main(string[] args) {
    int t = int.Parse(reader.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) { // Process each test case
      Solve();
    }
    writer.Flush(); // Flush the output buffer
  }
  
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/