using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using static System.Console;

#nullable enable
namespace A
{
    internal static class Program
    {
        private static void Main()
        {
            GC.TryStartNoGCRegion(100_000_000);

            var n = Input().As<long>();

            const long doubleMaxDelta = 2 * 1000;
            var top = Math.Min(Sqrt2(n) + doubleMaxDelta, n - 1);

            var minResult = long.MaxValue;
            for (var i = 2; i <= top; i += 1)
                if (n % i == 0)
                {
                    if (minResult == long.MaxValue)
                        minResult = i;
                    break;
                }

            if (minResult is long.MaxValue)
                Out.WriteLine(n.ToString());
            else
            {
                while (n % minResult == 0)
                    n /= minResult;
                
                if (n == 1)
                    Out.WriteLine(minResult.ToString());
                else
                    Out.WriteLine(1.ToString());
            }
        }

        public static bool IsPrime(this int number)
        {
            const int doubleMaxDelta = 2 * 1000;
            if (number <= 2) return true;
            if (number % 2 == 0) return false;
            var top = Math.Min(((float)number).Sqrt2() + doubleMaxDelta, number - 1);
            for (var i = 3; i <= top; i += 2)
                if (number % i == 0)
                    return false;
            return true;
        }

        /// <summary>
        ///     Approximation sqrt
        /// </summary>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static float Sqrt2(this float z)
        {
            if (z == 0) return 0;
            FloatIntUnion u;
            u.@int = 0;
            var half = 0.5f * z;
            u.@float = z;
            u.@int = 0x5f375a86 - (u.@int >> 1);
            u.@float *= 1.5f - half * u.@float * u.@float;
            return u.@float * z;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static int IntSqrt(this int num)
        {
            if (0 == num) return 0;
            var n = num / 2 + 1;
            var n1 = (n + num / n) / 2;
            while (n1 < n)
            {
                n = n1;
                n1 = (n + num / n) / 2;
            }

            return n;
        }


        #region linqutils

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static TSource MinBy<TSource, TKey>(
            this IEnumerable<TSource> source,
            Func<TSource, TKey> selector,
            Comparer<TKey>? comparer = null)
        {
            if (source == null) throw new ArgumentNullException(nameof(source));
            if (selector == null) throw new ArgumentNullException(nameof(selector));
            comparer ??= Comparer<TKey>.Default;

            using var sourceIterator = source.GetEnumerator();
            if (!sourceIterator.MoveNext()) throw new InvalidOperationException("Sequence contains no elements");

            var min = sourceIterator.Current;
            var minKey = selector(min);
            while (sourceIterator.MoveNext())
            {
                var candidate = sourceIterator.Current;
                var candidateProjected = selector(candidate);
                if (comparer.Compare(candidateProjected, minKey) < 0)
                {
                    min = candidate;
                    minKey = candidateProjected;
                }
            }

            return min;
        }

        #endregion

        [StructLayout(LayoutKind.Explicit)]
        private struct FloatIntUnion
        {
            [FieldOffset(0)] public float @float;

            [FieldOffset(0)] public int @int;
        }

        #region stdutils

#if FILE_OUTOUT
        private static readonly string ProjectDirectory =
            Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.FullName;

        private static readonly string OutPutFileName = Path.Combine(ProjectDirectory, "output.txt");
        private static readonly string InputFileName = Path.Combine(ProjectDirectory, "input.txt");

        static Program()
        {
            File.Delete(OutPutFileName);

            var writer = new StreamWriter(OutPutFileName, true);
            writer.AutoFlush = true;
            SetOut(writer);

            var reader = new StreamReader(InputFileName);
            SetIn(reader);
        }
#endif
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static void Print(string value)
        {
            Out.WriteLine(value);
        }


        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static string Input()
        {
            return In.ReadLine()?.Trim() ?? throw new Exception("Empty input");
        }


        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static T As<T>(this string str) where T : IConvertible
        {
            if (typeof(T) == typeof(int))
                return (T)(object)int.Parse(str);
            if (typeof(T) == typeof(long))
                return (T)(object)long.Parse(str);
            if (typeof(T) == typeof(string))
                return (T)(object)str;
            if (typeof(T) == typeof(short))
                return (T)(object)short.Parse(str);

            return (T)Convert.ChangeType(str, typeof(T));
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static IEnumerable<T> AsArray<T>(this string str, string separator = " ") where T : IConvertible
        {
            return str.Split(separator).Select(As<T>);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static (T1, T2) As<T1, T2>(this string str, string separator = " ")
            where T1 : IConvertible where T2 : IConvertible
        {
            var items = str.Split(separator);

            return (items[0].As<T1>(), items[1].As<T2>());
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static (T1, T2, T3) As<T1, T2, T3>(this string str, string separator = " ") where T1 : IConvertible
            where T2 : IConvertible
            where T3 : IConvertible
        {
            var items = str.Split(separator);

            return (items[0].As<T1>(), items[1].As<T2>(), items[2].As<T3>());
        }


        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static (T1, T2, T3, T4) As<T1, T2, T3, T4>(this string str, string separator = " ")
            where T1 : IConvertible
            where T2 : IConvertible
            where T3 : IConvertible
            where T4 : IConvertible
        {
            var items = str.Split(separator);

            return (items[0].As<T1>(), items[1].As<T2>(), items[2].As<T3>(), items[3].As<T4>());
        }

        #endregion

        #region geometry

        #endregion
    }
}