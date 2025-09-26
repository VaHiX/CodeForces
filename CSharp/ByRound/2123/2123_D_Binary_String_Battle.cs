using System.Collections;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Runtime.Intrinsics;
using static Utility.Program;
using static InputUtil.Current.InputUtil;
using static System.Math;
using System.Text;
using System.Linq;
using System.Net;
using System.Collections.Immutable;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Runtime.Intrinsics.X86;
using System.Security.AccessControl;
using Utility;
using System.Text.Json.Serialization;
using Microsoft.VisualBasic;
using System;
using System.Dynamic;
using System.Reflection.Metadata;

/*
var n = ReadLine<int>();
var cnt = 0;
while (cnt < 10)
{
    var A = Enumerable.Range(1, n).ToList().OrderBy(_ => Guid.NewGuid()).ToList();
    var result = new bool[n];
    result[0] = true;
    result[n - 1] = true;
    for (var i = 1; i < n - 1; i++)
    {
        if (A[i - 1] > A[i]) result[i] = true;
        else break;
    }
    for (var i = n - 2; i >= 0; i--)
    {
        if (A[i] > A[i + 1]) result[i] = true;
        else break;
    }
    var sb = new StringBuilder();
    foreach (var b in result)
    {
        sb.Append(b ? '1' : '0');
    }
    Out(Join(A));
    var guchoku = Guchoku(A.ToArray());
    if (sb.ToString() != guchoku)
    {
        Out(guchoku);
        cnt++;
    }
}
*/

NTestCases(() =>
{
    var (n, k) = ReadLine<int>();
    string s = ReadLine();
    var cnt = 0;
    foreach (var c in s)
    {
        if (c == '1') cnt++;
    }
    if (n < k * 2)
    {
        Out("Alice");
    }
    else
    {
        if (cnt <= k)
        {
            Out("Alice");
        }
        else Out("Bob");
    }
});

namespace Utility
{
    public class Factorials
    {
        List<long> numbers;

        public Factorials(int n)
        {
            numbers = new List<long>(n + 1) { 1, 1 };
        }

        public long nPr(int n, int r)
        {
            return Get(n) / Get(n - r);
        }

        public long nCr(int n, int r)
        {
            return nPr(n, r) / Get(r);
        }

        public long Get(int n)
        {
            if (n < numbers.Count)
            {
                return numbers[n];
            }
            else
            {
                var val = Get(n - 1) * n;
                numbers.Add(val);
                return val;
            }
        }

        public long this[int n]
        {
            get
            {
                return Get(n);
            }
        }
    }

    public class UnionFind_1indexed
    {
        int[] _edgeTo;
        int[] _ranks;
        int[] _sizes;

        public UnionFind_1indexed(int vertsCount)
        {
            _edgeTo = new int[vertsCount];
            _ranks = new int[vertsCount];
            _sizes = new int[vertsCount];
            for (int i = 0; i < _edgeTo.Length; i++)
            {
                _edgeTo[i] = i;
                _ranks[i] = 1;
                _sizes[i] = 1;
            }
        }

        private int _Root(int i)
        {
            // 内部メソッドなので0-indexed
            if (_edgeTo[i] == i)
            {
                return i;
            }
            else
            {
                var newRoot = _Root(_edgeTo[i]);
                _edgeTo[i] = newRoot;
                return newRoot;
            }
        }

        public void Unite(int a, int b)
        {
            a--; b--; // 1 → 0-indexed
            var rootA = _Root(a);
            var rootB = _Root(b);
            if (rootA == rootB) return;

            // 背の低いほうをrootAにする
            if (_ranks[rootB] < _ranks[rootA])
            {
                (rootA, rootB) = (rootB, rootA);
            }
            _edgeTo[rootA] = rootB; // rootB ← rootA
            _ranks[rootB] = int.Max(_ranks[rootB], _ranks[rootA] + 1);
            _sizes[rootB] += _sizes[rootA];
        }

        public bool IsSame(int a, int b)
        {
            a--; b--; // 1 → 0-indexed
            return _Root(a) == _Root(b);
        }

        public int GetSize(int i)
        {
            i--; // 1 → 0-indexed
            return _sizes[_Root(i)];
        }
    }


    class SegTree<T>
    {
        int _length;
        T[] _arr;
        Func<T, T, T> _op;
        T _unit;

        public SegTree(int count, Func<T, T, T> operation, T unit) : this(new T[count], operation, unit) { }

