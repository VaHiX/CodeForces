// Problem: CF 2149 E - Hidden Knowledge of the Ancients
// https://codeforces.com/contest/2149/problem/E

/*
E. Hidden Knowledge of the Ancients

Algorithm: Two Pointers + Sliding Window
Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

The problem asks to count the number of continuous subarrays that contain exactly k distinct numbers and have length between l and r (inclusive).

Approach:
1. Use two sliding windows:
   - First window (map0, cnt0): finds the rightmost position where we have exactly k distinct elements.
   - Second window (map1, cnt1): finds the rightmost position where we have at most k distinct elements.
2. For each left pointer (i), we determine how many valid subarrays can start from index i:
   - The left boundary l of valid range is max(i + L - 1, r0 - 1)
   - The right boundary r of valid range is min(i + R, cnt1 == K ? r1 : r1 - 1)
   - Add (r - l) to answer if l <= r.

The two-pointer technique ensures that we process each element at most twice, making the time complexity linear.
*/

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

  private int N, K, L, R;
  private int[] A;

  void Query(Scanner sc) {
    checked {
      N = sc.NextInt();
      K = sc.NextInt();
      L = sc.NextInt();
      R = sc.NextInt();
      A = sc.IntArray();

      // Two pointers to maintain sliding windows
      int r0 = 0;   // Right of window with exactly K distinct elements
      int r1 = 0;   // Right of window with at most K distinct elements
      var map0 = new HashMap<int, int>(); // Frequency map for first window
      var map1 = new HashMap<int, int>(); // Frequency map for second window
      int cnt0 = 0; // Number of distinct elements in first window
      int cnt1 = 0; // Number of distinct elements in second window

      long ans = 0;

      // Iterate over all possible left boundaries (i)
      for (int i = 0; i < N; i++) {
        // Expand r0 until we have exactly K distinct elements
        while (r0 < N && cnt0 < K) {
          if (map0[A[r0]]++ == 0) // If this element was not present before
            cnt0++;               // Increase distinct count
          r0++;
        }

        // Expand r1 until we have at most K distinct elements
        while (r1 < N && cnt1 <= K) {
          if (map1[A[r1]]++ == 0)
            cnt1++;
          r1++;
        }

        // If we have exactly K distinct elements in the current window starting from i
        if (cnt0 == K) {
          int l = Math.Max(i + L - 1, r0 - 1);   // Left boundary of valid range
          int r = Math.Min(i + R, cnt1 == K ? r1 : r1 - 1); // Right boundary of valid range

          // If valid range exists, add to answer
          if (l <= r)
            ans += r - l;
        }

        // Shrink windows by removing the element at index i
        if (--map0[A[i]] == 0)
          cnt0--;
        if (--map1[A[i]] == 0)
          cnt1--;
      }

      Console.WriteLine(ans);
    }
  }

  public static void Main(string[] args) => new Program().Solve();
}

namespace CompLib.Collections {
  using System.Collections.Generic;

  public class HashMap<TKey, TValue> : Dictionary<TKey, TValue> {
    public HashMap(IEqualityComparer<TKey> comparer) : base(comparer) {}
    public HashMap(int capacity) : base(capacity) {}
    public HashMap(int capacity, IEqualityComparer<TKey> comparer)
        : base(capacity, comparer) {}
    public HashMap() : base() {}

    public new TValue this[TKey key] {
      get {
        TValue o;
        return TryGetValue(key, out o) ? o : default(TValue);
      }
      set { base[key] = value; }
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