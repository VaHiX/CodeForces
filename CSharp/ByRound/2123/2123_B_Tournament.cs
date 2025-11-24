// Problem: CF 2123 B - Tournament
// https://codeforces.com/contest/2123/problem/B

/*
B. Tournament
Algorithms/Techniques: Simulation with greedy approach and max element comparison
Time Complexity: O(n) per test case
Space Complexity: O(n) due to input array storage

The problem simulates a tournament where players are eliminated based on strength.
We determine if player j can be among the last k remaining players.

Key observations:
- If k > 1, player j can always be in the final k players (because we remove one player at a time until k remain)
- If k == 1, player j must be the absolute strongest to survive all rounds
*/
using System;
using System.Linq;
public class Program {
  public static void Solve() {
    int[] input = Console.ReadLine().Split().Select(int.Parse).ToArray();
    int n = input[0];
    int j = input[1];
    int k = input[2];
    int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray();
    if (k > 1) {
      // If k > 1, player j can always make it to the final k players
      Console.WriteLine("YES");
    } else {
      // If k == 1, only the strongest player survives
      int maxStrength = a.Max();
      if (a[j - 1] == maxStrength) {
        // Player j has maximum strength, so can survive to last
        Console.WriteLine("YES");
      } else {
        // Player j doesn't have maximum strength, cannot be last
        Console.WriteLine("NO");
      }
    }
  }
  public static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/codeForces/