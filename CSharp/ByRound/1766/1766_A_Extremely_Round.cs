// Problem: CF 1766 A - Extremely Round
// https://codeforces.com/contest/1766/problem/A

/*
 * Problem: Count the number of "extremely round" integers from 1 to n (inclusive).
 * An extremely round integer has only one non-zero digit.
 * 
 * Algorithm:
 * - For a given number n, we determine how many extremely round numbers exist <= n.
 * - We extract the first (most significant) digit and count total digits.
 * - Then, we compute how many extremely round numbers are there:
 *   - All numbers with fewer digits than n are counted (9 each, 1,2,3...9 for 1-digit; 10,20,30...90 for 2-digit, etc.)
 *   - We also consider numbers with same number of digits as n but less than or equal to n.
 * 
 * Time Complexity: O(log n) per test case, since we process digits of n.
 * Space Complexity: O(1) additional space (excluding input/output buffer).
 */
using System;
using System.Text;
public class ExtremelyRound {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine()); // Read current test case number
      byte countDigit = 0; // Count of digits in n
      byte firstDigit = 0; // First (most significant) digit of n
      while (n > 0) {
        firstDigit = Convert.ToByte(n % 10); // Extract last digit (rightmost)
        countDigit++; // Increment digit count
        n /= 10; // Remove last digit
      }
      // Calculate the result: 
      // firstDigit gives us how many valid numbers with same digits are there <= n (from 1 to firstDigit)
      // 9 * (countDigit - 1) gives us all valid numbers with fewer digits (1-digit: 9; 2-digit: 9; etc.)
      byte ansi = Convert.ToByte(firstDigit + 9 * (countDigit - 1)); 
      ans.Append(ansi);
      ans.AppendLine(); // Append result and newline
    }
    Console.Write(ans); // Output all results
  }
}


// https://github.com/VaHiX/CodeForces/