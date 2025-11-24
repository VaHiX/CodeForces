// Problem: CF 1987 C - Basil's Garden
// https://codeforces.com/contest/1987/problem/C

/*
Flowerbox:
Problem: Basil's Garden
Algorithm: Observation-based approach
Time Complexity: O(n) per test case, where n is the number of flowers
Space Complexity: O(1) additional space, not counting input storage

The key insight is that each flower's height decreases over time based on 
the relative heights of adjacent flowers. The process effectively simulates 
a "wave" of reduction moving from left to right. Instead of simulating each 
second, we can calculate the maximum time required for any flower to reach 0.

For each flower at position i with height h_i, it will take at most h_i + i seconds 
to become 0. This is because it starts at height h_i and decrements each second, 
but can only decrement if it's taller than the flower to its right. The time needed 
is the maximum of all such values across all flowers.

This is a greedy approach where we compute for each flower the maximum time 
it would take to reach 0, and the answer is the maximum among all.
*/

using System;
using System.Linq;
class Program {
  static void Main() {
    var input = new InputReader();
    int t = input.ReadInt(); // Read number of test cases
    while (t-- > 0) {
      int n = input.ReadInt(); // Read number of flowers
      long ans = 0; // Initialize result to 0
      for (int i = 0; i < n; ++i) {
        long x = input.ReadLong(); // Read height of current flower
        // Calculate the maximum time it would take for this flower to reach 0
        // It takes x seconds to reduce from x to 0, and an additional i seconds 
        // due to the propagation effect from the left
        ans = Math.Max(ans, x + i);
      }
      Console.WriteLine(ans); // Output the maximum time required
    }
  }
}
class InputReader {
  private string[] _tokens;
  private int _index;
  public InputReader() {
    _tokens = Console.ReadLine()?.Split();
    _index = 0;
  }
  public int ReadInt() {
    EnsureTokens();
    return int.Parse(_tokens[_index++]);
  }
  public long ReadLong() {
    EnsureTokens();
    return long.Parse(_tokens[_index++]);
  }
  private void EnsureTokens() {
    if (_index >= _tokens.Length) {
      _tokens = Console.ReadLine()?.Split();
      _index = 0;
    }
  }
}


// https://github.com/VaHiX/CodeForces/