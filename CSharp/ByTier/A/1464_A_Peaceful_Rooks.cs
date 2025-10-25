// Problem: CF 1464 A - Peaceful Rooks
// https://codeforces.com/contest/1464/problem/A

﻿/*
 * Problem: Peaceful Rooks
 * Algorithm: Graph traversal to find minimum moves to place rooks on main diagonal
 * 
 * Approach:
 * 1. For each rook, we track which row and column it occupies
 * 2. We build a mapping from row/column to rook index
 * 3. We process rooks in cycles - if a rook needs to move, we follow the chain
 *    of rook dependencies until we return to the starting rook or find a conflict
 * 4. Each cycle contributes to the total move count
 * 
 * Time Complexity: O(n) for each test case, where n is the size of the board
 * Space Complexity: O(n) for storing row/column mappings and visited flags
 */
using System;
using System.Linq;
namespace codeforces201220 {
class Program {
  static void Main(string[] args) { A(); }
  static void A() {
    var t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      var dims = Console.ReadLine().Split().Select(x => int.Parse(x)).ToArray();
      var n = dims[0];
      var m = dims[1];
      var positions = Enumerable.Range(0, m)
                          .Select(x => new IntPair(Console.ReadLine()))
                          .ToArray();
      var cols = new int[n + 1];  // Mapping from column to rook index
      for (int j = 0; j < cols.Length; j++)
        cols[j] = -1;
      var rows = new int[n + 1];  // Mapping from row to rook index
      for (int j = 0; j < rows.Length; j++)
        rows[j] = -1;
      for (int i1 = 0; i1 < positions.Length; i1++) {
        IntPair p = positions[i1];
        cols[p.First] = i1;    // Store which rook is in this column
        rows[p.Second] = i1;   // Store which rook is in this row
      }
      var done = new bool[m];  // Track visited rooks to avoid double counting
      var score = 0;           // Total moves required
      for (int j = 0; j < m; j++) {
        if (done[j])
          continue;      // Skip if already processed
        done[j] = true;    // Mark this rook as processed
        var p = positions[j];
        if (p.First == p.Second)
          continue;      // Already on diagonal, no moves needed
        score += 1;      // Move this rook to diagonal
        // If there is another rook in the same row or column, form a cycle
        if (rows[p.First] == -1 || cols[p.Second] == -1)
          continue;
        var current = rows[p.First];  // Start following the cycle
        while (current != -1 && !done[current]) {
          done[current] = true;             // Mark as visited
          current = rows[positions[current].First];  // Move to next in the chain
          score += 1;    // Add move for each step in the cycle
        }
        if (current == j)
          score += 1;    // If cycle returns to start, one more move needed
      }
      Console.WriteLine(score);
    }
  }
}
public struct IntPair {
  public int First;
  public int Second;
  public IntPair(string s) {
    var split = s.Split();
    First = int.Parse(split[0]);
    Second = int.Parse(split[1]);
  }
  public IntPair(int first, int second) {
    First = first;
    Second = second;
  }
  public static bool operator ==(IntPair p1, IntPair p2) => p1.First == p2.First
                                                            && p1.Second
                                                                   == p2.Second;
  public static bool operator !=(IntPair p1, IntPair p2) => p1.First != p2.First
                                                            || p1.Second
                                                                   != p2.Second;
  public override string ToString() => $"{First} {Second}";
  public override bool Equals(object obj) {
    var p = obj as IntPair ? ;
    return p.HasValue && p.Value.First == First && p.Value.Second == Second;
  }
  public override int GetHashCode() {
    uint rol5 = ((uint)First << 5) | ((uint)First >> 27);
    return ((int)rol5 + First) ^ Second;
  }
}
}


// https://github.com/VaHiX/CodeForces/