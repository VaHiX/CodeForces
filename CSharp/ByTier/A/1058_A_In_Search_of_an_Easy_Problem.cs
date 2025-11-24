// Problem: CF 1058 A - In Search of an Easy Problem
// https://codeforces.com/contest/1058/problem/A

/*
 * Problem: A. In Search of an Easy Problem
 * Algorithm: Linear scan to check if any person thinks the problem is hard
 * Time Complexity: O(n) - where n is the number of people
 * Space Complexity: O(n) - for storing the array of responses
 * 
 * The solution reads n responses (0 = easy, 1 = hard) and determines if 
 * the problem should be changed based on whether at least one person 
 * thinks it's hard.
 */

using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
public class Program {
  public void Solve() {
    var sc = new Scanner();
    int n = sc.NextInt(); // Read number of people
    int[] a = sc.IntArray(); // Read the array of responses
    // Check if any person thinks the problem is hard (i.e., any element is 1)
    Console.WriteLine(a.Any(num => num == 1) ? "HARD" : "EASY");
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