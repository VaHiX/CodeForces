// Problem: CF 2107 B - Apples in Boxes
// https://codeforces.com/contest/2107/problem/B

/*
B. Apples in Boxes

Algorithm:
This problem is a game theory problem involving optimal play between two players (Tom and Jerry).
The key insight is to determine the winning condition based on the difference between max and min
values in the array after certain operations.

Approach:
1. Sort the array to simplify analysis of max and min values.
2. Check critical cases where taking one apple from the last box (highest value) would immediately cause the difference to exceed k.
3. Also check if taking one apple from the second-highest box causes the condition to fail.
4. If these conditions are not met, determine the winner based on the parity of the total number of apples:
   - If odd sum, Tom wins (because he starts first and will always have the last move in optimal play).
   - If even sum, Jerry wins.

Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing the array and auxiliary copy.

*/
using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Text;
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
    int n = sc.NextInt();
    int k = sc.NextInt();
    int[] a = sc.IntArray();
    Array.Sort(a);
    {
      var b = a.ToArray();
      b[n - 1]--; // Try reducing the largest element by 1
      if (b[n - 1] - b[0] > k) {
        Console.WriteLine("Jerry");
        return;
      }
      if (n >= 3 && b[n - 2] - b[0] > k) { // Check if second largest also creates imbalance
        Console.WriteLine("Jerry");
        return;
      }
    }
    long sum = 0;
    foreach (int ai in a)
      sum += ai;
    Console.WriteLine(sum % 2 == 1 ? "Tom" : "Jerry");
  }
  public static void Main(string[] args) => new Program().Solve();
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