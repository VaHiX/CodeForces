// Problem: CF 2047 B - Replace Character
// https://codeforces.com/contest/2047/problem/B

/*
 * Purpose: This program aims to minimize the number of distinct permutations of a given string
 *          by performing exactly one operation of replacing a character at index i with the character at index j.
 *          
 * Algorithm/Techniques:
 * - Count frequency of each character in the string.
 * - Sort characters by their frequencies in ascending order.
 * - Find the least frequent character (cFrom) and the most frequent character (cTo).
 * - Replace the first occurrence of cFrom with cTo.
 * - Output the modified string.
 * 
 * Time Complexity: O(n log n) due to sorting, where n is the length of the string.
 * Space Complexity: O(1) as we use fixed-size arrays (26 characters) regardless of input size.
 */
using System;
public class ReplaceCharacter {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());  // Read number of test cases
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine());  // Read length of string
      string s = Console.ReadLine();  // Read the string
      byte[] counters = new byte[26];  // Array to count frequency of each character
      byte[] idxs = new byte[26];  // Array to store indices of characters
      for (byte j = 0; j < n; j++)
        counters[s[j] - 'a']++;  // Count each character
      for (byte j = 0; j < 26; j++)
        idxs[j] = j;  // Initialize index array
      Array.Sort(counters, idxs);  // Sort by frequency (ascending), keeping track of original character indices
      byte k = 0;
      while (counters[k] == 0)  // Skip zero frequencies
        k++;
      char cFrom = Convert.ToChar('a' + idxs[k]);  // Least frequent character
      char cTo = Convert.ToChar('a' + idxs[25]);  // Most frequent character
      k = 0;
      while (s[k] != cFrom)  // Find first occurrence of least frequent character
        k++;
      s = s.Remove(k, 1).Insert(k, cTo.ToString());  // Replace it with most frequent character
      Console.WriteLine(s);  // Output result
    }
  }
}


// https://github.com/VaHiX/CodeForces/