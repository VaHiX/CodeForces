using System;
using System.Buffers;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Runtime.Intrinsics.X86;
using CodeforcesRound543Div1.Problems;

namespace CodeforcesRound543Div1.Problems
{
    public class ProblemA : ProblemBase
    {
        public ProblemA() : base(false) { }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        protected override void SolveEach(IOManager io)
        {
            var flowerCount = io.ReadInt();
            var wreathLength = io.ReadInt();
            var citizens = io.ReadInt();
            var neededCount = io.ReadInt();
            var flowers = io.ReadIntArray(flowerCount);
            var needed = io.ReadIntArray(neededCount);

            for (var i = 0; i < flowers.Length; i++)
            {
                flowers[i]--;
            }

            var neededCounts = new int[500000];
            var counts = new int[500000];
            var set = new HashSet<int>();

            for (var i = 0; i < needed.Length; i++)
            {
                needed[i]--;
                neededCounts[needed[i]]++;
                set.Add(needed[i]);
            }

            var surplus = flowerCount - citizens * wreathLength;
            var width = surplus + wreathLength;

            for (var i = 0; i < width; i++)
            {
                var flower = flowers[i];
                if (neededCounts[flower] > 0)
                {
                    counts[flower]++;
                    if (counts[flower] >= neededCounts[flower])
                    {
                        set.Remove(flower);
                    }
                }
            }

            if (set.Count == 0)
            {
                var results = GetToRemove(0);
                io.WriteLine(results.Count);
                io.WriteLine(results, ' ');
                return;
            }

            for (var i = width; i < flowers.Length; i++)
            {
                var flower = flowers[i];
                if (neededCounts[flower] > 0)
                {
                    counts[flower]++;
                    if (counts[flower] >= neededCounts[flower])
                    {
                        set.Remove(flower);
                    }
                }

                var toRemove = i - width;
                var left = toRemove + 1;
                var removedFlower = flowers[toRemove];

                if (neededCounts[removedFlower] > 0)
                {
                    counts[removedFlower]--;
                    if (counts[removedFlower] < neededCounts[removedFlower])
                    {
                        set.Add(removedFlower);
                    }
                }

                if (set.Count == 0 && left % wreathLength == 0)
                {
                    var results = GetToRemove(left);
                    io.WriteLine(results.Count);
                    io.WriteLine(results, ' ');
                    return;
                }
            }

            io.WriteLine(-1);

            List<int> GetToRemove(int left)
            {
                var results = new List<int>();
                var counts = new int[500000];
                var span = flowers.AsSpan(left, width);
                var removed = 0;

                for (var i = 0; i < span.Length; i++)
                {
                    var flower = span[i];
                    if (counts[flower] < neededCounts[flower])
                    {
                        counts[flower]++;
                    }
                    else if (removed < surplus)
                    {
                        results.Add(left + i + 1);
                        removed++;
                    }
                }

                return results;
            }
        }
    }
}

namespace CodeforcesRound543Div1
{
    class Program
    {
        static void Main(string[] args)
        {
            IProblem question = new ProblemA();
            using var io = new IOManager(Console.OpenStandardInput(), Console.OpenStandardOutput());
            question.Solve(io);
        }
    }
}

#region Base Class

namespace CodeforcesRound543Div1.Problems
{
    public interface IProblem
    {
        string Solve(string input);
        void Solve(IOManager io);
    }

    public abstract class ProblemBase : IProblem
    {
        protected bool HasMultiTestCases { get; }

        protected ProblemBase(bool hasMultiTestCases) => HasMultiTestCases = hasMultiTestCases;

        public string Solve(string input)
        {
            var inputStream = new MemoryStream(Encoding.UTF8.GetBytes(input));
            var outputStream = new MemoryStream();
            using var manager = new IOManager(inputStream, outputStream);

            Solve(manager);
            manager.Flush();

            outputStream.Seek(0, SeekOrigin.Begin);
            var reader = new StreamReader(outputStream);
            return reader.ReadToEnd();
        }

