// Problem: CF 1239 A - Ivan the Fool and the Probability Theory
// https://codeforces.com/contest/1239/problem/A

/*
 * Problem: Ivan the Fool and the Probability Theory
 * Algorithm: Dynamic Programming with Fibonacci-like sequence
 * Time Complexity: O(max(N, M))
 * Space Complexity: O(max(N, M))
 * 
 * The key insight is that for a valid "random" picture, each row/column 
 * can be seen as a sequence where no two adjacent cells have the same color.
 * This leads to a Fibonacci-like recurrence relation.
 * 
 * For a single row of length k, the number of valid patterns is F(k+2) where 
 * F is the Fibonacci sequence starting with F(0)=1, F(1)=1.
 * 
 * The solution uses the fact that the total number of valid pictures is the sum
 * of valid patterns for each row and each column, minus 2 (to avoid double counting).
 */

using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using CompLib.Mathematics;
public class Program {
  private int N, M;
  public void Solve() {
    var sc = new Scanner();
    N = sc.NextInt();
    M = sc.NextInt();
    ModInt ans = 0;
    var dp = new ModInt[100001];
    dp[1] = 2;
    dp[0] = 2;
    for (int i = 2; i <= 100000; i++) {
      dp[i] += dp[i - 1] + dp[i - 2];  // Fibonacci recurrence relation
    }
    ans += dp[M] + dp[N];
    Console.WriteLine(ans - 2);  // Subtract 2 to avoid double counting
  }
  public static void Main(string[] args) => new Program().Solve();
}
namespace CompLib.Mathematics {
#region ModInt
public struct ModInt {
  public const long Mod = (int)1e9 + 7;
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
    for (k %= Mod - 1; k > 0; k >>= 1, v = v * v % Mod)
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
      if (n < 0 || n >= fact.Length || r < 0 || r > n)
        return 0;
      return fact[n] * ifact[n - r] * ifact[r];
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
  public int[] IntArray() => Array().Select(int.Parse).ToArray();
  public long[] LongArray() => Array().Select(long.Parse).ToArray();
  public double[] DoubleArray() => Array().Select(double.Parse).ToArray();
  public decimal[] DecimalArray() => Array().Select(decimal.Parse).ToArray();
}
}


// https://github.com/VaHiX/CodeForces/