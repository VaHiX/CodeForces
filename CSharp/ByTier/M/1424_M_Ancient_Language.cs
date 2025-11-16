// Problem: CF 1424 M - Ancient Language
// https://codeforces.com/contest/1424/problem/M

/*
Algorithm: Topological Sorting (Kahn's Algorithm)
Purpose: Reconstruct the alien alphabet from a dictionary of words by determining the order of letters based on their lexical ordering.

Time Complexity: O(n * m * L + V + E)
- n: number of pages
- m: number of words per page
- L: average length of words
- V: number of vertices in graph (26 for alphabet)
- E: number of edges (comparisons between letters)

Space Complexity: O(V^2 + n * m * L)
- V^2 for adjacency matrix (26x26)
- n * m * L for storing all words
*/

using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
public class Solution {
  public void Solve() {
    int n = ReadInt(); // Read number of pages
    int m = ReadInt(); // Read number of words per page
    var a = new List<(int, string[])>(); // Store pages with their word lists
    for (int i = 0; i < n; i++) {
      int x = ReadInt(); // Read page number
      var lines = ReadLines(m); // Read m words from page
      a.Add((x, lines)); // Add page data to list
    }
    a.Sort((a1, a2) => a1.Item1.CompareTo(a2.Item1)); // Sort pages by their numbers
    
    // Flatten all words into a single array
    var b = new string[n * m];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        b[i * m + j] = a[i].Item2[j];
        
    // Build directed graph of letter relationships
    var g = new bool[26, 26]; // Adjacency matrix for graph
    var f = new bool[26]; // Track which letters are present in the dictionary
    
    // Mark all letters that are used in the dictionary
    for (int i = 0; i < n * m; i++)
      foreach (char c in b[i])
        f[c - 'a'] = true;
        
    // Determine letter order by comparing adjacent words
    for (int i = 0; i + 1 < n * m; i++) {
      for (int j = 0; j < b[i].Length; j++) {
        // If we've gone past the end of next word, invalid dictionary
        if (j >= b[i + 1].Length) {
          Write("IMPOSSIBLE");
          return;
        } else if (b[i][j] != b[i + 1][j]) {
          // Add directed edge: b[i][j] -> b[i+1][j]
          g[b[i][j] - 'a', b[i + 1][j] - 'a'] = true;
          break; // Stop comparing once we find first different character
        }
      }
    }
    
    // Calculate in-degrees of all vertices (letters)
    var deg = new int[26];
    for (int i = 0; i < 26; i++)
      for (int j = 0; j < 26; j++)
        if (g[i, j])
          deg[j]++;
          
    // Topological sort using Kahn's algorithm
    var q = new Queue<int>(); // Queue for nodes with zero in-degree
    var ans = new StringBuilder(); // Resulting alphabet
    
    // Initialize queue with all letters having zero in-degree
    for (int i = 0; i < 26; i++)
      if (f[i] && deg[i] == 0) {
        q.Enqueue(i); // Add node to queue
        f[i] = false; // Mark as visited
        ans.Append((char)(i + 'a')); // Add to result
      }
      
    // Process nodes in topological order
    while (q.Count > 0) {
      int x = q.Dequeue(); // Get a node with zero in-degree
      for (int i = 0; i < 26; i++)
        if (f[i] && g[x, i]) {
          deg[i]--; // Decrease in-degree of neighbors
          if (deg[i] == 0) { // If in-degree becomes zero
            f[i] = false; // Mark as visited
            q.Enqueue(i); // Add to queue
            ans.Append((char)(i + 'a')); // Add to result
          }
        }
    }
    
    // Check for cycles in graph (if any node still has in-degree > 0)
    if (deg.Any(dd => dd > 0)) {
      Write("IMPOSSIBLE");
      return;
    }
    
    Write(ans); // Output the reconstructed alphabet
  }
#region Main
  protected static TextReader reader;
  protected static TextWriter writer;
  static void Main() {
#if DEBUGLOCAL
    reader = new StreamReader("..\\..\\input.txt");
    writer = Console.Out;
#else
    reader = new StreamReader(Console.OpenStandardInput());
    writer = new StreamWriter(Console.OpenStandardOutput());
#endif
    try {
      new Solution().Solve();
    } catch (Exception ex) {
#if DEBUG
      Console.WriteLine(ex);
#else
      throw;
#endif
    }
    reader.Close();
    writer.Close();
  }
#endregion
#region Read / Write
  private static Queue<string> currentLineTokens = new Queue<string>();
  private static string[] ReadAndSplitLine() {
    return reader.ReadLine().Split(
        new[] {
          ' ',
          '\t',
        },
        StringSplitOptions.RemoveEmptyEntries);
  }
  public static string ReadToken() {
    while (currentLineTokens.Count == 0)
      currentLineTokens = new Queue<string>(ReadAndSplitLine());
    return currentLineTokens.Dequeue();
  }
  public static int ReadInt() { return int.Parse(ReadToken()); }
  public static long ReadLong() { return long.Parse(ReadToken()); }
  public static double ReadDouble() {
    return double.Parse(ReadToken(), CultureInfo.InvariantCulture);
  }
  public static int[] ReadIntArray() {
    return ReadAndSplitLine().Select(int.Parse).ToArray();
  }
  public static long[] ReadLongArray() {
    return ReadAndSplitLine().Select(long.Parse).ToArray();
  }
  public static double[] ReadDoubleArray() {
    return ReadAndSplitLine()
        .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
        .ToArray();
  }
  public static int[][] ReadIntMatrix(int numberOfRows) {
    int[][] matrix = new int [numberOfRows][];
    for (int i = 0; i < numberOfRows; i++)
      matrix[i] = ReadIntArray();
    return matrix;
  }
  public static int[][] ReadAndTransposeIntMatrix(int numberOfRows) {
    int[][] matrix = ReadIntMatrix(numberOfRows);
    int[][] ret = new int[matrix[0].Length][];
    for (int i = 0; i < ret.Length; i++) {
      ret[i] = new int[numberOfRows];
      for (int j = 0; j < numberOfRows; j++)
        ret[i][j] = matrix[j][i];
    }
    return ret;
  }
  public static string[] ReadLines(int quantity) {
    string[] lines = new string[quantity];
    for (int i = 0; i < quantity; i++)
      lines[i] = reader.ReadLine().Trim();
    return lines;
  }
  public static void WriteArray<T>(IEnumerable<T> array) {
    writer.WriteLine(string.Join(" ", array));
  }
  public static void Write(params object[] array) { WriteArray(array); }
  public static void WriteLines<T>(IEnumerable<T> array) {
    foreach (var a in array)
      writer.WriteLine(a);
  }
  private class SDictionary<TKey, TValue> : Dictionary<TKey, TValue> {
    public new TValue this[TKey key] {
      get { return ContainsKey(key) ? base[key] : default(TValue);
  }
  set { base[key] = value; }
}
}
private static T[] Init<T>(int size)
    where T : new() {
  var ret = new T[size];
  for (int i = 0; i < size; i++)
    ret[i] = new T();
  return ret;
}
#endregion
}


// https://github.com/VaHiX/CodeForces/