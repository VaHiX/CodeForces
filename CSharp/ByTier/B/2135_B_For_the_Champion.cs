// Problem: CF 2135 B - For the Champion
// https://codeforces.com/contest/2135/problem/B

// Problem: B. For the Champion
// Purpose: Find the initial coordinates (X,Y) of a robot on an infinite 2D plane using Manhattan distances to anchor points.
// Algorithm:
// - Uses binary search strategy with directional queries (U, D, L, R) to determine bounds.
// - Computes maximums of (x_i + y_i) and (x_i - y_i) across all anchors.
// - Queries robot in 4 directions with large k values to bound its position.
// Time Complexity: O(n + 10) = O(n), where n is number of anchor points
// Space Complexity: O(1), constant space usage

using System.Text;
namespace ForTheChampion;
class Program {
  static void Solve() {
    int n = int.Parse(reader.ReadLine()); // Read number of anchors
    long max1 = long.MinValue; // Max (x + y) among anchors
    long max2 = long.MinValue; // Max (x - y) among anchors
    for (int i = 0; i < n; i++) {
      long[] pp = reader.ReadLine()
                      .Split(' ')
                      .Where(e => !string.IsNullOrEmpty(e))
                      .Select(long.Parse)
                      .ToArray();
      max1 = Math.Max(max1, pp[0] + pp[1]); // Update max1
      max2 = Math.Max(max2, pp[0] - pp[1]); // Update max2
    }
    long z = 1000000000; // Large k value to bound search space
    
    // Query in 4 directions with large z to find bounds
    Ask(0, z); // U
    Ask(0, z); // U
    Ask(3, z); // R
    long p = Ask(3, z); // R - result gives us a bound
    Ask(1, z); // D
    Ask(1, z); // D
    Ask(1, z); // D
    Ask(1, z); // D
    Ask(1, z); // D
    long q = Ask(1, z); // D - result gives us another bound
    
    // Calculate X and Y based on derived formulas
    long x = (p + max1 + q + max2 - 10 * z) / 2; // Derived from Manhattan equations
    long y = p + max1 - x - 4 * z; // Derived from Manhattan equations
    Ans(x, y); // Output final coordinates
  }
  
  static long Ask(int dir, long k) {
    writer.Write("? ");
    switch (dir) {
    case 0:
      writer.Write("U "); // Up
      break;
    case 1:
      writer.Write("D "); // Down
      break;
    case 2:
      writer.Write("L "); // Left
      break;
    case 3:
      writer.Write("R "); // Right
      break;
    }
    writer.WriteLine(k);
    writer.Flush();
    return long.Parse(reader.ReadLine());
  }
  
  static void Ans(long x, long y) {
    writer.WriteLine($"! {x} {y}");
    writer.Flush();
  }
  
  static void Main(string[] args) {
    int t = int.Parse(reader.ReadLine()); // Number of test cases
    for (int i = 0; i < t; i++) {
      Solve(); // Process each test case
    }
    writer.Flush(); // Flush final output
  }
  
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/