        public SegTree(T[] arr, Func<T, T, T> operation, T unit)
        {
            _op = operation;
            _unit = unit;
            _length = arr.Length;

            // size = arr.Length以下の最大の2^n
            int size;
            for (size = 1; size < arr.Length; size <<= 1) ;
            // 配列の初期化
            _arr = new T[size * 2];
            for (int i = 0; i < _arr.Length; i++) _arr[i] = _unit;

            // 最下段にarrの値を代入
            for (int i = 0; i < arr.Length; i++)
            {
                _arr[size + i] = arr[i];
            }
            // セグ木構築
            for (int i = size - 1; i >= 1; i--)
            {
                _arr[i] = _op(_arr[i << 1], _arr[(i << 1) + 1]);
            }
        }

        public T this[Index index]
        {
            set
            {
                var i = _arr.Length / 2 + index.GetOffset(_length);
                _arr[i] = value;
                i >>= 1;
                while (i > 0)
                {
                    _arr[i] = _op(_arr[i << 1], _arr[(i << 1) + 1]);
                    i >>= 1;
                }
            }
            get
            {
                var i = index.GetOffset(_length);
                return this[i..(i + 1)];
            }
        }

        public T this[Range range]
        {
            get
            {
                var l = _arr.Length / 2 + range.Start.GetOffset(_length);
                var r = _arr.Length / 2 + range.End.GetOffset(_length) - 1;
                var ans = _unit;
                while (r - l > 1)
                {
                    // 左端 xxx0: 右ビットシフト
                    if ((l & 1) == 0) l >>= 1;
                    // 左端 xxx1: 集約値計算、右ビットシフト + 1
                    else
                    {
                        ans = _op(ans, _arr[l]);
                        l = (l >> 1) + 1;
                    }

                    // 右端 xxx1: 右ビットシフト
                    if ((r & 1) == 1) r >>= 1;
                    // 右端 xxx0: 集約値計算、右ビットシフト - 1
                    else
                    {
                        ans = _op(ans, _arr[r]);
                        r = (r >> 1) - 1;
                    }
                }

                var lr = (l == r) ? _arr[l] : _op(_arr[l], _arr[r]);
                return _op(ans, lr);
            }
        }

        public void Out()
        {
            Console.WriteLine(string.Join(" ", _arr));
        }
    }

    public class BorderChecker2D
    {
        private int _rMin;
        private int _rMax;
        private int _cMin;
        private int _cMax;

        public BorderChecker2D(int rMin, int cMin, int rMax, int cMax)
        {
            _rMin = rMin;
            _rMax = rMax;
            _cMin = cMin;
            _cMax = cMax;
        }

        public bool In(int r, int c)
        {
            return _rMin <= r && r <= _rMax && _cMin <= c && c <= _cMax;
        }

        public bool In((int, int) at)
        {
            return _rMin <= at.Item1 && at.Item1 <= _rMax && _cMin <= at.Item2 && at.Item2 <= _cMax;
        }
    }

    public static class Program
    {
        public static List<T> PrefixCuml<T>(this IReadOnlyList<T> arr, Func<T, T, T> func, T monoid)
        {
            var list = new List<T>(arr.Count) { func(monoid, arr[0]) };
            for (var i = 1; i < arr.Count; i++)
            {
                list.Add(func(list[list.Count - 1], arr[i]));
            }
            return list;
        }

        public static List<T> SuffixCuml<T>(this IReadOnlyList<T> arr, Func<T, T, T> func, T monoid)
        {
            var list = Enumerable.Repeat(monoid, arr.Count).ToList();
            list[arr.Count - 1] = func(monoid, arr[arr.Count - 1]);
            for (var i = arr.Count - 2; i >= 0; i--)
            {
                list[i] = func(list[i + 1], arr[i]);
            }
            return list;
        }

        public static void UseTextStdin()
        {
            var exStdIn = new System.IO.StreamReader("../../../stdin.txt");
            System.Console.SetIn(exStdIn);
        }

        public static List<T>[] ListedGraph<T>(int n)
        {
            var G = new List<T>[n + 1];
            for (int i = 0; i < n + 1; i++)
            {
                G[i] = new List<T>();
            }
            return G;
        }

        public static List<int>[] ListedGraph(int n)
        {
            var G = new List<int>[n + 1];
            for (int i = 0; i < n + 1; i++)
            {
                G[i] = new List<int>();
            }
            return G;
        }

        public static void AutoFlush(Action func)
        {
            func();
        }

