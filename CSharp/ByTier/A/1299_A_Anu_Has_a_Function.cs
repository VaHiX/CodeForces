using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Threading;
using System.Runtime.CompilerServices;
using System.Text;
using System.Diagnostics;
using System.Numerics;
using static System.Console;
using static System.Convert;
using static System.Math;
using static Template;
using SC = Scanner;

public partial class Solver
{
    public void Solve()
    {
        var N = sc.Int;
        var A = sc.ArrInt;
        var ct = new int[31];
        for(int i = 0; i < N; i++)
        {
            for (int j = 0; j < 31; j++)
                if ((1 & A[i] >> j) == 1) ct[j]++;
        }
        var res = 0L;int idx = 0;
        for(int i = 0; i < N; i++)
        {
            var calc = 0L;
            for (int j = 0; j < 31; j++)
                calc += ToInt64(ct[j] == 1) * (1 & A[i] >> j) * (1L << j);
            if (chmax(ref res, calc)) idx = i;

        }
        var r = new List<int> { A[idx] };
        for (int i = 0; i < N; i++)
        {
            if (i != idx) r.Add(A[i]);
        }
        Console.WriteLine(string.Join(" ", r));
    }
}

#region Template
public partial class Solver
{
    public SC sc = new SC();
    static void Main(string[] args)
    {
        Console.SetOut(new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false });
        var sol = new Solver();
        int testcase = 1;
        //testcase = sol.sc.Int;
        //var th = new Thread(sol.Solve, 1 << 26);th.Start();th.Join();
        while (testcase-- > 0)
            sol.Solve();
        Console.Out.Flush();
    }
}
public static class Template
{
    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool chmin<T>(ref T a, T b) where T : IComparable<T> { if (a.CompareTo(b) > 0) { a = b; return true; } return false; }
    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool chmax<T>(ref T a, T b) where T : IComparable<T> { if (a.CompareTo(b) < 0) { a = b; return true; } return false; }
    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static void swap<T>(ref T a, ref T b) { var t = b; b = a; a = t; }
    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static void swap<T>(this IList<T> A, int i, int j) { var t = A[i]; A[i] = A[j]; A[j] = t; }
    public static T[] Create<T>(int n, Func<T> f) { var rt = new T[n]; for (var i = 0; i < rt.Length; ++i) rt[i] = f(); return rt; }
    public static T[] Create<T>(int n, Func<int, T> f) { var rt = new T[n]; for (var i = 0; i < rt.Length; ++i) rt[i] = f(i); return rt; }
    public static void Out<T>(this IList<T> A, out T a) => a = A[0];
    public static void Out<T>(this IList<T> A, out T a, out T b) { a = A[0]; b = A[1]; }
    public static void Out<T>(this IList<T> A, out T a, out T b, out T c) { A.Out(out a, out b); c = A[2]; }
    public static void Out<T>(this IList<T> A, out T a, out T b, out T c, out T d) { A.Out(out a, out b, out c); d = A[3]; }
    public static string Concat<T>(this IEnumerable<T> A, string sp) => string.Join(sp, A);
    public static char ToChar(this int s, char begin = '0') => (char)(s + begin);
    public static IEnumerable<T> Shuffle<T>(this IEnumerable<T> A) => A.OrderBy(v => Guid.NewGuid());
    public static int CompareTo<T>(this T[] A, T[] B, Comparison<T> cmp = null) { cmp = cmp ?? Comparer<T>.Default.Compare; for (var i = 0; i < Min(A.Length, B.Length); i++) { int c = cmp(A[i], B[i]); if (c > 0) return 1; else if (c < 0) return -1; } if (A.Length == B.Length) return 0; if (A.Length > B.Length) return 1; else return -1; }
    public static string ToStr<T>(this T[][] A) => A.Select(a => a.Concat(" ")).Concat("\n");
    public static int ArgMax<T>(this IList<T> A, Comparison<T> cmp = null) { cmp = cmp ?? Comparer<T>.Default.Compare; T max = A[0]; int rt = 0; for (int i = 1; i < A.Count; i++) if (cmp(max, A[i]) < 0) { max = A[i]; rt = i; } return rt; }
    public static T PopBack<T>(this List<T> A) { var v = A[A.Count - 1]; A.RemoveAt(A.Count - 1); return v; }
    public static void Fail<T>(T s) { Console.WriteLine(s); Console.Out.Close(); Environment.Exit(0); }
}
public class Scanner
{
    public string Str => Console.ReadLine().Trim();
    public int Int => int.Parse(Str);
    public long Long => long.Parse(Str);
    public double Double => double.Parse(Str);
    public int[] ArrInt => Str.Split(' ').Select(int.Parse).ToArray();
    public long[] ArrLong => Str.Split(' ').Select(long.Parse).ToArray();
    public char[][] Grid(int n) => Create(n, () => Str.ToCharArray());
    public int[] ArrInt1D(int n) => Create(n, () => Int);
    public long[] ArrLong1D(int n) => Create(n, () => Long);
    public int[][] ArrInt2D(int n) => Create(n, () => ArrInt);
    public long[][] ArrLong2D(int n) => Create(n, () => ArrLong);
    private Queue<string> q = new Queue<string>();
    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public T Next<T>() { if (q.Count == 0) foreach (var item in Str.Split(' ')) q.Enqueue(item); return (T)Convert.ChangeType(q.Dequeue(), typeof(T)); }
    public void Make<T1>(out T1 v1) => v1 = Next<T1>();
    public void Make<T1, T2>(out T1 v1, out T2 v2) { v1 = Next<T1>(); v2 = Next<T2>(); }
    public void Make<T1, T2, T3>(out T1 v1, out T2 v2, out T3 v3) { Make(out v1, out v2); v3 = Next<T3>(); }
    public void Make<T1, T2, T3, T4>(out T1 v1, out T2 v2, out T3 v3, out T4 v4) { Make(out v1, out v2, out v3); v4 = Next<T4>(); }
    public void Make<T1, T2, T3, T4, T5>(out T1 v1, out T2 v2, out T3 v3, out T4 v4, out T5 v5) { Make(out v1, out v2, out v3, out v4); v5 = Next<T5>(); }
    public void Make<T1, T2, T3, T4, T5, T6>(out T1 v1, out T2 v2, out T3 v3, out T4 v4, out T5 v5, out T6 v6) { Make(out v1, out v2, out v3, out v4, out v5); v6 = Next<T6>(); }
    public void Make<T1, T2, T3, T4, T5, T6, T7>(out T1 v1, out T2 v2, out T3 v3, out T4 v4, out T5 v5, out T6 v6, out T7 v7) { Make(out v1, out v2, out v3, out v4, out v5, out v6); v7 = Next<T7>(); }
    public (T1, T2) Make<T1, T2>() { Make(out T1 v1, out T2 v2); return (v1, v2); }
    public (T1, T2, T3) Make<T1, T2, T3>() { Make(out T1 v1, out T2 v2, out T3 v3); return (v1, v2, v3); }
    public (T1, T2, T3, T4) Make<T1, T2, T3, T4>() { Make(out T1 v1, out T2 v2, out T3 v3, out T4 v4); return (v1, v2, v3, v4); }
}

#endregion