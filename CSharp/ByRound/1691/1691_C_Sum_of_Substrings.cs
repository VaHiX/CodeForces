// Problem: CF 1691 C - Sum of Substrings
// https://codeforces.com/contest/1691/problem/C

/*
 * Problem: C. Sum of Substrings
 * 
 * Algorithm/Techniques:
 * - Greedy approach with careful swapping to minimize the sum of decimal values of adjacent pairs.
 * - The key insight is to move '1's toward the beginning and '0's toward the end to form smaller numbers.
 * - For the last character being '0', we try to move the leftmost '1' to the end to make the last pair "10".
 * - For the first character being '0', we try to move the rightmost '1' to the front to make the first pair "10".
 * - After these operations, we compute the sum of all adjacent pairs.
 * 
 * Time Complexity: O(n), where n is the length of the string. Each operation and the final pass is linear.
 * Space Complexity: O(n), for the StringBuilder storing the string.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SubstrSum1691C {
class Program {
  static void Main(string[] args) {
    int t = Int32.Parse(Console.ReadLine());
    for (int p = 0; p < t; p++) {
      string[] input = Console.ReadLine().Split(' ');
      int n = Int32.Parse(input[0]);
      int k = Int32.Parse(input[1]);
      StringBuilder sb = new StringBuilder(Console.ReadLine());
      int i = 0;
      
      // If the last character is '0', attempt to move the leftmost '1' to the end
      if (sb[sb.Length - 1] == '0') {
        i = sb.Length - 2;
        while (i >= 0 && sb[i] == '0')
          --i;
        // If we can move it within the allowed operations, do it
        if (i >= 0 && sb.Length - i - 1 <= k) {
          sb[i] = '0';
          sb[sb.Length - 1] = '1';
          k -= (sb.Length - i - 1);
        }
      }
      
      // If the first character is '0', attempt to move the rightmost '1' to the front
      if (sb[0] == '0') {
        i = 1;
        while (i < sb.Length - 1 && sb[i] == '0')
          ++i;
        // If we can move it within the allowed operations, do it
        if (i < sb.Length - 1 && i <= k) {
          sb[0] = '1';
          sb[i] = '0';
        }
      }
      
      // Compute the final result by summing all adjacent pairs
      long result = 0;
      for (i = 0; i < sb.Length - 1; i++) {
        if (sb[i] == '1' && sb[i + 1] == '1')
          result += 11;
        else if (sb[i] == '1' && sb[i + 1] == '0')
          result += 10;
        else if (sb[i] == '0' && sb[i + 1] == '1')
          ++result;
      }
      Console.WriteLine(result);
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/