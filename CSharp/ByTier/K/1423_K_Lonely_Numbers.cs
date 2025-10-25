// Problem: CF 1423 K - Lonely Numbers
// https://codeforces.com/contest/1423/problem/K

/*
K. Lonely Numbers

Algorithm:
- For each number n, we need to count how many numbers from 1 to n are "lonely".
- A number a is lonely if there's no other number b (a != b) such that a and b form friends.
- Two numbers a and b are friends if gcd(a,b), a/gcd(a,b), and b/gcd(a,b) can form a triangle.
- This implies that we need to check whether for two numbers a and b, the triangle inequality holds for their reduced forms.
- We can optimize this using prime sieve to precompute primes up to 1e6.
- A key observation is that for a number to be lonely, no other number shares enough common factors to allow friend relationships.
- The problem can actually be solved by determining how many numbers are "not friends" with any other number. 
  This happens when a number's prime factorization leads to unique combinations of reduced values.

Time Complexity: O(N log log N + T), where N = 10^6, T = number of test cases
Space Complexity: O(N)

*/

using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using CompLib.Mathematics;

public class Program {
  const int Max = 1000000;
  List<int> P; // List of primes up to Max

  public void Solve() {
    P = new List<int>();
    MathEx.Sieve(Max, P); // Precompute all primes up to Max
    var sc = new Scanner();
#if !DEBUG
    System.Console.SetOut(new System.IO.StreamWriter(
        System.Console.OpenStandardOutput()) { AutoFlush = false });
#endif
    int t = sc.NextInt(); // Read number of test cases
    for (int i = 0; i < t; i++) {
      Q(sc); // Process each query
    }
    System.Console.Out.Flush();
  }

  int N;

  void Q(Scanner sc) {
    N = sc.NextInt(); // Current value of n

    // Binary search to find the largest prime <= sqrt(N)
    int ok = -1;
    int ng = P.Count;
    while (ng - ok > 1) {
      int mid = (ok + ng) / 2;
      if ((long)P[mid] * P[mid] <= N)
        ok = mid;
      else
        ng = mid;
    }

    // Binary search to find the largest prime <= N
    int ok2 = -1;
    int ng2 = P.Count;
    while (ng2 - ok2 > 1) {
      int mid = (ok2 + ng2) / 2;
      if (P[mid] <= N)
        ok2 = mid;
      else
        ng2 = mid;
    }

    // The count of lonely numbers is the difference in indices between two binary searches
    int cnt = ng2 - ng + 1; 
    Console.WriteLine(cnt);
  }

  public static void Main(string[] args) => new Program().Solve();
}

namespace CompLib.Mathematics {
using System;
using System.Collections.Generic;

#region GCD LCM
public static partial class MathEx {
  public static int GCD(int n, int m) { return (int)GCD((long)n, m); }
  public static long GCD(long n, long m) {
    n = Math.Abs(n);
    m = Math.Abs(m);
    while (n != 0) {
      m %= n;
      if (m == 0)
        return n;
      n %= m;
    }
    return m;
  }
  public static long LCM(long n, long m) { return (n / GCD(n, m)) * m; }
}
#endregion

#region PrimeSieve
public static partial class MathEx {
  public static bool[] Sieve(int max, List<int> primes = null) {
    var isPrime = new bool[max + 1];
    for (int i = 2; i < isPrime.Length; i++)
      isPrime[i] = true;
    for (int i = 2; i * i <= max; i++)
      if (!isPrime[i])
        continue;
      else
        for (int j = i * i; j <= max; j += i)
          isPrime[j] = false;
    if (primes != null)
      for (int i = 0; i <= max; i++)
        if (isPrime[i])
          primes.Add(i);
    return isPrime;
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


// https://github.com/VaHiX/codeForces/