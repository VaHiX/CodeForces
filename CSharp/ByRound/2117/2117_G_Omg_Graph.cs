using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Text;
using CompLib.DataStructure;

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

    private int N, M;
    private (int U, int V, long W)[] E;

    void Query(Scanner sc)
    {
        N = sc.NextInt();
        M = sc.NextInt();
        E = new (int U, int V, long W)[M];
        for (int i = 0; i < M; i++)
        {
            E[i] = (sc.NextInt() - 1, sc.NextInt() - 1, sc.NextLong());
        }

        var uf = new UnionFind(N);
        var min = new long[N];
        var max = new long[N];
        Array.Fill(min, long.MaxValue);
        Array.Fill(max, long.MinValue);

        long ans = long.MaxValue;
        Array.Sort(E, (l, r) => l.W.CompareTo(r.W));
        foreach ((int u, int v, long w) in E)
        {
            int lu = uf.Find(u);
            int lv = uf.Find(v);
            if (lu == lv)
            {
                max[lu] = Math.Max(max[lu], w);
                min[lu] = Math.Min(min[lu], w);
            }
            else
            {
                uf.Connect(lu, lv);
                int ll = uf.Find(lu);
                min[ll] = Math.Min(min[ll], Math.Min(min[lu], min[lv]));
                max[ll] = Math.Min(max[ll], Math.Min(max[lu], max[lv]));
                max[ll] = Math.Max(max[ll], w);
                min[ll] = Math.Min(min[ll], w);
            }

            if (uf.Same(0, N - 1))
            {
                int l = uf.Find(0);
                ans = Math.Min(ans, min[l] + max[l]);
            }

            // Console.WriteLine(string.Join(" ", min));
            // Console.WriteLine(string.Join(" ", max));
        }

        Console.WriteLine(ans);
    }

    public static void Main(string[] args) => new Program().Solve();
    // public static void Main(string[] args) => new Thread(new Program().Solve, 1 << 27).Start();
}

namespace CompLib.DataStructure
{
    using System.Collections.Generic;
    using System.Linq;

    class UnionFind
    {
        private readonly int _n;
        private readonly int[] _parent, _size;
        public int GroupsCount { get; private set; }

        /// <summary>
        /// n頂点の無向グラフに 1.辺を追加, 2.2頂点が同じ連結成分に属するか判定 ができるデータ構造
        /// </summary>
        /// <param name="n">頂点の個数</param>
        public UnionFind(int n)
        {
            _n = n;
            _parent = new int[_n];
            _size = new int[_n];
            for (int i = 0; i < _n; i++)
            {
                _parent[i] = i;
                _size[i] = 1;
            }

            GroupsCount = _n;
        }

        /// <summary>
        /// iがいる連結成分の代表値
        /// </summary>
        /// <param name="i"></param>
        /// <returns></returns>
        public int Find(int i) => _parent[i] == i ? i : Find(_parent[i]);

        /// <summary>
        /// x,yが同じ連結成分にいるか?
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public bool Same(int x, int y) => Find(x) == Find(y);

        /// <summary>
        /// (x, y)に辺を追加する
        /// </summary>
        /// <remarks>
        /// ACLでは連結された代表値を返しますが、ここでは連結できたか?を返します
        /// </remarks>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns>x,yが違う連結成分だったならtrueを返す</returns>
        public bool Connect(int x, int y)
        {
            x = Find(x);
            y = Find(y);
            if (x == y) return false;

            // データ構造をマージする一般的なテク
            if (_size[x] > _size[y])
            {
                _parent[y] = x;
                _size[x] += _size[y];
            }
            else
            {
                _parent[x] = y;
                _size[y] += _size[x];
            }

            GroupsCount--;
            return true;
        }

        /// <summary>
        /// iが含まれる成分のサイズ
        /// </summary>
        /// <param name="i"></param>
        /// <returns></returns>
        public int GetSize(int i) => _size[Find(i)];

        /// <summary>
        /// 連結成分のリスト
        /// </summary>
        /// <returns></returns>
        public List<int>[] Groups()
        {
            var leaderBuf = new int[_n];
            var groupSize = new int[_n];
            for (int i = 0; i < _n; i++)
            {
                leaderBuf[i] = Find(i);
                groupSize[leaderBuf[i]]++;
            }

            var result = new List<int>[_n];
            for (int i = 0; i < _n; i++)
            {
                result[i] = new List<int>(groupSize[i]);
            }

            for (int i = 0; i < _n; i++)
            {
                result[leaderBuf[i]].Add(i);
            }

            return result.Where(ls => ls.Count > 0).ToArray();
        }
    }
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