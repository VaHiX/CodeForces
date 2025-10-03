using System;
using System.Linq;
using CompLib.Util;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Text;
using CompLib.Collections;
using System.Numerics;

public class Program
{
    int A, B;
    int AX, AY, BX, BY;
    int N;

    int[] X1, Y1, X2, Y2;

    public void Solve()
    {
        var sc = new Scanner();
        A = sc.NextInt();
        B = sc.NextInt();

        AX = sc.NextInt();
        AY = sc.NextInt();

        BX = sc.NextInt();
        BY = sc.NextInt();

        N = sc.NextInt();

        X1 = new int[N];
        Y1 = new int[N];
        X2 = new int[N];
        Y2 = new int[N];
        for (int i = 0; i < N; i++)
        {
            X1[i] = sc.NextInt();
            Y1[i] = sc.NextInt();
            X2[i] = sc.NextInt();
            Y2[i] = sc.NextInt();
        }

        // 0 ~ N-1 塹壕
        // N スタート
        // N+1 ゴール
        double[] dist = new double[N + 2];
        Array.Fill(dist, double.MaxValue);
        dist[N] = 0;

        var pq = new PriorityQueue<(int p, double d)>((l, r) => l.d.CompareTo(r.d));
        pq.Enqueue((N, 0));

        while (pq.Count > 0)
        {
            (int p, double d) = pq.Dequeue();
            // if (dist[p] < d) continue;

            if (p == N)
            {
                for (int i = 0; i < N; i++)
                {
                    long dist2 = Dist1(i, AX, AY);
                    if (dist2 <= A * A && dist[p] + A + B < dist[i])
                    {
                        dist[i] = dist[p] + A + B;
                        pq.Enqueue((i, dist[i]));
                    }

                    // Console.WriteLine($"{i} {dist3}");
                }
                {
                    long dist2 = Dist2(AX, AY, BX, BY);
                    double dist3 = Math.Sqrt(dist2);
                    if (dist2 <= A * A && dist3 + dist[p] < dist[N + 1])
                    {
                        dist[N + 1] = dist3 + dist[p];
                        pq.Enqueue((N + 1, dist[N + 1]));
                    }
                }
            }
            else if (p == N + 1)
            {
                break;
            }
            else
            {
                for (int i = 0; i < N; i++)
                {
                    if (i == p) continue;
                    long dist2 = Dist3(p, i);
                    if (dist2 <= A * A && dist[p] + A + B < dist[i])
                    {
                        dist[i] = dist[p] + A + B;
                        pq.Enqueue((i, dist[i]));
                    }
                }

                {
                    long dist2 = Dist1(p, BX, BY);
                    double dist3 = Math.Sqrt(dist2);
                    if (dist2 <= A * A && dist3 + dist[p] < dist[N + 1])
                    {
                        dist[N + 1] = dist3 + dist[p];
                        pq.Enqueue((N + 1, dist[N + 1]));
                    }
                }
            }
        }

        if (dist[N + 1] > int.MaxValue)
        {
            Console.WriteLine("-1");
        }
        else
        {
            Console.WriteLine($"{dist[N + 1]:F12}");
        }

        // a秒チャージ
        // b秒照射
        // 
        // 最初 (AX,AY)にいる
        // ()
    }


    long Dist1(int i, int x, int y)
    {
        // 線分i, (x,y)の距離

        if (X1[i] == X2[i])
        {
            int minY = Math.Min(Y1[i], Y2[i]);
            int maxY = Math.Max(Y1[i], Y2[i]);

            if (y < minY)
            {
                return Dist2(x, y, X1[i], minY);
            }
            else if (y > maxY)
            {
                return Dist2(x, y, X1[i], maxY);
            }
            else
            {
                return (x - X1[i]) * (x - X1[i]);
            }
        }
        else
        {
            int minX = Math.Min(X1[i], X2[i]);
            int maxX = Math.Max(X1[i], X2[i]);

            if (x < minX)
            {
                return Dist2(x, y, minX, Y1[i]);
            }
            else if (x > maxX)
            {
                return Dist2(x, y, maxX, Y1[i]);
            }
            else
            {
                return (y - Y1[i]) * (y - Y1[i]);
            }
        }
    }


    long Dist2(int x1, int y1, int x2, int y2)
    {
        long dx = x1 - x2;
        long dy = y1 - y2;
        return dx * dx + dy * dy;
    }

    long Dist3(int i, int j)
    {
        long a = Dist1(i, X1[j], Y1[j]);
        long b = Dist1(i, X2[j], Y2[j]);
        long c = Dist1(j, X1[i], Y1[i]);
        long d = Dist1(j, X2[i], Y2[i]);

        return Math.Min(a, Math.Min(b, Math.Min(c, d)));
    }

