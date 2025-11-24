// Problem: CF 1879 C - Make it Alternating
// https://codeforces.com/contest/1879/problem/C

﻿/*
Algorithm: Greedy + Combinatorics
Approach:
1. First, we identify consecutive blocks of same characters.
2. For each block of same characters, we need to remove all but one character to make it alternating.
3. The number of operations needed is the total number of characters minus the number of blocks.
4. For counting arrangements:
   - For each block of size k, we can choose any one character to keep (k choices).
   - For the total permutations of removals, we multiply by factorial of operations.

Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(1) - Only using constant extra space.
*/
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
class Program {
  private static void Main(string[] args) {
    var t = RI();
    while (t-- > 0) {
      var s = ReadStringLine();
      var toRemove = 0;
      var answer = 1L;
      var blockSize = 1;
      for (int i = 1; i < s.Length; i++) {
        if (s[i] == s[i - 1]) {
          blockSize++;
          toRemove++; // Increment the count of characters to remove
        }
        if (s[i] != s[i - 1] || i == (s.Length - 1)) {
          answer = (answer * blockSize) % 998244353L; // Multiply by choices for current block
          blockSize = 1; // Reset block size
        }
      }
      // Multiply by factorial of operations (permutations of removals)
      for (int i = 1; i <= toRemove; i++)
        answer = (answer * i) % 998244353L;
      Console.WriteLine(toRemove + " " + answer);
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
  private static char[] ReadWord() {
    int ans;
    do {
      ans = consoleReader.Read();
    } while (!((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z') ||
               (ans == '*')));
    List<char> s = new List<char>();
    do {
      s.Add((char)ans);
      ans = consoleReader.Read();
    } while ((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z') ||
             (ans == '*'));
    return s.ToArray();
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