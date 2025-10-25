// Problem: CF 2121 B - Above the Clouds
// https://codeforces.com/contest/2121/problem/B

/*
 * Problem: B. Above the Clouds
 * Algorithm: Two-pointer technique with frequency counting
 * Time Complexity: O(n) per test case, where n is the length of the string
 * Space Complexity: O(1) - fixed size arrays of 26 elements for each alphabet letter
 * 
 * Description:
 * Given a string s of length n, determine whether there exist three non-empty strings a, b, and c
 * such that a + b + c = s and b is a substring of a + c.
 * 
 * Approach:
 * 1. Use two frequency arrays to simulate the distribution of characters in two parts: prefix (a) and suffix (c), 
 *    excluding the middle character (b).
 * 2. Iterate through possible positions for the start of string b, adjusting frequencies accordingly.
 * 3. Check if at any point there is overlap between characters from a and c that can form the required substring b.
 */

using System;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      string str = Console.ReadLine();
      int[] freq = new int[26]; // Frequency array for characters in suffix from index 1 to n-1
      int[] freq1 = new int[26]; // Frequency array for characters in prefix including first character
      
      // Initialize frequency array with all characters from index 1 to n-1
      for (int i = 1; i < n; i++) {
        freq[str[i] - 'a']++;
      }
      
      // Add first character to prefix frequency
      freq1[str[0] - 'a']++;
      
      bool found = false;
      
      // Iterate through possible positions for the start of string b (from index 1 to n-2)
      for (int i = 1; i < n - 1 && !found; i++) {
        var ch = str[i];
        
        // Remove current character from suffix frequency
        freq[ch - 'a']--;
        
        // Check if the character is present in both prefix and suffix, 
        // indicating that a valid decomposition exists
        if (freq[ch - 'a'] > 0 || freq1[ch - 'a'] > 0) {
          found = true;
        }
        
        // Add current character to prefix frequency for next iteration
        freq1[ch - 'a']++;
      }
      
      if (found) {
        Console.WriteLine("yes");
      } else {
        Console.WriteLine("no");
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/