        public void Solve(IOManager io)
        {
            var tests = HasMultiTestCases ? io.ReadInt() : 1;

            for (var t = 0; t < tests; t++)
            {
                SolveEach(io);
            }
        }

        protected abstract void SolveEach(IOManager io);
    }
}

#endregion

#region Utils

namespace CodeforcesRound543Div1
{
    public class IOManager : IDisposable
    {
        private readonly BinaryReader _reader;
        private readonly StreamWriter _writer;
        private bool _disposedValue;
        private byte[] _buffer = new byte[1024];
        private int _length;
        private int _cursor;
        private bool _eof;

        const char ValidFirstChar = '!';
        const char ValidLastChar = '~';

        public IOManager(Stream input, Stream output)
        {
            _reader = new BinaryReader(input);
            _writer = new StreamWriter(output) { AutoFlush = false };
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private char ReadAscii()
        {
            if (_cursor == _length)
            {
                _cursor = 0;
                _length = _reader.Read(_buffer);

                if (_length == 0)
                {
                    if (!_eof)
                    {
                        _eof = true;
                        return char.MinValue;
                    }
                    else
                    {
                        ThrowEndOfStreamException();
                    }
                }
            }

            return (char)_buffer[_cursor++];
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public char ReadChar()
        {
            char c;
            while (!IsValidChar(c = ReadAscii())) { }
            return c;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public string ReadString()
        {
            var builder = new StringBuilder();
            char c;
            while (!IsValidChar(c = ReadAscii())) { }

            do
            {
                builder.Append(c);
            } while (IsValidChar(c = ReadAscii()));

            return builder.ToString();
        }

        public int ReadInt() => (int)ReadLong();

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public long ReadLong()
        {
            long result = 0;
            bool isPositive = true;
            char c;

            while (!IsNumericChar(c = ReadAscii())) { }

            if (c == '-')
            {
                isPositive = false;
                c = ReadAscii();
            }

            do
            {
                result *= 10;
                result += c - '0';
            } while (IsNumericChar(c = ReadAscii()));

            return isPositive ? result : -result;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private Span<char> ReadChunk(Span<char> span)
        {
            var i = 0;
            char c;
            while (!IsValidChar(c = ReadAscii())) { }

            do
            {
                span[i++] = c;
            } while (IsValidChar(c = ReadAscii()));

            return span.Slice(0, i);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public double ReadDouble() => double.Parse(ReadChunk(stackalloc char[32]));

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public decimal ReadDecimal() => decimal.Parse(ReadChunk(stackalloc char[32]));

        public int[] ReadIntArray(int n)
        {
            var a = new int[n];
            for (int i = 0; i < a.Length; i++)
            {
                a[i] = ReadInt();
            }
            return a;
        }

        public long[] ReadLongArray(int n)
        {
            var a = new long[n];
            for (int i = 0; i < a.Length; i++)
            {
                a[i] = ReadLong();
            }
            return a;
        }

        public double[] ReadDoubleArray(int n)
        {
            var a = new double[n];
            for (int i = 0; i < a.Length; i++)
            {
                a[i] = ReadDouble();
            }
            return a;
        }

        public decimal[] ReadDecimalArray(int n)
        {
            var a = new decimal[n];
            for (int i = 0; i < a.Length; i++)
            {
                a[i] = ReadDecimal();
            }
            return a;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void Write<T>(T value) => _writer.Write(value.ToString());

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public void WriteLine<T>(T value) => _writer.WriteLine(value.ToString());

        public void WriteLine<T>(IEnumerable<T> values, char separator)
        {
            var e = values.GetEnumerator();
            if (e.MoveNext())
            {
                _writer.Write(e.Current.ToString());

                while (e.MoveNext())
                {
                    _writer.Write(separator);
                    _writer.Write(e.Current.ToString());
                }
            }

            _writer.WriteLine();
        }

        public void WriteLine<T>(T[] values, char separator) => WriteLine((ReadOnlySpan<T>)values, separator);
        public void WriteLine<T>(Span<T> values, char separator) => WriteLine((ReadOnlySpan<T>)values, separator);

        public void WriteLine<T>(ReadOnlySpan<T> values, char separator)
        {
            for (int i = 0; i < values.Length - 1; i++)
            {
                _writer.Write(values[i]);
                _writer.Write(separator);
            }

            if (values.Length > 0)
            {
                _writer.Write(values[^1]);
            }

            _writer.WriteLine();
        }

        public void Flush() => _writer.Flush();

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static bool IsValidChar(char c) => ValidFirstChar <= c && c <= ValidLastChar;

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static bool IsNumericChar(char c) => ('0' <= c && c <= '9') || c == '-';

        private void ThrowEndOfStreamException() => throw new EndOfStreamException();

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposedValue)
            {
                if (disposing)
                {
                    _reader.Dispose();
                    _writer.Flush();
                    _writer.Dispose();
                }

                _disposedValue = true;
            }
        }

        public void Dispose()
        {
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }
    }

    public static class UtilExtensions
    {
        public static bool ChangeMax<T>(ref this T value, T other) where T : struct, IComparable<T>
        {
            if (value.CompareTo(other) < 0)
            {
                value = other;
                return true;
            }
            return false;
        }

        public static bool ChangeMin<T>(ref this T value, T other) where T : struct, IComparable<T>
        {
            if (value.CompareTo(other) > 0)
            {
                value = other;
                return true;
            }
            return false;
        }

        public static void SwapIfLargerThan<T>(ref this T a, ref T b) where T : struct, IComparable<T>
        {
            if (a.CompareTo(b) > 0)
            {
                (a, b) = (b, a);
            }
        }

        public static void SwapIfSmallerThan<T>(ref this T a, ref T b) where T : struct, IComparable<T>
        {
            if (a.CompareTo(b) < 0)
            {
                (a, b) = (b, a);
            }
        }

        public static void Sort<T>(this T[] array) where T : IComparable<T> => Array.Sort(array);
        public static void Sort<T>(this T[] array, Comparison<T> comparison) => Array.Sort(array, comparison);
    }

    public static class CollectionExtensions
    {
        private class ArrayWrapper<T>
        {
#pragma warning disable CS0649
            public T[] Array;
#pragma warning restore CS0649
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Span<T> AsSpan<T>(this List<T> list)
        {
            return Unsafe.As<ArrayWrapper<T>>(list).Array.AsSpan(0, list.Count);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Span<T> GetRowSpan<T>(this T[,] array, int i)
        {
            var width = array.GetLength(1);
            return MemoryMarshal.CreateSpan(ref array[i, 0], width);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Span<T> GetRowSpan<T>(this T[,,] array, int i, int j)
        {
            var width = array.GetLength(2);
            return MemoryMarshal.CreateSpan(ref array[i, j, 0], width);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Span<T> GetRowSpan<T>(this T[,,,] array, int i, int j, int k)
        {
            var width = array.GetLength(3);
            return MemoryMarshal.CreateSpan(ref array[i, j, k, 0], width);
        }

        public static void Fill<T>(this T[] array, T value) => array.AsSpan().Fill(value);
        public static void Fill<T>(this T[,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0], array.Length).Fill(value);
        public static void Fill<T>(this T[,,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0, 0], array.Length).Fill(value);
        public static void Fill<T>(this T[,,,] array, T value) => MemoryMarshal.CreateSpan(ref array[0, 0, 0, 0], array.Length).Fill(value);
    }

    public static class SearchExtensions
    {
        struct LowerBoundComparer<T> : IComparer<T> where T : IComparable<T>
        {
            public int Compare(T x, T y) => 0 <= x.CompareTo(y) ? 1 : -1;
        }

        struct UpperBoundComparer<T> : IComparer<T> where T : IComparable<T>
        {
            public int Compare(T x, T y) => 0 < x.CompareTo(y) ? 1 : -1;
        }

        // https://trsing.hatenablog.com/entry/2019/08/27/211038
        public static int GetGreaterEqualIndex<T>(this ReadOnlySpan<T> span, T inclusiveMin) where T : IComparable<T> => ~span.BinarySearch(inclusiveMin, new UpperBoundComparer<T>());
        public static int GetGreaterThanIndex<T>(this ReadOnlySpan<T> span, T exclusiveMin) where T : IComparable<T> => ~span.BinarySearch(exclusiveMin, new LowerBoundComparer<T>());
        public static int GetLessEqualIndex<T>(this ReadOnlySpan<T> span, T inclusiveMax) where T : IComparable<T> => ~span.BinarySearch(inclusiveMax, new LowerBoundComparer<T>()) - 1;
        public static int GetLessThanIndex<T>(this ReadOnlySpan<T> span, T exclusiveMax) where T : IComparable<T> => ~span.BinarySearch(exclusiveMax, new UpperBoundComparer<T>()) - 1;
        public static int GetGreaterEqualIndex<T>(this Span<T> span, T inclusiveMin) where T : IComparable<T> => ((ReadOnlySpan<T>)span).GetGreaterEqualIndex(inclusiveMin);
        public static int GetGreaterThanIndex<T>(this Span<T> span, T exclusiveMin) where T : IComparable<T> => ((ReadOnlySpan<T>)span).GetGreaterThanIndex(exclusiveMin);
        public static int GetLessEqualIndex<T>(this Span<T> span, T inclusiveMax) where T : IComparable<T> => ((ReadOnlySpan<T>)span).GetLessEqualIndex(inclusiveMax);
        public static int GetLessThanIndex<T>(this Span<T> span, T exclusiveMax) where T : IComparable<T> => ((ReadOnlySpan<T>)span).GetLessThanIndex(exclusiveMax);

        public static int BoundaryBinarySearch(Predicate<int> predicate, int ok, int ng)
        {
            while (Math.Abs(ok - ng) > 1)
            {
                var mid = (ok + ng) / 2;
                if (predicate(mid))
                {
                    ok = mid;
                }
                else
                {
                    ng = mid;
                }
            }
            return ok;
        }

        public static long BoundaryBinarySearch(Predicate<long> predicate, long ok, long ng)
        {
            while (Math.Abs(ok - ng) > 1)
            {
                var mid = (ok + ng) / 2;
                if (predicate(mid))
                {
                    ok = mid;
                }
                else
                {
                    ng = mid;
                }
            }
            return ok;
        }

        public static BigInteger BoundaryBinarySearch(Predicate<BigInteger> predicate, BigInteger ok, BigInteger ng)
        {
            while (BigInteger.Abs(ok - ng) > 1)
            {
                var mid = (ok + ng) / 2;
                if (predicate(mid))
                {
                    ok = mid;
                }
                else
                {
                    ng = mid;
                }
            }
            return ok;
        }

        public static double BoundaryBinarySearch(Predicate<double> predicate, double ok, double ng, double eps = 1e-9, int loopLimit = 1000)
        {
            var count = 0;

            while (Math.Abs(ok - ng) > eps && count++ < loopLimit)
            {
                var mid = (ok + ng) * 0.5;
                if (predicate(mid))
                {
                    ok = mid;
                }
                else
                {
                    ng = mid;
                }
            }

            return (ok + ng) * 0.5;
        }

        public static double Bisection(Func<double, double> f, double a, double b, double eps = 1e-9)
        {
            if (f(a) * f(b) >= 0)
            {
                throw new ArgumentException("f(a)とf(b)は異符号である必要があります。");
            }

            const int maxLoop = 100;
            double mid = (a + b) / 2;

            for (int i = 0; i < maxLoop; i++)
            {
                if (f(a) * f(mid) < 0)
                {
                    b = mid;
                }
                else
                {
                    a = mid;
                }
                mid = (a + b) / 2;
                if (Math.Abs(b - a) < eps)
                {
                    break;
                }
            }
            return mid;
        }
    }
}

#endregion
