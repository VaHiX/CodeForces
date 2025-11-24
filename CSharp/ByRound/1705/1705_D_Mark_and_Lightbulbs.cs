// Problem: CF 1705 D - Mark and Lightbulbs
// https://codeforces.com/contest/1705/problem/D

/*
 * Problem: Mark and Lightbulbs
 * 
 * Algorithm/Approach:
 * - The key insight is that we can only toggle a bulb at position i if s[i-1] != s[i+1].
 * - This means we can only change middle bulbs, not the first or last bulb.
 * - Any transformation from s to t requires the first and last bulbs to match.
 * - We group consecutive same characters in both strings to represent segments.
 * - Then, we calculate the number of operations required to convert one segment structure to another.
 * - The difference in segment counts corresponds to the number of operations needed.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(n) for storing the segments.
 */

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int fyt = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < fyt; z++) {
      var n = long.Parse(Console.ReadLine());
      var s1 = Console.ReadLine();
      var s2 = Console.ReadLine();
      long o = 0;
      int t = 1;
      char c = s1[0];
      List<int> a = new List<int>(); // segments of s1
      List<int> b = new List<int>(); // segments of s2
      for (int i = 1; i < n; i++) {
        char c1 = s1[i];
        if (c1 == c)
          t++;
        else {
          c = c1;
          a.Add(t);
          t = 1;
        }
      }
      a.Add(t); // Add the last segment
      
      t = 1;
      c = s2[0];
      for (int i = 1; i < n; i++) {
        char c1 = s2[i];
        if (c1 == c)
          t++;
        else {
          c = c1;
          b.Add(t);
          t = 1;
        }
      }
      b.Add(t); // Add the last segment
      
      // Check if the transformation is possible
      if (a.Count != b.Count || s1[0] != s2[0])
        o = -1;
      else {
        int l1 = 0;
        int l2 = 0;
        for (int i = 0; i < a.Count; i++) {
          o += (Math.Abs(l2 - l1)); // Add the difference in positions
          l1 += a[i];
          l2 += b[i];
        }
        o += (Math.Abs(l2 - l1)); // Add the final difference
      }
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/