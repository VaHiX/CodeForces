// Problem: CF 2042 B - Game with Colored Marbles
// https://codeforces.com/contest/2042/problem/B

/*
B. Game with Colored Marbles
Algorithm: Greedy + Hash Map
Time Complexity: O(n) per test case
Space Complexity: O(n) for the hash map storing counts

The problem involves two players (Alice and Bob) taking turns removing marbles from a game.
Alice wants to maximize her score, Bob wants to minimize it. Both play optimally.

Alice's score is calculated as:
1 point for each color where she took at least one marble.
1 additional point for each color where she took ALL marbles of that color.

The key idea:
- For each color, we count how many marbles there are.
- We then determine whether Alice can secure all or just some of the marbles of a given color.
- If a color has only one marble, Alice might get 1 point (if she takes it) or 2 points if Bob takes the last one (and Alice gets both).
- The approach computes how many points each player will get based on optimal play.

The formula used:
ans = (c1 + 1) / 2 * 2 + dc - c1
Where:
- dc: number of distinct colors
- c1: count of colors with exactly one marble

This simplifies the logic for optimal greedy play.
*/

using System.Collections.Generic;
using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      Console.ReadLine();
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      getAns(a);
    }
  }
  static void getAns(int[] a) {
    var d = new Dictionary<int, int>(); // Store count of each color
    foreach (var x in a) {
      if (d.ContainsKey(x))
        d[x]++;
      else
        d[x] = 1;
    }
    var dc = d.Count; // Total number of distinct colors
    var c1 = d.Count(x => x.Value == 1); // Number of colors with exactly one marble
    var ans = (c1 + 1) / 2 * 2 + dc - c1; // Compute Alice's score using derived formula
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/