        public static void NoAutoFlush(Action func)
        {
            var sw = new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false };
            Console.SetOut(sw);
            try
            {
                func();
            }
            finally
            {
                Console.Out.Flush();
            }
        }

        public static void NTestCases(Action func)
        {
            int t = ReadLine<int>();
            for (int i = 0; i < t; i++)
            {
                func();
            }
        }

        public static int Elapsed(DateTime dt)
        {
            return (int)(dt - DateTime.Now).TotalMilliseconds;
        }

        public static long Mod1000000007(long value)
        {
            return value % 1000000007;
        }

        public static long Mod998244353(long value)
        {
            return value % 998244353;
        }

        public static bool TakeMax(this ref int variable, params int[] values)
        {
            var origin = variable;
            foreach (var v in values)
            {
                variable = int.Max(variable, v);
            }
            return origin != variable;
        }

        public static bool TakeMax(this ref long variable, params long[] values)
        {
            var origin = variable;
            foreach (var v in values)
            {
                variable = long.Max(variable, v);
            }
            return origin != variable;
        }

        public static bool TakeMax(this ref double variable, params double[] values)
        {
            var origin = variable;
            foreach (var v in values)
            {
                variable = double.Max(variable, v);
            }
            return origin != variable;
        }

        public static bool TakeMax(this ref BigInteger variable, params BigInteger[] values)
        {
            var origin = variable;
            foreach (var v in values)
            {
                variable = BigInteger.Max(variable, v);
            }
            return origin != variable;
        }

        public static bool TakeMin(this ref int variable, params int[] values)
        {
            var origin = variable;
            foreach (var v in values)
            {
                variable = int.Min(variable, v);
            }
            return origin != variable;
        }

        public static bool TakeMin(this ref long variable, params long[] values)
        {
            var origin = variable;
            foreach (var v in values)
            {
                variable = long.Min(variable, v);
            }
            return origin != variable;
        }

        public static bool TakeMin(this ref double variable, params double[] values)
        {
            var origin = variable;
            foreach (var v in values)
            {
                variable = double.Min(variable, v);
            }
            return origin != variable;
        }

        public static bool TakeMin(this ref BigInteger variable, params BigInteger[] values)
        {
            var origin = variable;
            foreach (var v in values)
            {
                variable = BigInteger.Min(variable, v);
            }
            return origin != variable;
        }

        public static int[] Shifted(this int[] array, int fillValue = 0, int shiftCount = 1)
        {
            return Filled(fillValue, shiftCount).Concat(array).ToArray();
        }

        public static long[] Shifted(this long[] array, long fillValue = 0, int shiftCount = 1)
        {
            return Filled(fillValue, shiftCount).Concat(array).ToArray();
        }

        public static T[] Shifted<T>(this T[] array, T fillValue, int shiftCount = 1)
        {
            return Filled(fillValue, shiftCount).Concat(array).ToArray();
        }

        // https://qiita.com/gazf/items/5d5393ac37c2304ecf0a
        public static T Clone<T>(T src)
        {
            ReadOnlySpan<byte> b = System.Text.Json.JsonSerializer.SerializeToUtf8Bytes<T>(src);
            return System.Text.Json.JsonSerializer.Deserialize<T>(b)!;
        }

        public static T[] Filled<T>(T value, int count, bool deepCopy = false)
        {
            var arr = new T[count];
            for (int i = 0; i < count; i++)
            {
                if (deepCopy)
                {
                    arr[i] = Clone(value);
                }
                else
                {
                    arr[i] = value;
                }
            }
            return arr;
        }

        public static T[,] Filled<T>(T value, int count1, int count2, bool deepCopy = false)
        {
            var arr = new T[count1, count2];
            for (int i = 0; i < count1; i++)
            {
                for (int j = 0; j < count2; j++)
                {
                    if (deepCopy)
                    {
                        arr[i, j] = Clone(value);
                    }
                    else
                    {
                        arr[i, j] = value;
                    }
                }
            }
            return arr;
        }

        public static T[,,] Filled<T>(T value, int count1, int count2, int count3, bool deepCopy = false)
        {
            var arr = new T[count1, count2, count3];
            for (int i = 0; i < count1; i++)
            {
                for (int j = 0; j < count2; j++)
                {
                    for (int k = 0; k < count3; k++)
                    {
                        if (deepCopy)
                        {
                            arr[i, j, k] = Clone(value);
                        }
                        else
                        {
                            arr[i, j, k] = value;
                        }
                    }
                }
            }
            return arr;
        }

