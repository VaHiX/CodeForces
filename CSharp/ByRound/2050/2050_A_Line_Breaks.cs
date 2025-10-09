// Problem: CF 2050 A - Line Breaks
// https://codeforces.com/contest/2050/problem/A

/*
 * Problem: Maximum Words That Can Fit on First Strip
 * 
 * Purpose: Given a list of words and a maximum character limit for the first strip,
 * determine the maximum number of consecutive words from the beginning of the list
 * that can fit on the first strip without exceeding the character limit.
 * 
 * Algorithm: Greedy approach - iterate through the words and keep adding them to the
 * first strip while the total length does not exceed the limit m.
 * 
 * Time Complexity: O(n * L) where n is the number of words and L is the average word length.
 * Space Complexity: O(n) for storing the list of words that fit in the first strip.
 * 
 * Techniques:
 *   - Greedy algorithm
 *   - Linear iteration with cumulative sum
 */

using System;
using System.Text;
using System.Diagnostics.CodeAnalysis;
using System.Security.Cryptography.X509Certificates;
using System.Collections.Generic;
using System.Diagnostics.Tracing;

class Program {
  static void Main() {
    int tk = int.Parse(Console.ReadLine()), sum = 0; // Read number of test cases
    for (int l = 0; l < tk; l++) {
      string[] nm = Console.ReadLine().Split(' '); // Read n and m
      int n = int.Parse(nm[0]), m = int.Parse(nm[1]); // Parse n and m
      sum = 0; // Reset cumulative length
      bool a = true; // Flag to control adding words
      List<string> list = new List<string>(); // Store words that fit on first strip
      for (int i = 0; i < n; i++) {
        string word = Console.ReadLine(); // Read next word
        if (a) { // If we are still allowed to add words
          if (sum + word.Length > m) { // Check if adding the word exceeds the limit
            a = false; // Stop adding words
          } else {
            list.Add(word); // Add the word to the list
            sum += word.Length; // Update cumulative length
          }
        }
      }
      if (list.Count == 0) { // If no words fit
        Console.WriteLine(0);
      } else
        Console.WriteLine(list.Count); // Output number of words that fit
    }
  }
}


// https://github.com/VaHiX/codeForces/