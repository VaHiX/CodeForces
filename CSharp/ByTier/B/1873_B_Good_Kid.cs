// Problem: CF 1873 B - Good Kid
// https://codeforces.com/contest/1873/problem/B

/*
 * Problem: B. Good Kid
 * 
 * Approach:
 * - For each test case, we are given an array of digits.
 * - We must add 1 to exactly one of the digits to maximize the product of all digits.
 * - The strategy is to determine which digit to increment based on the current product and count of zeros.
 * 
 * Key Observations:
 * - If no zeros are present, we can increment the smallest digit to get maximum gain.
 *   For a product P and smallest digit d, new product = P + P/d.
 * - If there is at least one zero, incrementing any digit other than zero will make the product 0.
 *   If there is exactly one zero, we can increment that zero and ignore it in the product,
 *   which gives us the product of all non-zero digits.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) excluding input/output storage
 */

using System;
using System.Text;
public class GoodKid {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int prod = 1;                        // Product of all digits as is
      int prodWithout0 = 1;                // Product of all digits except zeros
      byte countZero = 0;                  // Count of zeros in the array
      byte aMin = 9;                       // Smallest digit in the array
      for (byte j = 0; j < n; j++) {
        byte aj = byte.Parse(parts[j]);
        prod *= aj;                        // Compute full product
        if (aj == 0)
          countZero++;                     // Track zero count
        else
          prodWithout0 *= aj;              // Compute product without zeros
        if (aj < aMin)
          aMin = aj;                       // Track minimum digit
      }
      int ansi = 0;
      if (aMin > 0)                        // If no zeros, increment smallest digit
        ansi = prod + (prod / aMin);
      else if (countZero == 1)             // If exactly one zero, remove it
        ansi = prodWithout0;
      ans.Append(ansi);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/