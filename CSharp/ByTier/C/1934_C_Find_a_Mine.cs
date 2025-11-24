// Problem: CF 1934 C - Find a Mine
// https://codeforces.com/contest/1934/problem/C

/*
 * Problem: Find a Mine (Interactive)
 * 
 * Algorithm/Technique: 
 * - Use queries at strategic positions to determine the location of one mine
 * - Strategy involves querying corners (1,1) and (n,1) to establish initial constraints
 * - If either query returns 0, we've found a mine directly
 * - Otherwise, based on Manhattan distances, deduce candidate positions for mines
 * - Use additional queries to narrow down to the exact position
 * 
 * Time Complexity: O(1) - constant number of queries (at most 4)
 * Space Complexity: O(1) - only using a constant amount of extra space
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
  int t, n, m;
  int query(int x, int y) {
    ioHelper.WriteLine($"? {x} {y}");
    ioHelper.Flush();
    return ioHelper.ReadNextInt();
  }
  void ans(int x, int y) {
    ioHelper.WriteLine($"! {x} {y}");
    ioHelper.Flush();
  }
  public void Solve() {
    t = ioHelper.ReadNextInt();
    while (t-- > 0) {
      n = ioHelper.ReadNextInt();
      m = ioHelper.ReadNextInt();
      int r1 = query(1, 1); // Query top-left corner
      if (r1 == 0) {
        ans(1, 1);
        continue;
      }
      int r2 = query(n, 1); // Query bottom-left corner
      if (r2 == 0) {
        ans(n, 1);
        continue;
      }
      bool bDiff = false;
      int y_targ = r1 + r2 + 3 - n; // Calculate target y coordinate
      if (y_targ % 2 > 0)
        bDiff = true; // Check if target coordinates are odd
      y_targ /= 2;   // Divide to get target y
      int x_targ = r1 + 2 - y_targ; // Calculate target x coordinate
      if (x_targ < 1 || x_targ > n || y_targ < 1 || y_targ > m)
        bDiff = true; // Check bounds
      if (!bDiff) { // If target coordinates are valid
        int q1 = query(x_targ, y_targ); // Query target point
        if (q1 == 0) {
          ans(x_targ, y_targ);
          continue;
        }
        if (q1 % 2 > 0)
          throw new Exception(); // If distance is odd, something unexpected happened
        q1 /= 2; // Divide by 2 to get distance from target
        int xcand1 = x_targ - q1; // Candidate x1
        int ycand = y_targ + q1; // Candidate y (both candidates are on the same diagonal)
        int xcand2 = x_targ + q1; // Candidate x2
        if (xcand1 >= 1 && xcand1 <= n && query(xcand1, ycand) == 0) {
          ans(xcand1, ycand); // If first candidate has distance 0, it's a mine
          continue;
        } else {
          ans(xcand2, ycand); // Otherwise the second one is the mine
          continue;
        }
      } else { // If coordinates are odd, handle different case
        int xq = 1;
        int yq = r1 + 1; // Calculate different starting point
        if (yq > m) { // Adjust if needed
          xq += yq - m;
          yq = m;
        }
        int q2 = query(xq, yq); // Query this point
        if (q2 == 0) {
          ans(xq, yq);
          continue;
        }
        if (q2 % 2 > 0)
          throw new Exception(); // Unexpected case
        q2 /= 2; // Half the distance
        int xcand = xq + q2; // Calculate candidate x
        int ycand = yq - q2; // Calculate candidate y
        ans(xcand, ycand); // Output the result
        continue;
      }
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