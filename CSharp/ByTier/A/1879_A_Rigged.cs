// Problem: CF 1879 A - Rigged!
// https://codeforces.com/contest/1879/problem/A

/*
 * Problem: Rigged Weightlifting Competition
 * 
 * Purpose:
 *   Given n athletes with strength s[i] and endurance e[i], find a weight w such that
 *   the first athlete (Polycarp) wins the competition. An athlete can lift the barbell
 *   e[i] times if w <= s[i], otherwise they cannot lift it at all. If multiple athletes
 *   lift the barbell the same maximum number of times, there is no winner.
 * 
 * Algorithm:
 *   - For a given weight w, an athlete can lift the barbell e[i] times if w <= s[i].
 *   - To ensure that athlete 0 (Polycarp) wins, we must:
 *     1. Ensure that he can lift it (w <= s[0])
 *     2. Ensure that no other athlete can lift it more times than athlete 0.
 *   - So, for each athlete j (j > 0):
 *     - If s[j] >= s[0] and e[j] >= e[0], then athlete j can lift as many times or more,
 *       so he could potentially tie or win, which makes it impossible for Polycarp to win.
 *     - Otherwise, if s[j] < s[0], then we are okay as long as w does not exceed s[j] (or the max w).
 *   - To satisfy the constraint that w > 0, we look for a w such that only Polycarp
 *     can lift the barbell e[0] times, which means setting w slightly above the highest s[j] where s[j] >= s[0] and e[j] >= e[0].
 *   - Strategy:
 *     - If Polycarp's endurance e[0] is larger than everyone else's endurance e[j] (with s[j] >= s[0]),
 *       we can set w = s[0] + 1 and he will win.
 *     - However, if there exists any athlete j (j != 0) such that s[j] >= s[0] and e[j] >= e[0],
 *       it's impossible for Polycarp to win.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
using System;
using System.Text;
public class Rigged {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    byte t = byte.Parse(Console.ReadLine());
    for (byte i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine());
      int[] s = new int[n];
      byte[] e = new byte[n];
      for (byte j = 0; j < n; j++) {
        string[] parts = Console.ReadLine().Split();
        s[j] = int.Parse(parts[0]);
        e[j] = byte.Parse(parts[1]);
      }
      int ansi = s[0];
      for (byte j = 1; j < n && ansi > 0; j++)
        if (s[j] >= s[0] && e[j] >= e[0])
          ansi = -1;
      ans.Append(ansi);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/