// Problem: CF 933 A - A Twisty Movement
// https://codeforces.com/contest/933/problem/A

/*
 * Algorithm: Dynamic Programming with Prefix Sums
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 * 
 * The problem requires finding the maximum length of a non-decreasing subsequence 
 * after reversing any subarray in the given array.
 * 
 * The approach:
 * 1. Precompute prefix counts of 1s and 2s to quickly calculate how many 1s/2s 
 *    exist before a certain index.
 * 2. For each possible subarray [l, r], compute the best possible non-decreasing 
 *    subsequence ending at different states (1 or 2) in the reversed portion.
 * 3. For each such subarray, calculate the total length of the longest possible 
 *    non-decreasing subsequence by combining:
 *    - Count of 1s before l
 *    - Best subsequence from l to r (reversed)
 *    - Count of 2s after r
 * 4. Return the maximum of all such combinations.
 */

using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;
public class Program {
  public void Solve() {
    var sc = new Scanner();
    int n = sc.NextInt();
    int[] a = sc.IntArray();
    int[] fCnt1 = new int[n + 1];
    int[] fCnt2 = new int[n + 1];
    for (int i = 0; i < n; i++) {
      fCnt1[i + 1] = fCnt1[i];
      fCnt2[i + 1] = fCnt2[i];
      if (a[i] == 1)
        fCnt1[i + 1]++;
      else
        fCnt2[i + 1]++;
    }
    var dp = new int[n + 1, n + 1, 3, 3];
    for (int l = 0; l < n; l++) {
      for (int r = l + 1; r <= n; r++) {
        if (a[r - 1] == 1) {
          dp[l, r, 1, 1] = dp[l, r - 1, 1, 1] + 1; // Continue subsequence ending with 1
          dp[l, r, 2, 1] = Math.Max(dp[l, r - 1, 2, 2], dp[l, r - 1, 2, 1]) + 1; // Start new subsequence ending with 2
          dp[l, r, 2, 2] = dp[l, r - 1, 2, 2]; // No change in ending with 2
        } else {
          dp[l, r, 1, 1] = dp[l, r - 1, 1, 1]; // No change in ending with 1
          dp[l, r, 2, 1] = dp[l, r - 1, 2, 1]; // No change in ending with 1
          dp[l, r, 2, 2] = dp[l, r - 1, 2, 2] + 1; // Continue subsequence ending with 2
        }
      }
    }
    int ans = 0;
    for (int l = 0; l < n; l++) {
      for (int r = l + 1; r <= n; r++) {
        int[] cnt = new int[5];
        // cnt[0]: 1s before l + best subsequence (ending with 2) + 2s after r
        cnt[0] = fCnt1[l] + dp[l, r, 2, 1] + (fCnt2[n] - fCnt2[r]);
        // cnt[1]: 1s before l + best subsequence (ending with 1) + 2s after r
        cnt[1] = fCnt1[l] + dp[l, r, 1, 1] + (fCnt2[n] - fCnt2[r]);
        // cnt[2]: 1s before l + best subsequence (ending with 1) + 1s after r
        cnt[2] = fCnt1[l] + dp[l, r, 1, 1] + (fCnt1[n] - fCnt1[r]);
        // cnt[3]: 1s before l + best subsequence (ending with 2) + 2s after r
        cnt[3] = fCnt1[l] + dp[l, r, 2, 2] + (fCnt2[n] - fCnt2[r]);
        // cnt[4]: 2s before l + best subsequence (ending with 2) + 2s after r
        cnt[4] = fCnt2[l] + dp[l, r, 2, 2] + (fCnt2[n] - fCnt2[r]);
        ans = Math.Max(ans, cnt.Max());
      }
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