    public static void Main(string[] args) => new Program().Solve();
    // public static void Main(string[] args) => new Thread(new Program().Solve, 1 << 27).Start();
}

// https://bitbucket.org/camypaper/complib
namespace CompLib.Collections
{
    using System;
    using System.Collections.Generic;

    #region PriorityQueue

    /// <summary>
    /// 指定した型のインスタンスを最も価値が低い順に取り出すことが可能な可変サイズのコレクションを表します．
    /// </summary>
    /// <typeparam name="T">優先度付きキュー内の要素の型を指定します．</typeparam>
    /// <remarks>内部的にはバイナリヒープによって実装されています．</remarks>
    public class PriorityQueue<T>
    {
        readonly List<T> heap = new List<T>();
        readonly Comparison<T> cmp;

        /// <summary>
        /// デフォルトの比較子を使用してインスタンスを初期化します．
        /// </summary>
        /// <remarks>この操作は O(1) で実行されます．</remarks>
        public PriorityQueue()
        {
            cmp = Comparer<T>.Default.Compare;
        }

        /// <summary>
        /// デリゲートで表されるような比較関数を使用してインスタンスを初期化します．
        /// </summary>
        /// <param name="comparison"></param>
        /// <remarks>この操作は O(1) で実行されます．</remarks>
        public PriorityQueue(Comparison<T> comparison)
        {
            cmp = comparison;
        }

        /// <summary>
        /// 指定された比較子を使用してインスタンスを初期化します．
        /// </summary>
        /// <param name="comparer"></param>
        /// <remarks>この操作は O(1) で実行されます．</remarks>
        public PriorityQueue(IComparer<T> comparer)
        {
            cmp = comparer.Compare;
        }

        /// <summary>
        /// 優先度付きキューに要素を追加します．
        /// </summary>
        /// <param name="item">優先度付きキューに追加される要素</param>
        /// <remarks>最悪計算量 O(log N) で実行されます．</remarks>
        public void Enqueue(T item)
        {
            var pos = heap.Count;
            heap.Add(item);
            while (pos > 0)
            {
                var par = (pos - 1) / 2;
                if (cmp(heap[par], item) <= 0)
                    break;
                heap[pos] = heap[par];
                pos = par;
            }

            heap[pos] = item;
        }

        /// <summary>
        /// 優先度付きキューから最も価値が低い要素を削除し，返します．
        /// </summary>
        /// <returns>優先度付きキューから削除された要素．</returns>
        /// <remarks>最悪計算量 O(log N) で実行されます．</remarks>
        public T Dequeue()
        {
            var ret = heap[0];
            var pos = 0;
            var x = heap[heap.Count - 1];

            while (pos * 2 + 1 < heap.Count - 1)
            {
                var lch = pos * 2 + 1;
                var rch = pos * 2 + 2;
                if (rch < heap.Count - 1 && cmp(heap[rch], heap[lch]) < 0) lch = rch;
                if (cmp(heap[lch], x) >= 0)
                    break;
                heap[pos] = heap[lch];
                pos = lch;
            }

            heap[pos] = x;
            heap.RemoveAt(heap.Count - 1);
            return ret;
        }

        /// <summary>
        ///  優先度付きキューに含まれる最も価値が低い要素を削除せずに返します．
        /// </summary>
        /// <returns>優先度付きキューに含まれる最も価値が低い要素．</returns>
        /// <remarks>この操作は O(1) で実行されます．</remarks>
        public T Peek()
        {
            return heap[0];
        }

        /// <summary>
        /// 優先度付きキュー内の要素の数を取得します．
        /// </summary>
        /// <returns>優先度付キュー内にある要素の数</returns>
        /// <remarks>最悪計算量 O(1) で実行されます．</remarks>
        public int Count
        {
            get { return heap.Count; }
        }

        /// <summary>
        /// 優先度付きキュー内に要素が存在するかどうかを O(1) で判定します．
        /// </summary>
        /// <returns>優先度付キュー内にある要素が存在するならば true，そうでなければ　false．</returns>
        /// <remarks>この操作は O(1) で実行されます．</remarks>
        public bool Any()
        {
            return heap.Count > 0;
        }

        /// <summary>
        /// 優先度付きキューに含まれる要素を昇順に並べて返します．
        /// </summary>
        /// <remarks>この操作は計算量 O(N log N)で実行されます．</remarks>
        public T[] Items
        {
            get
            {
                var ret = heap.ToArray();
                Array.Sort(ret, cmp);
                return ret;
            }
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
