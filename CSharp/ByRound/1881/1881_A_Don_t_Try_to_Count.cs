// Problem: CF 1881 A - Don't Try to Count
// https://codeforces.com/contest/1881/problem/A

/*
 * Problem: Don't Try to Count
 * 
 * Purpose: Given two strings x and s, determine the minimum number of operations
 *          required to make s a substring of x, where each operation appends x to itself.
 * 
 * Algorithm:
 *   - Start with string x.
 *   - Keep appending x to itself until s is found as a substring or we exceed reasonable limits.
 *   - If not found after first expansion, try one more expansion.
 *   - If still not found, return -1.
 *   
 * Time Complexity: O(n * m * log(n * m)) in worst case, where we may expand x up to log(n*m) times.
 * Space Complexity: O(n * m), as we store the growing string x.
 */

using System;
using System.Text;
public class DonTTryToCount {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      byte n = byte.Parse(parts[0]);
      byte m = byte.Parse(parts[1]);
      string x = Console.ReadLine();
      string s = Console.ReadLine();
      short ansi = 0;
      // Continue expanding x while its length is <= m and s is not found
      while (x.Length <= m && !x.Contains(s)) {
        x = string.Concat(x, x); // Append x to itself
        ansi++;
      }
      // If s is not found yet, expand one more time
      if (!x.Contains(s)) {
        x = string.Concat(x, x);
        if (x.Contains(s))
          ansi++;
        else
          ansi = -1;
      }
      ans.Append(ansi);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/