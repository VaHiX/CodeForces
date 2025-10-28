// Problem: CF 1857 B - Maximum Rounding
// https://codeforces.com/contest/1857/problem/B

/*
 * Problem: Maximum Rounding
 * 
 * Algorithm/Techniques: Greedy approach with digit manipulation
 * 
 * Time Complexity: O(n), where n is the length of the input string x
 * Space Complexity: O(n), for storing the string representation of x
 * 
 * The solution uses a greedy strategy to round digits from right to left,
 * determining at each step whether to round up or down based on digit values.
 * When rounding up causes a carry (e.g., 9+1=10), it propagates the carry
 * to higher digits and resets lower digits to zero.
 */
using System;
using System.Text;
public class MaximumRounding {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string x = Console.ReadLine();
      StringBuilder sbx = new StringBuilder(x);
      int l = sbx.Length - 1; // Left pointer starting from the last digit
      int r = l; // Right pointer also starting from the last digit
      bool carry = false; // Flag to indicate if there's a carry from previous operation
      
      // Traverse the digits from right to left
      while (l > -1) {
        // If there is a carry, increment the current digit if it's less than '9', otherwise set to '0'
        if (carry)
          sbx[l] = Convert.ToChar(sbx[l] < '9' ? sbx[l] + 1 : '0');
        
        // Check if we need to round up (current digit >= 5) or if there was a carry and the digit is '0'
        if (sbx[l] > '4' || (carry && sbx[l] == '0')) {
          carry = true; // A carry will result from rounding up
          
          // Reset all digits from r down to l to '0' (as they are rounded down)
          while (r >= l) {
            sbx[r] = '0';
            r--;
          }
        } else {
          carry = false; // No carry, continue with normal processing
        }
        l--; // Move the left pointer one digit to the left
      }
      
      // If there's still a carry after processing all digits, insert '1' at the beginning
      if (carry)
        sbx.Insert(0, '1');
        
      Console.WriteLine(sbx);
    }
  }
}


// https://github.com/VaHiX/CodeForces/