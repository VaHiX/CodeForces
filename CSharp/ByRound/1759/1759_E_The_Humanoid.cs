// Problem: CF 1759 E - The Humanoid
// https://codeforces.com/contest/1759/problem/E

/*
Algorithm: Greedy with 3 strategies
Time Complexity: O(n log n) due to sorting and linear scan
Space Complexity: O(n) for storing astronaut powers

The problem involves a humanoid that can absorb astronauts or use serums to increase its power,
aiming to maximize the number of absorbed astronauts. The humanoid has two green serums and one blue serum.
Three strategies are tried:
1. Use green serum first, then blue
2. Use blue serum first, then green
3. Use green serum twice, then blue

Each strategy is simulated by:
- Sorting astronauts by power
- For each astronaut, if their power < humanoid power, absorb them
- Otherwise, use a serum (green or blue) as per strategy
- After using a serum, reduce serum count and restart scan from current position
- The strategy with maximum absorption count is returned
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
    for (int hz = 0; hz < fyt; hz++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      var b =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToArray();
      long o = 0;
      long o1 = 0;
      Array.Sort(b);
      long h = a[1];
      int g = 3;
      for (int i = 0; i < a[0]; i++) {
        if (b[i] < h) {
          o1++;
          h += b[i] / 2;
        } else {
          if (g == 3)
            h *= 2;  // Use first green serum
          else if (g == 2)
            h *= 2;  // Use second green serum
          else if (g == 1)
            h *= 3;  // Use blue serum
          else
            break;   // No serums left
          g--;
          i--;     // Restart from same index after using serum
        }
      }
      o = Math.Max(o1, o);
      o1 = 0;
      g = 3;
      h = a[1];
      for (int i = 0; i < a[0]; i++) {
        if (b[i] < h) {
          o1++;
          h += b[i] / 2;
        } else {
          if (g == 3)
            h *= 3;  // Use blue serum first
          else if (g == 2)
            h *= 2;  // Use green serum
          else if (g == 1)
            h *= 2;  // Use remaining green serum
          else
            break;
          g--;
          i--;     // Restart from same index after using serum
        }
      }
      o = Math.Max(o1, o);
      o1 = 0;
      g = 3;
      h = a[1];
      for (int i = 0; i < a[0]; i++) {
        if (b[i] < h) {
          o1++;
          h += b[i] / 2;
        } else {
          if (g == 3)
            h *= 2;  // Use first green serum
          else if (g == 2)
            h *= 3;  // Use blue serum
          else if (g == 1)
            h *= 2;  // Use remaining green serum
          else
            break;   // No serums left
          g--;
          i--;     // Restart from same index after using serum
        }
      }
      o = Math.Max(o1, o);
      o1 = 0;
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/