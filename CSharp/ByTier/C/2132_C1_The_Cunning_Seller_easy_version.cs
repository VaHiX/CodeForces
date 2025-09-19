// Problem: CF 2132 C1 - The Cunning Seller (easy version)
// https://codeforces.com/contest/2132/problem/C1

/*
 * Problem: C1. The Cunning Seller (easy version)
 * 
 * Purpose:
 *   Given a number n representing the number of watermelons to buy,
 *   determine the minimum cost using the fewest possible deals.
 *   
 *   Each deal sells 3^x watermelons for 3^(x+1) + x * 3^(x-1) coins.
 *   This can be viewed as a dynamic programming or greedy-like problem
 *   that uses a ternary representation approach to find the minimal cost.
 *
 * Algorithms/Techniques:
 *   - Ternary number system manipulation
 *   - Greedy solution based on ternary decomposition
 *
 * Time Complexity: O(log n) per test case
 * Space Complexity: O(log n) for storing ternary digits
 */

using System;
using System.Collections.Generic;
using System.IO;
namespace CodeForces.Problems.Round2132.C1 {
public static class CunningSellerEasy {
  private static readonly StreamReader reader =
      new StreamReader(Console.OpenStandardInput());
  private static readonly StreamWriter writer =
      new StreamWriter(Console.OpenStandardOutput());
  
  /// <summary>
  /// Calculates the special sum based on the ternary representation of a number.
  /// This is part of the optimal greedy strategy to compute the minimum cost for n watermelons.
  /// </summary>
  /// <param name="number">The number of watermelons to buy</param>
  /// <returns>The minimum coins needed to purchase exactly 'number' watermelons</returns>
  public static long CalculateSpecialSum(long number) {
    var ternaryDigits = new List<long>(); // Store ternary digits of number
    while (number > 0) {
      ternaryDigits.Add(number % 3); // Extract least significant ternary digit
      number /= 3; // Move to next higher digit
    }
    long powerOfThree = 1; // Represents 3^position
    long result = 0;
    
    // Process each ternary digit to compute the total cost
    for (int position = 0; position < ternaryDigits.Count; position++) {
      long digit = ternaryDigits[position]; // Current ternary digit
      
      // Compute term: 3 * 3^position + position * (3^(position-1) if position>0 else 0)
      long term =
          3 * powerOfThree + position * (position > 0 ? powerOfThree / 3 : 0);
      
      result += digit * term; // Add contribution to final result
      
      powerOfThree *= 3; // Update for next higher power of 3
    }
    return result;
  }
  
  /// <summary>
  /// Reads a long integer from standard input.
  /// </summary>
  /// <returns>A long integer read from input</returns>
  private static long ReadLong() {
    int c;
    int sign = 1;
    long result = 0;
    
    // Skip leading whitespace and check for negative sign
    do {
      c = reader.Read();
      if (c == '-')
        sign = -1;
    } while (c < '0' || c > '9');
    
    // Read first digit of number
    result = c - '0';
    
    // Continue reading digits until a non-digit character is found
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return sign * result;
      result = result * 10 + (c - '0');
    }
  }
  
  /// <summary>
  /// Main entry point of the program.
  /// Processes multiple test cases and outputs the results.
  /// </summary>
  public static void Main(string[] args) {
    long testCases = ReadLong(); // Total number of test cases
    
    for (int i = 0; i < testCases; i++) {
      long number = ReadLong(); // Number of watermelons to buy
      long result = CalculateSpecialSum(number); // Compute minimum cost
      writer.WriteLine(result); // Output result for current case
    }
    
    writer.Flush(); // Ensure all output is written
  }
}
}


// https://github.com/VaHiX/codeForces/