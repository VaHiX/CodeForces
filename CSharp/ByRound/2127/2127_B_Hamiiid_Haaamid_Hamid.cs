// Problem: CF 2127 B - Hamiiid, Haaamid... Hamid?
// https://codeforces.com/contest/2127/problem/B

/*
 * Problem: B. Hamiiid, Haaamid... Hamid?
 * Purpose: Simulate a game between Mani and Hamid on a 1D grid where Mani builds walls and Hamid escapes,
 *          with both players playing optimally.
 * 
 * Algorithms/Techniques:
 *   - Greedy simulation
 *   - Two-pointer technique to find nearest walls
 *   - Optimal play analysis (Mani maximizes escape time, Hamid minimizes)
 *
 * Time Complexity: O(n) per test case — we iterate through the string at most twice.
 * Space Complexity: O(n) — storing input string and processing variables.
 */

using System.Text;
namespace HamiiidHaaamidHamid;
class Program {
  static int Solve() {
    var p = reader.ReadLine()
                .Split(' ')
                .Where(e => !string.IsNullOrEmpty(e))
                .Select(int.Parse)
                .ToList();
    int n = p[0];
    int x = p[1] - 1; // Convert to 0-indexed
    string s = reader.ReadLine();
    int r = -1; // Rightmost wall after current position (x)
    for (int i = x + 1; i < s.Length; i++) {
      if (s[i] == '#') {
        r = i;
        break;
      }
    }
    int l = -1; // Leftmost wall before current position (x)
    for (int i = x - 1; i >= 0; i--) {
      if (s[i] == '#') {
        l = i;
        break;
      }
    }

    // If no walls to the left or right:
    if (l < 0 && r < 0)
      return 1;

    // If there's a wall immediately adjacent, Hamid can escape directly:
    if (l + 1 == x || x + 1 == r)
      return Math.Min(x + 1, s.Length - x);

    // If there is no wall to the left or right, Hamid just needs one day:
    if (l < 0)
      return Math.Min(x + 1, s.Length - r + 1);
    if (r < 0)
      return Math.Min(l + 2, s.Length - x);

    // Compare distances based on optimal play:
    if (l + 1 < s.Length - r)
      return Math.Min(x + 1, s.Length - r + 1);
    if (l + 1 > s.Length - r)
      return Math.Min(l + 2, s.Length - x);

    // Fallback case:
    return Math.Max(Math.Min(x + 1, s.Length - r + 1),
                    Math.Min(l + 2, s.Length - x));
  }
  static void Main(string[] args) {
    int t = int.Parse(reader.ReadLine());
    for (int i = 0; i < t; i++) {
      writer.WriteLine(Solve());
    }
    writer.Flush();
  }
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/