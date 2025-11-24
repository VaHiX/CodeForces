// Problem: CF 1498 B - Box Fitting
// https://codeforces.com/contest/1498/problem/B

/*
Purpose: This code solves the "Box Fitting" problem where we need to determine the minimum height of a box required to fit all given rectangles of height 1, with widths being powers of 2.

Algorithm:
- Use a greedy approach to pack rectangles into levels (rows) of the box.
- For each level, try to fit as many rectangles as possible such that their total width does not exceed W.
- A dictionary tracks how many rectangles of each width we have left to place.
- While there are rectangles to place:
    - For each power of 2 from largest to smallest:
        - If a rectangle of that width exists and adding it doesn't exceed the box width:
            - Place it (reduce count or remove from dict)
            - Add its width to current level's total width
    - Increment level counter
- Return the number of levels used.

Time Complexity: O(n * log(max_width)) where n is number of rectangles and max_width is the largest rectangle width.
Space Complexity: O(n) for storing the counts of rectangles by width.
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace ConsoleApp2 {
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n, w;
      string[] s = Console.ReadLine().Split();
      n = int.Parse(s[0]);
      w = int.Parse(s[1]);
      string[] str = Console.ReadLine().Split();
      Dictionary<int, int> dict = new Dictionary<int, int>();
      int max = -1;
      for (int i = 0; i < n; i++) {
        int a = int.Parse(str[i]);
        if (!dict.ContainsKey(a)) {
          dict.Add(a, 1);
          if (a > max)
            max = a;
        } else {
          dict[a] += 1;
        }
      }
      int count = 0;
      while (dict.Count > 0) {
        int sum = 0;
        for (int i = max; i >= 1; i /= 2) {
          if (dict.ContainsKey(i) && sum + i <= w) {
            sum += i;
            if (dict[i] == 1)
              dict.Remove(i);
            else
              dict[i] -= 1;
            i *= 2; // This is a trick to avoid revisiting same width in inner loop
          }
        }
        count++;
      }
      Console.WriteLine(count);
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/