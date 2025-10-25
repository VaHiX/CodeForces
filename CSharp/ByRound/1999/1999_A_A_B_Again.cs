// Problem: CF 1999 A - A+B Again?
// https://codeforces.com/contest/1999/problem/A

using System;
public class SumOfDigits {
  /*
   * Problem: Calculate the sum of digits of a two-digit number
   * Algorithm: Extract individual digits using integer division and modulo operations
   * Time Complexity: O(t) where t is the number of test cases
   * Space Complexity: O(1) - only using a constant amount of extra space
   * 
   * Techniques:
   * - Integer division (n / 10) to get the tens digit
   * - Modulo operation (n % 10) to get the units digit
   */
  public static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine()); // Read the two-digit number
      int sum = (n / 10) + (n % 10); // Extract tens digit and units digit, then sum them
      Console.WriteLine(sum); // Output the sum of digits
    }
  }
}

// https://github.com/VaHiX/CodeForces/