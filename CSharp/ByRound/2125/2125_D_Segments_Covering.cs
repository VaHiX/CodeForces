// Problem: CF 2125 D - Segments Covering
// https://codeforces.com/contest/2125/problem/D

/*
D. Segments Covering

Purpose:
This code calculates the probability that each cell in a linear strip of m cells is covered by exactly one segment out of n given segments.

Each segment [l,r] exists with probability p/q independently. The task is to calculate the probability that every cell is covered by exactly one segment.

Algorithms/Techniques:
- Dynamic Programming
- Modular Arithmetic (ModInt)
- Probability computation with inclusion-exclusion principle

Time Complexity: O(N * M)
Space Complexity: O(N + M)

*/

using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Text;
using CompLib.Mathematics;

public class Program {
  private int N, M;
  private (int L, int R, int P, int Q)[] S;
  public void Solve() {
    var sc = new Scanner();
    N = sc.NextInt();
    M = sc.NextInt();
    S = new(int L, int R, int P, int Q)[N];
    for (int i = 0; i < N; i++) {
      S[i] = (sc.NextInt() - 1, sc.NextInt(), sc.NextInt(), sc.NextInt()); // Convert l to 0-based index
    }
    
    // ls[r] stores all segments ending at position r with their contribution probabilities
    var ls = new List<(int l, ModInt p)>[M + 1];
    for (int i = 0; i <= M; i++) {
      ls[i] = new List<(int l, ModInt p)>();
    }
    
    // For each segment, add it to the list of segments ending at its rightmost position
    foreach ((int l, int r, int p, int q) in S) {
      ls[r].Add((l, p * ModInt.Inverse(q))); // Store probability of existence and contribution
    }
    
    // dp[i] = probability that cell i is covered by exactly one segment (and all previous cells are satisfied)
    var cnt = new ModInt[M + 1]; // Number of ways to reach position i
    var dp = new ModInt[M + 1];  // Probability of coverage at position i
    
    // Base case: empty prefix has probability 1
    cnt[0] = 1;
    dp[0] = 1;
    
    // Process each cell from 1 to M
    for (int i = 1; i <= M; i++) {
      foreach ((int l, ModInt p) in ls[i]) {
        // Update count and probability:
        // cnt[i] += cnt[l]: add all ways ending at position l to count of ways to reach position i
        // dp[i] += dp[l] * p * Inverse(1 - p): update probability for current cell using contribution from previous positions
        
        cnt[i] += cnt[l];
        dp[i] += dp[l] * p * ModInt.Inverse(1 - p);
      }
    }
    
    // Calculate the product of all probabilities that a segment does not exist
    // This is used to normalize final result
    ModInt all = 1;
    foreach ((_, _, int p, int q) in S) {
      all *= 1 - (p * ModInt.Inverse(q));
    }
    
    // The final answer is dp[M] multiplied by the normalization factor
    Console.WriteLine(dp[M] * all);
  }
  
  public static void Main(string[] args) => new Program().Solve();
}

namespace CompLib.Mathematics {
#region ModInt
public struct ModInt {
  public const long Mod = 998244353;
  public long num;
  public ModInt(long n) { num = n; }
  public override string ToString() { return num.ToString(); }
  
  public static ModInt operator +(ModInt l, ModInt r) {
    l.num += r.num;
    if (l.num >= Mod)
      l.num -= Mod;
    return l;
  }
  
  public static ModInt operator -(ModInt l, ModInt r) {
    l.num -= r.num;
    if (l.num < 0)
      l.num += Mod;
    return l;
  }
  
  public static ModInt operator *(ModInt l, ModInt r) {
    return new ModInt(l.num * r.num % Mod);
  }
  
  public static implicit operator ModInt(long n) {
    n %= Mod;
    if (n < 0)
      n += Mod;
    return new ModInt(n);
  }
  
  public static ModInt Pow(ModInt v, long k) { return Pow(v.num, k); }
  
  public static ModInt Pow(long v, long k) {
    long ret = 1;
    if (Mod == 998244353 || Mod == (long)1e9 + 7)
      k %= Mod - 1;
    for (; k > 0; k >>= 1, v = v * v % Mod)
      if ((k & 1) == 1)
        ret = ret * v % Mod;
    return new ModInt(ret);
  }
  
  public static ModInt Inverse(ModInt v) { return Pow(v, Mod - 2); }
}
#endregion
#region Binomial Coefficient
public class BinomialCoefficient {
  public ModInt[] fact, ifact;
  public BinomialCoefficient(int n) {
    fact = new ModInt[n + 1];
    ifact = new ModInt[n + 1];
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
      fact[i] = fact[i - 1] * i;
    ifact[n] = ModInt.Inverse(fact[n]);
    for (int i = n - 1; i >= 0; i--)
      ifact[i] = ifact[i + 1] * (i + 1);
    ifact[0] = ifact[1];
  }
  
  public ModInt this[int n, int r] {
    get {
      if (n >= 0) {
        if (!(0 <= r && r <= n))
          return 0;
        return fact[n] * ifact[n - r] * ifact[r];
      } else {
        if (!(0 <= r))
          throw new ArgumentOutOfRangeException();
        return (r % 2 == 0 ? 1 : -1) * this[-n + r - 1, r];
      }
    }
  }
  
  public ModInt RepeatedCombination(int n, int k) {
    if (k == 0)
      return 1;
    return this[n + k - 1, k];
  }
}
#endregion
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


// https://github.com/VaHiX/codeForces/