// Problem: CF 1774 A - Add Plus Minus Sign
// https://codeforces.com/contest/1774/problem/A

/*
 * Problem: Add Plus Minus Sign
 * 
 * Algorithm/Technique: Greedy approach
 * 
 * Time Complexity: O(n) where n is the length of the string
 * Space Complexity: O(1) - only using a constant amount of extra space
 * 
 * The strategy is to minimize the absolute value of the resulting expression.
 * We start with a '-' sign and alternate signs based on the value of the current character:
 * - If the character is '0', we use '+' to minimize the contribution to the total.
 * - If the character is '1', we use the current sign and flip it for the next step.
 * This greedy approach ensures we get the minimum absolute value.
 */

using System;
using System.Collections.Generic;
public class MainClass {
  public static void Solve() {
    int n;
    n = Convert.ToInt32(Console.ReadLine());
    string s = Console.ReadLine();
    char sign = '-';
    for (int i = 1; i < n; ++i) {
      // If the current character is '0', append '+' to minimize effect
      if (s[i] == '0') {
        Console.Write("+");
      } else {
        // If the current character is '1', use the current sign and flip it for next iteration
        Console.Write(sign);
        sign = sign == '-' ? '+' : '-';
      }
    }
    Console.WriteLine("");
  }
  public static void Main() {
    int t;
    t = Convert.ToInt32(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/CodeForces/