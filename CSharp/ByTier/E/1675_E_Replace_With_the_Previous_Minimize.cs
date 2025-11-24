// Problem: CF 1675 E - Replace With the Previous, Minimize
// https://codeforces.com/contest/1675/problem/E
 
/* 
 * Problem: E. Replace With the Previous, Minimize
 * 
 * Algorithm/Techniques:
 * - Greedy approach to minimize lexicographically
 * - For each character in the string, determine the optimal replacement
 *   by trying to reduce the character to the lowest possible value
 *   within the allowed number of operations k
 * 
 * Time Complexity: O(n * 26) = O(n), where n is the length of the string
 * Space Complexity: O(n), for storing the string and intermediate results
 * 
 * Key Idea:
 * - For each character, compute how much we can reduce it
 * - Prefer reducing characters early to achieve a lexicographically smaller result
 * - Use a greedy strategy to choose the best reduction path
 */
 
using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      var s = Console.ReadLine();
      int k = (int)a[1];
      char m1 = s[0];  // minimum character value to replace with
      char m2 = s[0];  // threshold character for replacement
      char m3 = s[0];  // intermediate replacement character
      char m4 = s[0];  // tracking variable
      for (int i = 0; i < s.Length; i++) {
        if (s[i] >= m2) {
          // If we can't reduce further or have too few operations to justify action
          if (k <= (m2 - m1) || m2 - m1 >= 25)
            break;
          // If we have enough operations to perform the transformation
          if (k - m2 + m1 > 0) {
            m4 = s[i];  // save the original character
            // Compute new replacement character
            if (s[i] - 'a' > k - m2 + m1)
              m3 = (char)(s[i] - k + m2 - m1);
            else
              m3 = 'a';  // best case: reduce to 'a'
          }
          // Update tracking variables to reflect the best transformation found so far
          if (m1 > m3) {
            m1 = m3;
            m2 = m4;
          }
          if (m3 <= m2) {
            m2 = m4;
          } else
            break;  // Stop if we're moving in wrong direction
        }
      }
      // Apply final replacements based on computed thresholds
      for (char c = 'a'; c <= 'z'; c++) {
        if (c <= m2 && c > m1)
          s = s.Replace(c, m1);  // replace characters within range with m1
        else if (c <= m4 && c > m3)
          s = s.Replace(c, m3);  // replace characters within range with m3
      }
      output.Add(s);
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}
 
 
// https://github.com/VaHiX/CodeForces/