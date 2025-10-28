// Problem: CF 1544 A - Binary Decimal
// https://codeforces.com/contest/1544/problem/A

﻿/*
Purpose: 
  The task is to find the minimum number of binary decimal numbers (numbers consisting only of digits 0 and 1) that sum up to a given number n.
  The key insight is that the minimum number of such binary decimals equals the largest digit in the decimal representation of n.
  This is because each binary decimal can contribute at most 1 to any digit position when added together, so we need as many binary decimals as the maximum digit.
  
Algorithm:
  - For each test case, read the number n as a string.
  - Find the maximum digit in the string representation of n.
  - Output this maximum digit as the answer.

Time Complexity: O(|n|) where |n| is the number of digits in n, since we need to scan all digits once.
Space Complexity: O(1) - only using a constant amount of extra space.

Techniques:
  - String parsing and digit comparison
  - Using LINQ's Max() function with character conversion
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
    for (int tt = ReadInt(); tt > 0; tt--) {
      // Find the maximum digit in the input number string and output it
      Write(ReadToken().Max(
          _ => _ - '0')); // Convert each character digit to integer and find maximum
    }
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
#if DEBUGLOCAL
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