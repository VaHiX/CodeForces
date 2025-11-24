// Problem: CF 1769 C2 - Подкрутка II
// https://codeforces.com/contest/1769/problem/C2

namespace AcmSolution4 {
using System;
using System.Collections.Generic;
using System.Linq;
namespace ConsoleApplication {
internal class Solver {
  public void Solve() {
    var tests = GetInt();
    while (--tests >= 0) {
      var a = FillArray();
      a.Add(0);
      a.Add(0);
      int max = 0;
      int i = 0;
      while (i < a.Count) {
        if (a[i] == 0) {
          ++i;
          continue;
        }
        int sum = Math.Abs(a[i]);
        if (a[i] > 0)
          sum++;
        while (a[i + 2] > 0) {
          sum += (a[i + 2] + 1);
          i += 2;
        }
        sum += Math.Abs(a[i + 2]);
        max = Math.Max(max, sum);
        ++i;
      }
      WL(max);
    }
  }
  private List<int> FillArray() {
    var n = GetInt();
    var q = GetInts();
    var a = new int[1000239];
    int i;
    for (i = 0; i < n; ++i) {
      a[q[i]]++;
    }
    var b = new List<int>();
    i = 0;
    while (i < a.Length) {
      int cnt = 0;
      bool mult = false;
      while (a[i] > 0) {
        mult |= a[i] > 1;
        ++i;
        cnt++;
      }
      if (cnt > 0) {
        if (!mult)
          cnt *= -1;
        b.Add(cnt);
      }
      cnt = 0;
      while (i < a.Length && a[i] == 0) {
        ++i;
        cnt++;
      }
      b.Add(0);
      if (cnt >= 2)
        b.Add(0);
    }
    return b;
  }
#region Utils
  private const double Epsilon = 0.00000001;
  private static int GetNextInt() {
    int i = 0;
    int sign = 1;
    bool ok = false;
    while (true) {
      var c = Console.In.Read();
      if (c == '-') {
        ok = true;
        sign = -1;
      } else if ('0' <= c && c <= '9') {
        ok = true;
        i = i * 10 + (c - '0');
      } else if (ok)
        break;
    }
    return sign * i;
  }
  private static string GetStr() { return Console.ReadLine(); }
  private static string[] GetStrs() {
    return GetStr().Split(new[] { ' ', '\t' },
                          StringSplitOptions.RemoveEmptyEntries);
  }
  private static string[] GetStrs(int cnt) {
    var s = new string[cnt];
    for (var i = 0; i < cnt; ++i)
      s[i] = GetStr();
    return s;
  }
  private static int GetInt() { return Int32.Parse(GetStr()); }
  private static long GetLong() { return Int64.Parse(GetStr()); }
  private static void GetInts(out int a, out int b) {
    var q = GetInts();
    a = q[0];
    b = q[1];
  }
  private static void GetInts(out int a, out int b, out int c) {
    var q = GetInts();
    a = q[0];
    b = q[1];
    c = q[2];
  }
  private static void GetLongs(out long a, out long b, out long c) {
    var q = GetLongs();
    a = q[0];
    b = q[1];
    c = q[2];
  }
  private static void WriteDouble<T>(T d) {
    Console.WriteLine(string.Format("{0:0.000000000}", d).Replace(',', '.'));
  }
  private static int[] GetInts() {
    var s = GetStrs();
    var a = new int[s.Length];
    for (var i = 0; i < s.Length; ++i)
      a[i] = Int32.Parse(s[i]);
    return a;
  }
  private static long[] GetLongs() {
    return GetStrs().Select(Int64.Parse).ToArray();
  }
  private static void WL<T>(T s) { Console.WriteLine(s); }
  private static void W<T>(T s) { Console.Write(s); }
  private static void Assert(bool b) {
    if (!b)
      throw new Exception();
  }
  private static void Swap<T>(ref T a, ref T b) {
    var temp = a;
    a = b;
    b = temp;
  }
#endregion
}
public class Program {
  public static void Assert(bool b) {
    if (!b)
      throw new Exception();
  }
  static void Main(string[] args) { new Solver().Solve(); }
}
}
}


// https://github.com/VaHiX/CodeForces/