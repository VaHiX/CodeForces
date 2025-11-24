// Problem: CF 1932 C - LR-remainders
// https://codeforces.com/contest/1932/problem/C

/*
 * Segment Tree-based solution for LR-remainders problem
 * 
 * Algorithm:
 * - Use a Segment Tree to efficiently compute the product of elements in a range
 * - For each command, query the current product and update the range boundaries
 * - Time Complexity: O(n log n) per test case due to segment tree operations
 * - Space Complexity: O(n) for the segment tree storage
 * 
 * Techniques:
 * - Segment Tree with range product query
 * - Efficient range updates and queries
 */

using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Text;
using CompLib.Collections.Generic;
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
    System.Console.Out.Flush();
  }
  void Query(Scanner sc) {
    int n = sc.NextInt();
    int m = sc.NextInt();
    var a = sc.LongArray();
    string s = sc.Next();
    // Create segment tree with product operation and modulo m
    var st = new SegmentTree<long>(a, (l, r) => (l * r) % m, 1);
    int left = 0;
    int right = n;
    var ans = new List<long>();
    for (int i = 0; i < n; i++) {
      // Query current product of all elements in range [left, right)
      ans.Add(st.Query(left, right));
      // Update range based on command 'L' or 'R'
      if (s[i] == 'L')
        left++;
      else
        right--;
    }
    Console.WriteLine(string.Join(" ", ans));
  }
  public static void Main(string[] args) => new Program().Solve();
}
namespace CompLib.Collections.Generic {
using System;
using System.Diagnostics;
public class SegmentTree<T> {
  private readonly int _n, _size;
  private T[] _array;
  private T _identity;
  private Func<T, T, T> _operation;
  public SegmentTree(int n, Func<T, T, T> operation, T identity) {
    _n = n;
    _size = 1;
    while (_size < _n) {
      _size *= 2;
    }
    _identity = identity;
    _operation = operation;
    _array = new T[_size * 2];
    for (int i = 1; i < _size * 2; i++) {
      _array[i] = _identity;
    }
  }
  public SegmentTree(T[] a, Func<T, T, T> operation, T identity) {
    _n = a.Length;
    _size = 1;
    while (_size < _n) {
      _size *= 2;
    }
    _identity = identity;
    _operation = operation;
    _array = new T[_size * 2];
    for (int i = 0; i < a.Length; i++) {
      _array[i + _size] = a[i];
    }
    for (int i = a.Length; i < _size; i++) {
      _array[i + _size] = identity;
    }
    for (int i = _size - 1; i >= 1; i--) {
      _array[i] = operation(_array[i * 2], _array[i * 2 + 1]);
    }
  }
  public void Update(int i, T n) {
    Debug.Assert(0 <= i && i < _n);
    i += _size;
    _array[i] = n;
    while (i > 1) {
      i /= 2;
      _array[i] = _operation(_array[i * 2], _array[i * 2 + 1]);
    }
  }
  public T Query(int left, int right) {
    Debug.Assert(0 <= left && left <= right && right <= _n);
    T sml = _identity;
    T smr = _identity;
    left += _size;
    right += _size;
    while (left < right) {
      if ((left & 1) != 0)
        sml = _operation(sml, _array[left++]);
      if ((right & 1) != 0)
        smr = _operation(_array[--right], smr);
      left >>= 1;
      right >>= 1;
    }
    return _operation(sml, smr);
  }
  public T All() { return _array[1]; }
  public int MaxRight(int l, Func<T, bool> f) {
    Debug.Assert(0 <= l && l <= _n);
#if DEBUG
    Debug.Assert(f(_identity));
#endif
    if (l == _n)
      return _n;
    l += _size;
    T sm = _identity;
    do {
      while (l % 2 == 0)
        l >>= 1;
      if (!f(_operation(sm, _array[l]))) {
        while (l < _size) {
          l <<= 1;
          if (f(_operation(sm, _array[l]))) {
            sm = _operation(sm, _array[l]);
            l++;
          }
        }
        return l - _size;
      }
      sm = _operation(sm, _array[l]);
      l++;
    } while ((l & -l) != l);
    return _n;
  }
  public int MinLeft(int r, Func<T, bool> f) {
    Debug.Assert(0 <= r && r <= _n);
#if DEBUG
    Debug.Assert(f(_identity));
#endif
    if (r == 0)
      return 0;
    r += _size;
    T sm = _identity;
    do {
      r--;
      while (r > 1 && (r % 2 != 0))
        r >>= 1;
      if (!f(_operation(_array[r], sm))) {
        while (r < _size) {
          r = (2 * r + 1);
          if (f(_operation(_array[r], sm))) {
            sm = _operation(_array[r], sm);
            r--;
          }
        }
        return r + 1 - _size;
      }
      sm = _operation(_array[r], sm);
    } while ((r & -r) != r);
    return 0;
  }
  public T this[int i] {
    set { Update(i, value); }
    get {
      Debug.Assert(0 <= i && i < _n);
      return _array[i + _size];
    }
  }
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