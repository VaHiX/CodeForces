// Problem: CF 1923 D - Slimes
// https://codeforces.com/contest/1923/problem/D

﻿/*
Algorithm: Slime Eating Process Simulation
Techniques: 
- Prefix sums for range sum queries
- Binary search to find optimal eating positions
- Preprocessing for left and right equal elements count
- Greedy approach to determine minimum time for each slime to be eaten

Time Complexity: O(n log n) per test case due to binary search operations
Space Complexity: O(n) for storing arrays and prefix sums

This solution processes each slime to find the minimum time it takes to be eaten
by considering all possible ways the process can proceed. It uses prefix sums to
efficiently calculate sums of segments and binary search to find optimal eating positions.
*/
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
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
  int t, n;
  long[] prefSum = new long[400004]; // Prefix sum array for range sum queries
  int[] a = new int[400004]; // Array to store slime sizes
  int[] numLeftEqual = new int[400004]; // Count of consecutive equal elements from left
  int[] numRightEqual = new int[400004]; // Count of consecutive equal elements from right
  public void Solve() {
    t = ioHelper.ReadNextInt();
    while (t-- > 0) {
      n = ioHelper.ReadNextInt();
      a[0] = ioHelper.ReadNextInt();
      prefSum[0] = a[0];
      numLeftEqual[0] = 1;
      int leftElem = a[0];
      int i;
      for (i = 1; i < n; i++) {
        a[i] = ioHelper.ReadNextInt();
        prefSum[i] = prefSum[i - 1] + a[i];
        numLeftEqual[i] = numLeftEqual[i - 1] + 1;
        if (leftElem != a[i])
          numLeftEqual[i] = 1;
        leftElem = a[i];
      }
      numRightEqual[n - 1] = 1;
      int rightElem = a[n - 1];
      for (i = n - 2; i >= 0; i--) {
        numRightEqual[i] = numRightEqual[i + 1] + 1;
        if (rightElem != a[i])
          numRightEqual[i] = 1;
        rightElem = a[i];
      }
      for (i = 0; i < n; i++) {
        int l = 0, r = i - 1;
        if (i > 0)
          r = i - 1 - numLeftEqual[i - 1]; // Optimization: skip consecutive equal elements
        int optLeft = -1;
        while (l <= r) {
          int mid = (l + r) / 2;
          var valAtMid = prefSum[i - 1];
          if (mid > 0)
            valAtMid -= prefSum[mid - 1]; // Calculate sum from mid to i-1
          if (valAtMid > a[i]) {
            optLeft = mid;
            l = mid + 1;
          } else {
            r = mid - 1;
          }
        }
        if (optLeft >= 0)
          optLeft = i - optLeft; // Convert to time
        int optRight = -1;
        l = i + 1;
        r = n - 1;
        if (i < n - 1)
          l = i + 1 + numRightEqual[i + 1]; // Optimization: skip consecutive equal elements
        while (l <= r) {
          int mid = (l + r) / 2;
          var valAtMid = prefSum[mid] - prefSum[i]; // Calculate sum from i+1 to mid
          if (valAtMid > a[i]) {
            optRight = mid;
            r = mid - 1;
          } else {
            l = mid + 1;
          }
        }
        if (optRight >= 0)
          optRight = optRight - i; // Convert to time
        int opt = optLeft;
        if (optRight >= 0)
          if (optRight < opt || opt == -1)
            opt = optRight;
        if (i > 0)
          if (a[i - 1] > a[i])
            opt = 1; // Direct neighbor eating
        if (i < n - 1)
          if (a[i + 1] > a[i])
            opt = 1; // Direct neighbor eating
        ioHelper.Write($"{opt.ToString()} ");
      }
      ioHelper.WriteLine("");
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