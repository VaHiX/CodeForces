using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using static System.Array;
using static System.Console;
using static System.Math;

namespace Olymp
{
  public class ProblemSolver
  {
    private readonly Tokenizer input;
    private readonly TextWriter output;

    private static bool IsGenerate(int[] p)
    {
      var n = p.Length;
      var ind = new int[n + 1];
      for (int i = 0; i < n; i++)
        ind[p[i]] = i;
      int r = n;
      int j = 1;
      while (j <= n)
      {
        int k0 = ind[j];
        int k = k0;
        while (k < r)
        {
          if (p[k] != j)
            return false;
          k++;
          j++;
        }
        r = k0;
      }
      return true;
    }
    
    public void Solve()
    {
      var t = input.ReadInt();
      var ans = new List<string>(t);
      for (int _ = 0; _ < t; _++)
      {
        var n = input.ReadInt();
        var p = input.ReadIntArray(n);
        ans.Add(IsGenerate(p) ? "Yes" : "No");
      }
      output.WriteLine(string.Join(Environment.NewLine, ans));
    }

    public ProblemSolver(TextReader input, TextWriter output)
    {
      this.input = new Tokenizer(input);
      this.output = output;
    }
  }

  #region Service classes

  public class Tokenizer
  {
    private readonly TextReader reader;

    private readonly StringBuilder tokenBuilder = new StringBuilder();

    public string ReadToEnd() => reader.ReadToEnd();

    public int ReadInt()
    {
      var c = SkipWs();
      if (c == -1)
        throw new EndOfStreamException();
      var isNegative = false;
      if (c == '-' || c == '+')
      {
        isNegative = c == '-';
        c = reader.Read();
        if (c == -1)
          throw new EndOfStreamException("Digit expected, but end of stream occurs");
      }

      if (!char.IsDigit((char)c))
        throw new InvalidOperationException($"Digit expected, but was: '{(char)c}'");

      checked
      {
        var result = (char)c - '0';
        c = reader.Read();
        while (c > 0 && !char.IsWhiteSpace((char)c))
        {
          if (!char.IsDigit((char)c))
            throw new InvalidOperationException($"Digit expected, but was: '{(char)c}'");
          result = result * 10 + (char)c - '0';
          c = reader.Read();
        }

        if (isNegative)
          result = -result;
        return result;
      }
    }

    public string ReadLine() => reader.ReadLine();
    
    public long ReadLong() => long.Parse(ReadToken());

    public double ReadDouble() => double.Parse(ReadToken(), CultureInfo.InvariantCulture);

    public (int, int) Read2Int() => (ReadInt(), ReadInt());

    public (int, int, int) Read3Int() => (ReadInt(), ReadInt(), ReadInt());

    public (int, int, int, int) Read4Int() => (ReadInt(), ReadInt(), ReadInt(), ReadInt());

    public (long, long) Read2Long() => (ReadLong(), ReadLong());

    public int[] ReadIntArray(int n) => ReadArray(n, ReadInt);

    public long[] ReadLongArray(int n) => ReadArray(n, ReadLong);

    public double[] ReadDoubleArray(int n) => ReadArray(n, ReadDouble);

    public string ReadToken()
    {
      var c = SkipWs();
      if (c == -1)
        return null;
      tokenBuilder.Clear();
      while (c > 0 && !char.IsWhiteSpace((char)c))
      {
        tokenBuilder.Append((char)c);
        c = reader.Read();
      }
      return tokenBuilder.ToString();
    }

    private int SkipWs()
    {
      var c = reader.Read();
      if (c == -1)
        return c;
      while (c > 0 && char.IsWhiteSpace((char)c))
        c = reader.Read();
      return c;
    }
    
    private static T[] ReadArray<T>(int n, Func<T> readFunc)
    {
      var a = new T[n];
      for (var i = 0; i < n; i++)
        a[i] = readFunc();
      return a;
    }

    public Tokenizer(TextReader reader)
    {
      this.reader = reader;
    }
  }

  internal static class Program
  {
    private const int BufferSize = 1024 * 10;

    public static void Main()
    {
      using var reader = new StreamReader(OpenStandardInput(BufferSize), Encoding.ASCII, false, BufferSize);
      using var writer = new StreamWriter(OpenStandardOutput(BufferSize), Encoding.ASCII, BufferSize);
      var solver = new ProblemSolver(reader, writer);
      solver.Solve();
    }
  }

  #endregion
}
