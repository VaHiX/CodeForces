// Problem: CF 1858 A - Buttons
// https://codeforces.com/contest/1858/problem/A

/*
 * Problem: Determine the winner of a turn-based game where Anna and Katie press buttons.
 *          - a buttons: only Anna can press
 *          - b buttons: only Katie can press
 *          - c buttons: either can press
 *          Anna goes first. The player who can't make a move loses.
 *
 * Algorithm:
 *   - The key insight is to analyze parity of c (the number of shared buttons)
 *     and compare a and b.
 *   - If c is even:
 *     - Anna wins if a > b (she can always take the last shared button and force a win).
 *   - If c is odd:
 *     - Anna wins if a >= b (she can take the last shared button and has enough
 *       advantage to avoid losing).
 *   - Otherwise, Katie wins.
 *
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1) excluding input/output storage.
 */
using System;
using System.Text;
public class Buttons {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int a = int.Parse(parts[0]);
      int b = int.Parse(parts[1]);
      int c = int.Parse(parts[2]);
      // Determine the winner based on parity of c and relative values of a and b
      string ansi =
          ((c % 2 == 0 && a > b) || (c % 2 > 0 && a >= b) ? "First" : "Second");
      ans.Append(ansi);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/