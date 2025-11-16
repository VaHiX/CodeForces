// Problem: CF 2120 D - Matrix game
// https://codeforces.com/contest/2120/problem/D

/*
 * Problem: D. Matrix game
 * 
 * Purpose:
 *   Given integers a, b, and k, find the lexicographically smallest pair (n, m) such that
 *   any n×m matrix with elements from 1 to k must contain a submatrix of size a×b
 *   where all elements are equal. This is a problem related to the concept of van der Waerden's theorem and
 *   extremal combinatorics.
 *
 * Algorithm:
 *   - The solution involves determining minimum n and m such that no matter how Harshith fills the matrix,
 *     Aryan can always find an a×b submatrix with all equal elements.
 *   - This is solved using the concept of "avoiding" patterns; essentially finding the smallest dimensions
 *     where it's impossible to avoid having a monochromatic submatrix of size a×b.
 *   - The formula derived uses combinatorics and modular arithmetic to compute n = (a - 1) * k + 1,
 *     and m = (b - 1) * Binom(n, a) * k + 1, where Binom represents the binomial coefficient.
 *   - Efficient computation of large binomial coefficients is achieved using precomputed factorials and inverses modulo 1e9+7.
 *
 * Time Complexity: O(max(a, b, k)) for the initialization of factorials in BinomialCoefficient,
 *                  and amortized O(1) for each query due to memoization.
 *
 * Space Complexity: O(max(a, b, k)) for storing precomputed factorials and inverse factorials.
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

  void Query(Scanner sc) {
    long a = sc.NextInt(); // Number of rows in target submatrix
    long b = sc.NextInt(); // Number of columns in target submatrix
    long k = sc.NextInt(); // Range of values in matrix (1 to k)
    
    // Compute n using the derived formula for minimal required rows
    long n = (a - 1) * k + 1;
    
    // Compute m using the derived formula involving binomial coefficient and modular arithmetic
    ModInt m = (b - 1) * Binom(n, a) * k + 1;
    
    Console.WriteLine($"{n % ModInt.Mod} {m}");
  }

  // Function to compute binomial coefficient C(n, a) modulo 1e9+7 using precomputed factorials
  ModInt Binom(long n, long a) {
    ModInt ans = 1;
    for (int i = 0; i < a; i++) {
      ans *= (n - i) % ModInt.Mod;         // Multiply by numerator term
      ans *= ModInt.Inverse(a - i);        // Divide by denominator term using modular inverse
    }
    return ans;
  }

  public static void Main(string[] args) => new Program().Solve();
}

namespace CompLib.Mathematics {
#region ModInt
public struct ModInt {
  public const long Mod = (int)1e9 + 7; // Prime modulus for modular arithmetic operations
  public long num;
  public ModInt(long n) { num = n; }
  public override string ToString() { return num.ToString(); }

  // Addition in modular arithmetic
  public static ModInt operator +(ModInt l, ModInt r) {
    l.num += r.num;
    if (l.num >= Mod)
      l.num -= Mod;
    return l;
  }

  // Subtraction in modular arithmetic
  public static ModInt operator -(ModInt l, ModInt r) {
    l.num -= r.num;
    if (l.num < 0)
      l.num += Mod;
    return l;
  }

  // Multiplication in modular arithmetic
  public static ModInt operator *(ModInt l, ModInt r) {
    return new ModInt(l.num * r.num % Mod);
  }

  // Conversion from long to ModInt with modulo handling
  public static implicit operator ModInt(long n) {
    n %= Mod;
    if (n < 0)
      n += Mod;
    return new ModInt(n);
  }

  // Fast exponentiation with modular arithmetic
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

  // Modular inverse using Fermat's little theorem
  public static ModInt Inverse(ModInt v) { return Pow(v, Mod - 2); }
}
#endregion

#region Binomial Coefficient
public class BinomialCoefficient {
  public ModInt[] fact, ifact; // Precomputed factorials and their inverses
  
  // Constructor initializes factorials up to n using dynamic programming
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

  // Accessor for computing C(n, r) using precomputed factorial values
  public ModInt this[int n, int r] {
    get {
      if (n >= 0) {
        if (!(0 <= r && r <= n))
          return 0;
        return fact[n] * ifact[n - r] * ifact[r];  // Efficient computation as fact[n]/(fact[n-r]*fact[r])
      } else {
        if (!(0 <= r))
          throw new ArgumentOutOfRangeException();
        return (r % 2 == 0 ? 1 : -1) * this[-n + r - 1, r]; // Handle negative n case
      }
    }
  }

  // Computes combination with repetition C(n + k - 1, k), also known as multiset coefficient
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

  // Read next token from input
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

  // Read entire line
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

  // Read array of strings from a line
  public string[] Array() {
    string s = Console.ReadLine();
    _line = s.Length == 0 ? new string[0] : s.Split(Separator);
    _index = _line.Length;
    return _line;
  }
}
}


// https://github.com/VaHiX/CodeForces/