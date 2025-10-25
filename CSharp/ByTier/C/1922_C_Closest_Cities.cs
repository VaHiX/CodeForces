// Problem: CF 1922 C - Closest Cities
// https://codeforces.com/contest/1922/problem/C

﻿/*
Purpose: 
This code solves the problem of finding the minimum cost to travel between cities, where each city has a unique closest city. The cost calculation considers two types of moves:
1. Moving directly to any city with cost equal to the distance
2. Moving to the closest city with cost 1 coin

The approach uses precomputation to compute minimum costs from the left and right sides, and then answers queries in O(1) time.

Algorithms/Techniques:
- Preprocessing with dynamic programming
- Two-pass computation: forward and backward
- Binary search or direct mapping for closest city identification

Time Complexity: O(n + m) per test case, where n is number of cities and m is number of queries
Space Complexity: O(n) for storing city positions, cost arrays, and reverse cost arrays

*/
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
namespace Test {
class IOHelper : IDisposable {
  StreamReader reader;
  StreamWriter writer;
  public IOHelper(string inputFile, string outputFile, Encoding encoding) {
    StreamReader iReader;
    StreamWriter oWriter;
    if (inputFile == null)
      iReader = new StreamReader(Console.OpenStandardInput(), encoding);
    else
      iReader = new StreamReader(inputFile, encoding);
    if (outputFile == null)
      oWriter = new StreamWriter(Console.OpenStandardOutput(), encoding);
    else
      oWriter = new StreamWriter(outputFile, false, encoding);
    reader = iReader;
    writer = oWriter;
    curLine = new string[] {};
    curTokenIdx = 0;
  }
  string[] curLine;
  int curTokenIdx;
  char[] whiteSpaces = new char[] { ' ', '\t', '\r', '\n' };
  public string ReadNextToken() {
    if (curTokenIdx >= curLine.Length) {
      string line = reader.ReadLine();
      if (line != null)
        curLine =
            line.Split(whiteSpaces, StringSplitOptions.RemoveEmptyEntries);
      else
        curLine = new string[] {};
      curTokenIdx = 0;
    }
    if (curTokenIdx >= curLine.Length)
      return null;
    return curLine[curTokenIdx++];
  }
  public int ReadNextInt() { return int.Parse(ReadNextToken()); }
  public double ReadNextDouble() {
    var nextToken = ReadNextToken();
    var result = 0.0;
    nextToken = nextToken.Replace(
        ".", System.Threading.Thread.CurrentThread.CurrentCulture.NumberFormat
                 .NumberDecimalSeparator);
    result = double.Parse(nextToken);
    return result;
  }
  public void Write(string stringToWrite) { writer.Write(stringToWrite); }
  public void WriteLine(string stringToWrite) {
    writer.WriteLine(stringToWrite);
  }
  public void WriteLine(double valueToWrite) {
    writer.WriteLine(valueToWrite.ToString("F8"));
  }
  public void Dispose() {
    try {
      if (reader != null) {
        reader.Dispose();
      }
      if (writer != null) {
        writer.Dispose();
      }
    } catch {
    };
  }
  public void Flush() {
    if (writer != null) {
      writer.Flush();
    }
  }
}
class Program {
  protected IOHelper ioHelper;
  int t, n, m;
  int[] city = new int[100002]; // Store city coordinates
  int[] cost = new int[100002];  // Cost from left to right
  int[] revcost = new int[100002]; // Cost from right to left
  int closest(int c) {
    // Find closest city to city c
    if (c == 0)
      return 1;
    if (c == n - 1)
      return n - 2;
    // Compare distances to neighbors
    if (city[c] - city[c - 1] > city[c + 1] - city[c])
      return c + 1;
    else
      return c - 1;
  }
  public void Solve() {
    t = ioHelper.ReadNextInt();
    while (t > 0) {
      n = ioHelper.ReadNextInt();
      int i;
      // Initialize arrays
      for (i = 0; i < n; i++) {
        cost[i] = revcost[i] = -1;
        city[i] = ioHelper.ReadNextInt();
      }
      // Precompute costs from left to right
      cost[0] = 0;
      for (i = 1; i < n; i++) {
        // If the closest city of city i-1 is i, cost increases by 1
        if (closest(i - 1) == i)
          cost[i] = cost[i - 1] + 1;
        else
          // Otherwise, it's direct cost which is distance
          cost[i] = cost[i - 1] + city[i] - city[i - 1];
      }
      // Precompute costs from right to left
      revcost[n - 1] = 0;
      for (i = n - 2; i >= 0; i--) {
        // If the closest city of city i+1 is i, cost increases by 1
        if (closest(i + 1) == i)
          revcost[i] = revcost[i + 1] + 1;
        else
          // Otherwise, it's direct cost which is distance
          revcost[i] = revcost[i + 1] + city[i + 1] - city[i];
      }
      m = ioHelper.ReadNextInt();
      while (m > 0) {
        int x = ioHelper.ReadNextInt();
        int y = ioHelper.ReadNextInt();
        x--;
        y--;
        if (x == y)
          ioHelper.WriteLine("0");
        else if (y > x)
          // If we move from x to right (y > x) use forward cost
          ioHelper.WriteLine((cost[y] - cost[x]).ToString());
        else
          // If we move from x to left (y < x) use backward cost
          ioHelper.WriteLine((revcost[y] - revcost[x]).ToString());
        m--;
      }
      t--;
    }
    ioHelper.Flush();
  }
  public Program(string inputFile, string outputFile) {
    ioHelper = new IOHelper(inputFile, outputFile, Encoding.Default);
    Solve();
    ioHelper.Dispose();
  }
  static void Main(string[] args) {
    Program myProgram = new Program(null, null);
  }
}
}


// https://github.com/VaHiX/CodeForces/