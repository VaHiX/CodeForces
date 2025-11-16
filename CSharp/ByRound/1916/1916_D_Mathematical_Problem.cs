// Problem: CF 1916 D - Mathematical Problem
// https://codeforces.com/contest/1916/problem/D

/*
 * Purpose: This program solves a mathematical problem where for a given odd number n,
 * it finds n different square numbers, each of length n, such that all have the same multiset of digits.
 *
 * Algorithm:
 * - For n = 1, output "1".
 * - For n > 1:
 *   - Generate n square numbers of length n using specific patterns.
 *   - Patterns are constructed using combinations of '1', '3', and '0' to ensure uniform digit multisets.
 *   - Uses BigInteger for handling large numbers.
 *
 * Time Complexity: O(n^2) - The loops iterate up to n/2 times and string operations are linear in n.
 * Space Complexity: O(n) - The space used by strings and intermediate calculations is proportional to n.
 */

using System;
using System.Numerics;
class Program {
  static void Main() {
    try {
      // Set up optimized input/output streams
      Console.SetIn(new System.IO.StreamReader(Console.OpenStandardInput(),
                                               Console.InputEncoding, false,
                                               bufferSize: 1024));
      Console.SetOut(new System.IO.StreamWriter(Console.OpenStandardOutput(),
                                                Console.OutputEncoding,
                                                bufferSize: 1024));
      int t = int.Parse(Console.ReadLine());
      for (int testCase = 0; testCase < t; testCase++) {
        int n = int.Parse(Console.ReadLine());
        PrintPatternSquares(n);
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
  static void PrintPatternSquares(int number) {
    if (number == 1) {
      Console.WriteLine(1);
      return;
    }
    int midpoint = number / 2 + 1;
    // Generate first set of square numbers using specific pattern
    for (int i = 0; i < midpoint - 1; i++) {
      string pattern =
          "1" + new string('0', i) + "3" + new string('0', midpoint - 2 - i);
      BigInteger patternNumber = BigInteger.Parse(pattern);
      Console.WriteLine(BigInteger.Pow(patternNumber, 2).ToString());
    }
    // Generate second set of square numbers using complementary pattern
    for (int i = 0; i < midpoint - 1; i++) {
      string pattern =
          "3" + new string('0', i) + "1" + new string('0', midpoint - 2 - i);
      BigInteger patternNumber = BigInteger.Parse(pattern);
      Console.WriteLine(BigInteger.Pow(patternNumber, 2).ToString());
    }
    // Generate final square number with fixed pattern
    string finalPattern = "14" + new string('0', midpoint - 2);
    BigInteger finalPatternNumber = BigInteger.Parse(finalPattern);
    Console.WriteLine(BigInteger.Pow(finalPatternNumber, 2).ToString());
  }
}


// https://github.com/VaHiX/CodeForces/