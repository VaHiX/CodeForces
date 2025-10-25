// Problem: CF 1434 A - Perform Easily
// https://codeforces.com/contest/1434/problem/A

﻿/*
Algorithm: Greedy with Max-Heap (Priority Queue)
Approach:
1. Sort the string values (a) and notes (b)
2. Use a max-heap to keep track of the maximum fret used so far for each note
3. Initially place all notes on the last string (highest value in 'a')
4. Greedily move notes to earlier strings to minimize the difference
5. At each step, pop the note with the highest fret and try to reduce it by moving to a lower string
6. Track the minimum difference between max and min frets

Time Complexity: O(n * log(n) + n * log(6)) where n is number of unique notes
Space Complexity: O(n + 6) = O(n) for storing unique notes and heap
*/

using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
public class Solution {
  public class Heap<T> {
    private readonly List<T> data;
    private readonly Comparison<T> compare;
    public Heap(Comparison<T> compare) {
      this.compare = compare;
      data = new List<T> { default(T) };
    }
    public int Count {
      get { return data.Count - 1; }
    }
    public T Peek() { return data[1]; }
    public void Push(T item) {
      data.Add(item);
      var curPlace = Count;
      while (curPlace > 1 && compare(item, data[curPlace / 2]) < 0) {
        data[curPlace] = data[curPlace / 2];
        data[curPlace / 2] = item;
        curPlace /= 2;
      }
    }
    public T Pop() {
      var ret = data[1];
      data[1] = data[Count];
      data.RemoveAt(Count);
      var curPlace = 1;
      while (true) {
        var max = curPlace;
        if (Count >= curPlace * 2 && compare(data[max], data[2 * curPlace]) > 0)
          max = 2 * curPlace;
        if (Count >= curPlace * 2 + 1 &&
            compare(data[max], data[2 * curPlace + 1]) > 0)
          max = 2 * curPlace + 1;
        if (max == curPlace)
          break;
        var item = data[max];
        data[max] = data[curPlace];
        data[curPlace] = item;
        curPlace = max;
      }
      return ret;
    }
  }
  public void Solve() {
    var a = ReadIntArray();
    ReadInt();
    var b = ReadIntArray().Distinct().ToArray();
    int n = b.Length;
    Array.Sort(a);
    Array.Sort(b);
    var q = new Heap<(int, int)>((t1, t2) => t1.Item1.CompareTo(t2.Item1));
    int max = b[n - 1] - a[5]; // Initial max fret when all notes are on last string
    int ans = int.MaxValue;
    // Initially place all notes on the last string (index 5)
    for (int i = 0; i < n; i++)
      q.Push((b[i] - a[5], 5));
    while (true) {
      var t = q.Pop(); // Get note with highest fret
      ans = Math.Min(ans, max - t.Item1); // Update minimum difference
      if (t.Item2 > 0) { // If we can move to a lower string
        int v = t.Item1 += a[t.Item2] - a[t.Item2 - 1]; // Calculate new fret value
        max = Math.Max(max, v); // Update max fret
        q.Push((v, t.Item2 - 1)); // Push new state to heap
      } else
        break; // No more moves possible
    }
    Write(ans);
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