        public static T[,,,] Filled<T>(T value, int count1, int count2, int count3, int count4, bool deepCopy = false)
        {
            var arr = new T[count1, count2, count3, count4];
            for (int i = 0; i < count1; i++)
            {
                for (int j = 0; j < count2; j++)
                {
                    for (int k = 0; k < count3; k++)
                    {
                        for (int l = 0; l < count4; l++)
                        {
                            if (deepCopy)
                            {
                                arr[i, j, k, l] = Clone(value);
                            }
                            else
                            {
                                arr[i, j, k, l] = value;
                            }
                        }
                    }
                }
            }
            return arr;
        }

        public static List<(char c, int len)> RunLength(string s)
        {
            s += '\n';
            var list = new List<(char c, int len)>();
            var prev = s[0];
            var cnt = 1;
            for (int i = 1; i < s.Length; i++)
            {
                if (s[i] != prev)
                {
                    list.Add((prev, cnt));
                    cnt = 1;
                }
                else
                {
                    cnt++;
                }
                prev = s[i];
            }
            return list;
        }

        public static bool In<T>(this IReadOnlyList<T> list, int index)
        {
            return index >= 0 && index < list.Count;
        }

        public static string Expand2D<T>(T[,] objects, T symbolize)
        {
            var sb = new StringBuilder();
            for (int i = 0; i < objects.GetLength(0); i++)
            {
                if (i != 0) sb.Append("\n");
                for (int j = 0; j < objects.GetLength(1); j++)
                {
                    if (j != 0) sb.Append(" ");
                    sb.Append(objects[i, j]!.Equals(symbolize) ? "*" : objects[i, j]);
                }
            }
            return sb.ToString();
        }

        public static void Out2D<T>(T[,] objects, T symbolize)
        {
            Out(Expand2D(objects, symbolize));
        }

        public static string Expand2D<T>(T[,] objects)
        {
            var sb = new StringBuilder();
            for (int i = 0; i < objects.GetLength(0); i++)
            {
                if (i != 0) sb.Append("\n");
                for (int j = 0; j < objects.GetLength(1); j++)
                {
                    if (j != 0) sb.Append(" ");
                    sb.Append(objects[i, j]);
                }
            }
            return sb.ToString();
        }

        public static void Out2D<T>(T[,] objects)
        {
            Out(Expand2D(objects));
        }

        public static void Out3D<T>(T[,,] objects)
        {
            var sb = new StringBuilder();
            for (int k = 0; k < objects.GetLength(0); k++)
            {
                if (k != 0) sb.Append("\n");
                sb.Append($"#{k}:\n");
                for (int i = 0; i < objects.GetLength(0); i++)
                {
                    if (i != 0) sb.Append("\n");
                    for (int j = 0; j < objects.GetLength(1); j++)
                    {
                        if (j != 0) sb.Append(" ");
                        sb.Append(objects[k, i, j]);
                    }
                }
            }
            Out(sb.ToString());
        }

        public static string Join<T>(IEnumerable<T> objects)
        {
            return string.Join(" ", objects);
        }

        public static string Concat<T>(IEnumerable<T> objects)
        {
            return string.Join("", objects);
        }

        public static void OutYN(bool b)
        {
            Out(b ? "Yes" : "No");
        }

        public static void Out(object s)
        {
            Console.WriteLine(s);
        }

        public static void Out(params object[] s)
        {
            Console.WriteLine(Join(s));
        }

        public static List<List<List<T>>> AllGrouped<T>(List<T> values)
        {
            return AllGrouped(values, values.Count);
        }

        public static List<List<List<T>>> AllGrouped<T>(IList<T> values, int length)
        {
            var result = new List<List<List<T>>>
            {
                values.Select(x => new List<T>{ x }).ToList()
            };
            for (int i = 1; i <= length; i++)
            {
                foreach (var comb in AllCombination(length, i))
                {
                    var min = comb.Min();
                    var group = new List<T>();
                    var excluded = new List<T>();
                    for (int j = 0; j < length; j++)
                    {
                        if (comb.Contains(j))
                        {
                            group.Add(values[j]);
                        }
                        else if (j > min)
                        {
                            excluded.Add(values[j]);
                        }
                    }
                    foreach (var subgroups in AllGrouped(excluded))
                    {
                        var groups = new List<List<T>> { group };
                        groups.AddRange(subgroups);
                        result.Add(groups);
                    }
                }
            }
            return result;
        }

