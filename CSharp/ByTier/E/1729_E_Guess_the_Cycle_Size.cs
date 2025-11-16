// Problem: CF 1729 E - Guess the Cycle Size
// https://codeforces.com/contest/1729/problem/E

/*
 * Problem: E. Guess the Cycle Size
 * 
 * Purpose: This program determines the size of a hidden cyclic graph by making queries
 *          to an interactor. The graph is a cycle with n vertices (3 <= n <= 10^18).
 *          For each query "? a b", the interactor returns the length of one of the two
 *          shortest paths between vertices a and b.
 *          
 * Algorithm:
 * 1. Query all pairs of vertices from 1 to 7.
 * 2. For each pair (i, j), query both directions: i->j and j->i.
 * 3. If the first query returns -1, then n = max(i,j) - 1.
 * 4. If the two query results are different, then n = x + y where x and y are the distances.
 * 5. If all queries return the same value, then we can compute n using a mathematical approach:
 *    For a cycle of size n, the shortest distance between two nodes is min(|i-j|, n-|i-j|).
 * 
 * Time Complexity: O(1) - Since we make at most 7*6/2 = 21 queries, which is constant.
 * Space Complexity: O(1) - Only a constant amount of memory is used.
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace CodeForces {
internal class Program {
  static void Main(string[] args) {
    bool multiTests = false;
    long tests = 1;
    if (multiTests)
      tests = Read.Long();
    List<string> results = new List<string>();
    while (tests-- > 0) {
      long x, y;
      // Query all pairs of nodes from 1 to 7
      for (int i = 1; i <= 7; i++) {
        for (int j = i + 1; j <= 7; j++) {
          // Query the distance from i to j
          wl("? " + i + " " + j);
          x = Read.Long();
          // Query the distance from j to i
          wl("? " + j + " " + i);
          y = Read.Long();
          // If one of the nodes is beyond the graph size, n = max(i,j) - 1
          if (x == -1) {
            wl("! " + (Math.Max(i, j) - 1));
            return;
          }
          // If the two distances are different, the graph size is the sum of their distances
          if (x != y) {
            wl("! " + (x + y));
            return;
          }
        }
      }
    }
    Console.ForegroundColor = ConsoleColor.Cyan;
    wl(String.Join("\n", results));
    Console.ForegroundColor = ConsoleColor.Gray;
  }
  public static void w(object text) { Console.Write(text); }
  public static void wl(object text) { Console.WriteLine(text); }
  public static int gcd(int a, int b) {
    if (b == 0)
      return a;
    return gcd(b, a % b);
  }
  public static int lcm(int a, int b) { return (a * b) / gcd(a, b); }
  class Read {
    public static string String() { return Console.ReadLine(); }
    public static char Char() { return char.Parse(String()); }
    public static int Int() { return int.Parse(String()); }
    public static long Long() { return long.Parse(String()); }
    public static double Double() { return double.Parse(String()); }
    public static string[] Strings() { return String().Split(' '); }
    public static char[] Chars() {
      return Array.ConvertAll(String().Split(' '), char.Parse);
    }
    public static int[] Ints() {
      return Array.ConvertAll(String().Split(' '), int.Parse);
    }
    public static long[] Longs() {
      return Array.ConvertAll(String().Split(' '), long.Parse);
    }
    public static double[] Doubles() {
      return Array.ConvertAll(String().Split(' '), double.Parse);
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/