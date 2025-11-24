// Problem: CF 1881 B - Three Threadlets
// https://codeforces.com/contest/1881/problem/B

/*
 * Problem: Three Threadlets
 * 
 * Algorithm/Technique:
 * - The key insight is that we can cut threadlets into smaller pieces, and we want to determine if
 *   after at most 3 cuts, we can make all threadlets of equal length.
 * - Each operation allows us to split one threadlet into two positive integer lengths.
 * - We simulate possible final lengths of threadlets (from 3 to 6 pieces, since 3 operations give
 *   max 3 new pieces, so 3 original + 3 new = 6 pieces total).
 * - For each possible number of pieces (j from 3 to 6), we compute the desired length (s/j).
 * - Then check if all original threadlets can be divided into segments of this length, with each
 *   segment being at least the desired length (since we are cutting, not merging).
 * - Time Complexity: O(t), where t is the number of test cases. Each test case does a constant amount of work.
 * - Space Complexity: O(1), only using a fixed amount of extra space.
 */

using System;
using System.Text;
public class ThreeThreadlets {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int a = int.Parse(parts[0]);
      int b = int.Parse(parts[1]);
      int c = int.Parse(parts[2]);
      long s = (long)a + b + c; // Total length of all threadlets
      bool ansi = false;
      for (byte j = 3; j <= 6 && !ansi; j++) {
        // Try all possible number of final threadlets (3 to 6)
        if (s % j == 0) {
          // If total length is divisible by number of pieces, we might be able to
          // split all into equal parts
          int d = Convert.ToInt32(s / j); // Compute desired length of each piece
          // Check if all original threadlets can be cut into pieces of length d
          // For a threadlet of length x, it must be divisible by d and at least d
          ansi = (a % d == 0 && a >= d && b % d == 0 && b >= d && c % d == 0 && c >= d);
        }
      }
      ans.Append(ansi ? "YES" : "NO");
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/