        // https://webbibouroku.com/Blog/Article/cs-permutation
        public static IEnumerable<int[]> AllPermutation(int n, int r, int begin = 0)
        {
            foreach (var a in AllCombination(n, r, begin))
            {
                while (true)
                {
                    var result = new int[r];
                    Array.Copy(a, result, a.Length);
                    yield return result;

                    // a[i] < a[i + 1]な一番大きいiを探す
                    int i;
                    for (i = r - 2; i >= 0; i--)
                    {
                        if (a[i] < a[i + 1])
                        {
                            break;
                        }
                    }
                    // なかったら（配列が降順にソートされてたら）終了
                    if (i < 0)
                    {
                        break;
                    }

                    // 配列を逆から見てa[i] < a[j]なjを探す
                    int j;
                    for (j = r - 1; j >= 0; j--)
                    {
                        if (a[i] < a[j])
                        {
                            break;
                        }
                    }

                    // a[i]とa[j]を入れ替えてa[>i]を反転
                    (a[i], a[j]) = (a[j], a[i]);
                    Array.Reverse(a, i + 1, r - i - 1);
                }
            }
        }

        public static IEnumerable<int[]> AllCombination(int n, int r, int begin = 0)
        {
            if (n < r)
            {
                yield break;
            }
            int end = begin + n - 1;
            var a = Enumerable.Range(begin, r).ToArray();
            while (true)
            {
                var result = new int[r];
                Array.Copy(a, result, a.Length);
                yield return result;

                int initCnt = 0;
                // 右端の要素から回して
                for (int i = r - 1; i >= 0; i--)
                {
                    // 進められるなら一つ進めてターンエンド
                    if (a[i] < end - initCnt)
                    {
                        a[i]++;
                        break;
                    }
                    // 進められないなら一旦その要素は放っておいてあとで初期化
                    else
                    {
                        initCnt++;
                        continue;
                    }
                }
                // 全要素もう進めないなら終了
                if (initCnt == r)
                {
                    yield break;
                }
                // 初期化（ひとつ左の要素の+1に）
                for (int i = r - initCnt; i < r; i++)
                {
                    a[i] = a[i - 1] + 1;
                }
            }
        }

        public static bool IsIn(this int x, int min, int max)
        {
            return (min <= x && x < max);
        }

        public static bool IsPalindrome(string s)
        {
            for (int i = 0; i < (s.Length + 1) / 2; i++)
                if (s[i] != s[s.Length - 1 - i]) return false;
            return true;
        }

        // https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a
        // mod mにおけるaの逆元
        public static long ModInverse(long a, long m)
        {
            long b = m;
            long u = 1;
            long v = 0;

            while (b >= 1)
            {
                long t = a / b;
                long b2 = a - t * b; a = b; b = b2;
                long v2 = u - t * v; u = v; v = v2;
            }

            u %= m;
            if (u < 0) u += m;
            return u;
        }

        // mod mにおけるa/b
        public static long FractionInMod(long a, long b, long m)
        {
            long lcm = LCM(a, b);
            a /= lcm; b /= lcm;
            return (a * ModInverse(b, m)) % m;
        }

        // https://qiita.com/gushwell/items/f08d0e71fa0480dbb396
        // 最小公倍数
        public static long LCM(long a, long b)
        {
            return a * b / GCD(a, b);
        }

        // 最大公約数
        public static long GCD(long a, long b)
        {
            if (a < b)
                return GCD(b, a);
            while (b != 0)
            {
                var t = a % b;
                a = b;
                b = t;
            }
            return a;
        }

        public static BigInteger LCM(BigInteger a, BigInteger b)
        {
            return a * b / GCD(a, b);
        }

        public static BigInteger GCD(BigInteger a, BigInteger b)
        {
            if (a < b)
                return GCD(b, a);
            while (b != 0)
            {
                var t = a % b;
                a = b;
                b = t;
            }
            return a;
        }
    }
}

namespace InputUtil.Current
{
    #region library
#pragma warning disable CA1050

