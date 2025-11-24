// Problem: CF 1927 A - Make it White
// https://codeforces.com/contest/1927/problem/A

/*
 * Problem: Make it White
 * Algorithm/Techniques: Two Pointers, Greedy
 * 
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(k) per test case, where k is the number of black cells,
 *                   which in the worst case can be n (if all cells are black).
 * 
 * Approach:
 * 1. Find all positions of 'B' (black cells) in the string.
 * 2. The minimum segment needed to cover all black cells is from the first black cell
 *    to the last black cell.
 * 3. Return the length of this segment (last_index - first_index + 1).
 */

using System;
using System.Collections.Generic;
class Program {
  public static void Main(string[] args) {
    int number = int.Parse(Console.ReadLine());
    for (int i = 0; i < number; i++) {
      int len = int.Parse(Console.ReadLine());
      int count = 0;
      string s = Console.ReadLine();
      List<int> num = new List<int>();
      for (int j = 0; j < len; j++) {
        if (s[j] == 'B') {
          num.Add(j); // Store positions of all black cells
        }
      }
      // Calculate the minimum segment length from first to last black cell
      Console.WriteLine(num[num.Count - 1] - num[0] + 1);
    }
  }
}


// https://github.com/VaHiX/CodeForces/