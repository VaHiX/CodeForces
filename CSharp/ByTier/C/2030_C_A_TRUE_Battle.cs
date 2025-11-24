// Problem: CF 2030 C - A TRUE Battle
// https://codeforces.com/contest/2030/problem/C

using System;
public class ATrueBattle {
  /*
   * Problem: A TRUE Battle
   * 
   * Purpose:
   *   Determine if Alice wins a game where she and Bob alternately place 'and' or 'or'
   *   operators between booleans, with Alice trying to make the final result true
   *   and Bob trying to make it false.
   * 
   * Algorithm:
   *   - The key insight is that in any expression with 'and' and 'or' operators:
   *     - If there is at least one '1' (true), Alice can always win by placing an 'or' 
   *       operator such that the result becomes true.
   *     - If all values are '0' (false), then the result will always be false.
   *     - The optimal strategy is to look for a pattern that allows Alice to secure
   *       a true value at some point.
   *   - The condition: s.StartsWith("1") || s.EndsWith("1") || s.IndexOf("11") > -1
   *     checks whether:
   *     - The first character is '1' (Alice can start with an 'or' to make result true),
   *     - The last character is '1' (Bob can't prevent the final true),
   *     - Or there's any consecutive '11' in the string (Alice can place an operator to 
   *       form a true subexpression).
   * 
   * Time Complexity: O(n) for each test case, where n is the length of the string.
   * Space Complexity: O(1) - only using a few variables for checks.
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string s = Console.ReadLine();
      // Evaluate whether Alice can force a win based on the structure of the string
      bool ans = s.StartsWith("1") || s.EndsWith("1") || s.IndexOf("11") > -1;
      Console.WriteLine(ans ? "YES" : "NO");
    }
  }
}

// https://github.com/VaHiX/CodeForces/