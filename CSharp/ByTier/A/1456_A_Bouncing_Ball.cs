// Problem: CF 1456 A - Bouncing Ball
// https://codeforces.com/contest/1456/problem/A

/*
Algorithm: Greedy with Sliding Window
Time Complexity: O(n)
Space Complexity: O(k)

The problem requires finding the minimum time to make a level passable by either:
1. Adding platforms to empty cells
2. Removing the first cell (reducing n) and renumbering cells

Key insights:
- We need platforms at positions: p, p+k, p+2k, p+3k, ...
- These positions form a pattern based on modulo k
- For each possible number of cells to remove (0 to n-p), we compute the cost
- The cost is: (removals * y) + (number of missing platforms * x)
- We maintain a count of missing platforms for each modulo class and update it as we slide the window
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Text;
using System.Linq;
using E = System.Linq.Enumerable;
using System.Threading;
internal partial class Solver {
  public void Run() {
    var t = ni();
    while (t-- > 0) {
      var n = ni();
      var p = ni();
      var k = ni();
      var a = ns();
      var x = ni();
      var y = ni();
      cout.WriteLine(Solve(n, p, k, a, x, y));
    }
  }
  private long Solve(int n, int p, int k, string a, int x, int y) {
    p--;
    // Count of missing platforms for each modulo class (0 to k-1)
    var zero = new int[k];
    for (int i = p; i < n; i++) {
      if (a[i] == '0')
        zero[i % k]++;
    }
    long ans = long.MaxValue;
    long removeCost = 0;
    // Try all possible numbers of removals from 0 to (n - p)
    for (int i = p; i < n; i++) {
      // Calculate cost to add platforms needed for current window
      var addCost = zero[i % k] * 1L * x;
      ans = Math.Min(ans, addCost + removeCost);
      removeCost += y;
      if (a[i] == '0')
        zero[i % k]--;
    }
    return ans;
  }
}
static public class StringExtensions {
  static public string JoinToString<T>(this IEnumerable<T> source,
                                       string separator = " ") {
    return string.Join(separator, source);
  }
}
internal partial class Solver : Scanner {
  static readonly int? StackSizeInMebiByte = null;
  public static void StartAndJoin(Action action, int maxStackSize) {
    var thread = new Thread(new ThreadStart(action), maxStackSize);
    thread.Start();
    thread.Join();
  }
  public static void Main() {
#if LOCAL
    byte[] inputBuffer = new byte[1000000];
    var inputStream = Console.OpenStandardInput(inputBuffer.Length);
    using (var reader = new StreamReader(inputStream, Console.InputEncoding,
                                         false, inputBuffer.Length)) {
      Console.SetIn(reader);
      new Solver(Console.In, Console.Out).Run();
    }
#else
    Console.SetOut(
        new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false });
    if (StackSizeInMebiByte.HasValue) {
      StartAndJoin(() => new Solver(Console.In, Console.Out).Run(),
                   StackSizeInMebiByte.Value * 1024 * 1024);
    } else {
      new Solver(Console.In, Console.Out).Run();
    }
    Console.Out.Flush();
#endif
  }
#pragma warning disable IDE0052
  private readonly TextReader cin;
  private readonly TextWriter cout;
  private readonly TextWriter cerr;
#pragma warning restore IDE0052
  public Solver(TextReader reader, TextWriter writer) : base(reader) {
    cin = reader;
    cout = writer;
    cerr = Console.Error;
  }
  public Solver(string input, TextWriter writer)
      : this(new StringReader(input), writer) {}
#pragma warning disable IDE1006
#pragma warning disable IDE0051
  private int ni() { return NextInt(); }
  private int[] ni(int n) { return NextIntArray(n); }
  private long nl() { return NextLong(); }
  private long[] nl(int n) { return NextLongArray(n); }
  private double nd() { return NextDouble(); }
  private double[] nd(int n) { return NextDoubleArray(n); }
  private string ns() { return Next(); }
  private string[] ns(int n) { return NextArray(n); }
#pragma warning restore IDE1006
#pragma warning restore IDE0051
}
#if DEBUG
internal static class LinqPadExtension {
  public static string TextDump<T>(this T obj) {
    if (obj is IEnumerable)
      return (obj as IEnumerable).Cast<object>().JoinToString().Dump();
    else
      return obj.ToString().Dump();
  }
  public static T Dump<T>(this T obj) { return LINQPad.Extensions.Dump(obj); }
}
#endif
public class Scanner {
  private readonly TextReader Reader;
  private readonly CultureInfo ci = CultureInfo.InvariantCulture;
  private readonly char[] buffer = new char[2 * 1024];
  private int cursor = 0, length = 0;
  private string Token;
  private readonly StringBuilder sb = new StringBuilder(1024);
  public Scanner() : this(Console.In) {}
  public Scanner(TextReader reader) { Reader = reader; }
  public int NextInt() { return checked((int)NextLong()); }
  public long NextLong() {
    var s = Next();
    long r = 0;
    int i = 0;
    bool negative = false;
    if (s[i] == '-') {
      negative = true;
      i++;
    }
    for (; i < s.Length; i++) {
      r = r * 10 + (s[i] - '0');
#if DEBUG
      if (!char.IsDigit(s[i]))
        throw new FormatException();
#endif
    }
    return negative ? -r : r;
  }
  public double NextDouble() { return double.Parse(Next(), ci); }
  public string[] NextArray(int size) {
    string[] array = new string[size];
    for (int i = 0; i < size; i++) {
      array[i] = Next();
    }
    return array;
  }
  public int[] NextIntArray(int size) {
    int[] array = new int[size];
    for (int i = 0; i < size; i++) {
      array[i] = NextInt();
    }
    return array;
  }
  public long[] NextLongArray(int size) {
    long[] array = new long[size];
    for (int i = 0; i < size; i++) {
      array[i] = NextLong();
    }
    return array;
  }
  public double[] NextDoubleArray(int size) {
    double[] array = new double[size];
    for (int i = 0; i < size; i++) {
      array[i] = NextDouble();
    }
    return array;
  }
  public string Next() {
    if (Token == null) {
      if (!StockToken()) {
        throw new Exception();
      }
    }
    var token = Token;
    Token = null;
    return token;
  }
  public bool HasNext() {
    if (Token != null) {
      return true;
    }
    return StockToken();
  }
  private bool StockToken() {
    while (true) {
      sb.Clear();
      while (true) {
        if (cursor >= length) {
          cursor = 0;
          if ((length = Reader.Read(buffer, 0, buffer.Length)) <= 0) {
            break;
          }
        }
        var c = buffer[cursor++];
        if (33 <= c && c <= 126) {
          sb.Append(c);
        } else {
          if (sb.Length > 0)
            break;
        }
      }
      if (sb.Length > 0) {
        Token = sb.ToString();
        return true;
      }
      return false;
    }
  }
}


// https://github.com/VaHiX/CodeForces/