// Problem: CF 2129 A - Double Perspective
// https://codeforces.com/contest/2129/problem/A

/*
 * Problem: Double Perspective
 * 
 * Purpose:
 *   Given n pairs (a_i, b_i), we must select a subset S' such that f(S') - g(S') is maximized.
 *   - f(S) = total length of union of segments on number line.
 *   - g(S) = number of nodes in at least one simple cycle (length >= 3) in graph formed by edges.
 *   
 * Approach:
 *   - Greedy algorithm with sorting by 'a' in ascending and 'b' in descending order.
 *   - Process pairs sequentially and select the best non-conflicting pair that increases f(S') without unnecessary decrease in g(S').
 *   - Uses a greedy approach similar to interval scheduling but modified to account for graph cycle properties.
 *   
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing pairs and result list
 */

using System.Text;
namespace DoublePerspective;

class Program {
  static void Solve() {
    int n = Next();
    var nn = new(int a, int b, int i)[n];
    for (int i = 0; i < n; i++)
      nn[i] = (Next(), Next(), i + 1); // Store each pair with its index

    // Sort by 'a' ascending, and by 'b' descending to handle overlap correctly
    Array.Sort(nn, (x, y) => {
      int c = x.a.CompareTo(y.a);
      if (c == 0)
        c = y.b.CompareTo(x.b); // Descending b
      return c;
    });

    List<int> ll = new() { nn[0].i }; // Start with first element's index

    for (int i = 1, max = nn[0].b, next = -1; i < n; next = -1) {
      // Find the next compatible segment that doesn't overlap too much
      while (i < n && nn[i].a <= max) {
        if (next == -1 || nn[next].b < nn[i].b)
          next = i; // Update next with better (higher b) candidate
        i++;
      }

      if (next == -1) {
        // No valid candidate found; add current one
        ll.Add(nn[i].i);
        max = nn[i].b;
      } else {
        // Add candidate if it improves our score
        if (nn[next].b > max) {
          ll.Add(nn[next].i);
          max = nn[next].b;
        }
      }
    }

    writer.WriteLine(ll.Count);
    foreach (var idx in ll) {
      writer.Write(idx);
      writer.Write(' ');
    }
    writer.WriteLine();
  }

  static void Main(string[] args) {
    long t = Next();
    for (int i = 0; i < t; i++)
      Solve();
    writer.Flush();
  }

  static int Next() {
    int c;
    int m = 1;
    int res = 0;
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

  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/