    /// <summary>
    /// 標準入力の読み取りを簡素化する機能を提供します。
    /// </summary>
    public static class InputUtil
    {
        /// <summary>
        /// 標準入力からスペースで区切られた値を指定の型に変換して読み込みます。
        /// </summary>
        /// <remarks>
        /// 1つの値を読み込むには型を明示し <c>int a = ReadLine&lt;int&gt;()</c> のように書きます。
        /// 定数個の値を読み取るには <c>var (a, b, c) = ReadLine&lt;int&gt;();</c> のように書きます。
        /// 可変個の値を読み取るには <c>foreach (var item in ReadLine&lt;int&gt;())</c> のように書きます。
        /// <c>ToArray()</c> メソッドや Linq も使えます。
        /// </remarks>
        /// <typeparam name="T">変換先の型</typeparam>
        /// <returns>標準入力の読み取り結果。</returns>
        /// <exception cref="FormatException"></exception>
        /// <exception cref="InvalidOperationException"></exception>
        public static InputToken<T, SpanParsableImpl<T>> ReadLine<T>() where T : ISpanParsable<T>
        {
            return new InputToken<T, SpanParsableImpl<T>>(Console.ReadLine() ?? throw new InvalidOperationException());
        }

        /// <summary>
        /// 標準入力から指定の文字で区切られた値を指定の型に変換して読み込みます。
        /// 使用方法は <see cref="ReadLine{T}"/> を参照してください。
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="formatProvider"></param>
        /// <param name="separator"></param>
        /// <returns></returns>
        /// <exception cref="InvalidOperationException"></exception>
        public static InputToken<T, SpanParsableImpl<T>> ReadLine<T>(IFormatProvider formatProvider, char separator) where T : ISpanParsable<T>
        {
            return new InputToken<T, SpanParsableImpl<T>>(Console.ReadLine() ?? throw new InvalidOperationException(), formatProvider, separator);
        }

        /// <summary>
        /// 標準入力からスペースで区切られた文字列を読み込みます。
        /// 使用方法は <see cref="ReadLine{T}"/> を参照してください。
        /// </summary>
        /// <returns></returns>
        /// <exception cref="InvalidOperationException"></exception>
        public static InputToken<string, StringImpl> ReadLine()
        {
            return new InputToken<string, StringImpl>(Console.ReadLine() ?? throw new InvalidOperationException());
        }

        /// <summary>
        /// 標準入力から指定の文字で区切られた文字列を読み込みます。
        /// 使用方法は <see cref="ReadLine{T}"/> を参照してください。
        /// </summary>
        /// <param name="formatProvider"></param>
        /// <param name="separator"></param>
        /// <returns></returns>
        /// <exception cref="InvalidOperationException"></exception>
        public static InputToken<string, StringImpl> ReadLine(IFormatProvider formatProvider, char separator)
        {
            return new InputToken<string, StringImpl>(Console.ReadLine() ?? throw new InvalidOperationException(), formatProvider, separator);
        }
    }

    public interface IReadNextValueImpl<TResult>
    {
        public static abstract TResult ReadNextValue(string input, ref int currentIndex, char separator, IFormatProvider formatProvider);

        public static abstract bool TryReadNextValue(string input, ref int currentIndex, char separator, IFormatProvider formatProvider, out TResult value);
    }

    public readonly struct SpanParsableImpl<T> : IReadNextValueImpl<T> where T : ISpanParsable<T>
    {
        public static T ReadNextValue(string input, ref int currentIndex, char separator, IFormatProvider formatProvider)
        {
            ReadOnlySpan<char> span = input.AsSpan()[currentIndex..];
            var index = span.IndexOf(separator);
            ReadOnlySpan<char> target = index == -1 ? span : span[..index];
            if (target.Length == 0)
            {
                ThrowSeparatorNotFound();
            }
            var value = T.Parse(target, formatProvider);
            currentIndex = index == -1 ? input.Length : currentIndex + index + 1;
            return value;
        }

        private static void ThrowSeparatorNotFound()
        {
            throw new FormatException($"Separator not found");
        }

        public static bool TryReadNextValue(string input, ref int currentIndex, char separator, IFormatProvider formatProvider, out T value)
        {
            ReadOnlySpan<char> span = input.AsSpan()[currentIndex..];
            var index = span.IndexOf(separator);
            ReadOnlySpan<char> target = index == -1 ? span : span[..index];
            if (target.Length == 0)
            {
                value = default!;
                return false;
            }
            value = T.Parse(target, formatProvider);
            currentIndex = index == -1 ? input.Length : currentIndex + index + 1;
            return true;
        }
    }

