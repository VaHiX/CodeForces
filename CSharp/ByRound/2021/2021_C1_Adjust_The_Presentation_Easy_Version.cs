// Problem: CF 2021 C1 - Adjust The Presentation (Easy Version)
// https://codeforces.com/contest/2021/problem/C1

/*
 * Problem: C1. Adjust The Presentation (Easy Version)
 * Algorithm/Techniques: Simulation with HashSet
 * Time Complexity: O(n + m) per test case
 * Space Complexity: O(n) due to the hash set usage
 *
 * Description:
 * We are given an initial lineup of n members (array a), and a sequence b of m members who must present slides.
 * Each slide is presented by the front member of the line. After presenting, that member can be moved to any position.
 * We check if it's possible to have each member in b present their respective slide following rules.
 *
 * Approach:
 * - We simulate the process:
 *   - Use a HashSet to store members already seen (or able to be used).
 *   - Traverse the b array and for each element:
 *     - If it matches current front of a, advance the pointer in a and add to set.
 *     - Else if not in set, return "TIDAK".
 *   - If all elements processed successfully, return "YA".
 */

using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var m = int.Parse(line[1]);
      getAns(n, m);
    }
  }
  static void getAns(int n, int m) {
    string[] line = Console.ReadLine().Trim().Split(' ');
    var a = Array.ConvertAll(line, int.Parse); // Initial lineup order
    line = Console.ReadLine().Trim().Split(' ');
    var b = Array.ConvertAll(line, int.Parse); // Required presenters per slide

    var hs = new HashSet<int>(); // Stores members that can be used in sequence
    var pa = 0; // Pointer to current front member in array a
    
    foreach (var x in b) {
      if (x == a[pa]) { // If current required member matches the front
        hs.Add(a[pa]); // Add to set of available members
        if (pa + 1 != n)
          pa++; // Move pointer forward if not at end
      } else {
        // If not matching and not in set, impossible to proceed
        if (!hs.Contains(x)) {
          Console.WriteLine("TIDAK");
          return;
        }
      }
    }
    Console.WriteLine("YA"); // All members matched correctly
  }
}


// https://github.com/VaHiX/codeForces/