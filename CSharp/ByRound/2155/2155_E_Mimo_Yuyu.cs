// Problem: CF 2155 E - Mimo & Yuyu
// https://codeforces.com/contest/2155/problem/E

/* 
E. Mimo & Yuyu
Algorithm: Game Theory (Nim-like game with specific movement rules)
Time Complexity: O(k log k) per test case due to grouping and max operations.
Space Complexity: O(k) for storing token positions.

The game is played on an n x m grid where tokens can be moved according to specific rules:
- A token can only be moved if its starting column is greater than the next column.
- Tokens must move towards column 1, always staying in non-increasing column order.
- The game ends when no player can make a legal move.

The key insight is to analyze parity of tokens in each row (excluding row 1) to determine winning condition:
- If there exists any row with an odd number of tokens (excluding those in row 1), Mimo wins.
- Otherwise, the outcome depends on the number of tokens in row 2 if n=1.
*/

using System.Text;
using System;
using System.IO;
using System.Linq;

namespace MimoYuyu{
class Program {
  static bool Solve() {
    long n = Next();
    long m = Next();
    long k = Next();
    var a = new(long x, long y)[k];
    for (int i = 0; i < k; i++)
      a[i] = (Next(), Next());
    long max = a.Max(e => e.y); // Find maximum column number
    if (max == 1)
      return false; // All tokens are in column 1, no valid moves possible
    if (n > 1) {
      // Group tokens by row and count how many tokens exist per row (excluding row 1)
      var p = a.GroupBy(e => e.y).Select(e => new { e.Key, cnt = e.Count() });
      foreach (var item in p) {
        if (item.Key == 1)
          continue; // Skip row 1 as it's not relevant to move rules
        if (item.cnt % 2 == 1) // If odd count in a row -> winning condition for Mimo
          return true;
      }
      return false; // All rows have even numbers of tokens, Yuyu wins
    }
    return a.Count(e => e.y == 2) % 2 == 1; // For n=1 case
  }
  static void Main(string[] args) {
    long t = Next();
    for (int i = 0; i < t; i++) {
      writer.WriteLine(Solve() ? "Mimo" : "Yuyu");
    }
    writer.Flush();
  }
  static long Next() {
    int c;
    int m = 1;
    long res = 0;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1;
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return m * res;
      res *= 10;
      res += c - '0';
    }
  }
  static readonly StreamReader reader = new StreamReader(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new StreamWriter(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}
}

// https://github.com/VaHiX/CodeForces/