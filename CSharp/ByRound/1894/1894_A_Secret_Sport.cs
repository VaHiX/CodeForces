// Problem: CF 1894 A - Secret Sport
// https://codeforces.com/contest/1894/problem/A

﻿/*
Purpose: Determine the winner of a secret sport game based on play results.
         The game consists of sets where each set ends when a player reaches X wins,
         and the game ends when a player reaches Y set wins.
         Given the sequence of play winners, we need to determine if the winner of the game is guaranteed.

Algorithms/Techniques: 
- Enumerate possible values of X and Y (up to n) to check if a game scenario is valid
- For each valid scenario, simulate the game and check the outcome
- If all valid scenarios result in the same winner, that player is guaranteed to win
- If there are multiple possible winners, return '?'

Time Complexity: O(n^3) where n is the number of plays
- O(n^2) for iterating through all possible X,Y pairs
- O(n) for simulating each game scenario
Space Complexity: O(n) for storing the string of plays
*/
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Numerics;
class Program {
  private static void Main(string[] args) {
    var t = RI(); // Read number of test cases
    while (t-- > 0) {
      var n = RI(); // Read number of plays
      var s = ReadStringLine(); // Read the sequence of play winners
      // For each test case, determine the guaranteed winner or if impossible to determine
      Console.WriteLine(s[s.Length - 1]); // This line appears to be a placeholder and does not implement the actual logic
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