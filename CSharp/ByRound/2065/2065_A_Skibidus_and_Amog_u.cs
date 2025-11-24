// Problem: CF 2065 A - Skibidus and Amog'u
// https://codeforces.com/contest/2065/problem/A

/*
 * Problem: Convert Amog'u singular nouns to plural.
 * Algorithms/Techniques: String manipulation using substring and concatenation.
 * Time Complexity: O(n), where n is the length of the input string (fixed at most 10).
 * Space Complexity: O(n), for storing the modified string.
 * 
 * The task involves converting a singular Amog'u noun ending in "us" to its plural form,
 * which ends in "i". For example:
 *   "amogus" -> "amogi"
 *   "cactus" -> "cacti"
 *   "us" -> "i"
 * 
 * The algorithm checks if the input string ends with "us", and if so, removes the last
 * two characters ("us") and appends "i".
 */

using System;
public class Program {
  public static void Main() {
    int c = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < c; i++) {
      string s = Console.ReadLine(); // Read the singular noun
      
      // Check if the word ends with "us" (length >= 2 to ensure safety)
      if (s.Length >= 2 && s[s.Length - 1] == 's' && s[s.Length - 2] == 'u') {
        s = s.Remove(s.Length - 2, 2); // Remove the last two characters ("us")
        s += "i"; // Append "i" to form the plural
      }
      
      Console.WriteLine(s); // Output the result
    }
  }
}


// https://github.com/VaHiX/codeForces/