// Problem: CF 1971 D - Binary Cut
// https://codeforces.com/contest/1971/problem/D

/*
 * Problem: Binary Cut
 * 
 * Purpose: Given a binary string, determine the minimum number of contiguous pieces 
 *          to cut it into so that the pieces can be rearranged into a sorted binary string.
 *          A sorted binary string has all 0s before all 1s.
 * 
 * Approach:
 * 1. Identify contiguous segments of same characters (0s or 1s).
 * 2. Count the number of such segments.
 * 3. Based on the number of segments:
 *    - If 1 segment: already sorted, return 1.
 *    - If 2 segments: if first is 0, return 1; otherwise return 2.
 *    - If more than 2 segments: return (number of segments - 1).
 * 
 * Time Complexity: O(n), where n is the length of the string. We iterate through the string once.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

using System;
public class BinaryCut {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string s = Console.ReadLine();
      short l = 0;
      short c = 0;
      while (l < s.Length) {
        short r = l;
        while (r < s.Length && s[r] == s[l])
          r++;
        c++; // Count number of contiguous segments
        l = r;
      }
      short ans = 0;
      if (c == 1)
        ans = 1;
      else if (c == 2)
        ans = Convert.ToInt16(s[0] == '0' ? 1 : 2); // If first is 0, no cut needed; otherwise one cut to separate 0s and 1s
      else
        ans = Convert.ToInt16(c - 1); // More than two segments: number of cuts is segments - 1
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/