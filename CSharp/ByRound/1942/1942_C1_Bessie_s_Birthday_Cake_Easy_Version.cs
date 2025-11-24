// Problem: CF 1942 C1 - Bessie's Birthday Cake (Easy Version)
// https://codeforces.com/contest/1942/problem/C1

/*
 * Problem: C1. Bessie's Birthday Cake (Easy Version)
 * 
 * Approach:
 * - The problem is about triangulating a polygon with given vertices.
 * - Since y=0, we can only use the x vertices chosen by Bessie.
 * - We want to maximize the number of non-intersecting triangles formed.
 * - Key idea: The number of triangles in a triangulation of a polygon with k vertices is k-2.
 * - But we're not limited to all vertices; we can choose any subset.
 * - So, we want to find the maximum number of triangles using subset of the given vertices.
 * - Sorting the vertices helps us identify contiguous segments.
 * - If we sort the vertices, the problem becomes finding segments of the polygon where we can form more triangles.
 * - The formula used: x - 2 + (number of gaps of size 2 between consecutive sorted vertices).
 * 
 * Time Complexity: O(x * log(x)) due to sorting
 * Space Complexity: O(x) for storing the list of vertices
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
  int t, n, x, y;
  List<int> givenVerts = new List<int>();
  public void Solve() {
    t = ioHelper.ReadNextInt();
    givenVerts.Capacity = 100005;
    while (t-- > 0) {
      n = ioHelper.ReadNextInt();
      x = ioHelper.ReadNextInt();
      y = ioHelper.ReadNextInt();
      givenVerts.Clear();
      int res = x - 2; // Initial count of triangles if all vertices were in one continuous segment
      int i;
      int a = -3; // Start marker for previous vertex
      for (i = 0; i < x; i++) {
        a = ioHelper.ReadNextInt();
        a--; // Convert to 0-based indexing
        givenVerts.Add(a);
      }
      givenVerts.Sort(); // Sort vertices in ascending order
      
      a = givenVerts[0]; // Reference to the first sorted vertex
      
      // Loop through sorted vertices to count gaps of exactly 2
      for (i = 1; i < x; i++) {
        int b = givenVerts[i];
        if (b - a == 2) // If the gap is exactly 2 steps
          res++; // We can form one extra triangle
        a = b; // Update a for next iteration
      }
      
      // Check if the polygon wraps around (gap between last and first vertex equals 2)
      if (givenVerts[0] + n - givenVerts[x - 1] == 2)
        res++;
        
      ioHelper.WriteLine(res.ToString());
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