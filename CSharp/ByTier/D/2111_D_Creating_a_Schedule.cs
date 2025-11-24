// Problem: CF 2111 D - Creating a Schedule
// https://codeforces.com/contest/2111/problem/D

/*
 * Problem: D. Creating a Schedule
 * Algorithm: Greedy sorting and pairing to maximize floor movements
 * Time Complexity: O(m log m + n * m) per test case (due to sorting and assignment)
 * Space Complexity: O(m) for storing classroom data and output buffer
 *
 * The approach:
 * 1. Sort classrooms by their floor number (first 3 digits except last two)
 * 2. Assign pairs of classrooms from both ends of sorted list to maximize movement between floors
 * 3. Each group gets 6 classrooms: 3 pairs, with alternating high-low floor numbers to increase movement count
 * 
 * Techniques used:
 * - Sorting with LINQ OrderBy
 * - Greedy pairing from extremes (left and right) of sorted array
 * - StringBuilder for efficient output construction
 */

using System.Text;
using System.Linq;
using System;
public class hello {
  public static StringBuilder sb;
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var m = int.Parse(line[1]);
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      getAns(n, m, a);
    }
  }
  static void getAns(int n, int m, int[] a) {
    sb = new StringBuilder();
    // Sort classrooms by floor number (first 3 digits)
    var bb = a.OrderBy(x => x / 100).ToArray();
    var c = 0;
    var pL = 0;
    var pr = m - 1;
    while (true) {
      // Assign pair of classrooms from left and right (maximize floor differences)
      print(bb[pL], bb[pr]);
      c++;
      if (c == n)
        break;
      // Alternate assignment pattern to ensure maximum number of moves across groups
      print(bb[pr--], bb[pL++]);
      c++;
      if (c == n)
        break;
    }
    Console.Write(sb);
  }
  static void print(int x, int y) {
    // Format output as "x y x y x y" for one group's 6 classes
    sb.AppendLine(string.Format("{0} {1} {0} {1} {0} {1}", x, y));
  }
}


// https://github.com/VaHiX/codeForces/