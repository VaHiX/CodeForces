// Problem: CF 2047 A - Alyona and a Square Jigsaw Puzzle
// https://codeforces.com/contest/2047/problem/A

/*
 * Problem: Alyona and a Square Jigsaw Puzzle
 * Algorithm: Simulation of layer completion in a square jigsaw puzzle.
 * Time Complexity: O(n), where n is the number of days.
 * Space Complexity: O(n), due to storing the list of daily piece counts.
 *
 * Description:
 * Alyona assembles a square jigsaw puzzle over n days. Each day she places
 * pieces in layers, starting from the center. Layers are completed before
 * moving to the next. A day is happy if at the end of that day, no layer is
 * partially filled (i.e., the cumulative sum equals a perfect square).
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace HelloWorld {
  public class Program {
    public static void Main() {
      int t = int.Parse(Console.ReadLine());
      for (int i = 0; i < t; i++) {
        int n = int.Parse(Console.ReadLine());
        List<int> list = Console.ReadLine().Split(' ').Select(int.Parse).ToList();
        int sum = 0;
        int res = 0;
        int start = 1;
        int uu = start * start;
        for (int j = 0; j < n; j++) {
          sum += list[j];  // Add pieces placed on current day to total
          if (sum == uu) {  // If we've completed a perfect square layer
            res++;  // Increment happy days counter
            start += 2;  // Move to next odd number (1, 3, 5, ...)
            uu = start * start;  // Update the target square
          } else if (sum > uu) {  // If we've exceeded the current layer target
            while (sum > uu) {  // Keep advancing until we reach a valid square
              start += 2;
              uu = start * start;
            }
            if (sum == uu) {  // If now exactly matching a square
              res++;
              start += 2;
              uu = start * start;
            }
          }
        }
        Console.WriteLine(res);
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/