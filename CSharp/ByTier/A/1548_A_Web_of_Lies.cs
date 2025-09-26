using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using static System.Math;
using System.Text;
using System.Threading;
using System.Globalization;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using Library;

namespace Program
{
    public static class ProblemA
    {
        static bool SAIKI = false;
        static public int numberOfRandomCases = 0;
        static public void MakeTestCase(List<string> _input, List<string> _output, ref Func<string[], bool> _outputChecker)
        {
        }
        static public void Solve()
        {
            var n = NN;
            var m = NN;
            var uv = Repeat(0, m).Select(_ => new { u = NN - 1, v = NN - 1 }).ToArray();
            var q = NN;
            var dic = new LIB_Dict<long, long>();
            var ans = n;
            foreach (var item in uv)
            {
                var min = Min(item.u, item.v);
                var max = Max(item.u, item.v);
                dic[min]++;
            }
            for (var i = 0; i < q; ++i)
            {
                var t = NN;
                if (t == 1)
                {
                    var u = NN - 1;
                    var v = NN - 1;
                    var min = Min(u, v);
                    var max = Max(u, v);
                    dic[min]++;
                }
                else if (t == 2)
                {
                    var u = NN - 1;
                    var v = NN - 1;
                    var min = Min(u, v);
                    var max = Max(u, v);
                    dic[min]--;
                    if (dic[min] == 0) dic.Remove(min);
                }
                else
                {
                    Console.WriteLine(ans - dic.Count);
                }
            }
        }
        class Printer : StreamWriter
        {
            public override IFormatProvider FormatProvider { get { return CultureInfo.InvariantCulture; } }
            public Printer(Stream stream) : base(stream, new UTF8Encoding(false, true)) { base.AutoFlush = false; }
            public Printer(Stream stream, Encoding encoding) : base(stream, encoding) { base.AutoFlush = false; }
        }
        static LIB_FastIO fastio = new LIB_FastIODebug();
        static public void Main(string[] args) { if (args.Length == 0) { fastio = new LIB_FastIO(); Console.SetOut(new Printer(Console.OpenStandardOutput())); } if (SAIKI) { var t = new Thread(Solve, 134217728); t.Start(); t.Join(); } else Solve(); Console.Out.Flush(); }
        static long NN => fastio.Long();
        static double ND => fastio.Double();
        static string NS => fastio.Scan();
        static long[] NNList(long N) => Repeat(0, N).Select(_ => NN).ToArray();
        static double[] NDList(long N) => Repeat(0, N).Select(_ => ND).ToArray();
        static string[] NSList(long N) => Repeat(0, N).Select(_ => NS).ToArray();
        static long Count<T>(this IEnumerable<T> x, Func<T, bool> pred) => Enumerable.Count(x, pred);
        static IEnumerable<T> Repeat<T>(T v, long n) => Enumerable.Repeat<T>(v, (int)n);
        static IEnumerable<int> Range(long s, long c) => Enumerable.Range((int)s, (int)c);
        static IOrderedEnumerable<T> OrderByRand<T>(this IEnumerable<T> x) => Enumerable.OrderBy(x, _ => xorshift);
        static IOrderedEnumerable<T> OrderBy<T>(this IEnumerable<T> x) => Enumerable.OrderBy(x.OrderByRand(), e => e);
        static IOrderedEnumerable<T1> OrderBy<T1, T2>(this IEnumerable<T1> x, Func<T1, T2> selector) => Enumerable.OrderBy(x.OrderByRand(), selector);
        static IOrderedEnumerable<T> OrderByDescending<T>(this IEnumerable<T> x) => Enumerable.OrderByDescending(x.OrderByRand(), e => e);
        static IOrderedEnumerable<T1> OrderByDescending<T1, T2>(this IEnumerable<T1> x, Func<T1, T2> selector) => Enumerable.OrderByDescending(x.OrderByRand(), selector);
        static IOrderedEnumerable<string> OrderBy(this IEnumerable<string> x) => x.OrderByRand().OrderBy(e => e, StringComparer.OrdinalIgnoreCase);
        static IOrderedEnumerable<T> OrderBy<T>(this IEnumerable<T> x, Func<T, string> selector) => x.OrderByRand().OrderBy(selector, StringComparer.OrdinalIgnoreCase);
        static IOrderedEnumerable<string> OrderByDescending(this IEnumerable<string> x) => x.OrderByRand().OrderByDescending(e => e, StringComparer.OrdinalIgnoreCase);
        static IOrderedEnumerable<T> OrderByDescending<T>(this IEnumerable<T> x, Func<T, string> selector) => x.OrderByRand().OrderByDescending(selector, StringComparer.OrdinalIgnoreCase);
        static string Join<T>(this IEnumerable<T> x, string separator = "") => string.Join(separator, x);
        static uint xorshift { get { _xsi.MoveNext(); return _xsi.Current; } }
        static IEnumerator<uint> _xsi = _xsc();
        static IEnumerator<uint> _xsc() { uint x = 123456789, y = 362436069, z = 521288629, w = (uint)(DateTime.Now.Ticks & 0xffffffff); while (true) { var t = x ^ (x << 11); x = y; y = z; z = w; w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)); yield return w; } }
        static bool Chmax<T>(this ref T lhs, T rhs) where T : struct, IComparable<T> { if (lhs.CompareTo(rhs) < 0) { lhs = rhs; return true; } return false; }
        static bool Chmin<T>(this ref T lhs, T rhs) where T : struct, IComparable<T> { if (lhs.CompareTo(rhs) > 0) { lhs = rhs; return true; } return false; }
        static void Fill<T>(this T[] array, T value) => array.AsSpan().Fill(value);
        static void Fill<T>(this T[,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0], array.Length).Fill(value);
        static void Fill<T>(this T[,,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0, 0], array.Length).Fill(value);
        static void Fill<T>(this T[,,,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0, 0, 0], array.Length).Fill(value);
    }
}
namespace Library {
    class LIB_Dict<K, V> : Dictionary<K, V>
    {
        Func<K, V> d;
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public LIB_Dict(Func<K, V> _d) { d = _d; }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public LIB_Dict() : this(_ => default(V)) { }
        new public V this[K i]
        {
            get
            {
                return TryGetValue(i, out var v) ? v : base[i] = d(i);
            }
            set
            {
                base[i] = value;
            }
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public override int GetHashCode()
        {
            unchecked
            {
                var ret = 23;
                for (var e = GetEnumerator(); e.MoveNext();) ret = (ret * 37) ^ (e.Current.Key.GetHashCode() << 5 + e.Current.Key.GetHashCode()) ^ e.Current.Value.GetHashCode();
                return ret;
            }
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public override bool Equals(object obj)
        {
            var o = (LIB_Dict<K, V>)obj;
            foreach (var kv in o)
            {
                if (!ContainsKey(kv.Key) || !this[kv.Key].Equals(kv.Value))
                    return false;
            }
            return o.Count == Count;
        }
    }
    class LIB_FastIO
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public LIB_FastIO() { str = Console.OpenStandardInput(); }
        readonly Stream str;
        readonly byte[] buf = new byte[2048];
        int len, ptr;
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        byte read()
        {
            if (ptr >= len)
            {
                ptr = 0;
                if ((len = str.Read(buf, 0, 2048)) <= 0)
                {
                    return 0;
                }
            }
            return buf[ptr++];
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        char Char()
        {
            byte b = 0;
            do b = read();
            while (b < 33 || 126 < b);
            return (char)b;
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        virtual public string Scan()
        {
            var sb = new StringBuilder();
            for (var b = Char(); b >= 33 && b <= 126; b = (char)read())
                sb.Append(b);
            return sb.ToString();
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        virtual public long Long()
        {
            long ret = 0; byte b = 0; var ng = false;
            do b = read();
            while (b != '-' && (b < '0' || '9' < b));
            if (b == '-') { ng = true; b = read(); }
            for (; true; b = read())
            {
                if (b < '0' || '9' < b)
                    return ng ? -ret : ret;
                else ret = (ret << 3) + (ret << 1) + b - '0';
            }
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        virtual public double Double() { return double.Parse(Scan(), CultureInfo.InvariantCulture); }
    }
    class LIB_FastIODebug : LIB_FastIO
    {
        Queue<string> param = new Queue<string>();
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        string NextString() { if (param.Count == 0) foreach (var item in Console.ReadLine().Split(' ')) param.Enqueue(item); return param.Dequeue(); }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public LIB_FastIODebug() { }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public override string Scan() => NextString();
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public override long Long() => long.Parse(NextString());
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public override double Double() => double.Parse(NextString());
    }
}
