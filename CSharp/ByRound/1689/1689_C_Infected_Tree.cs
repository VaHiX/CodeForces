// Problem: CF 1689 C - Infected Tree
// https://codeforces.com/contest/1689/problem/C

/*
 * Problem: C. Infected Tree
 * 
 * Algorithm: 
 * - Perform BFS traversal of the tree to calculate depths and analyze the structure.
 * - For each node, if it's not the root (has degree < 3), compute a potential saving score as 2 * depth + degree.
 * - For the root node, compute a potential saving score as 2 * depth + 1 + degree.
 * - The minimum such score across all nodes represents the minimum number of nodes that will be infected.
 * - The number of saved nodes = total nodes - minimum infected nodes.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing tree structure and BFS queue
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace CodeForces {
internal class Program {
  public static int[] depth;
  public static List<int>[] nodes;
  public static int bestV;
  static void Main(string[] args) {
    long tests = Read.Long();
    List<int> results = new List<int>();
    while (tests-- > 0) {
      int n = Read.Int();
      nodes = new List<int>[n];
      depth = new int[n];
      bestV = n;
      for (int i = 0; i < n; i++) {
        nodes[i] = new List<int>();
      }
      for (int i = 0; i < n - 1; i++) {
        List<int> a = Read.Ints().ToList();
        nodes[a[0] - 1].Add(a[1] - 1);
        nodes[a[1] - 1].Add(a[0] - 1);
      }
      Queue<int[]> q = new Queue<int[]>();
      q.Enqueue(new int[] { 0, 0, -1 });
      while (q.Count > 0) {
        var t = q.Dequeue();
        int i = t[0];
        int currentDepth = t[1];
        int parent = t[2];
        depth[i] = currentDepth;
        // Check if the current node is not the root and has degree less than 3
        if (nodes[i].Count < 3 && i != 0) {
          // Update bestV if this node offers better saving potential
          if (bestV > 2 * depth[i] + nodes[i].Count) {
            bestV = 2 * depth[i] + nodes[i].Count;
          }
        } else if (nodes[i].Count < 2 && i == 0) {
          // Special case for root node - root has degree at most 2
          if (bestV > 2 * depth[i] + 1 + nodes[i].Count) {
            bestV = 2 * depth[i] + 1 + nodes[i].Count;
          }
        }
        // Enqueue children for BFS
        nodes[i].ForEach(y => {
          if (parent != y)
            q.Enqueue(new int[] { y, currentDepth + 1, i });
        });
      }
      int o = n - bestV;
      results.Add(o);
    }
    Console.ForegroundColor = ConsoleColor.Cyan;
    Console.WriteLine(string.Join("\n", results));
    Console.ForegroundColor = ConsoleColor.Gray;
  }
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