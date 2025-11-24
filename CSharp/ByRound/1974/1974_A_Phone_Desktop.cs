// Problem: CF 1974 A - Phone Desktop
// https://codeforces.com/contest/1974/problem/A

/*
 * Problem: Phone Desktop
 * 
 * Purpose: Given x 1x1 icons and y 2x2 icons, place them on minimum number of 5x3 screens.
 * 
 * Algorithm:
 * - Each screen has 15 cells.
 * - 2x2 icons take 4 cells each; 1x1 icons take 1 cell each.
 * - Strategy:
 *   1. Place all 2x2 icons first optimally.
 *   2. For each 2x2 icon, we can fill up to 4 cells of a screen.
 *   3. A screen can hold at most 3 (2x2) icons (since 3*4 = 12 cells, leaving 3), or less.
 *   4. So, we try to use full or partially full screens.
 *   5. After placing all 2x2 icons, calculate how many more 1x1 icons fit.
 *   6. Each 1x1 icon takes 1 cell.
 *   7. Each screen holds 15 cells.
 * 
 * Time Complexity: O(1) - constant time per test case.
 * Space Complexity: O(1) - only using a fixed amount of variables.
 */

using System;
public class PhoneDesktop {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      byte x = byte.Parse(parts[0]);
      byte y = byte.Parse(parts[1]);
      
      // Calculate minimum number of screens needed for 2x2 icons
      // If y is even, we can fit y/2 screens completely (each 2x2 icon takes 4 cells)
      // If y is odd, we need one extra screen for the last 2x2 icon
      byte ans = Convert.ToByte(y % 2 == 0 ? y / 2 : (y + 1) / 2);
      
      // Calculate how many 1x1 icons can be placed in the screen(s) already used for 2x2 icons
      // We start by finding the number of 1x1s we can fit after placing 2x2 icons
      short numSmall = Convert.ToInt16(y % 2 == 0 ? ans * 7 : (ans - 1) * 7 + 11);
      
      // If the number of 1x1 icons exceeds what we can accommodate, add additional screens
      if (numSmall < x) {
        byte d = Convert.ToByte(x - numSmall);
        // Calculate how many additional screens are needed for remaining 1x1 icons
        ans += Convert.ToByte(d % 15 == 0 ? d / 15 : d / 15 + 1);
      }
      
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/