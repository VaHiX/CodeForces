// Problem: CF 1442 A - Extreme Subtraction
// https://codeforces.com/contest/1442/problem/A

/*
Algorithm: Greedy approach with prefix analysis
Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (not counting input storage)

The problem allows decrementing k elements from the start or end of the array.
The key insight is to simulate the process from left to right, maintaining a "flow" 
of how many elements can be decremented at each step.

The algorithm works as follows:
1. Start with the first element as the base flow
2. For each subsequent element:
   - Calculate the difference between current and previous elements
   - Determine how many elements can be decremented based on this difference
   - Update the flow to be the minimum of current flow and the calculated decrement
3. If at any point the flow becomes negative, return "NO"
4. If all elements are processed successfully, return "YES"
*/

using System;
using System.IO;
using System.Linq;
using CompLib.Util;
using System.Threading;
public class Program {
  public void Solve() {
    var sc = new Scanner();
    Console.SetOut(
        new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false });
    int t = sc.NextInt();
    for (int i = 0; i < t; i++) {
      Q(sc);
    }
    Console.Out.Flush();
  }
  void Q(Scanner sc) {
    int n = sc.NextInt();
    int[] a = sc.IntArray();
    int prev = a[0]; // Initialize with the first element
    bool f = true; // Flag to track if solution is possible
    for (int i = 1; f && i < n; i++) {
      int p = a[i - 1] - prev; // Calculate difference to determine decrement needed
      int tmp = Math.Min(prev, a[i] - p); // Calculate new flow level
      if (tmp < 0) // If flow becomes negative, impossible to make all zero
        f = false;
      else
        prev = tmp; // Update flow for next iteration
    }
    Console.WriteLine(f ? "YES" : "NO");
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