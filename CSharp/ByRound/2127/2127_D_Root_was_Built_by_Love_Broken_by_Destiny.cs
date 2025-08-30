using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Text;
using CompLib.Collections;
using CompLib.DataStructure;
using CompLib.Mathematics;

public class Program
{
    private BinomialCoefficient Binom;
    public void Solve()
    {
        Binom = new BinomialCoefficient(300000);
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
    private (int U, int V)[] T;

    private List<int>[] E;

    void Query(Scanner sc)
    {
        N = sc.NextInt();
        M = sc.NextInt();
        T = new (int U, int V)[M];
        for (int i = 0; i < M; i++)
        {
            T[i] = (sc.NextInt() - 1, sc.NextInt() - 1);
        }

        E = new List<int>[N];
        for (int i = 0; i < N; i++)
        {
            E[i] = new List<int>();
        }

        foreach ((int u, int v) in T)
        {
            E[u].Add(v);
            E[v].Add(u);
        }

        ModInt ans = 1;

        C = new int[N];
        Array.Fill(C, -1);
        for (int s = 0; s < N; s++)
        {
            if (C[s] != -1) continue;

            var tmp = F(s);
            ans *= tmp;
         break;
        }

        Console.WriteLine(ans);
    }

    private int[] C;

    ModInt F(int s)
    {
        C[s] = 0;
        var que = new Queue<int>();
        que.Enqueue(s);

        var ls = new List<int>();
        ls.Add(s);
        while (que.Count > 0)
        {
            int cur = que.Dequeue();
            foreach (int to in E[cur])
            {
                if (C[to] == -1)
                {
                    ls.Add(to);
                    C[to] = 1 - C[cur];
                    que.Enqueue(to);
                }
                else if (C[to] == C[cur]) return 0;
            }
        }
        
        // うに
        int cnt1 = 0;
        foreach (var li in ls)
        {
            if (E[li].Count == 1) cnt1++;
        }

        if (cnt1 == ls.Count)
        {
            return 2;
        }

        if (cnt1 == ls.Count - 1)
        {
            return 2 * Binom.fact[ls.Count - 1];
        }

        var cnt = new HashMap<int, int>();
        foreach (var li in ls)
        {
            if (E[li].Count == 1) cnt[E[li][0]]++;
        }

        ModInt ans = 1;

        var l2 = new List<int>();
        for (int i = 0; i < N; i++)
        {
            if(E[i].Count != 1) l2.Add(i);
        }
        foreach ((var k, var v) in cnt)
        {
            ans *= Binom.fact[v];
        }

        if (!F(l2)) return 0;
        return 4 *  ans;
    }

    bool F(List<int> v)
    {
        if (v.Count < 2) throw new Exception();
        var map = new int[N];
        Array.Fill(map, -1);
        for (int i = 0; i < v.Count; i++)
        {
            map[v[i]] = i;
        }

        var uf = new UnionFind(v.Count);
        int[] cnt = new int[v.Count];
        foreach ((int uu, int vv) in T)
        {
            if (map[uu] == -1 || map[vv] == -1) continue;
            cnt[map[uu]]++;
            cnt[map[vv]]++;
            uf.Connect(map[uu], map[vv]);
        }

        if (uf.GroupsCount != 1) return false;

        if (cnt.Count(num => num == 1) == 2 && cnt.Count(num => num == 2) == v.Count - 2) return true;
        return false;
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



namespace CompLib.Collections
{
    using System.Collections.Generic;

    public class HashMap<TKey, TValue> : Dictionary<TKey, TValue>
    {
        public HashMap(IEqualityComparer<TKey> comparer) : base(comparer)
        {
        }

        public HashMap(int capacity) : base(capacity)
        {
        }

        public HashMap(int capacity, IEqualityComparer<TKey> comparer) : base(capacity, comparer)
        {
        }

        public HashMap() : base()
        {
        }

        public new TValue this[TKey key]
        {
            get
            {
                TValue o;
                return TryGetValue(key, out o) ? o : default(TValue);
            }
            set { base[key] = value; }
        }
    }
}

// https://bitbucket.org/camypaper/complib
namespace CompLib.Mathematics
{
    #region ModInt

    /// <summary>
    /// [0,<see cref="Mod"/>) までの値を取るような数
    /// </summary>
    public struct ModInt
    {
        /// <summary>
        /// 剰余を取る値．
        /// </summary>
        public const long Mod = (int)1e9 + 7;
        // public const long Mod = 998244353;

        /// <summary>
        /// 実際の数値．
        /// </summary>
        public long num;

        /// <summary>
        /// 値が <paramref name="n"/> であるようなインスタンスを構築します．
        /// </summary>
        /// <param name="n">インスタンスが持つ値</param>
        /// <remarks>パフォーマンスの問題上，コンストラクタ内では剰余を取りません．そのため，<paramref name="n"/> ∈ [0,<see cref="Mod"/>) を満たすような <paramref name="n"/> を渡してください．このコンストラクタは O(1) で実行されます．</remarks>
        public ModInt(long n)
        {
            num = n;
        }

        /// <summary>
        /// このインスタンスの数値を文字列に変換します．
        /// </summary>
        /// <returns>[0,<see cref="Mod"/>) の範囲内の整数を 10 進表記したもの．</returns>
        public override string ToString()
        {
            return num.ToString();
        }

        public static ModInt operator +(ModInt l, ModInt r)
        {
            l.num += r.num;
            if (l.num >= Mod) l.num -= Mod;
            return l;
        }

        public static ModInt operator -(ModInt l, ModInt r)
        {
            l.num -= r.num;
            if (l.num < 0) l.num += Mod;
            return l;
        }

        public static ModInt operator *(ModInt l, ModInt r)
        {
            return new ModInt(l.num * r.num % Mod);
        }

        public static implicit operator ModInt(long n)
        {
            n %= Mod;
            if (n < 0) n += Mod;
            return new ModInt(n);
        }

        /// <summary>
        /// 与えられた 2 つの数値からべき剰余を計算します．
        /// </summary>
        /// <param name="v">べき乗の底</param>
        /// <param name="k">べき指数</param>
        /// <returns>繰り返し二乗法により O(N log N) で実行されます．</returns>
        public static ModInt Pow(ModInt v, long k)
        {
            return Pow(v.num, k);
        }

        /// <summary>
        /// 与えられた 2 つの数値からべき剰余を計算します．
        /// </summary>
        /// <param name="v">べき乗の底</param>
        /// <param name="k">べき指数</param>
        /// <returns>繰り返し二乗法により O(N log N) で実行されます．</returns>
        public static ModInt Pow(long v, long k)
        {
            long ret = 1;
            if (Mod == 998244353 || Mod == (long)1e9 + 7) k %= Mod - 1;
            for (; k > 0; k >>= 1, v = v * v % Mod)
                if ((k & 1) == 1)
                    ret = ret * v % Mod;
            return new ModInt(ret);
        }

        /// <summary>
        /// 与えられた数の逆元を計算します．
        /// </summary>
        /// <param name="v">逆元を取る対象となる数</param>
        /// <returns>逆元となるような値</returns>
        /// <remarks>法が素数であることを仮定して，フェルマーの小定理に従って逆元を O(log N) で計算します．</remarks>
        public static ModInt Inverse(ModInt v)
        {
            return Pow(v, Mod - 2);
        }
    }

    #endregion

    #region Binomial Coefficient

    public class BinomialCoefficient
    {
        public ModInt[] fact, ifact;

        public BinomialCoefficient(int n)
        {
            fact = new ModInt[n + 1];
            ifact = new ModInt[n + 1];
            fact[0] = 1;
            for (int i = 1; i <= n; i++)
                fact[i] = fact[i - 1] * i;
            ifact[n] = ModInt.Inverse(fact[n]);
            for (int i = n - 1; i >= 0; i--)
                ifact[i] = ifact[i + 1] * (i + 1);
            ifact[0] = ifact[1];
        }

        public ModInt this[int n, int r]
        {
            get
            {
                if (n >= 0)
                {
                    if (!(0 <= r && r <= n)) return 0;
                    return fact[n] * ifact[n - r] * ifact[r];
                }
                else
                {
                    if (!(0 <= r)) throw new ArgumentOutOfRangeException();
                    return (r % 2 == 0 ? 1 : -1) * this[-n + r - 1, r];
                }
            }
        }

        public ModInt RepeatedCombination(int n, int k)
        {
            if (k == 0) return 1;
            return this[n + k - 1, k];
        }
    }

    #endregion
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