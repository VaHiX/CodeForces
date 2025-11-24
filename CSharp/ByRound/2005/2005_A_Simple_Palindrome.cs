// Problem: CF 2005 A - Simple Palindrome
// https://codeforces.com/contest/2005/problem/A

/*
 * Problem: Simple Palindrome
 * 
 * Purpose: To find a string of length n consisting of vowels only such that the number of palindromic subsequences is minimized.
 * 
 * Algorithm:
 * - Distribute the length n as evenly as possible among the 5 vowels (a, e, i, o, u).
 * - Assign 'd' occurrences to each vowel, and distribute the remainder 'r' by giving one extra to the first 'r' vowels.
 * - Construct the string by repeating each vowel according to its count.
 * 
 * Time Complexity: O(n) per test case, since we iterate through the vowels and build the string.
 * Space Complexity: O(n) for storing the result string.
 */

using System;
using System.Text;
public class SimplePalindrome {
  public static void Main() {
    byte t = byte.Parse(Console.ReadLine()); // Read number of test cases
    char[] vowels = new char[] { 'a', 'e', 'i', 'o', 'u' }; // Define available vowels
    for (byte i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine()); // Read the length of the desired string
      byte[] counts = new byte[5]; // Array to store how many times each vowel appears
      byte d = Convert.ToByte(n / 5); // Base count for each vowel
      byte r = Convert.ToByte(n % 5); // Remainder to be distributed
      for (byte j = 0; j < 5; j++)
        counts[j] = Convert.ToByte(d + (r > 0 && j < r ? 1 : 0)); // Distribute remainder
      StringBuilder ans = new StringBuilder(); // Build the final string
      for (byte j = 0; j < 5; j++)
        ans.Append(new string(vowels[j], counts[j])); // Append each vowel repeated 'counts[j]' times
      Console.WriteLine(ans); // Output the constructed string
    }
  }
}


// https://github.com/VaHiX/CodeForces/