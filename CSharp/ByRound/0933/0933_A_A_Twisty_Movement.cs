using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;

public class Program
{

    public void Solve()
    {
        var sc = new Scanner();
        int n = sc.NextInt();
        int[] a = sc.IntArray();

        int[] fCnt1 = new int[n + 1];
        int[] fCnt2 = new int[n + 1];
        for (int i = 0; i < n; i++)
        {
            fCnt1[i + 1] = fCnt1[i];
            fCnt2[i + 1] = fCnt2[i];
            if (a[i] == 1) fCnt1[i + 1]++;
            else fCnt2[i + 1]++;
        }



        var dp = new int[n + 1, n + 1, 3, 3];
        for (int l = 0; l < n; l++)
        {
            for (int r = l + 1; r <= n; r++)
            {
                if (a[r - 1] == 1)
                {
                    dp[l, r, 1, 1] = dp[l, r - 1, 1, 1] + 1;
                    dp[l, r, 2, 1] = Math.Max(dp[l, r - 1, 2, 2], dp[l, r - 1, 2, 1]) + 1;
                    dp[l, r, 2, 2] = dp[l, r - 1, 2, 2];
                }
                else
                {
                    dp[l, r, 1, 1] = dp[l, r - 1, 1, 1];
                    dp[l, r, 2, 1] = dp[l, r - 1, 2, 1];
                    dp[l, r, 2, 2] = dp[l, r - 1, 2, 2] + 1;
                }
            }
        }

        int ans = 0;
        for (int l = 0; l < n; l++)
        {
            for (int r = l + 1; r <= n; r++)
            {
                // 1111 22222 11111 22222
                int[] cnt = new int[5];
                cnt[0] = fCnt1[l] + dp[l, r, 2, 1] + (fCnt2[n] - fCnt2[r]);
                cnt[1] = fCnt1[l] + dp[l, r, 1, 1] + (fCnt2[n] - fCnt2[r]);
                cnt[2] = fCnt1[l] + dp[l, r, 1, 1] + (fCnt1[n] - fCnt1[r]);
                cnt[3] = fCnt1[l] + dp[l, r, 2, 2] + (fCnt2[n] - fCnt2[r]);
                cnt[4] = fCnt2[l] + dp[l, r, 2, 2] + (fCnt2[n] - fCnt2[r]);
                ans = Math.Max(ans, cnt.Max());


            }
        }
        Console.WriteLine(ans);
    }

    public static void Main(string[] args) => new Program().Solve();
    // public static void Main(string[] args) => new Thread(new Program().Solve, 1 << 27).Start();
}

namespace CompLib.Util
{
    using System;
    using System.Linq;

    class Scanner
    {
        private string[] _line;
        private int _index;
        private const char Separator = ' ';

        public Scanner()
        {
            _line = new string[0];
            _index = 0;
        }

        public string Next()
        {
            if (_index >= _line.Length)
            {
                string s;
                do
                {
                    s = Console.ReadLine();
                } while (s.Length == 0);

                _line = s.Split(Separator);
                _index = 0;
            }

            return _line[_index++];
        }

        public string ReadLine()
        {
            _index = _line.Length;
            return Console.ReadLine();
        }

        public int NextInt() => int.Parse(Next());
        public long NextLong() => long.Parse(Next());
        public double NextDouble() => double.Parse(Next());
        public decimal NextDecimal() => decimal.Parse(Next());
        public char NextChar() => Next()[0];
        public char[] NextCharArray() => Next().ToCharArray();

        public string[] Array()
        {
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
