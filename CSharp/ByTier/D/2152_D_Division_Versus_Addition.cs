// Problem: CF 2152 D - Division Versus Addition
// https://codeforces.com/contest/2152/problem/D

// Problem: D. Division Versus Addition
// Purpose: For each query range [l,r], compute the minimum number of moves Poby makes in a two-player game where:
//          - Poby splits numbers by floor division (x -> x/2) to reduce them to 1
//          - Rekkles increments numbers by 1 to increase them
//          - Game ends when all elements are 1
//          - Both play optimally
// Time Complexity: O(n + q * log(max(a_i))) 
// Space Complexity: O(n)
using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Text;
using CompLib.Collections;

public class Program {
  public void Solve() {
    var sc = new Scanner();
#if !DEBUG
    System.Console.SetOut(new System.IO.StreamWriter(
        System.Console.OpenStandardOutput()) { AutoFlush = false });
#endif
    int t = sc.NextInt();
    for (int i = 0; i < t; i++) {
      Query(sc);
    }
    Console.Out.Flush();
  }

  // Process each query: compute the value of a subarray from l to r
  void Query(Scanner sc) {
    int n = sc.NextInt();
    int q = sc.NextInt();
    int[] a = sc.IntArray();
    
    // Precompute prefix sums for different categories:
    // CuSum of lg(num) values for each element (number of divisions needed)
    var cusumLg = new CuSum(a.Select(num => Lg(num)).ToArray());
    // CuSum of 1s if num is B-type, else 0 (B = numbers of form 2^k + 1)
    var cusumB = new CuSum(a.Select(num => IsB(num) ? 1 : 0).ToArray());
    // CuSum of 1s if num is C-type (neither A nor B), else 0 
    var cusumC = new CuSum(a.Select(num => IsC(num) ? 1 : 0).ToArray());
    
    for (int i = 0; i < q; i++) {
      int l = sc.NextInt() - 1;
      int r = sc.NextInt();
      
      // Query result is the sum of:
      // 1. Total division steps (sum of lg(x) over range)
      // 2. Half number of B-type numbers (rounded down since Poby and Rekkles alternate)
      // 3. Number of C-type numbers (always full count)
      Console.WriteLine(cusumLg.Query(l, r) + cusumB.Query(l, r) / 2 +
                        cusumC.Query(l, r));
    }
  }

  // Is a number B-type? (a number that can be formed as 2^k + 1 for k >= 0)
  bool IsB(int num) {
    if (num == 2)
      return false;
    return ((num - 1) & (num - 2)) == 0; // Check if there's exactly one bit set in (num-1) 
  }

  // Is a number A-type? (a power of 2)
  bool IsA(int num) { return (num & (num - 1)) == 0; }

  // Is a number C-type? (neither A-type nor B-type)
  bool IsC(int num) { return !IsA(num) && !IsB(num); }

  // Calculate lg(num) = floor(log2(num)) 
  int Lg(int num) {
    int ans = 0;
    while (num > 1) {
      ans++;
      num /= 2;
    }
    return ans;
  }

  public static void Main(string[] args) => new Program().Solve();
}

namespace CompLib.Collections {
using System;
using Num = Int32;

namespace Generic {
public class CuSum<T> {
  private readonly int Count;
  private readonly T[] _sum;
  private readonly Func<T, T, T> _op;
  private readonly Func<T, T> _inv;
  private readonly T _e;
  
  public CuSum(T[] array, Func<T, T, T> op, Func<T, T> inv, T e) {
    Count = array.Length;
    _sum = new T[Count + 1];
    _op = op;
    _inv = inv;
    _e = e;
    _sum[0] = _e;
    for (int i = 0; i < Count; i++) {
      _sum[i + 1] = _op(_sum[i], array[i]);
    }
  }

  public T Query(int r) { return _sum[r]; }
  public T Query(int l, int r) { return _op(Query(r), _inv(Query(l))); }
}
}

// Generic prefix sum implementation for integers
public class CuSum {
  private readonly int Count;
  private readonly Num[] _sum;

  public CuSum(Num[] array) {
    Count = array.Length;
    _sum = new Num[Count + 1];
    for (int i = 0; i < Count; i++) {
      _sum[i + 1] = _sum[i] + array[i];
    }
  }

  public Num Query(int r) { return _sum[r]; }
  public Num Query(int l, int r) { return Query(r) - Query(l); }
}
}

namespace CompLib.Util {
using System;
using System.Linq;

class Scanner {
  private string[] _line;
  private int _index;
  private const char Separator = ' ';
  
  public Scanner() {
    _line = new string[0];
    _index = 0;
  }
  
  public string Next() {
    if (_index >= _line.Length) {
      string s;
      do {
        s = Console.ReadLine();
      } while (s.Length == 0);
      _line = s.Split(Separator);
      _index = 0;
    }
    return _line[_index++];
  }
  
  public string ReadLine() {
    _index = _line.Length;
    return Console.ReadLine();
  }
  
  public int NextInt() => int.Parse(Next());
  public long NextLong() => long.Parse(Next());
  public ulong NextULong() => ulong.Parse(Next());
  public double NextDouble() => double.Parse(Next());
  public decimal NextDecimal() => decimal.Parse(Next());
  public char NextChar() => Next()[0];
  public char[] NextCharArray() => Next().ToCharArray();
  
  public string[] Array() {
    string s = Console.ReadLine();
    _line = s.Length == 0 ? new string[0] : s.Split(Separator);
    _index = _line.Length;
    return _line;
  }
  
  public int[] IntArray() => Array().AsParallel().Select(int.Parse).ToArray();
  public long[] LongArray() =>
      Array().AsParallel().Select(long.Parse).ToArray();
  public ulong[] ULongArray() =>
      Array().AsParallel().Select(ulong.Parse).ToArray();
  public double[] DoubleArray() =>
      Array().AsParallel().Select(double.Parse).ToArray();
  public decimal[] DecimalArray() =>
      Array().AsParallel().Select(decimal.Parse).ToArray();
}
}


// https://github.com/VaHiX/CodeForces/