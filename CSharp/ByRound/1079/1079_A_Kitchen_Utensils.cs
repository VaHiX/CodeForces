// Problem: CF 1079 A - Kitchen Utensils
// https://codeforces.com/contest/1079/problem/A

/*
Algorithm: 
- Count the frequency of each utensil type remaining after dinner
- Find the maximum count of any single utensil type
- Calculate minimum number of dishes per guest by ceiling division of max count and k (number of guests)
- For each utensil type, calculate how many additional utensils would be needed to satisfy k guests with the calculated number of dishes
- Sum up these differences to get the minimum number of stolen utensils

Time Complexity: O(n) where n is the number of remaining utensils
Space Complexity: O(1) since we use a fixed size array of 101 elements
*/

using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
public class Program {
  public void Solve() {
    var sc = new Scanner();
    int n = sc.NextInt();
    int k = sc.NextInt();
    int[] a = sc.IntArray();
    int[] cnt = new int[101]; // Array to count frequency of each utensil type
    foreach (int i in a) {
      cnt[i]++; // Count occurrences of each utensil type
    }
    int max = cnt.Max(); // Find maximum count of any utensil type
    int t = (max + k - 1) / k; // Calculate minimum number of dishes per guest (ceiling division)
    int ans = 0;
    for (int i = 1; i <= 100; i++) {
      if (cnt[i] == 0)
        continue; // Skip utensil types that don't exist
      ans += k * t - cnt[i]; // Add the number of stolen utensils for this type
    }
    Console.WriteLine(ans);
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