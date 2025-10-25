// Problem: CF 1883 B - Chemistry
// https://codeforces.com/contest/1883/problem/B

/*
 * Problem: Chemistry
 * 
 * Purpose: Determine if we can remove exactly k characters from a string such that
 *          the remaining characters can be rearranged to form a palindrome.
 * 
 * Algorithm:
 * - Count frequency of each character in the string.
 * - Count how many characters have odd frequencies.
 * - For a string to form a palindrome:
 *   - If length is even, all characters must have even frequency (0 odd frequencies).
 *   - If length is odd, exactly one character can have odd frequency (1 odd frequency).
 * - After removing k characters, the new length is (n - k).
 * - We need to check if we can make it possible to form a palindrome by removing k characters.
 *   - This means ensuring we have enough characters to adjust odd counts to match
 *     the parity of (n - k), and that the number of characters removed is sufficient.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1) since we use fixed-size array of size 26 for character counting.
 */
using System;
using System.Text;
public class Chemistry {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      int k = int.Parse(parts[1]);
      string s = Console.ReadLine();
      int[] counters = new int[26]; // Array to count frequency of each character (a-z)
      for (int j = 0; j < n; j++)
        counters[s[j] - 'a']++; // Increment count for the character
      byte countOdd = 0; // Count of characters with odd frequency
      for (byte j = 0; j < 26; j++)
        if (counters[j] % 2 == 1) // If character count is odd
          countOdd++; // Increment odd count
      // Check if it's possible to make a palindrome after removing k characters
      // The condition checks two cases:
      // 1. If (n - k) is even, then number of odd frequencies should be <= k (we can reduce them)
      // 2. If (n - k) is odd, then we can have 1 odd frequency, so we need (countOdd - 1) <= k
      bool ansi = (((n - k) % 2 == 0 && k >= countOdd) ||
                   ((n - k) % 2 == 1 && k + 1 >= countOdd));
      ans.Append(ansi ? "YES" : "NO");
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/