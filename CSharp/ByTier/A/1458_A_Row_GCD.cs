// Problem: CF 1458 A - Row GCD
// https://codeforces.com/contest/1458/problem/A

/*
Algorithm: Row GCD
Approach:
1. For each b_j, we need to compute GCD of (a_1 + b_j), ..., (a_n + b_j).
2. Key insight: GCD of a_1 + b_j, ..., a_n + b_j equals GCD of differences of a_i + b_j, i.e.
   GCD of (a_i + b_j) - (a_k + b_j) = GCD of (a_i - a_k).
3. If we sort a[], the GCD of all differences (a_i - a_k) is the same as GCD of consecutive differences.
4. We find this GCD of differences (let's denote it as gcd_diff), then for each b_j:
   - We compute the remainder mod gcd_diff of any a_i.
   - Then GCD of (b_j + remainder) and gcd_diff gives the final answer.
Time Complexity: O(n log n + m log(max(a_i)))
Space Complexity: O(n + m)

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
  public static long Gcd(long s, long t) { return t != 0 ? Gcd(t, s % t) : s; }
  public void Run() {
    var n = ni();
    var m = ni();
    var a = nl(n);
    var b = nl(m);
    var ans = new List<long>();
    a = a.Distinct().ToArray(); // Remove duplicates to reduce computation
    n = a.Length;
    Array.Sort(a); // Sort to compute consecutive differences
    if (n == 1) {
      foreach (var x in b) {
        ans.Add(x + a[0]); // If only one element, just add to each b_j
      }
    } else {
      var gcd = 0L;
      for (int i = 0; i + 1 < n; i++) {
        gcd = Gcd(gcd, Math.Abs(a[i + 1] - a[i])); // Compute GCD of differences
      }
      var mod = a.Select(x => x % gcd).Distinct().Single(); // Get remainder of any element
      foreach (var x in b) {
        ans.Add(Gcd(gcd, x + mod)); // Final GCD calculation
      }
    }
    cout.WriteLine(ans.JoinToString(" "));
  }
}
static public class StringExtensions {
  static public string JoinToString<T>(this IEnumerable<T> source,
                                       string separator = " ") {
    return string.Join(separator, source);
  }
}
internal partial class Solver : Scanner {
  static readonly int? StackSizeInMebiByte = 50;
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