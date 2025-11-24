// Problem: CF 1917 B - Erase First or Second Letter
// https://codeforces.com/contest/1917/problem/B

/*
Purpose: 
This code solves the problem of counting the number of distinct non-empty strings that can be generated 
by repeatedly removing either the first or second character from a given string. 

The approach leverages the fact that at each position in the string, we can choose to remove characters 
in a way that leads to various substrings. The key insight is that for each prefix of the string, 
the number of distinct strings we can form is equal to the number of unique characters seen so far 
plus the number of ways to form new strings by removals.

Algorithm:
- For each character in the string:
  - Add it to a set of unique characters seen so far.
  - Add the current size of the set to the result (as this represents new unique strings that can be formed).
  
Time Complexity: O(n), where n is the length of the string. Each character is processed once.
Space Complexity: O(1), since the maximum size of the HashSet is bounded by the number of distinct lowercase letters (26).
*/

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    try {
      Console.SetIn(new System.IO.StreamReader(Console.OpenStandardInput(),
                                               Console.InputEncoding, false,
                                               bufferSize: 1024));
      Console.SetOut(new System.IO.StreamWriter(Console.OpenStandardOutput(),
                                                Console.OutputEncoding,
                                                bufferSize: 1024));
      int t = int.Parse(Console.ReadLine());
      for (int testCase = 0; testCase < t; testCase++) {
        int n = int.Parse(Console.ReadLine());
        string soul = Console.ReadLine();
        long result = Solve(n, soul);
        Console.WriteLine($"{result}");
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
  static long Solve(int n, string soul) {
    HashSet<char> blind = new HashSet<char>(); // Set to track unique characters encountered so far
    long bmps = 0; // Result counter initialized to zero
    
    // Iterate through each character in the string
    foreach (char c in soul) {
      blind.Add(c); // Add current character to the set of unique characters
      bmps += blind.Count; // Add the number of unique characters seen so far to the result
    }
    
    return bmps; // Return total number of distinct strings
  }
}


// https://github.com/VaHiX/CodeForces/