// Problem: CF 1929 E - Sasha and the Happy Tree Cutting
// https://codeforces.com/contest/1929/problem/E

﻿/*
Algorithm/Techniques: 
- This solution uses a tree dynamic programming approach to find the minimum set of edges that covers all required vertex pairs.
- The algorithm builds a rooted tree and performs post-order traversal to compute the "color coverage" for each subtree.
- Each vertex's left and right color coverage represents which pairs of vertices are covered by paths going through the respective subtrees.
- The final step involves finding the minimum number of edges to cover all k pairs using bit manipulation and dynamic programming.

Time Complexity: O(n + k * 2^k) where n is the number of vertices and k is the number of pairs.
Space Complexity: O(n + 2^k) for storing tree structure and DP states.
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
public class RootedTreeIn0 {
  public class Node {
    public int parent;
    public List<int> children = new List<int>();
    public int myLeftColor = -1;
    public int myRightColor = -1;
    public uint leftComplexColor = 0;
    public uint rightComplexColor = 0;
  }
  public Node[] nodes;
  public RootedTreeIn0(int n) {
    nodes = new Node[n];
    int i;
    for (i = 0; i < n; i++)
      nodes[i] = new Node();
  }
  public void AddEdge(int i, int j) {
    nodes[i].children.Add(j);
    nodes[j].children.Add(i);
  }
  public void Init() {
    Tuple<int, int, int> pos = new Tuple<int, int, int>(0, -1, 0);
    Stack<Tuple<int, int, int>> stack = new Stack<Tuple<int, int, int>>();
    stack.Push(pos);
    while (stack.Count > 0) {
      var poped = stack.Pop();
      var node = poped.Item1;
      var parent = poped.Item2;
      var nextChildIdx = poped.Item3;
      if (nextChildIdx < nodes[node].children.Count)
        if (nodes[node].children[nextChildIdx] == parent)
          nextChildIdx++;
      if (nextChildIdx < nodes[node].children.Count) {
        stack.Push(new Tuple<int, int, int>(node, parent, nextChildIdx + 1));
        stack.Push(new Tuple<int, int, int>(nodes[node].children[nextChildIdx],
                                            node, 0));
      } else {
        uint zTotLeft = nodes[node].leftComplexColor;
        uint zTotRight = nodes[node].rightComplexColor;
        foreach (var child in nodes[node].children)
          if (child != parent) {
            var leftBelowchild = nodes[child].leftComplexColor;
            var rightBelowchild = nodes[child].rightComplexColor;
            var bothBelowChild =
                nodes[child].leftComplexColor & nodes[child].rightComplexColor;
            var notBothBelowChild = ~bothBelowChild;
            var zLeft = leftBelowchild & notBothBelowChild;
            var zRight = rightBelowchild & notBothBelowChild;
            var zTotal = zLeft | zRight;
            zTotLeft |= zLeft;
            zTotRight |= zRight;
            zTotLeft &= notBothBelowChild;
            zTotRight &= notBothBelowChild;
            numbers.Add(zTotal);
          }
        if (parent != -1) {
          nodes[parent].leftComplexColor |= zTotLeft;
          nodes[parent].rightComplexColor |= zTotRight;
        }
      }
    }
  }
  public HashSet<uint> numbers = new HashSet<uint>();
}
class Program {
  protected IOHelper ioHelper;
  int t, n, k;
  public void Solve() {
    t = ioHelper.ReadNextInt();
    while (t-- > 0) {
      n = ioHelper.ReadNextInt();
      int i, a, b;
      RootedTreeIn0 myTree = new RootedTreeIn0(n);
      for (i = 1; i < n; i++) {
        a = ioHelper.ReadNextInt() - 1;
        b = ioHelper.ReadNextInt() - 1;
        myTree.AddEdge(a, b);
      }
      uint target = 0;
      k = ioHelper.ReadNextInt();
      for (i = 0; i < k; i++) {
        target |= 1U << i;
        a = ioHelper.ReadNextInt() - 1;
        b = ioHelper.ReadNextInt() - 1;
        myTree.nodes[a].leftComplexColor |= 1U << i;
        myTree.nodes[b].rightComplexColor |= 1U << i;
      }
      myTree.Init();
      int res = 0;
      uint current = 0;
      HashSet<uint> numbers = new HashSet<uint>();
      HashSet<uint> newNumbers = new HashSet<uint>();
      numbers.Add(0);
      int[] best = new int[1 << k];
      foreach (var num in myTree.numbers) {
        newNumbers.Clear();
        foreach (var oldNum in numbers) {
          if (!newNumbers.Contains(oldNum | num))
            newNumbers.Add(oldNum | num);
          if ((oldNum | num) != 0) {
            if (best[oldNum | num] == 0 ||
                best[oldNum | num] > best[oldNum] + 1)
              best[oldNum | num] = best[oldNum] + 1;
          }
        }
        foreach (var nn in newNumbers)
          numbers.Add(nn);
      }
      res = best[target];
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