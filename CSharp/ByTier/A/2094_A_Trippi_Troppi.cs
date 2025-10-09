// Problem: CF 2094 A - Trippi Troppi
// https://codeforces.com/contest/2094/problem/A

/*
 * Problem: Trippi Troppi
 * Purpose: Given ancient country names consisting of three words, generate modern names 
 *          by concatenating the first letter of each word.
 * Algorithm: Simple string manipulation - for each test case, split input into words,
 *            extract first character of each word, and concatenate them.
 * Time Complexity: O(t * n) where t is number of test cases and n is average word length
 * Space Complexity: O(n) where n is the maximum word length for storing input strings
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      string[] words = Console.ReadLine().Split(); // Split input line into three words
      string modernName = words[0][0] + "" + words[1][0] + "" + words[2][0]; // Concatenate first characters
      Console.WriteLine(modernName); // Output the modern name
    }
  }
}


// https://github.com/VaHiX/codeForces/