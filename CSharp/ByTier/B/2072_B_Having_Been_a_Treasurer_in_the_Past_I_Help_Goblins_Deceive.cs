// Problem: CF 2072 B - Having Been a Treasurer in the Past, I Help Goblins Deceive
// https://codeforces.com/contest/2072/problem/B

/*
 * Problem: B. Having Been a Treasurer in the Past, I Help Goblins Deceive
 * Purpose: Given a string of '-' and '_', rearrange characters to maximize 
 *          the number of subsequences equal to "-_-".
 * 
 * Algorithm:
 *   - Count total '-' and '_' in the string.
 *   - To form a subsequence "-_-", we need 1 '-' on the left, 1 '_' in the middle, and 1 '-' on the right.
 *   - So we can pick any 2 '-' characters as left and right, and any 1 '_' character in the middle.
 *   - Maximum number of such subsequences is calculated as:
 *     (number of '-' choose 2) * (number of '_') = (m * (m - 1) / 2) * u
 *     But in code we use m * m / 4 * u to avoid floating point operations.
 *     
 * Time Complexity: O(n) per test case, where n is the length of the string. 
 * Space Complexity: O(1), only using a few integer variables for counting and computation.
 */

using System;
class Program {
  static void Main() {
    int munna = int.Parse(Console.ReadLine()); // Read number of test cases
    while (munna-- > 0) { // Loop through each test case
      int sakshi = int.Parse(Console.ReadLine()); // Read length of string
      string s = Console.ReadLine(); // Read the string
      int m = 0, u = 0; // Count '-' and '_' characters
      
      foreach (char c in s) { // Traverse the string to count characters
        if (c == '-')
          m++;
        else
          u++;
      }
      
      // If less than 2 dashes or no underscores, then no valid subsequence "-_-" can be formed
      if (m < 2 || u == 0) {
        Console.WriteLine(0);
      } else {
        // Calculate maximum number of subsequences "-_-"
        // Using the formula: (number of ways to choose 2 dashes) * (number of underscores)
        // Which is equivalent to (m * m / 4) * u to simplify operations
        Console.WriteLine((1L * m * m / 4) * u);
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/