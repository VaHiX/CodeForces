// Problem: CF 1894 B - Two Out of Three
// https://codeforces.com/contest/1894/problem/B

﻿/*
Algorithm: Two Out of Three
Approach:
1. Initialize all elements of array b to 1
2. For each element in array a, find the last occurrence of that value
3. If the current index is not the last occurrence and the value hasn't been processed yet,
   assign the next available number (2 or 3) to the last occurrence
4. If we managed to assign numbers to satisfy exactly two conditions, output the array
   otherwise output -1

Time Complexity: O(n^2) - due to the LastIndexOf operation which takes O(n) time
Space Complexity: O(n) - to store the arrays a and b

Techniques:
- Greedy approach to assign values to satisfy exactly two conditions
- Use of LastIndexOf to find last occurrence of an element
- Counter to track when exactly two conditions are satisfied
*/

﻿using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Numerics;
class Program {
  private static void Main(string[] args) {
    var t = RI();
    while (t-- > 0) {
      var n = RI();
      var a = RIA(n);
      var b = new int[n];
      for (int i = 0; i < n; i++)
        b[i] = 1;
      int next = 2;
      var qwe = -1;
      for (int i = 0; i < n; i++) {
        var j = Array.LastIndexOf(a, a[i]);  // Find last occurrence of a[i]
        if (i != j && a[i] != qwe && next <= 3) {  // If not last occurrence, value not processed yet and we can assign next number
          b[j] = next;  // Assign next available number (2 or 3)
          next++;
          qwe = a[i];   // Mark this value as processed
        }
      }
      if (next == 4) {  // If we successfully assigned values to satisfy exactly two conditions
        Console.WriteLine(string.Join(" ", b));
      } else
        Console.WriteLine(-1);
    }
  }
  private const int Mod = 1000000000 + 7;
#region Data Read
  private static int GCD(int a, int b) {
    if (a % b == 0)
      return b;
    return GCD(b, a % b);
  }
  private static List<int>[] ReadTree(int n) { return ReadGraph(n, n - 1); }
  private static List<int>[] ReadGraph(int n, int m) {
    List<int>[] g = new List<int>[n];
    for (int i = 0; i < g.Length; i++)
      g[i] = new List<int>();
    for (int i = 0; i < m; i++) {
      int a = RI() - 1;
      int b = RI() - 1;
      g[a].Add(b);
      g[b].Add(a);
    }
    return g;
  }
  private static int[,] ReadGraphAsMatrix(int n, int m) {
    int[,] matrix = new int[n + 1, n + 1];
    for (int i = 0; i < m; i++) {
      int a = RI();
      int b = RI();
      matrix[a, b] = matrix[b, a] = 1;
    }
    return matrix;
  }
  private static void Sort(ref int a, ref int b) {
    if (a > b)
      Swap(ref a, ref b);
  }
  private static void Swap(ref int a, ref int b) {
    int tmp = a;
    a = b;
    b = tmp;
  }
  private const int BufferSize = 1 << 16;
  private static StreamReader consoleReader;
  private static MemoryStream testData;
  private static int RI() {
    int ans = 0;
    int mul = 1;
    do {
      ans = consoleReader.Read();
      if (ans == -1)
        return 0;
      if (ans == '-')
        mul = -1;
    } while (ans < '0' || ans > '9');
    ans -= '0';
    while (true) {
      int chr = consoleReader.Read();
      if (chr < '0' || chr > '9')
        return ans * mul;
      ans = ans * 10 + chr - '0';
    }
  }
  private static ulong RUL() {
    ulong ans = 0;
    int chr;
    do {
      chr = consoleReader.Read();
      if (chr == -1)
        return 0;
    } while (chr < '0' || chr > '9');
    ans = (uint)(chr - '0');
    while (true) {
      chr = consoleReader.Read();
      if (chr < '0' || chr > '9')
        return ans;
      ans = ans * 10 + (uint)(chr - '0');
    }
  }
  private static long RL() {
    long ans = 0;
    int mul = 1;
    do {
      ans = consoleReader.Read();
      if (ans == -1)
        return 0;
      if (ans == '-')
        mul = -1;
    } while (ans < '0' || ans > '9');
    ans -= '0';
    while (true) {
      int chr = consoleReader.Read();
      if (chr < '0' || chr > '9')
        return ans * mul;
      ans = ans * 10 + chr - '0';
    }
  }
  private static int[] RIA(int n) {
    int[] ans = new int[n];
    for (int i = 0; i < n; i++)
      ans[i] = RI();
    return ans;
  }
  private static long[] RLA(int n) {
    long[] ans = new long[n];
    for (int i = 0; i < n; i++)
      ans[i] = RL();
    return ans;
  }
  private static char[] ReadString(int n) {
    int ans;
    do {
      ans = consoleReader.Read();
    } while (!((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z')));
    char[] s = new char[n];
    int pos = 0;
    do {
      s[pos++] = (char)ans;
      if (pos == n)
        break;
      ans = consoleReader.Read();
    } while ((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z'));
    return s;
  }
  private static char[] ReadStringLine() {
    int ans;
    do {
      ans = consoleReader.Read();
    } while (ans == 10 || ans == 13);
    List<char> s = new List<char>();
    do {
      s.Add((char)ans);
      ans = consoleReader.Read();
    } while (ans != 10 && ans != 13 && ans != -1);
    return s.ToArray();
  }
  private static char ReadLetter() {
    while (true) {
      int ans = consoleReader.Read();
      if ((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z'))
        return (char)ans;
    }
  }
  private static char ReadNonLetter() {
    while (true) {
      int ans = consoleReader.Read();
      if (!((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z')))
        return (char)ans;
    }
  }
  private static char ReadAnyOf(IEnumerable<char> allowed) {
    while (true) {
      char ans = (char)consoleReader.Read();
      if (allowed.Contains(ans))
        return ans;
    }
  }
  private static char ReadDigit() {
    while (true) {
      int ans = consoleReader.Read();
      if (ans >= '0' && ans <= '9')
        return (char)ans;
    }
  }
  private static int ReadDigitInt() { return ReadDigit() - (int)'0'; }
  private static char ReadAnyChar() { return (char)consoleReader.Read(); }
  private static string DoubleToString(double x) {
    return x.ToString(CultureInfo.InvariantCulture);
  }
  private static double DoubleFromString(string x) {
    return double.Parse(x, CultureInfo.InvariantCulture);
  }
  static Program() {
    consoleReader = new StreamReader(Console.OpenStandardInput(BufferSize),
                                     Encoding.ASCII, false, BufferSize);
  }
  private static void PushTestData(StringBuilder sb) {
    PushTestData(sb.ToString());
  }
  private static void PushTestData(string data) {
#if TOLYAN_TEST
    if (testData == null) {
      testData = new MemoryStream();
      consoleReader = new StreamReader(testData);
    }
    var pos = testData.Length;
    var bytes = Encoding.UTF8.GetBytes(data);
    testData.Write(bytes, 0, bytes.Length);
    testData.Flush();
    testData.Position = pos;
#endif
  }
#endregion
}


// https://github.com/VaHiX/CodeForces/