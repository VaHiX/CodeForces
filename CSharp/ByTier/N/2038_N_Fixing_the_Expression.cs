// Problem: CF 2038 N - Fixing the Expression
// https://codeforces.com/contest/2038/problem/N

/*
 * Problem: Fixing the Expression
 * 
 * Purpose: Given a string representing a 3-character expression with two digits and a comparison operator,
 *          modify the expression to make it a valid(true) expression by changing as few characters as possible.
 * 
 * Approach:
 * - Extract the first and last characters (digits) and the middle character (comparison operator).
 * - Determine the correct comparison operator based on the values of the two digits.
 * - If the first digit is less than the second, use '<'.
 * - If the first digit is greater than the second, use '>'.
 * - If the first digit equals the second, use '='.
 * - Construct and output the resulting valid expression.
 * 
 * Time Complexity: O(1) - Fixed number of operations per test case.
 * Space Complexity: O(1) - Only a fixed-size array and variables are used.
 * 
 * Algorithms/Techniques:
 * - Simple conditional logic to determine correct operator.
 * - String manipulation to form final result.
 */

using System;
public class FixingTheExpression {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string s = Console.ReadLine();
      char[] chars = new char[3];
      chars[0] = s[0];           // Copy the first digit
      chars[2] = s[2];           // Copy the second digit
      chars[1] = s[0]<s[2] ? '<' : s[0]> s[2] ? '>' : '=';  // Determine correct comparison operator
      string ans = new string(chars);
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/