    public readonly struct StringImpl : IReadNextValueImpl<string>
    {
        public static string ReadNextValue(string input, ref int currentIndex, char separator, IFormatProvider formatProvider)
        {
            ReadOnlySpan<char> span = input.AsSpan()[currentIndex..];
            var index = span.IndexOf(separator);
            ReadOnlySpan<char> target = index == -1 ? span : span[..index];
            if (target.Length == 0)
            {
                ThrowSeparatorNotFound();
            }
            var value = target.ToString();
            currentIndex = index == -1 ? input.Length : currentIndex + index + 1;
            return value;
        }

        private static void ThrowSeparatorNotFound()
        {
            throw new FormatException($"Separator not found");
        }


        public static bool TryReadNextValue(string input, ref int currentIndex, char separator, IFormatProvider formatProvider, out string value)
        {
            ReadOnlySpan<char> span = input.AsSpan()[currentIndex..];
            var index = span.IndexOf(separator);
            ReadOnlySpan<char> target = index == -1 ? span : span[..index];
            if (target.Length == 0)
            {
                value = default!;
                return false;
            }
            value = target.ToString();
            currentIndex = index == -1 ? input.Length : currentIndex + index + 1;
            return true;
        }
    }

    public struct InputToken<TResult, TImpl> : IEnumerable<TResult>, IEnumerator<TResult> where TImpl : IReadNextValueImpl<TResult>
    {
        private readonly string _input;

        private int _currentIndex;

        private readonly IFormatProvider _formatProvider;

        private readonly char _separator;

#pragma warning disable CS8618 // Property Current is initialized in MoveNext
        public InputToken(string input)
        {
            _input = input;
            _formatProvider = System.Globalization.CultureInfo.InvariantCulture;
            _separator = ' ';
        }

        public InputToken(string input, IFormatProvider formatProvider, char separator)
        {
            _input = input;
            _formatProvider = formatProvider;
            _separator = separator;
        }
#pragma warning restore CS8618

        public static implicit operator TResult(InputToken<TResult, TImpl> token)
        {
            return token.ReadNextValue();
        }

        public void Deconstruct(out TResult val1, out TResult val2)
        {
            val1 = ReadNextValue();
            val2 = ReadNextValue();
        }

        public void Deconstruct(out TResult val1, out TResult val2, out TResult val3)
        {
            val1 = ReadNextValue();
            val2 = ReadNextValue();
            val3 = ReadNextValue();
        }

        public void Deconstruct(out TResult val1, out TResult val2, out TResult val3, out TResult val4)
        {
            val1 = ReadNextValue();
            val2 = ReadNextValue();
            val3 = ReadNextValue();
            val4 = ReadNextValue();
        }

        public void Deconstruct(out TResult val1, out TResult val2, out TResult val3, out TResult val4, out TResult val5)
        {
            val1 = ReadNextValue();
            val2 = ReadNextValue();
            val3 = ReadNextValue();
            val4 = ReadNextValue();
            val5 = ReadNextValue();
        }

        public void Deconstruct(out TResult val1, out TResult val2, out TResult val3, out TResult val4, out TResult val5, out TResult val6)
        {
            val1 = ReadNextValue();
            val2 = ReadNextValue();
            val3 = ReadNextValue();
            val4 = ReadNextValue();
            val5 = ReadNextValue();
            val6 = ReadNextValue();
        }

        public void Deconstruct(out TResult val1, out TResult val2, out TResult val3, out TResult val4, out TResult val5, out TResult val6, out TResult val7)
        {
            val1 = ReadNextValue();
            val2 = ReadNextValue();
            val3 = ReadNextValue();
            val4 = ReadNextValue();
            val5 = ReadNextValue();
            val6 = ReadNextValue();
            val7 = ReadNextValue();
        }

        public void Deconstruct(out TResult val1, out TResult val2, out TResult val3, out TResult val4, out TResult val5, out TResult val6, out TResult val7, out TResult val8)
        {
            val1 = ReadNextValue();
            val2 = ReadNextValue();
            val3 = ReadNextValue();
            val4 = ReadNextValue();
            val5 = ReadNextValue();
            val6 = ReadNextValue();
            val7 = ReadNextValue();
            val8 = ReadNextValue();
        }

        private TResult ReadNextValue()
        {
            return TImpl.ReadNextValue(_input, ref _currentIndex, _separator, _formatProvider);
        }

        public readonly InputToken<TResult, TImpl> GetEnumerator()
        {
            return this;
        }

        public TResult Current { get; private set; }

        readonly object IEnumerator.Current => Current!;

        public bool MoveNext()
        {
            var val = TImpl.TryReadNextValue(_input, ref _currentIndex, _separator, _formatProvider, out TResult? current);
            Current = current;
            return val;
        }

