// Problem: CF 2039 C1 - Shohag Loves XOR (Easy Version)
// https://codeforces.com/contest/2039/problem/C1

/*
Algorithm: Brute Force with Optimization
Time Complexity: O(x * log(m)) where x <= 10^6 and m <= 10^18
Space Complexity: O(1)

Approach:
- For each possible y from 1 to min(m, 2*x), we compute x⊕y
- We check if the result is a divisor of either x or y (or both)
- Since the XOR result must divide x or y, and x⊕y = z, we check z | x or z | y
- Optimization: loop until y < 2*x, because larger y values won't produce meaningful XOR results within the bounds
*/

using Lib;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using static Lib.OutputLib;
public class Solver {
  const bool MultiTestCase = true;
  void Solve() {
    int x = ri;
    long m = rl;
    int n = 1;
    while (n <= x)
      n *= 2;
    long ans = 0;
    for (int y = 1; y < n && y <= m; y++) {
      if (y == x)
        continue;
      int z = x ^ y;  // Compute XOR of x and y
      if (x % z == 0 || y % z == 0)  // Check if z divides x or y
        ans++;
    }
    Write(ans);
  }
#pragma warning disable CS0162
  public Solver() {
    if (!MultiTestCase)
      Solve();
    else
      for (int t = ri; t > 0; t--)
        Solve();
  }
#pragma warning restore CS0162
  const int IINF = 1 << 30;
  const long INF = 1L << 60;
  int ri {
    [MethodImpl(256)]
    get => (int)sc.Integer();
  }
  long rl {
    [MethodImpl(256)]
    get => sc.Integer();
  }
  uint rui {
    [MethodImpl(256)]
    get => (uint)sc.UInteger();
  }
  ulong rul {
    [MethodImpl(256)]
    get => sc.UInteger();
  }
  double rd {
    [MethodImpl(256)]
    get => sc.Double();
  }
  string rs {
    [MethodImpl(256)]
    get => sc.Scan();
  }
  string rline {
    [MethodImpl(256)]
    get => sc.Line();
  }
  public StreamScanner sc = new StreamScanner(Console.OpenStandardInput());
  void ReadArray(out int[] a, int n) {
    a = new int[n];
    for (int i = 0; i < a.Length; i++)
      a[i] = ri;
  }
  void ReadArray(out long[] a, int n) {
    a = new long[n];
    for (int i = 0; i < a.Length; i++)
      a[i] = rl;
  }
  void ReadArray<T>(out T[] a, int n, Func<T> read) {
    a = new T[n];
    for (int i = 0; i < a.Length; i++)
      a[i] = read();
  }
  void ReadArray<T>(out T[] a, int n, Func<int, T> read) {
    a = new T[n];
    for (int i = 0; i < a.Length; i++)
      a[i] = read(i);
  }
}
static class Program {
  static public void Main(string[] args) {
    SourceExpander.Expander.Expand();
    Console.SetOut(
        new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false });
    new Solver();
    Console.Out.Flush();
  }
}
#region Expanded by https:
namespace Lib {
public partial class StreamScanner {
  public StreamScanner(Stream stream) { str = stream; }
  private readonly Stream str;
  private readonly byte[] buf = new byte[1024];
  private int len, ptr;
  public bool isEof = false;
  public bool IsEndOfStream {
    get { return isEof; }
  }
  [MethodImpl(256)]
  private byte Read() {
    if (isEof)
      throw new EndOfStreamException();
    if (ptr >= len) {
      ptr = 0;
      if ((len = str.Read(buf, 0, 1024)) <= 0) {
        isEof = true;
        return 0;
      }
    }
    return buf[ptr++];
  }
  [MethodImpl(256)]
  public char Char() {
    byte b;
    do
      b = Read();
    while (b < 33 || 126 < b);
    return (char)b;
  }
  [MethodImpl(256)]
  public string Line() {
    var sb = new StringBuilder();
    for (var b = Char(); b != 10 && !isEof; b = (char)Read())
      sb.Append(b);
    return sb.ToString();
  }
  [MethodImpl(256)]
  public string Scan() {
    var sb = new StringBuilder();
    for (var b = Char(); b >= 33 && b <= 126; b = (char)Read())
      sb.Append(b);
    return sb.ToString();
  }
  [MethodImpl(256)]
  public long Integer() {
    long ret = 0;
    var ng = false;
    byte b;
    do
      b = Read();
    while (b != '-' && (b < '0' || '9' < b));
    if (b == '-') {
      ng = true;
      b = Read();
    }
    for (; '0' <= b && b <= '9'; b = Read())
      ret = ret * 10 + (b ^ '0');
    return ng ? -ret : ret;
  }
  [MethodImpl(256)]
  public ulong UInteger() {
    ulong ret = 0;
    byte b;
    do
      b = Read();
    while (b < '0' || '9' < b);
    for (; '0' <= b && b <= '9'; b = Read())
      ret = ret * 10 + (ulong)(b ^ '0');
    return ret;
  }
  [MethodImpl(256)]
  public double Double() => double.Parse(Scan());
}
}
namespace Lib {
public static class OutputLib {
  [MethodImpl(256)]
  public static void WriteJoin<T>(string s, IEnumerable<T> t) =>
      Console.WriteLine(string.Join(" ", t.Select(x => x.ToString())));
  [MethodImpl(256)]
  public static void WriteMat<T>(T[][] a, string sep = " ") {
    foreach (var ar in a)
      WriteJoin(sep, ar);
  }
  [MethodImpl(256)]
  public static void WriteMat<T>(T[][] a, Func<T, string> map,
                                 string sep = " ") {
    foreach (var ar in a)
      WriteJoin(sep, ar.Select(x => map(x)));
  }
  [MethodImpl(256)]
  public static void Write(object t) => Console.WriteLine(t.ToString());
  [MethodImpl(256)]
  public static void Write(params object[] arg) =>
      Console.WriteLine(string.Join(" ", arg.Select(x => x.ToString())));
  [MethodImpl(256)]
  public static void Write(string str) => Console.WriteLine(str);
  [MethodImpl(256)]
  public static void WriteFlush(object t) {
    Console.WriteLine(t.ToString());
    Console.Out.Flush();
  }
  [MethodImpl(256)]
  public static void
  WriteError(object t) => Console.Error.WriteLine(t.ToString());
  [MethodImpl(256)]
  public static void Flush() => Console.Out.Flush();
  [MethodImpl(256)]
  public static void YN(bool t) => Console.WriteLine(t ? "YES" : "NO");
  [MethodImpl(256)]
  public static void Yn(bool t) => Console.WriteLine(t ? "Yes" : "No");
  [MethodImpl(256)]
  public static void yn(bool t) => Console.WriteLine(t ? "yes" : "no");
  [MethodImpl(256)]
  public static void DeleteLine() => Console.Write("\x1b[1A\x1b[2K");
  [MethodImpl(256)]
  public static void ProgressBar(long now, long total, int blocks = 50) {
    int x = (int)((2 * now * blocks + 1) / (2 * total));
    Console.Write(
        $"\x1b[G[\x1b[42m{string.Concat(Enumerable.Repeat("_",x))}\x1b[0m{string.Concat(Enumerable.Repeat("_",blocks-x))}] : {now} / {total}");
  }
}
}
namespace SourceExpander {
public class Expander {
  [Conditional("EXP")]
  public static void Expand(string inputFilePath = null,
                            string outputFilePath = null,
                            bool ignoreAnyError = true) {}
  public static string ExpandString(string inputFilePath = null,
                                    bool ignoreAnyError = true) {
    return "";
  }
}
}
#endregion Expanded by https:


// https://github.com/VaHiX/CodeForces/