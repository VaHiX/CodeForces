// Problem: CF 1926 C - Vlad and a Sum of Sum of Digits
// https://codeforces.com/contest/1926/problem/C

/*
 * Problem: Vlad and a Sum of Sum of Digits
 * Algorithm: Digit DP (Dynamic Programming) with precomputed digit sums
 * 
 * Approach:
 * - For each number from 1 to n, compute the sum of its digits.
 * - The direct approach would be too slow; instead we use a digit DP technique.
 * - We process digits from right to left, and for each position, calculate contribution
 *   of that digit place to the total sum.
 * 
 * Time Complexity: O(log n) per test case
 * Space Complexity: O(1) - only using a fixed-size array for precomputed sums
 * 
 * Precomputed array sumDigits[i] holds sum of digits from 0 to i.
 * 
 * Example:
 *   n = 12 => numbers: 1..12 => digit sums: 1,2,3,4,5,6,7,8,9,1,2,3 => sum = 51
 */

using System;
public class VladAndASumOfSumOfDigits {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    // Precomputed sum of digits from 0 to 9
    byte[] sumDigits = new byte[] { 0, 1, 3, 6, 10, 15, 21, 28, 36, 45 };
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      int m = n;
      int pow10 = 1;
      int ans = 0;
      while (n / pow10 > 0) {
        // Extract last digit
        byte d = Convert.ToByte(m % 10);
        // Compute contribution of current digit position to total sum
        ans += n / (10 * pow10) * 45 * pow10 +
               sumDigits[Math.Max(0, d - 1)] * pow10 + d * (n % pow10 + 1);
        pow10 *= 10;
        m /= 10;
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/