        public TResult[] ToArray()
        {
            if (_input.Length == 0)
            {
                return Array.Empty<TResult>();
            }
            ref var begin = ref Unsafe.As<char, ushort>(ref MemoryMarshal.GetReference(_input.AsSpan()));
            var count = SpanHelpers.CountValueType(ref begin, _separator, _input.Length) + (_input[^1] == _separator ? 0 : 1);
            var array = new TResult[count];
            for (var i = 0; i < array.Length; i++)
            {
                array[i] = ReadNextValue();
            }
            return array;
        }

        readonly IEnumerator<TResult> IEnumerable<TResult>.GetEnumerator()
        {
            return this;
        }

        readonly IEnumerator IEnumerable.GetEnumerator()
        {
            return this;
        }

        void IEnumerator.Reset()
        {
            _currentIndex = 0;
        }

        readonly void IDisposable.Dispose()
        {

        }
    }

    // Source: [System.Private.CoreLib]System.SpanHelpers
    internal static class SpanHelpers
    {
        public static int CountValueType<T>(ref T current, T value, int length) where T : struct, IEquatable<T>?
        {
            var count = 0;
            ref T end = ref Unsafe.Add(ref current, length);

            if (Vector128.IsHardwareAccelerated && length >= Vector128<T>.Count)
            {
                // Vector512 is not supported on .NET 7.0 so Vector512 code is not included.
                if (Vector256.IsHardwareAccelerated && length >= Vector256<T>.Count)
                {
                    var targetVector = Vector256.Create(value);
                    ref T oneVectorAwayFromEnd = ref Unsafe.Subtract(ref end, Vector256<T>.Count);
                    do
                    {
                        count += BitOperations.PopCount(Vector256.Equals(Vector256.LoadUnsafe(ref current), targetVector).ExtractMostSignificantBits());
                        current = ref Unsafe.Add(ref current, Vector256<T>.Count);
                    }
                    while (!Unsafe.IsAddressGreaterThan(ref current, ref oneVectorAwayFromEnd));

                    // If there are just a few elements remaining, then processing these elements by the scalar loop
                    // is cheaper than doing bitmask + popcount on the full last vector. To avoid complicated type
                    // based checks, other remainder-count based logic to determine the correct cut-off, for simplicity
                    // a half-vector size is chosen (based on benchmarks).
                    var remaining = (uint)Unsafe.ByteOffset(ref current, ref end) / (uint)Unsafe.SizeOf<T>();
                    if (remaining > Vector256<T>.Count / 2)
                    {
                        var mask = Vector256.Equals(Vector256.LoadUnsafe(ref oneVectorAwayFromEnd), targetVector).ExtractMostSignificantBits();

                        // The mask contains some elements that may be double-checked, so shift them away in order to get the correct pop-count.
                        var overlaps = (uint)Vector256<T>.Count - remaining;
                        mask >>= (int)overlaps;
                        count += BitOperations.PopCount(mask);

                        return count;
                    }
                }
                else
                {
                    var targetVector = Vector128.Create(value);
                    ref T oneVectorAwayFromEnd = ref Unsafe.Subtract(ref end, Vector128<T>.Count);
                    do
                    {
                        count += BitOperations.PopCount(Vector128.Equals(Vector128.LoadUnsafe(ref current), targetVector).ExtractMostSignificantBits());
                        current = ref Unsafe.Add(ref current, Vector128<T>.Count);
                    }
                    while (!Unsafe.IsAddressGreaterThan(ref current, ref oneVectorAwayFromEnd));

                    var remaining = (uint)Unsafe.ByteOffset(ref current, ref end) / (uint)Unsafe.SizeOf<T>();
                    if (remaining > Vector128<T>.Count / 2)
                    {
                        var mask = Vector128.Equals(Vector128.LoadUnsafe(ref oneVectorAwayFromEnd), targetVector).ExtractMostSignificantBits();

                        // The mask contains some elements that may be double-checked, so shift them away in order to get the correct pop-count.
                        var overlaps = (uint)Vector128<T>.Count - remaining;
                        mask >>= (int)overlaps;
                        count += BitOperations.PopCount(mask);

                        return count;
                    }
                }
            }

            while (Unsafe.IsAddressLessThan(ref current, ref end))
            {
                if (current.Equals(value))
                {
                    count++;
                }

                current = ref Unsafe.Add(ref current, 1);
            }

            return count;
        }
    }

    #endregion
}