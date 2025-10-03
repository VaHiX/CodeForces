// Problem: CF 2093 B - Expensive Number
// https://codeforces.com/contest/2093/problem/B

/*
B. Expensive Number
Algorithm: Greedy approach to minimize the cost of a number by removing digits.
The cost is defined as n / (sum of digits), so to minimize it, we need to minimize n or maximize the sum of digits.
However, the constraint "remove any number of digits" implies we want the smallest possible value for n while keeping at least one digit.
So, we look for the minimum value that can be formed after removing some digits. 
The key insight is: If there is a '0', we should try to include that in our result because 0 reduces the value and can potentially reduce cost if combined with small digits.
If there's no '0', we just remove all but one smallest digit.
Time Complexity: O(n) where n is the length of the string representing the number.
Space Complexity: O(1) - only using a few integer variables.
*/

using System;
public class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      string s = Console.ReadLine();
      int n = s.Length;
      int lz = 0, cnt = 0;
      for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '0') { // If current digit is zero
          if (lz == 0) // First zero encountered
            cnt++;   // Increment count as we need to keep it
        } else {
          if (lz == 0) // If no zero seen yet, start counting digits
            lz = 1;  // Mark that a non-zero digit has been seen
          else
            cnt++;   // Otherwise increment count, since this is not the first non-zero
        }
      }
      Console.WriteLine($"{cnt}");
    }
  }
}


// https://github.com/VaHiX/codeForces/