// Problem: CF 1950 D - Product of Binary Decimals
// https://codeforces.com/contest/1950/problem/D

/*
 * Problem: Product of Binary Decimals
 * 
 * Algorithm/Techniques:
 * - A binary decimal is a number that consists only of digits 0 and 1.
 * - The approach is to reduce the given number n by dividing it by known binary decimal factors (11, 101, 111).
 * - If after a series of divisions we reach a number that is itself a binary decimal, then the original number can be represented as a product of binary decimals.
 * - If we cannot reduce it to a binary decimal using the given factors, then it's impossible.
 * 
 * Time Complexity: O(log n) per test case, since we are dividing by factors like 11, 101, 111 in each step.
 * Space Complexity: O(1), as we only use a constant amount of extra space.
 */

using System;
public class ProductOfBinaryDecimals {
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      int m = n;
      bool solved = false;
      bool ans = false;
      while (!solved) {
        // Check if current number m is a binary decimal
        if (BinaryDecimal(m)) {
          ans = true;
          solved = true;
        }  
        // Try to divide by 11 if divisible
        else if (m % 11 == 0)
          m /= 11;
        // Try to divide by 101 if divisible
        else if (m % 101 == 0)
          m /= 101;
        // Try to divide by 111 if divisible
        else if (m % 111 == 0)
          m /= 111;
        // If not divisible by any of the binary decimals, give up
        else
          solved = true;
      }
      Console.WriteLine(ans ? "YES" : "NO");
    }
  }
  
  // Function to check if a number is a binary decimal
  public static bool BinaryDecimal(int n) {
    bool binDec = true;
    while (n > 0 && binDec) {
      byte r = Convert.ToByte(n % 10);  // Get last digit
      if (r > 1)  // If any digit is greater than 1, not a binary decimal
        binDec = false;
      else
        n /= 10;  // Remove last digit
    }
    return binDec;
  }
}


// https://github.com/VaHiX/CodeForces/