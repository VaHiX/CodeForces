// Problem: CF 1969 B - Shifts and Sorting
// https://codeforces.com/contest/1969/problem/B

using System;
public class ShiftsAndSorting {
  /*
   * Problem: Minimum cost to sort a binary string using cyclic shifts.
   * 
   * Approach:
   * - The key insight is that we need to count how many '1's are in the prefix of the string,
   *   and we can move '0's to the left by performing shifts.
   * - We iterate through the string and find segments of '1's and '0's.
   * - For each transition from '1' to '0', we calculate the cost of moving these '0's to the left,
   *   using the number of '1's that have come before (as they will be shifted to the right).
   * 
   * Time Complexity: O(n) where n is the total length of all strings in the input.
   * Space Complexity: O(1) as we use only constant extra space.
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string s = Console.ReadLine();
      int n = s.Length;
      int count1 = 0; // Counter for number of 1's seen so far
      long ans = 0;   // Total cost
      int l = Search(s, 0, '1'); // Find first '1'
      while (l < n) {
        int r = Search(s, l, '0'); // Find first '0' after current '1'
        if (r < n) {
          count1 += r - l; // Add number of 1's in this segment
          l = r;           // Move to start of '0' segment
          r = Search(s, l, '1'); // Find next '1'
          ans += ((long)count1 + 1) * (r - l); // Cost for shifting
        }
        l = r; // Update l to be the next '1' or end of string
      }
      Console.WriteLine(ans);
    }
  }
  public static int Search(string s, int i, char d) {
    while (i < s.Length && s[i] != d)
      i++;
    return i;
  }
}


// https://github.com/VaHiX/CodeForces/