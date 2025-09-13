using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Text;

public class Program
{
    public void Solve()
    {
        var sc = new Scanner();
#if !DEBUG
        System.Console.SetOut(new System.IO.StreamWriter(System.Console.OpenStandardOutput()) { AutoFlush = false });
#endif
        int t = sc.NextInt();
        for (int i = 0; i < t; i++)
        {
            Query(sc);
        }

        Console.Out.Flush();
    }

    private int N;
    private (long A, long B, int I)[] T;

    void Query(Scanner sc)
    {
        N = sc.NextInt();
        T = new (long A, long B, int I)[N];
        for (int i = 0; i < N; i++)
        {
            T[i] = (sc.NextInt(), sc.NextInt(), i);
        }

        var arA = new (long a, int i)[N];
        var arB = new (long b, int i)[N];
        for (int i = 0; i < N; i++)
        {
            arA[i] = (T[i].A, i);
            arB[i] = (T[i].B, i);
        }

        Array.Sort(arA, (l, r) => l.a.CompareTo(r.a));
        Array.Sort(arB, (l, r) => l.b.CompareTo(r.b));

        var signA = new int[N];
        var signB = new int[N];
        for (int i = 0; i < N / 2; i++)
        {
            signA[arA[i].i] = 0;
            signA[arA[i + N / 2].i] = 1;

            signB[arB[i].i] = 0;
            signB[arB[i + N / 2].i] = 1;
        }

        var ls = new List<int>[2, 2];
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                ls[i, j] = new List<int>();
            }
        }

        for (int i = 0; i < N; i++)
        {
            ls[signA[i], signB[i]].Add(i);
        }

        var ans = new List<(int i, int j)>();
        for (int i = 0; i < ls[0,0].Count; i++)
        {
            ans.Add((ls[0,0][i]+1, ls[1,1][i] + 1));
        }

        for (int i = 0; i < ls[0,1].Count; i++)
        {
            ans.Add((ls[0,1][i]+1,ls[1,0][i] + 1));
        }

        foreach ((int i, int j) in ans)
        {
            Console.WriteLine($"{i} {j}");
        }
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
        public ulong NextULong() => ulong.Parse(Next());
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

        public int[] IntArray() => Array().AsParallel().Select(int.Parse).ToArray();
        public long[] LongArray() => Array().AsParallel().Select(long.Parse).ToArray();
        public ulong[] ULongArray() => Array().AsParallel().Select(ulong.Parse).ToArray();
        public double[] DoubleArray() => Array().AsParallel().Select(double.Parse).ToArray();
        public decimal[] DecimalArray() => Array().AsParallel().Select(decimal.Parse).ToArray();
    }
}