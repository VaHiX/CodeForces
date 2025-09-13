using System;
using System.Linq;
using CompLib.Util;
using System.Threading;

public class Program
{
    public void Solve()
    {
        var sc = new Scanner();
#if !DEBUG
        Console.SetOut(new System.IO.StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false });
#endif
        int t = sc.NextInt();
        for (int i = 0; i < t; i++)
        {
            Q(sc);
        }

        Console.Out.Flush();
    }

    void Q(Scanner sc)
    {
        int n = sc.NextInt();
        string s = sc.Next();

        // 2個カッコ列 a,b
        // s_i = 1なら a_i = b_i
        // else a_i != b_i

        if (s[0] == '0' || s[^1] == '0')
        {
            Console.WriteLine("NO");
            return;
        }

        int cnt0 = s.Count(ch => ch == '0');
        if (cnt0 % 2 == 1)
        {
            Console.WriteLine("NO");
            return;
        }

        // cnt0個
        // 半分 (, 半分)


        int cnt1 = n - cnt0;

        char[] a = new char[n];
        char[] b = new char[n];

        int q = 0;
        int w = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '1')
            {
                if (q < cnt1 / 2)
                {
                    a[i] = b[i] = '(';
                }
                else
                {
                    a[i] = b[i] = ')';
                }

                q++;
            }
            else
            {
                if (w % 2 == 0)
                {
                    a[i] = '(';
                    b[i] = ')';
                }
                else
                {
                    a[i] = ')';
                    b[i] = '(';
                }

                w++;
            }
        }

        Console.WriteLine("YES");
        Console.WriteLine(new string(a));
        Console.WriteLine(new string(b));
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