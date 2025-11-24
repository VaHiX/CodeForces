// Problem: CF 803 A - Maximal Binary Matrix
// https://codeforces.com/contest/803/problem/A

/*
 * Problem: Maximal Binary Matrix
 * 
 * Approach:
 * 1. First check if it's possible to place k ones in an n x n matrix.
 *    If k > n * n, then it's impossible and we return -1.
 * 2. To make the matrix lexicographically maximal, we should place 1s as early as possible.
 *    Since we want lexicographically maximal, we should fill the matrix row by row,
 *    and within each row, column by column.
 * 3. For each position (i, j), if ans[i][j] is 0:
 *    - If i == j (diagonal element), place 1 if we have at least 1 one left to place.
 *    - If i != j (non-diagonal), place 1 at both (i,j) and (j,i) if we have at least 2 ones left.
 * 4. Prioritize placing 1s on the diagonal first for lexicographic maximality.
 * 
 * Time Complexity: O(n^2) - We iterate through the matrix once.
 * Space Complexity: O(n^2) - We store the matrix.
 */

using System;
using System.IO;
using System.Linq;
using CompLib.Util;
using System.Threading;
public class Program {
  public void Solve() {
    var sc = new Scanner();
    int n = sc.NextInt();
    int k = sc.NextInt();
    if (n * n < k) {
      Console.WriteLine("-1");
      return;
    }
    var ans = new int [n][];
    for (int i = 0; i < n; i++) {
      ans[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (ans[i][j] == 0) {
          if (i == j && k >= 1) {
            k--;
            ans[i][j] = 1;
          } else if (i != j && k >= 2) {
            k -= 2;
            ans[i][j] = 1;
            ans[j][i] = 1;
          }
        }
      }
    }
    Console.SetOut(
        new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false });
    for (int i = 0; i < n; i++) {
      Console.WriteLine(string.Join(" ", ans[i]));
    }
    Console.Out.Flush();
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