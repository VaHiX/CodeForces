// Problem: CF 1765 E - Exchange
// https://codeforces.com/contest/1765/problem/E

/*
 * Problem: E. Exchange
 * Purpose: Find the minimum number of quests (gold coins) needed to accumulate at least n silver coins,
 *          using the ability to exchange gold for silver (both buying and selling).
 * 
 * Approach:
 * - If 'a' (selling rate) is greater than 'b' (buying rate), it's better to sell all gold coins obtained
 *   directly to get silver coins, without buying more.
 * - Otherwise, determine how many gold coins are needed to get at least n silver coins.
 *   This is done via ceiling division of n by a (i.e. (n + a - 1) / a) or manually computed.
 * 
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), excluding the output buffer.
 */
using System;
using System.Text;
public class Exchange {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      byte a = byte.Parse(parts[1]);
      byte b = byte.Parse(parts[2]);
      int ansi = 0;
      // If selling rate is higher than buying rate, just sell all gold coins obtained
      if (a > b)
        ansi = 1;
      else
        // Otherwise, calculate minimum number of gold coins needed to get enough silver
        ansi = (n % a > 0 ? n / a + 1 : n / a);
      ans.Append(ansi);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/